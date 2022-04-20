// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"

// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
{
}

bool USAttributeComponent::ApplyHealthChange(float DeltaHealth)
{
	const float LastHealth = Health;
	Health = FMath::Clamp(Health + DeltaHealth, 0.f, MaxHealth);
	const float ActualDeltaHealth = Health - LastHealth;
	
	OnHealthChanged.Broadcast(nullptr, this, Health, ActualDeltaHealth);
	return ActualDeltaHealth != 0.0f;
}

bool USAttributeComponent::IsAlive() const
{
	return Health > 0.f;
}




