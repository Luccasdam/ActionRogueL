// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SAttributesComponent.h"
#include "GameFramework/Character.h"
#include "SAICharacter.generated.h"

class UPawnSensingComponent;
class USAttributesComponent;
class USWorldWidget;

UCLASS()
class ACTIONROGUELRESTART_API ASAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASAICharacter();

	virtual void PostInitializeComponents() override;

protected:

	UFUNCTION()
	void OnPawnSeen(APawn* Pawn);

	UFUNCTION()
	void OnApplyHealthChange(AActor* InstigatorActor, USAttributesComponent* OwningComp, float NewHealth, float Delta);

	UFUNCTION()
	void OnDeath(AActor* InstigatorActor);

	void SetTargetActor(AActor* NewTarget);
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPawnSensingComponent* PawnSensingComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USAttributesComponent* AttributesComp;

	UPROPERTY(VisibleAnywhere, Category = "Effects")
	FName HitFlash_TimeParamName;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<USWorldWidget> HealthBarWidgetClass;

	UPROPERTY(VisibleAnywhere, Category = "UI")
	USWorldWidget* HealthBarWidget;
};
