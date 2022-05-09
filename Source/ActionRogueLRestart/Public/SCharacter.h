// Fill out your copyright notice in the Description page of Project Settings.


#pragma once
#include "CoreMinimal.h"
#include "SAttributesComponent.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"


class USpringArmComponent;
class UCameraComponent;
class USInteractionComponent;
class ASProjectileBase;
class USAttributesComponent;
class USActionComponent;

UCLASS()
class ACTIONROGUELRESTART_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASCharacter();

	virtual void PostInitializeComponents() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual FVector GetPawnViewLocation() const override;

protected:

	void MoveForward(float Value);

	void MoveRight(float Value);

	void SprintStart();

	void SprintStop();

	void PrimaryAttack();

	void SecondaryAttack();

	void UltimateAttack();
	
	void Interact();

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, USAttributesComponent* OwningComp, float NewHealth, float Delta);

	UFUNCTION()
	void OnDeath(AActor* InstigatorActor);
	

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USInteractionComponent* InteractionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USAttributesComponent* AttributesComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USActionComponent* ActionComp;

	
public:
	UFUNCTION(Exec)
	void HealSelf(float Amount = 100)	{ AttributesComp->ApplyHealthChange(this, Amount); }

};