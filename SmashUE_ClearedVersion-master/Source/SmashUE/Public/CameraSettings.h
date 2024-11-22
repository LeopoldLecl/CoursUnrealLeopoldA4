// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "CameraSettings.generated.h"

UCLASS(Config = Game,DefaultConfig,meta = (DisplayName = "Smash Camera Settings"))

class SMASHUE_API UCameraSettings : public UDeveloperSettings
{
	GENERATED_BODY()


	public:
	UPROPERTY(config, EditAnywhere,Category="Camera")
	FName CameraMainTag = "CameraMain";
	
	UPROPERTY(config, EditAnywhere,Category="Camera")
	FName CameraDistanceMinTag = "CameraDistanceMin";
	
	UPROPERTY(config, EditAnywhere,Category="Camera")
	FName CameraDistanceMaxTag = "CameraDistanceMax";

	UPROPERTY(config, EditAnywhere,Category="Camera")
	FName CameraBoundsTag = "CameraBounds";

	UPROPERTY(config, EditAnywhere,Category="Camera")
	float DistanceBetweenTargetMin = 300.f;

	UPROPERTY(config, EditAnywhere,Category="Camera")
	float DistanceBetweenTargetMax = 1500.f;

	UPROPERTY(config, EditAnywhere,Category="Camera")
	float SizeDampingFactor = 5.f;

	UPROPERTY(config, EditAnywhere,Category="Camera")
	float PositionDampingFactor = 5.f;
};
