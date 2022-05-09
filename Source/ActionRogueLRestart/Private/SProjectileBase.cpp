// Fill out your copyright notice in the Description page of Project Settings.


#include "SProjectileBase.h"

#include "SAttributesComponent.h"
#include "SGameplayFunctionLibrary.h"
#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"


ASProjectileBase::ASProjectileBase()
	:	SphereComp(CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp")))
	,	ParticleComp(CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleComp")))
	,	FlightSoundComp(CreateDefaultSubobject<UAudioComponent>(TEXT("FlightSoundComp")))
	,	ProjMovComp(CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent")))
{
	RootComponent = SphereComp;
	SphereComp->SetCollisionProfileName(TEXT("Projectile"));
	SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);
	
	ParticleComp->SetupAttachment(SphereComp);

	FlightSoundComp->SetupAttachment(SphereComp);

	ProjMovComp->InitialSpeed = 5000.f;
	ProjMovComp->ProjectileGravityScale = 0.f;
	ProjMovComp->bRotationFollowsVelocity = true;
	ProjMovComp->bInitialVelocityInLocalSpace = true;
}

void ASProjectileBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	SphereComp->OnComponentHit.AddDynamic(this, &ASProjectileBase::OnActorHit);
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASProjectileBase::OnActorBeginOverlap);
}

void ASProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(5.f);
}

void ASProjectileBase::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Explode();
}

void ASProjectileBase::Explode_Implementation()
{
	if (ensure(!IsPendingKill()))
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, HitVFX, GetActorLocation(), GetActorRotation());
		UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation(), GetActorRotation());
		UGameplayStatics::PlayWorldCameraShake(this, CameraShake, GetActorLocation(), 200, 1000);
		Destroy();
	}	
}

void ASProjectileBase::OnActorBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherActor == nullptr || OtherActor == GetInstigator())	return;
		
	if (USGameplayFunctionLibrary::ApplyDirectionalDamage(GetInstigator(), OtherActor, Damage, SweepResult))
	{
		Explode();
	}
}

