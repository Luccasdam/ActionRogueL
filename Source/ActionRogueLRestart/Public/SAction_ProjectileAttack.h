// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SAction.h"
#include "SAction_ProjectileAttack.generated.h"

class ASProjectileBase;

/**
 * 
 */
UCLASS(Abstract)
class ACTIONROGUELRESTART_API USAction_ProjectileAttack : public USAction
{
	GENERATED_BODY()

public:
	USAction_ProjectileAttack();
	
	virtual void StartAction_Implementation(AActor* InstigatorActor) override;

protected:

	UFUNCTION()
	void AttackDelay_TimeElapsed(ACharacter* InstigatorCharacter);

	UPROPERTY(VisibleAnywhere, Category = "Effects")
	FName HandSocketName;

	UPROPERTY(EditAnywhere, CAtegory = "Attack")
	TSubclassOf<ASProjectileBase> ProjectileClass;	

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	float AttackAnimDelay;

	UPROPERTY(EditAnywhere, Category = "Attack")
	UAnimMontage* AttackAnimMontage;

	/* Partciels System played during attack animation */
	UPROPERTY(EditAnywhere, Category = "Attack")
	UParticleSystem* CastingEffect;




};
