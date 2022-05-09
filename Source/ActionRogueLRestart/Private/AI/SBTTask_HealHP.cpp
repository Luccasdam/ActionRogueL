// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTTask_HealHP.h"

#include "AIController.h"
#include "SAttributesComponent.h"
#include "GameFramework/Character.h"

EBTNodeResult::Type USBTTask_HealHP::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const AAIController* AIC = OwnerComp.GetAIOwner();

	ACharacter* AICharacter = Cast<ACharacter>(AIC->GetPawn());
	if (AICharacter == nullptr)		return EBTNodeResult::Failed;

	USAttributesComponent* AttributesComp = Cast<USAttributesComponent>(AICharacter->GetComponentByClass(USAttributesComponent::StaticClass()));
	if (AttributesComp != nullptr)	return AttributesComp->ApplyHealthChange(AICharacter, AttributesComp->GetMaxHealth()) ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;

	return EBTNodeResult::Failed;
}
