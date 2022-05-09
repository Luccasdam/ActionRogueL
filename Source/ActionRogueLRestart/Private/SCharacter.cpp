// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"

#include "SActionComponent.h"
#include "SAttributesComponent.h"
#include "SInteractionComponent.h"
#include "SProjectileBase.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"


ASCharacter::ASCharacter()
	:	SpringArmComp(CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp")))
	,	CameraComp(CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp")))
	,	InteractionComp(CreateDefaultSubobject<USInteractionComponent>(TEXT("InteractionComp")))
	,	AttributesComp(CreateDefaultSubobject<USAttributesComponent>(TEXT("AttributesComp")))
	,	ActionComp(CreateDefaultSubobject<USActionComponent>(TEXT("ActionComp")))
	,	HandSocketName(TEXT("Muzzle_01"))
{
	SpringArmComp->SetupAttachment(RootComponent);
	CameraComp->SetupAttachment(SpringArmComp);
	
	SpringArmComp->bUsePawnControlRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;
}


void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ASCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ASCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ASCharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ASCharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("PrimaryAttack"), IE_Pressed, this, &ASCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction(TEXT("SecundaryAttack"), IE_Pressed, this, &ASCharacter::SecundaryAttack);
	PlayerInputComponent->BindAction(TEXT("UltimateAttack"), IE_Pressed, this, &ASCharacter::UltimateAttack);
	PlayerInputComponent->BindAction(TEXT("Interact"), IE_Pressed, this, &ASCharacter::Interact);

	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Pressed, this, &ASCharacter::SprintStart);
	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Released, this, &ASCharacter::SprintStop);
}

void ASCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AttributesComp->OnApplyHealthChange.AddDynamic(this, &ASCharacter::OnHealthChanged);
	AttributesComp->OnDeath.AddDynamic(this, &ASCharacter::OnDeath);
}

FVector ASCharacter::GetPawnViewLocation() const
{
	return CameraComp->GetComponentLocation();
}


void ASCharacter::MoveForward(float Value)
{
	FVector ForwardVec = CameraComp->GetForwardVector();
	ForwardVec.Z = 0.f;
	AddMovementInput(ForwardVec, Value);
}

void ASCharacter::MoveRight(float Value)
{
	FVector RightVec = CameraComp->GetRightVector();
	RightVec.Z = 0.f;
	AddMovementInput(RightVec, Value);
}

void ASCharacter::SprintStart()
{
	ActionComp->StartActionByName(this, "Sprint");
}

void ASCharacter::SprintStop()
{
	ActionComp->StopActionByName(this, "Sprint");
}


void ASCharacter::PrimaryAttack()
{	
	PlayAnimMontage(AttackAnimMontage);
	ProjectileClass = MagicProjectileClass;
	GetWorldTimerManager().SetTimer(TimerHandle_Attack, this, &ASCharacter::Attack_TimeElapsed, 0.169f);
}

void ASCharacter::SecundaryAttack()
{
	PlayAnimMontage(AttackAnimMontage);
	ProjectileClass = DashProjectileClass;
	GetWorldTimerManager().SetTimer(TimerHandle_Attack, this, &ASCharacter::Attack_TimeElapsed, 0.169f);
}

void ASCharacter::UltimateAttack()
{
	PlayAnimMontage(AttackAnimMontage);
	ProjectileClass = BlackHoleProjectileClass;
	GetWorldTimerManager().SetTimer(TimerHandle_Attack, this, &ASCharacter::Attack_TimeElapsed, 0.169f);
}

void ASCharacter::Attack_TimeElapsed()
{
	const FVector HandLocation = GetMesh()->GetSocketLocation(HandSocketName);
	
	FHitResult Hit;
	FVector EndLocation = CameraComp->GetComponentLocation() + CameraComp->GetForwardVector() * 2000.f;
	
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(this);
	
	bool bHitTarget = GetWorld()->LineTraceSingleByChannel(Hit, HandLocation, EndLocation, ECC_Visibility, CollisionQueryParams);
	FVector TargetLocation = bHitTarget ? Hit.Location : Hit.TraceEnd;
	FRotator TargetRotation = (TargetLocation - HandLocation).Rotation();

	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	const FTransform SpawnTM = FTransform(TargetRotation, HandLocation);
	
	GetWorld()->SpawnActor<ASProjectileBase>(ProjectileClass, SpawnTM, SpawnParams);
	
	UGameplayStatics::SpawnEmitterAttached(CastSpellEffect, GetMesh(), HandSocketName, FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget);
}


void ASCharacter::Interact()
{
	InteractionComp->Interact();
}

void ASCharacter::OnHealthChanged(AActor* InstigatorActor, USAttributesComponent* OwningComp, float NewHealth, float Delta)
{
	const FVector HitFlashColor = Delta < 0.f ? FVector(1.f, 0.f, 0.f) : FVector(0.f, 1.f, 0.f);
	
	GetMesh()->SetVectorParameterValueOnMaterials(TEXT("HitFlash_Color"), HitFlashColor);
	GetMesh()->SetScalarParameterValueOnMaterials(TEXT("HitFlash_Time"), GetWorld()->TimeSeconds);
}

void ASCharacter::OnDeath(AActor* InstigatorActor)
{
	APlayerController* PC = Cast<APlayerController>(GetController());
	DisableInput(PC);

	SetActorEnableCollision(false);
	SpringArmComp->bDoCollisionTest = false;
}