// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTService_WithinRange.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void USBTService_WithinRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();
	if (!ensure(BBComp != nullptr))    return;

	const AAIController* AIC = OwnerComp.GetAIOwner();
	
	const APawn* AIPawn = AIC->GetPawn();
	if (ensure(AIPawn))
	{
		const AActor* TargetActor = Cast<AActor>(BBComp->GetValueAsObject("TargetActor"));
		if (TargetActor == nullptr)    return;

		const float TargetDistance = FVector::Distance(TargetActor->GetActorLocation(), AIPawn->GetActorLocation());

		const bool bWithinRange = TargetDistance < 2000.f;

		const bool bHasLOS = bWithinRange ? AIC->LineOfSightTo(TargetActor) : false;

		BBComp->SetValueAsBool(WithinRangeKey.SelectedKeyName, bHasLOS);
	}

	
	
}
