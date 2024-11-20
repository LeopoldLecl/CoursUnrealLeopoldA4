// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Subsystems/WorldSubsystem.h"
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
	
	UPROPERTY()
	TArray<UObject*> FollowTargets;
#pragma endregion

#pragma region Misc
	
	protected:

	UPROPERTY()
	TObjectPtr<UCameraComponent> CameraMain;
	
	void TickUpdateCameraPosition(float DeltaTime);



	FVector CalculateAveragePositionBetweenTargets();

	UCameraComponent* FindCameraByTag(const FName& Tag) const;

#pragma endregion


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
};
