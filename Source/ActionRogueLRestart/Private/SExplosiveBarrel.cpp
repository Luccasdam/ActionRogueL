// Fill out your copyright notice in the Description page of Project Settings.


#include "SExplosiveBarrel.h"

#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
ASExplosiveBarrel::ASExplosiveBarrel()
	:	BarrelMesh(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BarrelMesh")))
	,	RadialForceComp(CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComponent")))
{
	RootComponent = BarrelMesh;
	BarrelMesh->SetCollisionProfileName(TEXT("PhysicsActor"));
	BarrelMesh->SetSimulatePhysics(true);
	
	RadialForceComp->SetupAttachment(BarrelMesh);
	RadialForceComp->Radius = 700.f;
	RadialForceComp->ImpulseStrength = 2000.f;
	RadialForceComp->bImpulseVelChange = true;
	RadialForceComp->bAutoActivate = false;
}


void ASExplosiveBarrel::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	BarrelMesh->OnComponentHit.AddDynamic(this, &ASExplosiveBarrel::Explode);
}


void ASExplosiveBarrel::Explode(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	RadialForceComp->FireImpulse();
}

