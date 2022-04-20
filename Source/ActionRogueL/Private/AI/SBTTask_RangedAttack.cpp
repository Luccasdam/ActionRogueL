// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTTask_RangedAttack.h"

#include "AIController.h"
#include "SProjectileBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"

EBTNodeResult::Type USBTTask_RangedAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	const AAIController* AIC = OwnerComp.GetAIOwner();
	if (ensure((AIC)))
	{
		const ACharacter* AICharacter = Cast<ACharacter>(AIC->GetPawn());
		if (AICharacter == nullptr)	return EBTNodeResult::Failed;

		const APawn* TargetPawn = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetPawn"));
		if (TargetPawn == nullptr)	return EBTNodeResult::Failed;

		if (ProjectileClass == nullptr)    return EBTNodeResult::Failed;
		

		const FVector MuzzleLocation = AICharacter->GetMesh()->GetSocketLocation("Muzzle_front");
		const FRotator AimRotation = (TargetPawn->GetActorLocation() - MuzzleLocation).Rotation();
		
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		SpawnParams.Instigator = AIC->GetPawn();
		
		const ASProjectileBase* SpawnedProjectile = GetWorld()->SpawnActor<ASProjectileBase>(ProjectileClass, MuzzleLocation, AimRotation, SpawnParams);
		return SpawnedProjectile ? EBTNodeResult::Succeeded : EBTNodeResult::Failed; 
	}
	
	return EBTNodeResult::Failed;	
}
