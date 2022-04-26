// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SAttributeComponent.generated.h"

class USAttributeComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChanged, AActor*, InstigatorActor, USAttributeComponent*, OwningComp, float, NewHealth, float, Delta);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONROGUEL_API USAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USAttributeComponent();

	UFUNCTION(BlueprintCallable, Category = Attributes)
	static USAttributeComponent* GetAttributes(AActor* FromActor);

	UFUNCTION(BlueprintCallable, Category = Attributes)
	static bool IsActorAlive(APawn* FromPawn);

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	float MaxHealth;

private:

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", meta = (AllowPrivateAccess))
	float Health;

public:

	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool ApplyHealthChange(AActor* InstigatorActor, float DeltaHealth);

	UFUNCTION(BlueprintCallable)
	bool IsAlive() const;

	UFUNCTION(BlueprintCallable)
	float GetHealth() const;

	UFUNCTION(BlueprintCallable)
	void SetHealthToFull();

	UFUNCTION(BlueprintCallable)
	bool IsFullHealth() const;
};

inline float USAttributeComponent::GetHealth() const	{ return Health; }

inline void USAttributeComponent::SetHealthToFull()	{ Health = MaxHealth; }

inline bool USAttributeComponent::IsFullHealth() const	{ return Health == MaxHealth; }

inline bool USAttributeComponent::IsAlive() const	{ return Health > 0.0f; }

