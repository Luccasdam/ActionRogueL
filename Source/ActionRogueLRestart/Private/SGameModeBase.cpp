// Fill out your copyright notice in the Description page of Project Settings.


#include "SGameModeBase.h"
#include "EngineUtils.h"
#include "SAttributesComponent.h"
#include "SCharacter.h"
#include "AI/SAICharacter.h"
#include "EnvironmentQuery/EnvQueryManager.h"


static TAutoConsoleVariable<bool> CVarSpawnBots(TEXT("su.SpawnBots"), true, TEXT("Enable Spawning Bots via Timer"), ECVF_Cheat);


ASGameModeBase::ASGameModeBase()
	:	BotSpawnInterval(2.0f)
{
}

void ASGameModeBase::StartPlay()
{
	Super::StartPlay();

	UE_LOG(LogTemp, Warning, TEXT("GameMode Start Play"))
	GetWorldTimerManager().SetTimer(TimerHandle_SpawnBots, this, &ASGameModeBase::SpawnBots_TimeElapsed, BotSpawnInterval);
}

void ASGameModeBase::SpawnBots_TimeElapsed()
{
	if (CVarSpawnBots.GetValueOnGameThread() == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("Bot spawning disabled via CVar 'CVarSpawnBots'."))
	}
	
	GetWorldTimerManager().SetTimer(TimerHandle_SpawnBots, this, &ASGameModeBase::SpawnBots_TimeElapsed, BotSpawnInterval);
	
	int32 NumberOfBots = 0;
	for (TActorIterator<ASAICharacter> Bot(GetWorld()); Bot; ++Bot)
	{
		const USAttributesComponent* BotAttributes = USAttributesComponent::GetAttributes(*Bot);
		if (BotAttributes && BotAttributes->IsAlive())	++NumberOfBots;
	}
	
	int32 MaxBots = MaxBotsCurve ? MaxBotsCurve->GetFloatValue(GetWorld()->TimeSeconds) : 10;
	UE_LOG(LogTemp, Warning, TEXT("Max bots = %i"), MaxBots)
	UE_LOG(LogTemp, Warning, TEXT("Alive bots = %i"), NumberOfBots)
	if (NumberOfBots >= MaxBots)	return;
	
	UEnvQueryInstanceBlueprintWrapper* QueryInst = UEnvQueryManager::RunEQSQuery(this, EQ_FindBotSpawnLocations, this, EEnvQueryRunMode::RandomBest5Pct, nullptr);

	if (ensure(QueryInst))
	{
		UE_LOG(LogTemp, Warning, TEXT("GameMode Run Query"))
		QueryInst->GetOnQueryFinishedEvent().AddDynamic(this, &ASGameModeBase::SpawnBots_QueryCompleted);
	}
}

void ASGameModeBase::SpawnBots_QueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus)
{
	if (QueryStatus != EEnvQueryStatus::Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("SpawnBots EQS Failed!"))
		return;
	}	
	
	TArray<FVector> SpawnLocations = QueryInstance->GetResultsAsLocations();

	if (SpawnLocations.IsValidIndex(0))
	{		
		AActor* SpawnedBot = GetWorld()->SpawnActor<AActor>(MinionClass, SpawnLocations[0], FRotator::ZeroRotator);
		FString SpawnedBotString = SpawnedBot ? "Bot is Spawned with Success" : "Bot failed to Spawn";

		UE_LOG(LogTemp, Warning, TEXT("%s"), *SpawnedBotString)		
	}
}

void ASGameModeBase::KillBots()
{
	for (TActorIterator<ASAICharacter> Bot(GetWorld()); Bot; ++Bot)
	{
		USAttributesComponent* BotAttributes = USAttributesComponent::GetAttributes(*Bot);
		if (BotAttributes && BotAttributes->IsAlive())	BotAttributes->ApplyHealthChange(this, -BotAttributes->GetMaxHealth());
	}
}

void ASGameModeBase::OnActorKilled(AActor* VictimActor, AActor* KillerActor)
{
	ASCharacter* Player = Cast<ASCharacter>(VictimActor);
	if (Player != nullptr)
	{
		FTimerHandle TimerHandle_RespawnPlayer;

		FTimerDelegate TimerDelegate_RespawnPlayer;
		TimerDelegate_RespawnPlayer.BindUFunction(this, "RespawnPlayer_TimeElapsed", Player->GetController());

		float RespawnDelay = 2.0f;
		GetWorldTimerManager().SetTimer(TimerHandle_SpawnBots, TimerDelegate_RespawnPlayer, RespawnDelay, false);
	}

	UE_LOG(LogTemp, Log, TEXT("OnActorKilled: Victim: %s, Killer: %s"), *GetNameSafe(VictimActor), *GetNameSafe(KillerActor))
}

void ASGameModeBase::RespawnPlayer_TimeElapsed(APlayerController* PC)
{
	if (ensure(PC))
	{
		PC->UnPossess();
		RestartPlayer(PC);
	}
}
