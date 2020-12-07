#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

AGun::AGun()
{
	PrimaryActorTick.bCanEverTick = false;

	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Scene Component"));
	SetRootComponent(RootSceneComponent);

	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh"));
	MeshComponent->SetupAttachment(RootSceneComponent);
}

void AGun::BeginPlay()
{
	Super::BeginPlay();
}

void AGun::Shoot(FVector& LookAtTarget) 
{
	// Spawn shooting effects
	if (MuzzleParticleComp == nullptr) 
	{
		MuzzleParticleComp = UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, MeshComponent, TEXT("MuzzleFlashSocket"));
		MuzzleParticleComp->SetRelativeScale3D(FVector(0.5, 0.5, 0.5));
	}	
	// Perform our shooting line trace
	FHitResult HitResult;
	FVector ShotDirection;
	bool Success = GunTrace(HitResult, LookAtTarget);
	if (Success) 
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, HitResult.ImpactPoint, FRotator::ZeroRotator);
		// Apply damage if we hit an actor that isn't the player
		AActor* HitActor = HitResult.GetActor();
		if (HitActor != nullptr && HitActor != GetOwner()) 
		{
			UGameplayStatics::ApplyDamage(HitActor, Damage, GetInstigatorController(), this, DamageType);
		}
	}
}

void AGun::Release() 
{
	// Stop particles if we stopped shooting
	if (MuzzleParticleComp != nullptr) 
	{
		MuzzleParticleComp->DestroyComponent();
		MuzzleParticleComp = nullptr;
	}
}

bool AGun::GunTrace(FHitResult& OutHitResult, FVector& LookAtTarget) 
{
	AController* OwnerController = GetOwnerController();
	if (OwnerController == nullptr) { return false; }
	// Perform a line trace	from the gun towards our mouse position
	const USkeletalMeshSocket* Socket = MeshComponent->GetSocketByName("MuzzleFlashSocket");
	FVector Start = Socket->GetSocketLocation(MeshComponent);
	FVector Dir = FVector(LookAtTarget - Start);
	FVector End = Dir * MaxRange;
	// Ignore hits against the gun and the player
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());
	// Perform the actual line trace and return results
	return GetWorld()->LineTraceSingleByChannel(OutHitResult, Start, End, ECC_Visibility);
}

AController* AGun::GetOwnerController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn) { return nullptr; }
	return OwnerPawn->GetController();
}