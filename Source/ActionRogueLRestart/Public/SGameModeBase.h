// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "GameFramework/GameModeBase.h"
#include "SGameModeBase.generated.h"

class UEnvQuery;
class UEnvQueryInstanceBlueprintWrapper;



/**
 * 
 */
UCLASS()
class ACTIONROGUELRESTART_API ASGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASGameModeBase();
	
	virtual void StartPlay() override;

	virtual void OnActorKilled(AActor* VictimActor, AActor* KillerActor);

protected:

	UFUNCTION()
	void RespawnPlayer_TimeElapsed(APlayerController* PC);

	void SpawnBots_TimeElapsed();

	UFUNCTION()
	void SpawnBots_QueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);

	FTimerHandle TimerHandle_SpawnBots;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	float BotSpawnInterval;

	UPROPERTY(EditAnywhere, Category = "AI")
	UCurveFloat* MaxBotsCurve;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UEnvQuery* EQ_FindBotSpawnLocations;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TSubclassOf<AActor> MinionClass;
	
public:
	UFUNCTION(Exec)
	void KillBots();
	

	
};
