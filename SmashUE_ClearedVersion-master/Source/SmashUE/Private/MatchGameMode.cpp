// Fill out your copyright notice in the Description page of Project Settings.


#include "MatchGameMode.h"

#include "ArenaSettings.h"
#include "SmashCharacter.h"
#include "Arena/ArenaPlayerStart.h"
#include "Kismet/GameplayStatics.h"

void AMatchGameMode::BeginPlay()
{
	Super::BeginPlay();


	TArray<AArenaPlayerStart*> PlayerStartsPoints;
	FindPlayersStartActorsInArena(PlayerStartsPoints);
	SpawnCharacters(PlayerStartsPoints);

	for (AArenaPlayerStart* PlayerStartPoint : PlayerStartsPoints)
	{
		EAutoReceiveInput::Type InputType = PlayerStartPoint->AutoReceiveInput.GetValue();
		TSubclassOf<ASmashCharacter> SmashCharacterClass = GetSmashCharacterClassFromInputType(InputType);

		if (SmashCharacterClass == nullptr)
		{
			continue;
		}


		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, PlayerStartPoint->GetFName().ToString());
	}
}

void AMatchGameMode::FindPlayersStartActorsInArena(TArray<AArenaPlayerStart*>& ResultsActors)
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AArenaPlayerStart::StaticClass(), FoundActors);

	for (int i = 0; i < FoundActors.Num(); i++)
	{
		AArenaPlayerStart* ArenaPlayerStartActor = Cast<AArenaPlayerStart>(FoundActors[i]);
		if (ArenaPlayerStartActor == nullptr)
		{
			continue;
		}

		ResultsActors.Add(ArenaPlayerStartActor);
	}
}

TSubclassOf<ASmashCharacter> AMatchGameMode::GetSmashCharacterClassFromInputType(
	EAutoReceiveInput::Type InputType) const
{
	const UArenaSettings* ArenaSettings = GetDefault<UArenaSettings>();
	
	switch (InputType)
	{
	case EAutoReceiveInput::Player0:
		return ArenaSettings->ASmashCharacterClassP0;
	case EAutoReceiveInput::Player1:
		return ArenaSettings->ASmashCharacterClassP1;
	case EAutoReceiveInput::Player2:
		return ArenaSettings->ASmashCharacterClassP2;
	case EAutoReceiveInput::Player3:
		return ArenaSettings->ASmashCharacterClassP3;

	default:
		return nullptr;
	}
}


void AMatchGameMode::SpawnCharacters(const TArray<AArenaPlayerStart*>& SpawnPoints)
{
	for (AArenaPlayerStart* SpawnPoint : SpawnPoints)
	{
		EAutoReceiveInput::Type InputType = SpawnPoint->AutoReceiveInput.GetValue();
		TSubclassOf<ASmashCharacter> SmashCharacterClass = GetSmashCharacterClassFromInputType(InputType);
		if (SmashCharacterClass == nullptr)
		{
			continue;
		}

		ASmashCharacter* NewCharacter = GetWorld()->SpawnActorDeferred<ASmashCharacter>(
			SmashCharacterClass,
			SpawnPoint->GetTransform()
		);

		if (NewCharacter == nullptr)
		{
			continue;
		}

		NewCharacter->AutoPossessPlayer = SpawnPoint->AutoReceiveInput;
		NewCharacter->SetOrientX(SpawnPoint->GetStartOrientX());
		NewCharacter->FinishSpawning(SpawnPoint->GetTransform());

		CharactersInsideArena.Add(NewCharacter);
	}
}
