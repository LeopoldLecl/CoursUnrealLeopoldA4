// Fill out your copyright notice in the Description page of Project Settings.


#include "SmashCharacterStateMachine.h"

void USmashCharacterStateMachine::Init(ASmashCharacter* InCharacter)
{
	Character = InCharacter;
}


ASmashCharacter* USmashCharacterStateMachine::GetCharacter() const
{
	return Character;
}
