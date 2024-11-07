// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SmashCharacter.h"
#include "Engine/DeveloperSettings.h"
#include "ArenaSettings.generated.h"

/**
 * 
 */
UCLASS(Config = Game,DefaultConfig,meta = (DisplayName = "Smash Arena Settings"))
class SMASHUE_API UArenaSettings : public UDeveloperSettings
{
	GENERATED_BODY()


	public:
	UPROPERTY(config, EditAnywhere,Category="Characters")
	TSubclassOf<ASmashCharacter> ASmashCharacterClassP0;
	
	UPROPERTY(config, EditAnywhere,Category="Characters")
	TSubclassOf<ASmashCharacter> ASmashCharacterClassP1;
	
	UPROPERTY(config, EditAnywhere,Category="Characters")
	TSubclassOf<ASmashCharacter> ASmashCharacterClassP2;
	
	UPROPERTY(config, EditAnywhere,Category="Characters")
	TSubclassOf<ASmashCharacter> ASmashCharacterClassP3;
};
