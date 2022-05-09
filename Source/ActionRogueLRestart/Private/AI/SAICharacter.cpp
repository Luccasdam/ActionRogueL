// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SAICharacter.h"
#include "AIController.h"
#include "BrainComponent.h"
#include "DrawDebugHelpers.h"
#include "SAttributesComponent.h"
#include "SGameplayFunctionLibrary.h"
#include "SWorldWidget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/PawnSensingComponent.h"


ASAICharacter::ASAICharacter()
	:	PawnSensingComp(CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp")))
	,	AttributesComp(CreateDefaultSubobject<USAttributesComponent>(TEXT("AttributesComp")))
	,	HitFlash_TimeParamName(TEXT("HitFlash_Time"))
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Ignore);
	GetMesh()->SetGenerateOverlapEvents(true);
}

void ASAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	PawnSensingComp->OnSeePawn.AddDynamic(this, &ASAICharacter::OnPawnSeen);

	AttributesComp->OnApplyHealthChange.AddDynamic(this, &ASAICharacter::OnApplyHealthChange);
	AttributesComp->OnDeath.AddDynamic(this, &ASAICharacter::OnDeath);
}

void ASAICharacter::OnPawnSeen(APawn* Pawn)
{
	SetTargetActor(Pawn);

	DrawDebugString(GetWorld(), GetActorLocation(), "Player Spotted", nullptr, FColor::White, 4.0f, true);
}

void ASAICharacter::OnApplyHealthChange(AActor* InstigatorActor, USAttributesComponent* OwningComp, float NewHealth, float Delta)
{	
	if (Delta < 0.f)
	{
		SetTargetActor(InstigatorActor);
		GetMesh()->SetScalarParameterValueOnMaterials(HitFlash_TimeParamName, GetWorld()->TimeSeconds);
	}

	if (HealthBarWidget != nullptr)	return;
	if (InstigatorActor == nullptr)	return;
	
	APlayerController* PC = Cast<APlayerController>(InstigatorActor->GetInstigatorController());
	if (PC != nullptr)
	{
		HealthBarWidget = CreateWidget<USWorldWidget>(PC, HealthBarWidgetClass);
		if (HealthBarWidget != nullptr)
		{
			HealthBarWidget->AttachedActor = this;
			HealthBarWidget->AddToViewport();
		}
	}
}

void ASAICharacter::OnDeath(AActor* InstigatorActor)
{
	AAIController* AIC = Cast<AAIController>(GetController());
	if (AIC == nullptr)	return;

	AIC->GetBrainComponent()->StopLogic("AI Died");

	GetMesh()->SetCollisionProfileName("Ragdoll");
	GetMesh()->SetAllBodiesSimulatePhysics(true);

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//GetCharacterMovement()->DisableMovement();	Do i need this?

	USGameplayFunctionLibrary::ApplyCreditsChange(InstigatorActor, 1);
	
	SetLifeSpan(10.0f);
}

void ASAICharacter::SetTargetActor(AActor* NewTarget)
{
	AAIController* AIC = Cast<AAIController>(GetController());
	if (!ensure(AIC))    return;
		
	AIC->GetBlackboardComponent()->SetValueAsObject("TargetActor", NewTarget);
}
