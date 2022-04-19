// Fill out your copyright notice in the Description page of Project Settings.


#include "SInteractionComponent.h"

#include "DrawDebugHelpers.h"
#include "SGameplayInterface.h"

// Sets default values for this component's properties
USInteractionComponent::USInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}




// Called when the game starts
void USInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USInteractionComponent::PrimaryInteract()
{
	TArray<FHitResult> Hits;
	
	FVector ViewLocation;
	FRotator ViewRotation;
	GetOwner()->GetActorEyesViewPoint(ViewLocation, ViewRotation);

	FVector EndLocation = ViewLocation + (ViewRotation.Vector() * 1000.f);

	FCollisionObjectQueryParams ObjQueryParams;
	ObjQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	FCollisionShape CollisionShape;
	CollisionShape.SetSphere(30.f);
	
	GetWorld()->SweepMultiByObjectType(Hits, ViewLocation, EndLocation, FQuat::Identity, ObjQueryParams, CollisionShape);

	for (FHitResult& Hit : Hits)
	{
		if(AActor* HitActor = Hit.GetActor())
		{
			const bool bIsInteractAble = HitActor->Implements<USGameplayInterface>();
			if (bIsInteractAble)
			{
				APawn* InstigatorPawn = Cast<APawn>(GetOwner());
				ISGameplayInterface::Execute_Interact(HitActor, InstigatorPawn);
			}
			
			const FVector DrawEndLocation = Hit.bBlockingHit ? Hit.Location : Hit.TraceEnd;
			const FColor DebugColor = bIsInteractAble ? FColor::Green : FColor::Red;
			DrawDebugSphere(GetWorld(), DrawEndLocation, 15.f, 16, DebugColor, false, 2.f, 0, 2.f);
			
			break;
		}
	}
}