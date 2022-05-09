// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SAction.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, Abstract)
class ACTIONROGUELRESTART_API USAction : public UObject
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	void StartAction(AActor* InstigatorActor);

	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	void StopAction(AActor* InstigatorActor);

	virtual UWorld* GetWorld() const override;
	
	UPROPERTY(EditDefaultsOnly, Category = "Action")
	FName ActionName;
	
};
