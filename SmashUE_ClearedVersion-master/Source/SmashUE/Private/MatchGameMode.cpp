// Fill out your copyright notice in the Description page of Project Settings.


#include "MatchGameMode.h"

#include "Arena/ArenaPlayerStart.h"
#include "Kismet/GameplayStatics.h"

void AMatchGameMode::FindPlayersStartActorsInArena(TArray<AArenaPlayerStart*>& ResultsActors)
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),AArenaPlayerStart::StaticClass(),FoundActors);

	for (int i = 0;i<FoundActors.Num();i++)
	{
		AArenaPlayerStart* ArenaPlayerStartActor = Cast<AArenaPlayerStart>(FoundActors[i]);
		if (ArenaPlayerStartActor==false)
		{
			continue;
		}

		ResultsActors.Add(ArenaPlayerStartActor);
	}
}
