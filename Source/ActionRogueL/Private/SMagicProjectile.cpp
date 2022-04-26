// Fill out your copyright notice in the Description page of Project Settings.


#include "SMagicProjectile.h"

#include "SAttributeComponent.h"
#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASMagicProjectile::ASMagicProjectile()
{	
	ProjectileFlightSound = CreateDefaultSubobject<UAudioComponent>(TEXT("ProjFlightSound"));
	ProjectileFlightSound->SetupAttachment(SphereComp);
}

// Called when the game starts or when spawned
void ASMagicProjectile::BeginPlay()
{
	Super::BeginPlay();

	const ACharacter* InstigatorCharacter = Cast<ACharacter>(GetInstigator());
	if (InstigatorCharacter)
	{
		const FVector HandLocation = InstigatorCharacter->GetMesh()->GetSocketLocation("Muzzle_01");
		UGameplayStatics::SpawnEmitterAttached(CastEffect, nullptr, NAME_None, HandLocation);
	}
}

void ASMagicProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASMagicProjectile::OnActorOverlap);
}

void ASMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,	const FHitResult& SweepResult)
{
	if (OtherActor != GetInstigator())
	{
		USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(OtherActor->GetComponentByClass(USAttributeComponent::StaticClass()));
		if (AttributeComp)    AttributeComp->ApplyHealthChange(GetInstigator(), ProjectileDamage);
		
		Explode();
	}
}

void ASMagicProjectile::Explode_Implementation()
{
	Super::Explode_Implementation();

	UGameplayStatics::PlayWorldCameraShake(this, CameraShake, GetActorLocation(), 0.f, CameraShakeOuterRadius);
	UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation());
}