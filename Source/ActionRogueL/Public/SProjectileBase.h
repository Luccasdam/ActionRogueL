// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SProjectileBase.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS(Abstract)
class ACTIONROGUEL_API ASProjectileBase : public AActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attack")
	float ProjectileDamage;
	
public:	
	// Sets default values for this actor's properties
	ASProjectileBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components")
	USphereComponent* SphereComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components")
	UParticleSystemComponent* EffectComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components")
	UProjectileMovementComponent* ProjMovComp;

	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintImplementableEvent)
	void CustomHit(const FHitResult& inSweepResult);
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
