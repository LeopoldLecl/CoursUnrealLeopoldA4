// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Subsystems/WorldSubsystem.h"
#include "CameraSettings.h"
#include "CameraWorldSubsystem.generated.h"


UCLASS()
class SMASHUE_API UCameraWorldSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()
#pragma region Subsystems Ovverides
public:
	virtual void PostInitialize() override;

	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

	virtual void Tick(float DeltaTime) override;

	virtual TStatId GetStatId() const override {return TStatId();};

#pragma endregion

#pragma region Follow Targets
	void AddFollowTarget(AActor* FollowTarget);

	void RemoveFollowTarget(AActor* FollowTarget);
	
	FVector CalculateAveragePositionBetweenTargets();

	float CalculateGreatestDistanceBetweenTargets();
	
	UPROPERTY()
	TArray<UObject*> FollowTargets;

	
#pragma endregion

#pragma region Misc
	
	protected:

	UPROPERTY()
	TObjectPtr<UCameraComponent> CameraMain;

	UPROPERTY()
	TObjectPtr<const UCameraSettings> CameraSettings;
	
	void TickUpdateCameraPosition(float DeltaTime);

	void TickUpdateCameraZoom(float DeltaTime);

	void TickUpdateDampingCameraPosition(float DeltaTime);


	UCameraComponent* FindCameraByTag(const FName& Tag) const;

#pragma endregion

#pragma region Bounds

	UPROPERTY()
	FVector2D CameraBoundsMin;

	UPROPERTY()
	FVector2D CameraBoundsMax;

	UPROPERTY()
	float CameraBoundsYProjectionCenter;

	AActor* FindCameraBoundsActor();

	void InitCameraBounds(AActor* CameraBoundsActor);

	void ClampPositionIntoCameraBounds(FVector2d& OutViewPortBoundsMin, FVector2d& OutViewPortBoundsMax);

	void GetViewportBounds(FVector2D& OutViewportBoundsMin,FVector2D& OutViewportBoundsMax);

	FVector CalculateWorldPositionFromViewPortPosition(const FVector2d& ViewPortPosition);

#pragma endregion

#pragma region Camera Zoom

	protected:
	UPROPERTY()
	float CameraZoomYMin = 0.f;

	UPROPERTY()
	float CameraZoomYMax = 0.f;

	UPROPERTY()
	float CameraZoomDistanceBetweenTargetsMin = 300.f;

	UPROPERTY()
	float CameraZoomDistanceBetweenTargetsMax = 1500.f;

	UFUNCTION()
	void InitCameraZoomParameters();

	float InverseLerp(float Start, float End, float Value);

private:
	FVector GoalTargetPosition = FVector::ZeroVector;
	
#pragma endregion

};
