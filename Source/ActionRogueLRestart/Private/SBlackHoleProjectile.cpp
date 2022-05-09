// Fill out your copyright notice in the Description page of Project Settings.


#include "SBlackHoleProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"

ASBlackHoleProjectile::ASBlackHoleProjectile()
	:	RadialForceComp(CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComp")))
{	
	RadialForceComp->SetupAttachment(RootComponent);
	RadialForceComp->Radius = 2000.f;
	RadialForceComp->ForceStrength = -320000.f;

	SphereComp->SetCollisionProfileName("OverlapAllDynamic");

	ProjMovComp->InitialSpeed = 750.f;
}

void ASBlackHoleProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SetLifeSpan(5.f);

	//SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASBlackHoleProjectile::BlackHoleDestroy);
}

/*
void ASBlackHoleProjectile::BlackHoleDestroy(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherComp->IsSimulatingPhysics())    OtherActor->Destroy();
}*/

void ASBlackHoleProjectile::OnActorBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherComp->IsSimulatingPhysics())    OtherActor->Destroy();
}