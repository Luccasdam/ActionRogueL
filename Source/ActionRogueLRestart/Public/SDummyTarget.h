// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SAttributesComponent.h"
#include "GameFramework/Actor.h"
#include "SDummyTarget.generated.h"

class USAttributesComponent;

UCLASS()
class ACTIONROGUELRESTART_API ASDummyTarget : public AActor
{
	GENERATED_BODY()
	
public:	
	ASDummyTarget();

	virtual void PostInitializeComponents() override;

protected:

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, USAttributesComponent* OwningComp, float NewHealth, float Delta);
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* BaseMesh;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USAttributesComponent* AttributesComp;
	
};
