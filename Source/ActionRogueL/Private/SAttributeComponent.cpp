// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"

// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
{
}

bool USAttributeComponent::ApplyHealthChange(float DeltaHealth)
{
	const float LastHealth = Health;
	
	Health += DeltaHealth;
	const float NewHealth = FMath::Clamp(Health, 0.f, MaxHealth);
	Health = NewHealth;
	
	if (Health != LastHealth)
	{
		OnHealthChanged.Broadcast(nullptr, this, NewHealth, DeltaHealth);

		UE_LOG(LogTemp, Warning, TEXT("New Health is %f"), NewHealth)
		return true;
	}	

	return false;
}

bool USAttributeComponent::IsAlive() const
{
	return Health > 0.f;
}




