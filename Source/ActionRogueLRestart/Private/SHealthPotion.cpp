// Fill out your copyright notice in the Description page of Project Settings.


#include "SHealthPotion.h"

#include "SAttributesComponent.h"
#include "SGameplayFunctionLibrary.h"

ASHealthPotion::ASHealthPotion()
	:	Cost(2)
	,	HealAmount(25)
{
}

void ASHealthPotion::Interact_Implementation(APawn* InstigatorPawn)
{
	Super::Interact_Implementation(InstigatorPawn);

	if (!USGameplayFunctionLibrary::ApplyCreditsChange(InstigatorPawn, -Cost))	return;
	
	USAttributesComponent* AttributesComp = USAttributesComponent::GetAttributes(InstigatorPawn);
	if (AttributesComp != nullptr)
	{
		if (AttributesComp->ApplyHealthChange(InstigatorPawn, HealAmount))    SetItemOnCooldown();
		else USGameplayFunctionLibrary::ApplyCreditsChange(InstigatorPawn, Cost);
	}
}
