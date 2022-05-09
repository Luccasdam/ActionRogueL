// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SPickUpItem.h"
#include "SCoinItem.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELRESTART_API ASCoinItem : public ASPickUpItem
{
	GENERATED_BODY()

public:
	ASCoinItem();

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;
	
protected:
	UPROPERTY(EditDefaultsOnly)
	int32 CreditAmount;
	
};
