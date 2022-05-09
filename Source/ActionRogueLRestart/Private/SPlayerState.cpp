// Fill out your copyright notice in the Description page of Project Settings.


#include "SPlayerState.h"

ASPlayerState::ASPlayerState()
	:	Credits(10)
{
}

ASPlayerState* ASPlayerState::GetPlayerState(AActor* FromActor)
{
	UE_LOG(LogTemp, Warning, TEXT("Trying to get PlayerState"))
	if (FromActor == nullptr)	return nullptr;
	
	const APawn* FromPawn = Cast<APawn>(FromActor);
	if (FromPawn == nullptr)	return nullptr;

	return Cast<ASPlayerState>(FromPawn->GetPlayerState());
}

bool ASPlayerState::ApplyCreditsChange(int32 Amount)
{
	const int32 CreditsResult = Credits + Amount;
	if (CreditsResult < 0)	return false;

	Credits = CreditsResult;
	OnCreditsChange.Broadcast(Credits);
	return true;
}
