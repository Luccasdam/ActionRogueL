// Fill out your copyright notice in the Description page of Project Settings.


#include "SDummyTarget.h"
#include "SAttributesComponent.h"


ASDummyTarget::ASDummyTarget()
	:	BaseMesh(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh")))
	,	AttributesComp(CreateDefaultSubobject<USAttributesComponent>(TEXT("AttributesComponent")))
{
}

void ASDummyTarget::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AttributesComp->OnApplyHealthChange.AddDynamic(this, &ASDummyTarget::OnHealthChanged);
}

void ASDummyTarget::OnHealthChanged(AActor* InstigatorActor, USAttributesComponent* OwningComp, float NewHealth, float Delta)
{
	if (Delta < 0.f)    BaseMesh->SetScalarParameterValueOnMaterials(TEXT("HitFlash_Time"), GetWorld()->TimeSeconds);
	
	if (NewHealth <= 0.0f)
	{
		BaseMesh->SetScalarParameterValueOnMaterials(TEXT("Dissolve_Time"), GetWorld()->TimeSeconds);
		SetActorEnableCollision(false);
		SetLifeSpan(2.f);
	}
}
