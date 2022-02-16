// Fill out your copyright notice in the Description page of Project Settings.


#include "SProjectileBase.h"

#include "SAttributeComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ASProjectileBase::ASProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SetRootComponent(SphereComp);
	SphereComp->SetCollisionProfileName("Projectile");
	SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);


	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EffectComp"));
	EffectComp->SetupAttachment(SphereComp);

	ProjMovComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjMovComp"));
	ProjMovComp->InitialSpeed = 5000.f;
	ProjMovComp->bRotationFollowsVelocity = true;
}

// Called when the game starts or when spawned
void ASProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	//SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);
	UE_LOG(LogTemp, Log, TEXT("Instigator of Projectile is: %s"), *GetNameSafe(GetInstigator()))
	
}

void ASProjectileBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	

	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASProjectileBase::OnComponentBeginOverlap);
}

// Called every frame
void ASProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASProjectileBase::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == GetInstigator())	{return;}
	
	USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(OtherActor->GetComponentByClass(USAttributeComponent::StaticClass()));
	if (AttributeComp)
	{
		AttributeComp->ApplyHealthChange(ProjectileDamage);

		UE_LOG(LogTemp, Log, TEXT("Actor Hit is: %s"), *GetNameSafe(OtherActor))

		CustomHit(SweepResult);
	}
}
