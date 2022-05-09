// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SPickUpItem.h"
#include "SHealthPotion.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELRESTART_API ASHealthPotion : public ASPickUpItem
{
	GENERATED_BODY()

public:
	ASHealthPotion();
	
	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

protected:
	UPROPERTY(EditDefaultsOnly)
	int32 Cost;
	
	UPROPERTY(EditDefaultsOnly)
	float HealAmount;
	
};
