#pragma once

#include "CoreMinimal.h"
#include "ArenaSettings.h"
#include "SmashCharacterInputData.h"
#include "Arena/ArenaPlayerStart.h"
#include "GameFramework/GameModeBase.h"
#include "Engine/StreamableManager.h" // Placez tous les includes avant le .generated.h

#include "MatchGameMode.generated.h" // Assurez-vous que ce fichier est la dernière inclusion

class ASmashCharacter;
class AArenaPlayerStart;


UCLASS()
class SMASHUE_API AMatchGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

protected:
	UPROPERTY()
	TArray<ASmashCharacter*> CharactersInsideArena;

	// UPROPERTY(EditAnywhere)
	// TSubclassOf<ASmashCharacter> SmashCharacterClassP0;
	//
	// UPROPERTY(EditAnywhere)
	// TSubclassOf<ASmashCharacter> SmashCharacterClassP1;
	//
	// UPROPERTY(EditAnywhere)
	// TSubclassOf<ASmashCharacter> SmashCharacterClassP2;
	//
	// UPROPERTY(EditAnywhere)
	// TSubclassOf<ASmashCharacter> SmashCharacterClassP3;


private :
	USmashCharacterInputData* LoadInputDataFromConfig();

	UInputMappingContext* LoadInputMappingContextFromConfig();

	void FindPlayersStartActorsInArena(TArray<AArenaPlayerStart*>& ResultsActors);

	void SpawnCharacters(const TArray<AArenaPlayerStart*>& SpawnPoints);

	TSubclassOf<ASmashCharacter> GetSmashCharacterClassFromInputType(EAutoReceiveInput::Type InputType) const;
};
