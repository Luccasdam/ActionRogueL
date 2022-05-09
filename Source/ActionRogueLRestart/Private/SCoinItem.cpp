// Fill out your copyright notice in the Description page of Project Settings.


#include "SCoinItem.h"

#include "SGameplayFunctionLibrary.h"

ASCoinItem::ASCoinItem()
	:	CreditAmount(5)
{
}

void ASCoinItem::Interact_Implementation(APawn* InstigatorPawn)
{
	Super::Interact_Implementation(InstigatorPawn);

	if (USGameplayFunctionLibrary::ApplyCreditsChange(InstigatorPawn, CreditAmount))	SetItemOnCooldown();
}

