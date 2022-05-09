// Fill out your copyright notice in the Description page of Project Settings.


#include "SItemChest.h"

#include "Particles/ParticleSystemComponent.h"

// Sets default values
ASItemChest::ASItemChest()
	:	BaseMesh(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh")))
	,	LidMesh(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LidMesh")))
	,	GoldMesh(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GoldMesh")))
	,	GoldBurstEffect(CreateDefaultSubobject<UParticleSystemComponent>(TEXT("GoldBurstEffect")))
	,	TargetPitch(130.f)
{
	RootComponent = BaseMesh;
	LidMesh->SetupAttachment(BaseMesh);
	GoldMesh->SetupAttachment(BaseMesh);
	GoldBurstEffect->SetupAttachment(GoldMesh);
	GoldBurstEffect->bAutoActivate = false;
}

void ASItemChest::Interact_Implementation(APawn* InstigatorPawn)
{
	LidMesh->SetRelativeRotation(FRotator(TargetPitch, 0.f, 0.f));
}