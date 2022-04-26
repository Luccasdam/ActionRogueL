// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SAICharacter.h"

#include "AIController.h"
#include "BrainComponent.h"
#include "DrawDebugHelpers.h"
#include "SAttributeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/PawnSensingComponent.h"

// Sets default values
ASAICharacter::ASAICharacter()
	:	AttributeComp(CreateDefaultSubobject<USAttributeComponent>(TEXT("AttributeComponent")))
	,	PawnSenseComp(CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSenseComp")))
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}


void ASAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AttributeComp->OnHealthChanged.AddDynamic(this, &ASAICharacter::OnHealthChanged);
	PawnSenseComp->OnSeePawn.AddDynamic(this, &ASAICharacter::OnPawnSeen);
}

void ASAICharacter::OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	if (Delta < 0.0f)
	{
		if (InstigatorActor != this)	SetTargetPawn(Cast<APawn>(InstigatorActor));
		
		if (NewHealth <= 0.0f && Delta < 0.0f)
		{
			AAIController* AIC = Cast<AAIController>(GetController());
			if (AIC)	AIC->GetBrainComponent()->StopLogic("Killed");

			GetMesh()->SetAllBodiesSimulatePhysics(true);
			GetMesh()->SetCollisionProfileName("Ragdoll");
			GetMesh()->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->TimeSeconds);

			SetLifeSpan(10.0f);
		}
	}
}

void ASAICharacter::OnPawnSeen(APawn* Pawn)
{
	DrawDebugString(GetWorld(), GetActorLocation(), "Player Spotted", nullptr, FColor::White, 4.0f, true);
	SetTargetPawn(Pawn);
}

void ASAICharacter::SetTargetPawn(APawn* TargetPawn)
{
	AAIController* AIC = Cast<AAIController>(GetController());
	if (AIC)	AIC->GetBlackboardComponent()->SetValueAsObject("TargetPawn", TargetPawn);
}
