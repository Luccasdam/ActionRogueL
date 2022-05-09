// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCreditsChange, int32, CurrentCredits);

/**
 * 
 */
UCLASS()
class ACTIONROGUELRESTART_API ASPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	ASPlayerState();

	UPROPERTY(BlueprintAssignable, Category = "Gameplay")
	FOnCreditsChange OnCreditsChange;

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	static ASPlayerState* GetPlayerState(AActor* FromActor);

	bool ApplyCreditsChange(int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	int32 GetCredits() const	{ return Credits; }

protected:
	int32 Credits;
	
};
