// Fill out your copyright notice in the Description page of Project Settings.


#include "SPickUpItem.h"
#include "Components/SphereComponent.h"


ASPickUpItem::ASPickUpItem()
	:	SphereComp(CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp")))
	,	ItemMesh(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh")))
	,	AwakeTime(10.f)
{
	SetRootComponent(SphereComp);
	ItemMesh->SetupAttachment(SphereComp);
}


void ASPickUpItem::BeginPlay()
{
	Super::BeginPlay();
	
	SetItemOnCooldown();
}

void ASPickUpItem::Interact_Implementation(APawn* InstigatorPawn)
{
	ISGameplayInterface::Interact_Implementation(InstigatorPawn);
}


void ASPickUpItem::SetItemOnCooldown()
{
	ToggleItemState();

	FTimerHandle TimerHandle_ItemCooldown;
	GetWorldTimerManager().SetTimer(TimerHandle_ItemCooldown, this, &ASPickUpItem::ToggleItemState, AwakeTime);
}

void ASPickUpItem::ToggleItemState()
{
	ItemMesh->SetVisibility(!ItemMesh->IsVisible());
	SetActorEnableCollision(ItemMesh->IsVisible());
}
