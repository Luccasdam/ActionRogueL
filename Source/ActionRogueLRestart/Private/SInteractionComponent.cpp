// Fill out your copyright notice in the Description page of Project Settings.


#include "SInteractionComponent.h"
#include "DrawDebugHelpers.h"
#include "SGameplayInterface.h"


static TAutoConsoleVariable<bool> CVarDebugDrawInteraction(TEXT("su.InteractionDebugDraw"), false, TEXT("Enable Debug Draw for Interaction Component"), ECVF_Cheat);


USInteractionComponent::USInteractionComponent()
	:	TraceDistance(500.f)
{
}

void USInteractionComponent::Interact()
{	
	TArray<FHitResult> Hits;
	
	FVector EyeLocation;
	FRotator EyeRotation;
	GetOwner()->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	const FVector TraceEnd = EyeLocation + EyeRotation.Vector() * TraceDistance;

	FCollisionObjectQueryParams ObjQueryParams;
	ObjQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	FCollisionShape CollisionShape;
	CollisionShape.SetSphere(20.f);

	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(GetOwner());
	
	if (GetWorld()->SweepMultiByObjectType(Hits, EyeLocation, TraceEnd, FQuat::Identity, ObjQueryParams, CollisionShape, CollisionQueryParams))
	{
		/* Debug Only */
		if (CVarDebugDrawInteraction.GetValueOnGameThread())
		{
			DrawDebugLine(GetWorld(), EyeLocation, TraceEnd, FColor::Blue, false, 2.f, 0, 2.f);
		}
		
		for (FHitResult Hit : Hits)
		{
			const bool bHitInteractableActor = Hit.Actor->Implements<USGameplayInterface>();
			
			FColor DebugColor = bHitInteractableActor ? FColor::Green : FColor::Red;

			/* Debug Only */
			if (CVarDebugDrawInteraction.GetValueOnGameThread())
			{
				DrawDebugSphere(GetWorld(), Hit.ImpactPoint, 5.f, 32, DebugColor, false, 2.f, 0, 2.f);
			}
						
			if (bHitInteractableActor)
			{
				APawn* InstigatorPawn = Cast<APawn>(GetOwner());
				ISGameplayInterface::Execute_Interact(Hit.GetActor(), InstigatorPawn);
				break;
			}
		}
	}
	
}
