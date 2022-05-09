// Fill out your copyright notice in the Description page of Project Settings.


#include "SDashProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

ASDashProjectile::ASDashProjectile()
	:	TimeToDetonate(0.2f)
	,	TimeToTeleport(0.2f)
{
	ProjMovComp->InitialSpeed = 7500.f;
}

void ASDashProjectile::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(TimerHandle_Detonate, this, &ASDashProjectile::Explode, TimeToDetonate);
}

void ASDashProjectile::Explode_Implementation()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_Detonate);

	SphereComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ParticleComp->DeactivateSystem();
	ProjMovComp->StopMovementImmediately();

	UGameplayStatics::SpawnEmitterAtLocation(this, HitVFX, GetActorLocation(), GetActorRotation());

	FTimerHandle TimerHandle_Teleport;
	GetWorldTimerManager().SetTimer(TimerHandle_Teleport, this, &ASDashProjectile::Teleport_TimeElapsed, TimeToTeleport);
}


void ASDashProjectile::Teleport_TimeElapsed()
{
	if (ensure(GetInstigator() != nullptr))    GetInstigator()->TeleportTo(GetActorLocation(), GetInstigator()->GetActorRotation());
}
