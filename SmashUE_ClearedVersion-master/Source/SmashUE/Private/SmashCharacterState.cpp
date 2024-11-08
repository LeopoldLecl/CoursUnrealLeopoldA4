// Fill out your copyright notice in the Description page of Project Settings.


#include "SmashCharacterState.h"

#include "SmashCharacterStateID.h"

// Sets default values
USmashCharacterState::USmashCharacterState()
{
 	PrimaryComponentTick.bCanEverTick = false;
}

ESmashCharacterStateID USmashCharacterState::GetStateID()
{
	return ESmashCharacterStateID::None;
}

void USmashCharacterState::StateInit(USmashCharacterState* InStateMachine)
{
	
}




