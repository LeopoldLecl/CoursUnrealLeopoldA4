// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SmashCharacterSettings.h"
#include "SmashCharacterStateID.h"
#include "GameFramework/Actor.h"
#include "SmashCharacterState.generated.h"
class USmashCharacterSettings;
class ASmashCharacter;
class USmashCharacterStateMachine;

UCLASS(Abstract)
class SMASHUE_API USmashCharacterState : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	USmashCharacterState();

	virtual ESmashCharacterStateID GetStateID();

	virtual void StateInit(USmashCharacterStateMachine* InStateMachine,const USmashCharacterSettings* InCharacterSettings);

	virtual void StateEnter(ESmashCharacterStateID PreviousStateID);

	virtual void StateExit(ESmashCharacterStateID NextStateID);

	virtual void StateTick(float DeltaTime);

	

	protected:
	UPROPERTY()
	TObjectPtr<ASmashCharacter> Character;
	UPROPERTY()
	TObjectPtr<USmashCharacterStateMachine> StateMachine;
	UPROPERTY();
	TObjectPtr<USmashCharacterSettings> CharacterSettings;
	
};
