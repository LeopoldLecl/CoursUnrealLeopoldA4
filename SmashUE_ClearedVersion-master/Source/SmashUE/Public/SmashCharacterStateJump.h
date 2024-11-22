// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SmashCharacterState.h"
#include "SmashCharacterStateJump.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SMASHUE_API USmashCharacterStateJump : public USmashCharacterState
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, Category="Jump")
	float JumpWalkSpeed = 400.f;
	UPROPERTY(EditDefaultsOnly, Category="Jump")
	float JumpMaxHeight = 280.f;
	UPROPERTY(EditDefaultsOnly, Category="Jump")
	float JumpDuration = 1.f;
	UPROPERTY(EditDefaultsOnly, Category="Jump")
	float JumpAirControl = 1.f;

	
	virtual ESmashCharacterStateID GetStateID() override;

	UFUNCTION()

	virtual void StateEnter(ESmashCharacterStateID PreviousStateID) override;

	virtual void StateExit(ESmashCharacterStateID NextStateID) override;

	virtual void StateTick(float DeltaTime) override;

	private:
	void PerformJump();
};
