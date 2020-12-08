#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/TimelineComponent.h"
#include "CloseDoorComponent.generated.h"

class ATriggerVolume;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EPICMEGAJAM2020_API UCloseDoorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCloseDoorComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void CheckPressurePlate() const;
	void InitVars();
	void CloseDoor();

	UFUNCTION()
	void ControlClose();
	UFUNCTION()
	void SetCloseState();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate = nullptr;
	UPROPERTY(EditAnywhere)
	UCurveFloat* CloseCurve;

	UFUNCTION()
	void OnBeginOverlap(AActor* MyOverlappedActor, AActor* OtherActor);

	AActor* PlayerPawn;
	bool DoorClosed = false;
	bool DoorClosing = false;
	float CurveFloatValue;
	float TimelineValue;
	FTimeline CloseTimeline;

	void SetupTimeline();

};