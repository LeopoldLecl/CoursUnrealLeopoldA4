// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SmashCharacterState.h"
#include "SmashCharacterStateFall.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SMASHUE_API USmashCharacterStateFall : public USmashCharacterState
{
	GENERATED_BODY()

	public:

	UPROPERTY(EditDefaultsOnly, Category="Fall")
	float FallHorizontalMoveSpeed = 400.f;
	UPROPERTY(EditDefaultsOnly, Category="Fall")
	float FallVAirControl = 1.f;
	UPROPERTY(EditDefaultsOnly, Category="Fall")
	float FallGravityScale = 9.8f;
	UPROPERTY(EditDefaultsOnly, Category="Fall")
	float FallFastGravityScale = 20.f;
	




	
	virtual ESmashCharacterStateID GetStateID() override;

	UFUNCTION()
	virtual void StateEnter(ESmashCharacterStateID PreviousStateID) override;

	virtual void StateExit(ESmashCharacterStateID NextStateID) override;

	virtual void StateTick(float DeltaTime) override;
};
