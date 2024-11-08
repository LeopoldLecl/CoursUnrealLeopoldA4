// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SmashCharacterStateID.h"
#include "GameFramework/Actor.h"
#include "SmashCharacterState.generated.h"
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

	virtual void StateInit(USmashCharacterState* InStateMachine);

	protected:
	UPROPERTY()
	TObjectPtr<ASmashCharacter> SmashCharacter;
	UPROPERTY()
	TObjectPtr<USmashCharacterStateMachine> StateMachine;
};