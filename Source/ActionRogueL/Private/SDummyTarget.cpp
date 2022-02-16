// Fill out your copyright notice in the Description page of Project Settings.


#include "SDummyTarget.h"

#include "SAttributeComponent.h"
#include "Blueprint/UserWidget.h"

// Sets default values
ASDummyTarget::ASDummyTarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	SetRootComponent(BaseMesh);

	AttributeComp = CreateDefaultSubobject<USAttributeComponent>(TEXT("AttributeComp"));

}

// Called when the game starts or when spawned
void ASDummyTarget::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASDummyTarget::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AttributeComp->OnHealthChanged.AddDynamic(this, &ASDummyTarget::OnHealthChanged);
}

// Called every frame
void ASDummyTarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASDummyTarget::OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	BaseMesh->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->TimeSeconds);
}