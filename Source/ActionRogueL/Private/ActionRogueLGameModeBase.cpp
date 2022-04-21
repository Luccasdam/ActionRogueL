// Copyright Epic Games, Inc. All Rights Reserved.


#include "ActionRogueLGameModeBase.h"

#include "EngineUtils.h"
#include "SAttributeComponent.h"
#include "AI/SAICharacter.h"
#include "EnvironmentQuery/EnvQueryManager.h"

AActionRogueLGameModeBase::AActionRogueLGameModeBase()
	:	SpawnBotsTimerInterval(2.0f)
{
}

void AActionRogueLGameModeBase::StartPlay()
{
	Super::StartPlay();

	GetWorldTimerManager().SetTimer(TimerHandle_SpawnBots, this, &AActionRogueLGameModeBase::SpawnBots_TimeElapsed, SpawnBotsTimerInterval, true);
}

void AActionRogueLGameModeBase::SpawnBots_TimeElapsed()
{
	UEnvQueryInstanceBlueprintWrapper* QueryInstance = UEnvQueryManager::RunEQSQuery(this, SpawnBotsQuery, this, EEnvQueryRunMode::RandomBest5Pct, nullptr);

	if (ensure(QueryInstance))	QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this, &AActionRogueLGameModeBase::OnQueryCompleted);
}

void AActionRogueLGameModeBase::OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus)
{
	if (QueryStatus != EEnvQueryStatus::Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("EQS Spawn Bots Query Failed!"))
		return;
	}

	int32 NumberOfAliveBots = 0;
	for (TActorIterator<ASAICharacter> Bot(GetWorld()); Bot; ++Bot)
	{
		const USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(Bot->GetComponentByClass(USAttributeComponent::StaticClass()));
		if (AttributeComp && AttributeComp->IsAlive())	++NumberOfAliveBots;		
	}
	
	const float MaxBotsCounter = DifficultyCurve ? DifficultyCurve->GetFloatValue(GetWorld()->TimeSeconds) : 10.0f;
	if (NumberOfAliveBots >= MaxBotsCounter)	return;


	
	TArray<FVector> Locations = QueryInstance->GetResultsAsLocations();
	if (Locations.IsValidIndex(0))
	{
		GetWorld()->SpawnActor<ASAICharacter>(MinionClass, Locations[0], FRotator::ZeroRotator);
	}
}
