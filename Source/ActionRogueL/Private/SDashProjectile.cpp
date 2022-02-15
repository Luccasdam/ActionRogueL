// Fill out your copyright notice in the Description page of Project Settings.


#include "SDashProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

void ASDashProjectile::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(TimerHandle_Dash, this, &ASDashProjectile::Dash_TimeElapsed, .2f);
}

void ASDashProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SphereComp->OnComponentHit.AddDynamic(this, &ASDashProjectile::OnDashHit);
}

void ASDashProjectile::Dash_TimeElapsed()
{
	ProjMovComp->StopMovementImmediately();

	SphereComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	EffectComp->SetVisibility(false);
	
	UGameplayStatics::SpawnEmitterAtLocation(this, ExplosionParticle, GetActorLocation(), GetActorRotation());

	GetWorldTimerManager().SetTimer(TimerHandle_Teleport, this, &ASDashProjectile::Teleport_TimeElapsed, .2f);

}

void ASDashProjectile::Teleport_TimeElapsed()
{
	AActor* InstigatorActor = GetInstigator();
	InstigatorActor->TeleportTo(GetActorLocation(), InstigatorActor->GetActorRotation());

	Destroy();
}

void ASDashProjectile::OnDashHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	GetWorldTimerManager().ClearTimer(TimerHandle_Dash);

	Dash_TimeElapsed();
}
