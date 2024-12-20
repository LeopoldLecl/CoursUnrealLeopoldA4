// Fill out your copyright notice in the Description page of Project Settings.


#include "SmashCharacterState.h"

#include "SmashCharacterSettings.h"
#include "SmashCharacterStateID.h"
#include "SmashCharacterStateMachine.h"


// Sets default values
USmashCharacterState::USmashCharacterState()
{
 	PrimaryComponentTick.bCanEverTick = false;
}

ESmashCharacterStateID USmashCharacterState::GetStateID()
{
	return ESmashCharacterStateID::None;
}

void USmashCharacterState::StateInit(USmashCharacterStateMachine* InStateMachine,const USmashCharacterSettings* InCharacterSettings)
{
	StateMachine = InStateMachine;
	Character = InStateMachine->GetCharacter();
	CharacterSettings = const_cast<USmashCharacterSettings*>(InCharacterSettings);
	
	GEngine->AddOnScreenDebugMessage(
		-1,
		3.f,
		FColor::Red,
		FString::Printf(TEXT("Init State %d"),GetStateID())
	);
}




void USmashCharacterState::StateEnter(ESmashCharacterStateID PreviousStateID)
{
	
}

void USmashCharacterState::StateExit(ESmashCharacterStateID NextStateID)
{
	
}

void USmashCharacterState::StateTick(float DeltaTime)
{
}






