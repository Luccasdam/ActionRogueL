// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGameplayInterface.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "SPickUpItem.generated.h"

UCLASS()
class ACTIONROGUEL_API ASPickUpItem : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASPickUpItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	bool ItemEffect(APawn* InstigatorPawn);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* ItemMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults")
	float ItemCooldown = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults")
	bool bStartInactive = true;
	
	UFUNCTION(BlueprintCallable)
	void SetupCooldown(float inDelay);

	UFUNCTION(BlueprintCallable)
	void ActivateItem();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
