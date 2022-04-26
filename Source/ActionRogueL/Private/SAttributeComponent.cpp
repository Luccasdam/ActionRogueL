// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"

// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
	:	MaxHealth(100)
	,	 Health(MaxHealth)
{
}


bool USAttributeComponent::ApplyHealthChange(AActor* InstigatorActor, float DeltaHealth)
{
	const float LastHealth = Health;
	Health = FMath::Clamp(Health + DeltaHealth, 0.f, MaxHealth);
	const float ActualDeltaHealth = Health - LastHealth;
	
	OnHealthChanged.Broadcast(InstigatorActor, this, Health, ActualDeltaHealth);
	return ActualDeltaHealth != 0.0f;
}


USAttributeComponent* USAttributeComponent::GetAttributes(AActor* FromActor)
{
	return FromActor ? Cast<USAttributeComponent>(FromActor->GetComponentByClass(USAttributeComponent::StaticClass())) : nullptr;
}

bool USAttributeComponent::IsActorAlive(APawn* FromPawn)
{
	const USAttributeComponent* AttributeComp = GetAttributes(FromPawn);
	return AttributeComp ? AttributeComp->IsAlive() : false;
}
