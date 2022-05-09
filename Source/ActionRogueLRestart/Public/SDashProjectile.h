// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SProjectileBase.h"
#include "SDashProjectile.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class ACTIONROGUELRESTART_API ASDashProjectile : public ASProjectileBase
{
	GENERATED_BODY()

public:
	ASDashProjectile();

protected:
	virtual void BeginPlay() override;
	
	virtual void Explode_Implementation() override;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	float TimeToDetonate;

	FTimerHandle TimerHandle_Detonate;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	float TimeToTeleport;
	
	void Teleport_TimeElapsed();
};
