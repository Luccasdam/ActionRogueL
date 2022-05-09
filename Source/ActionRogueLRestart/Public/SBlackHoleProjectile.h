// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SProjectileBase.h"
#include "SBlackHoleProjectile.generated.h"

class URadialForceComponent;

/**
 * 
 */
UCLASS(Abstract)
class ACTIONROGUELRESTART_API ASBlackHoleProjectile : public ASProjectileBase
{
	GENERATED_BODY()

public:
	ASBlackHoleProjectile();

	virtual void PostInitializeComponents() override;

protected:
	
	virtual void OnActorBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	
	UPROPERTY(VisibleAnywhere)
	URadialForceComponent* RadialForceComp;
	
};
