// Fill out your copyright notice in the Description page of Project Settings.


#include "SPickUpItem.h"

// Sets default values
ASPickUpItem::ASPickUpItem()
	:	ItemMesh(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh")))
	,	ItemCooldown(10)
{
	SetRootComponent(ItemMesh);
	ItemMesh->SetCollisionProfileName("OverlapAllDynamic");
}

// Called when the game starts or when spawned
void ASPickUpItem::BeginPlay()
{
	Super::BeginPlay();
	
	if (bStartInactive)    SetupCooldown(ItemCooldown);	
}

void ASPickUpItem::Interact_Implementation(APawn* InstigatorPawn)
{
	ISGameplayInterface::Interact_Implementation(InstigatorPawn);

	if (ItemEffect(InstigatorPawn))    SetupCooldown(ItemCooldown);
}

void ASPickUpItem::SetupCooldown(float inDelay)
{
	ItemMesh->SetVisibility(false);
	SetActorEnableCollision(false);
	
	FTimerHandle TimerHandle_Cooldown;
	GetWorldTimerManager().SetTimer(TimerHandle_Cooldown, this, &ASPickUpItem::ActivateItem, inDelay);
}

void ASPickUpItem::ActivateItem()
{
	ItemMesh->SetVisibility(true);
	SetActorEnableCollision(true);
}
