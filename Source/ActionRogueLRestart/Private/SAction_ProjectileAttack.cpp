// Fill out your copyright notice in the Description page of Project Settings.


#include "SAction_ProjectileAttack.h"
#include "SProjectileBase.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"


USAction_ProjectileAttack::USAction_ProjectileAttack()
	:	HandSocketName(TEXT("Muzzle_01"))
	,	AttackAnimDelay(0.169f)
{
}

void USAction_ProjectileAttack::StartAction_Implementation(AActor* InstigatorActor)
{
	Super::StartAction_Implementation(InstigatorActor);

	ACharacter* InstigatorCharacter = Cast<ACharacter>(InstigatorActor);
	if (InstigatorCharacter != nullptr)
	{
		InstigatorCharacter->PlayAnimMontage(AttackAnimMontage);

		UGameplayStatics::SpawnEmitterAttached(CastingEffect, InstigatorCharacter->GetMesh(), HandSocketName, FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget);

		FTimerHandle TimerHandle_AttackDelay;

		FTimerDelegate TimerDelegate_AttackDelay;
		TimerDelegate_AttackDelay.BindUFunction(this, "AttackDelay_TimeElapsed", InstigatorCharacter);
		
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_AttackDelay, TimerDelegate_AttackDelay, AttackAnimDelay, false);
	}
}

void USAction_ProjectileAttack::AttackDelay_TimeElapsed(ACharacter* InstigatorCharacter)
{
	if (ensureAlways(ProjectileClass))
	{
		const FVector HandLocation = InstigatorCharacter->GetMesh()->GetSocketLocation(HandSocketName);
	
		FHitResult Hit;
		FVector StartLocation = InstigatorCharacter->GetPawnViewLocation();
		FVector EndLocation =  StartLocation + InstigatorCharacter->GetControlRotation().Vector() * 5000.f;
	
		FCollisionQueryParams CollisionQueryParams;
		CollisionQueryParams.AddIgnoredActor(InstigatorCharacter);
	
		if (GetWorld()->LineTraceSingleByChannel(Hit, StartLocation, EndLocation, ECC_Visibility, CollisionQueryParams))
		{
			EndLocation = Hit.ImpactPoint;
		}
		
		FRotator SpawnRotation = (EndLocation - HandLocation).Rotation();

		
		FActorSpawnParameters SpawnParams;
		SpawnParams.Instigator = InstigatorCharacter;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
		const FTransform SpawnTM = FTransform(SpawnRotation, HandLocation);
	
		GetWorld()->SpawnActor<ASProjectileBase>(ProjectileClass, SpawnTM, SpawnParams);
	}

	StopAction(InstigatorCharacter);
}
