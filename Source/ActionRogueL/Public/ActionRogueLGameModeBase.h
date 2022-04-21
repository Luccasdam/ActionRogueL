// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ActionRogueLGameModeBase.generated.h"

class UEnvQuery;
class UEnvQueryInstanceBlueprintWrapper;
class ASAICharacter;

/**
 * 
 */
UCLASS()
class ACTIONROGUEL_API AActionRogueLGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AActionRogueLGameModeBase();
	
	virtual void StartPlay() override;

protected:

	UPROPERTY(EditDefaultsOnly, Category = AI)
	TSubclassOf<ASAICharacter> MinionClass;

	UPROPERTY(EditDefaultsOnly, Category = AI)
	UEnvQuery* SpawnBotsQuery;
	
	FTimerHandle TimerHandle_SpawnBots;

	UPROPERTY(EditDefaultsOnly, Category = AI)
	float SpawnBotsTimerInterval;

	UPROPERTY(EditDefaultsOnly, Category = AI)
	UCurveFloat* DifficultyCurve;

	UFUNCTION()
	void SpawnBots_TimeElapsed();

	UFUNCTION()
	void OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);
	
};
