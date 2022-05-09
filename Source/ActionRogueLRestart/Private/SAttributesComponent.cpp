// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributesComponent.h"
#include "SGameModeBase.h"


static TAutoConsoleVariable<float> CVarDamageMultiplier(TEXT("su.DamageMultiplier"), 1.0f, TEXT("Global Damage Multiplier for Attribute Component."), ECVF_Cheat);


USAttributesComponent::USAttributesComponent()
	:	MaxHealth(100.f)
	,	Health(MaxHealth)
{
}

bool USAttributesComponent::IsAlive() const	{ return Health > 0.f; }

bool USAttributesComponent::ApplyHealthChange(AActor* InstigatorActor, float Delta)
{
	if (!GetOwner()->CanBeDamaged() && Delta < 0.f)	return false;
	if (InstigatorActor == GetOwner() && Delta < 0.f)	return false;

	Delta *= CVarDamageMultiplier.GetValueOnGameThread();
	
	const float OldHealth = Health;
	
	Health += Delta;
	Health = FMath::Clamp(Health, 0.f, MaxHealth);

	const float ActualDelta = Health - OldHealth;
	
	if (ActualDelta != 0)
	{
		OnApplyHealthChange.Broadcast(InstigatorActor, this, Health, ActualDelta);

		if (Health == 0)
		{
			OnDeath.Broadcast(InstigatorActor);
			ASGameModeBase* GM = GetWorld()->GetAuthGameMode<ASGameModeBase>();
			if (GM)	GM->OnActorKilled(GetOwner(), InstigatorActor);
		}
		
		return true;
	}
	
	return false;
}


USAttributesComponent* USAttributesComponent::GetAttributes(AActor* FromActor)
{
	if (FromActor != nullptr)	return Cast<USAttributesComponent>(FromActor->GetComponentByClass(USAttributesComponent::StaticClass()));
	
	return nullptr;
}

bool USAttributesComponent::IsActorAlive(AActor* FromActor)
{
	const USAttributesComponent* Attributes = GetAttributes(FromActor);
	if (Attributes != nullptr)	return Attributes->IsAlive();
	
	return false;
}
