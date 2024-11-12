// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Arena/MatchGameMode.h"
#include "Engine/DeveloperSettings.h"
#include "SmashCharacterSettings.generated.h"


UCLASS(Config = Game,DefaultConfig,meta = (DisplayName = "Smash Character Settings"))
class SMASHUE_API USmashCharacterSettings : public UDeveloperSettings
{
	GENERATED_BODY()

	public:
	UPROPERTY(config, EditAnywhere, Category = "Inputs")
	TSoftObjectPtr<USmashCharacterInputData> InputData;

	UPROPERTY(config, EditAnywhere, Category = "Inputs")
	TSoftObjectPtr<UInputMappingContext> InputMappingContext;
};
