// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "SPickUpItem.generated.h"

class USphereComponent;

UCLASS(Abstract)
class ACTIONROGUELRESTART_API ASPickUpItem : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()
	
public:	
	ASPickUpItem();

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

protected:
	virtual void BeginPlay() override;

	void SetItemOnCooldown();

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* ItemMesh;
	
	UPROPERTY(EditDefaultsOnly)
	float AwakeTime;

private:
	
	void ToggleItemState();
};
