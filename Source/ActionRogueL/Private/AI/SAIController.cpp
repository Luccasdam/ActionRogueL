// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void ASAIController::BeginPlay()
{
	Super::BeginPlay();

	if (ensureMsgf(BTMinionRanged, TEXT("Behavior Tree is nullptr! Please assign it in your AI Controller")))	RunBehaviorTree(BTMinionRanged);

	// APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	// if (PlayerPawn)
	// {
	// 	GetBlackboardComponent()->SetValueAsVector("MoveToLocation", PlayerPawn->GetActorLocation());
	//
	// 	GetBlackboardComponent()->SetValueAsObject("TargetPawn", PlayerPawn);
	// }
}
