#include "SmashCharacterStateWalk.h"

#include "SmashCharacter.h"
#include "SmashCharacterStateMachine.h"
#include "GeometryCollection/GeometryCollectionParticlesData.h"
#include "GameFramework/CharacterMovementComponent.h"

ESmashCharacterStateID USmashCharacterStateWalk::GetStateID()
{
	return ESmashCharacterStateID::Walk;
}

void USmashCharacterStateWalk::StateEnter(ESmashCharacterStateID PreviousStateID)
{
	Super::StateEnter(PreviousStateID);

	Character->PlayWalkAnimMontage();

	GEngine->AddOnScreenDebugMessage(
		-1,
		3.f,
		FColor::Green,
		TEXT("Enter StateWalk")
	);
}

void USmashCharacterStateWalk::StateExit(ESmashCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);

	GEngine->AddOnScreenDebugMessage(
		-1,
		3.f,
		FColor::Red,
		TEXT("Exit StateWalk")
	);
}

void USmashCharacterStateWalk::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);

	// if (Character && Character->GetCharacterMovement())
	// {
	// 	FVector CurrentVelocity = Character->GetVelocity();
	// 	float CurrentSpeed = CurrentVelocity.Size();
	//
	// 	if (CurrentSpeed < Character->MoveSpeedMax)
	// 	{
	// 		FVector Direction = Character->GetActorForwardVector();
	// 		Character->AddMovementInput(Direction, 1.0f);
	// 	}
	//
	// }
	GEngine->AddOnScreenDebugMessage(
		-1,
		3.f,
		FColor::Green,
		TEXT("Tick State Walk")
		);

	if(FMath::Abs(Character->GetInputMoveX())<0.1f)
	{
		StateMachine->ChangeState(ESmashCharacterStateID::Idle);
	}
	else
	{
		Character->SetOrientX(Character->GetInputMoveX());
		Character->AddMovementInput(FVector::ForwardVector,Character->GetOrientX());
	}
}
