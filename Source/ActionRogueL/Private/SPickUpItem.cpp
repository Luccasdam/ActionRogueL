// Fill out your copyright notice in the Description page of Project Settings.


#include "SPickUpItem.h"

// Sets default values
ASPickUpItem::ASPickUpItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
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

// bool ASPickUpItem::ItemEffect_Implementation(APawn* InstigatorPawn)
// {
// 	UE_LOG(LogTemp, Log, TEXT("Make your Item Implementation Logic"))
// 	return false;
// }

// Called every frame
void ASPickUpItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
