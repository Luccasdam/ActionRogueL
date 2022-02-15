// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SProjectileBase.h"
#include "SDashProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUEL_API ASDashProjectile : public ASProjectileBase
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly)
	UParticleSystem* ExplosionParticle;

protected:
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	FTimerHandle TimerHandle_Dash;

	FTimerHandle TimerHandle_Teleport;

	UFUNCTION()
	void Dash_TimeElapsed();

	UFUNCTION()
	void Teleport_TimeElapsed();

	UFUNCTION()
	void OnDashHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit );
	
};
