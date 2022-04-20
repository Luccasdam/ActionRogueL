// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTService_CheckLowHealth.h"
#include "AIController.h"
#include "SAttributeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

void USBTService_CheckLowHealth::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	const USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(OwnerComp.GetAIOwner()->GetPawn()->GetComponentByClass(USAttributeComponent::StaticClass()));
	if (AttributeComp == nullptr)	return;
	
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(LowHealthKey.SelectedKeyName, AttributeComp->GetHealth() < 40.0f);
}
