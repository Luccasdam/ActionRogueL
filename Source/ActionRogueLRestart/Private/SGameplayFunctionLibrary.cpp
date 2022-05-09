// Fill out your copyright notice in the Description page of Project Settings.


#include "SGameplayFunctionLibrary.h"

#include "SAttributesComponent.h"
#include "SPlayerState.h"

bool USGameplayFunctionLibrary::ApplyDamage(AActor* DamageCauser, AActor* TargetActor, float DamageAmount)
{
	USAttributesComponent* AttributesComp = USAttributesComponent::GetAttributes(TargetActor);
	if (AttributesComp != nullptr)
	{
		return AttributesComp->ApplyHealthChange(DamageCauser, -DamageAmount);
	}
	return false;
}

bool USGameplayFunctionLibrary::ApplyDirectionalDamage(AActor* DamageCauser, AActor* TargetActor, float DamageAmount, const FHitResult& HitResult)
{
	if (ApplyDamage(DamageCauser, TargetActor, DamageAmount))
	{
		UPrimitiveComponent* HitComp = HitResult.GetComponent();
		if (HitComp != nullptr && HitComp->IsSimulatingPhysics(HitResult.BoneName))
		{
			HitComp->AddImpulseAtLocation(-HitResult.ImpactNormal * 300000.f, HitResult.ImpactPoint, HitResult.BoneName);
		}
		return true;
	}
	return false;
}

bool USGameplayFunctionLibrary::ApplyCreditsChange(AActor* InstigatorActor, int32 CreditAmount)
{
	ASPlayerState* PS = ASPlayerState::GetPlayerState(InstigatorActor);
	if (PS == nullptr)	return false;

	return PS->ApplyCreditsChange(CreditAmount);
}
