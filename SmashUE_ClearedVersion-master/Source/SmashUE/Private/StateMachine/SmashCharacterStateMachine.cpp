// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachine/SmashCharacterStateMachine.h"

#include "SmashCharacter.h"
#include "SmashCharacterState.h"

void USmashCharacterStateMachine::Init(ASmashCharacter* InCharacter)
{
	Character = InCharacter;
	FindStates();
	InitStates();

	ChangeState(ESmashCharacterStateID::Idle);
}

void USmashCharacterStateMachine::Tick(float DeltaTime)
{
	if(CurrentState == nullptr)
	{
		return;
	}
	CurrentState->StateTick(DeltaTime);
}


ASmashCharacter* USmashCharacterStateMachine::GetCharacter() const
{
	return Character;
}

void USmashCharacterStateMachine::ChangeState(ESmashCharacterStateID NextStateID)
{
	USmashCharacterState* NextState = GetState(NextStateID);
	//DO nothing if nextState not found
	if (NextState==nullptr)
	{
		return;
	}

	if(CurrentState != nullptr)
	{
		CurrentState->StateExit(NextStateID);
	}

	ESmashCharacterStateID PreviousStateID = CurrentStateID;
	CurrentStateID = NextStateID;
	CurrentState = NextState;

	if(CurrentState != nullptr)
	{
		CurrentState->StateEnter(PreviousStateID);
	}
}


USmashCharacterState* USmashCharacterStateMachine::GetState(ESmashCharacterStateID StateID)
{
	for(USmashCharacterState* State : AllStates)
	{
		if(StateID == State->GetStateID())
		{
			return State;
		}
	}
	return nullptr;
}



void USmashCharacterStateMachine::FindStates()
{
	TArray<UActorComponent*> FoundComponents= Character->K2_GetComponentsByClass(UActorComponent::StaticClass());
	for (UActorComponent* StateComponent : FoundComponents)
	{
		USmashCharacterState* State = Cast<USmashCharacterState>(StateComponent);
		if (State==nullptr)
		{
			continue;
		}
		if (State->GetStateID()== ESmashCharacterStateID::None)
		{
			continue;
		}

		AllStates.Add(State);
	}
}

void USmashCharacterStateMachine::InitStates()
{
	const USmashCharacterSettings* Settings = GetDefault<USmashCharacterSettings>();
	for (USmashCharacterState* State : AllStates)
	{
		State->StateInit(this,Settings);
	}
}
