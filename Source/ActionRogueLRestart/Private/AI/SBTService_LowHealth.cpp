// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTService_LowHealth.h"
#include "AIController.h"
#include "SAttributesComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"

void USBTService_LowHealth::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* AIC = OwnerComp.GetAIOwner();
	
	const ACharacter* AICharacter = Cast<ACharacter>(AIC->GetPawn());
	if (AICharacter == nullptr)		return;

	const USAttributesComponent* AttributesComp = Cast<USAttributesComponent>(AICharacter->GetComponentByClass(USAttributesComponent::StaticClass()));
	if (AttributesComp != nullptr)
	{
		const float HealthPercent = AttributesComp->GetHealth() / AttributesComp->GetMaxHealth();

		OwnerComp.GetBlackboardComponent()->SetValueAsBool(HasLowHealthKey.SelectedKeyName, HealthPercent < LowHealthThreshold);
	}
}
