#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Kismet/GameplayStatics.h"

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
	FHitResult HitResult;
	bool Success = GunTrace(HitResult, LookAtTarget);
	if (Success) 
	{
		// TODO: REMOVE THIS
		const USkeletalMeshSocket* Socket = MeshComponent->GetSocketByName("MuzzleFlashSocket");
		FVector Start = Socket->GetSocketLocation(MeshComponent);
		DrawDebugLine(GetWorld(), Start, HitResult.ImpactPoint, FColor::Blue, true, 5.f, 0, 5.f);
		// Apply damage if we hit an actor that isn't the player
		AActor* HitActor = HitResult.GetActor();
		if (HitActor != nullptr && HitActor != GetOwner()) 
		{
			UGameplayStatics::ApplyDamage(HitActor, Damage, GetInstigatorController(), this, DamageType);
		}
	}
}

bool AGun::GunTrace(FHitResult& OutHitResult, FVector& LookAtTarget) 
{
	AController* OwnerController = GetOwnerController();
	if (OwnerController == nullptr) { return false; }
	// Perform a line trace	from the gun towards our mouse position
	const USkeletalMeshSocket* Socket = MeshComponent->GetSocketByName("MuzzleFlashSocket");
	FVector Start = Socket->GetSocketLocation(MeshComponent);
	FVector End = (LookAtTarget - Start) * MaxRange;
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