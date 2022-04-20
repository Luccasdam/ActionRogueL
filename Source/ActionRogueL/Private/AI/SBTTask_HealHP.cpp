// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTTask_HealHP.h"

#include "AIController.h"
#include "SAttributeComponent.h"

EBTNodeResult::Type USBTTask_HealHP::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(OwnerComp.GetAIOwner()->GetPawn()->GetComponentByClass(USAttributeComponent::StaticClass()));
	if (AttributeComp == nullptr)	return EBTNodeResult::Failed;

	AttributeComp->SetHealthToFull();
	return EBTNodeResult::Succeeded;
}
