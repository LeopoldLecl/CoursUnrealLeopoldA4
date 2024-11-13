// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SmashCharacter.generated.h"

class USmashCharacterInputData;
class UInputMappingContext;
class USmashCharacterStateMachine;
class UAnimMontage;
UCLASS()
class SMASHUE_API ASmashCharacter : public ACharacter
{
	GENERATED_BODY()


#pragma region StateMachine
	public:
	void CreateStateMachine();

	void InitStateMachine();

	void TickStateMachine(float DeltaTime) const;

	protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<USmashCharacterStateMachine> StateMachine;
#pragma endregion
	

#pragma region Unreal Default
	
public:
	// Sets default values for this character's properties
	ASmashCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

#pragma endregion

#pragma region Orient

public:
	float GetOrientX() const;

	void SetOrientX(float NewOrientX);

protected:
	UPROPERTY(BluePrintReadOnly)
	float OrientX = 1.f;
	void RotateMeshUsingOrientX() const;

#pragma endregion


#pragma region Movement / Anim / State Machine
	private:

	UPROPERTY(EditDefaultsOnly, Category="Animation")
	UAnimMontage* IdleAnimMontage;
	UPROPERTY(EditDefaultsOnly, Category="Animation")
	UAnimMontage* WalkAnimMontage;
	UPROPERTY(EditDefaultsOnly, Category="Animation")
	UAnimMontage* RunAnimMontage;



	
public:
	UPROPERTY(EditDefaultsOnly, Category="Player Stats")
	float MoveSpeedMax = 600.f;
	UPROPERTY(EditDefaultsOnly, Category="Player Stats")
	float RunMoveSpeedMax = 1200.f;
	void PlayWalkAnimMontage();
	void PlayIdleAnimMontage();
	void PlayRunAnimMontage();

#pragma endregion


#pragma region InputData / Mapping context

	public:
	UPROPERTY()
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY()
	TObjectPtr<USmashCharacterInputData> InputData;

	protected:
	void SetupMappingContextIntoController();


	
#pragma endregion
	
};
