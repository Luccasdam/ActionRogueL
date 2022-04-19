// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTService_CheckAttackRange.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void USBTService_CheckAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();
	if (ensure(BBComp))
	{
		const APawn* TargetPawn = Cast<APawn>(BBComp->GetValueAsObject("TargetPawn"));
		if (TargetPawn)
		{
			const AAIController* AIC = OwnerComp.GetAIOwner();
			if (ensure(AIC))
			{
				const APawn* AIPawn = AIC->GetPawn();
				if (ensure(AIPawn))
				{
					const float TargetDistance = FVector::Distance(TargetPawn->GetActorLocation(), AIPawn->GetActorLocation());

					const bool bHasLOS = AIC->LineOfSightTo(TargetPawn);

					const bool bWithinRange = TargetDistance < 2000.f;

					BBComp->SetValueAsBool(AttackRangeKey.SelectedKeyName, bWithinRange && bHasLOS);
				}
			}
		}
	}
}
