// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "SBTService_LowHealth.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELRESTART_API USBTService_LowHealth : public UBTService
{
	GENERATED_BODY()

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector HasLowHealthKey;

	UPROPERTY(EditAnywhere, Category = "AI")
	float LowHealthThreshold;
	
};
