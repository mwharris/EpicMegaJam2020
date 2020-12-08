#include "CloseDoorComponent.h"
#include "Engine/TriggerVolume.h"
#include "Kismet/GameplayStatics.h"

UCloseDoorComponent::UCloseDoorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCloseDoorComponent::BeginPlay()
{
	Super::BeginPlay();
	CheckPressurePlate();
	InitVars();
	SetupTimeline();
}

void UCloseDoorComponent::CheckPressurePlate() const
{
	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("UCloseDoorComponent: No Pressue Plate Found!"));
		return;
	}
	PressurePlate->OnActorBeginOverlap.AddDynamic(this, &UCloseDoorComponent::OnBeginOverlap);
}

void UCloseDoorComponent::InitVars() 
{
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerPawn == nullptr) 
	{
		UE_LOG(LogTemp, Error, TEXT("UCloseDoorComponent: No Player Found!"));
		return;
	}
}

void UCloseDoorComponent::SetupTimeline() 
{
	// Timeline will call this function when it's running
	FOnTimelineFloat TimelineCallback;
	TimelineCallback.BindUFunction(this, FName(TEXT("ControlClose")));
	// Timeline will call this function when it's completed running
	FOnTimelineEventStatic TimelineFinishedCallback;
	TimelineFinishedCallback.BindUFunction(this, FName(TEXT("SetCloseState")));
	// Setup the timeline to call the above functions 
	CloseTimeline.AddInterpFloat(CloseCurve, TimelineCallback);
	CloseTimeline.SetTimelineFinishedFunc(TimelineFinishedCallback);	
}

void UCloseDoorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (DoorClosing && !DoorClosed) 
	{
		CloseTimeline.TickTimeline(DeltaTime);
	}
}

void UCloseDoorComponent::OnBeginOverlap(AActor* MyOverlappedActor, AActor* OtherActor) 
{
	if (OtherActor == nullptr || PlayerPawn == nullptr || OtherActor != PlayerPawn || DoorClosed) { return; } 
	DoorClosing = true;
	CloseTimeline.PlayFromStart();
}

void UCloseDoorComponent::ControlClose() 
{
	FVector Location = GetOwner()->GetActorLocation();
	// Get the current time value
	TimelineValue = CloseTimeline.GetPlaybackPosition();
	// Get the current float value from the timeline using the time value above
	CurveFloatValue = CloseCurve->GetFloatValue(TimelineValue);
	// Set our new location given the timeline values
	FVector NewLocation = FVector(Location.X, Location.Y, CurveFloatValue);
	GetOwner()->SetActorLocation(NewLocation);
}

void UCloseDoorComponent::SetCloseState() 
{
	DoorClosed = true;
	DoorClosing = false;
}