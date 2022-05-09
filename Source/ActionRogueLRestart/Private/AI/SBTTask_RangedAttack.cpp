// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTTask_RangedAttack.h"

#include "AIController.h"
#include "SAttributesComponent.h"
#include "SProjectileBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"

USBTTask_RangedAttack::USBTTask_RangedAttack()
	:	MaxBulletSpread(5.f)
{
}

EBTNodeResult::Type USBTTask_RangedAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const AAIController* AIC = OwnerComp.GetAIOwner();

	const ACharacter* AICharacter = Cast<ACharacter>(AIC->GetPawn());
	if (AICharacter == nullptr)    return EBTNodeResult::Failed;

	AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TargetKey.SelectedKeyName));
	if (TargetActor == nullptr)    return EBTNodeResult::Failed;

	if (!USAttributesComponent::IsActorAlive(TargetActor))	return EBTNodeResult::Failed;
	

	const FVector MuzzleLocation = AICharacter->GetMesh()->GetSocketLocation("Muzzle_01");
	FRotator AttackRotation = (TargetActor->GetActorLocation() - MuzzleLocation).Rotation();

	AttackRotation.Pitch += FMath::RandRange(-MaxBulletSpread/4, MaxBulletSpread/2);
	AttackRotation.Yaw += FMath::RandRange(-MaxBulletSpread, MaxBulletSpread);

	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = AIC->GetPawn();
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	const AActor* SpawnedProjectile = GetWorld()->SpawnActor<ASProjectileBase>(ProjectileClass, MuzzleLocation, AttackRotation, SpawnParams);

	return SpawnedProjectile ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
}
