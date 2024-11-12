
#include "SmashCharacterStateRun.h"

#include "SmashCharacter.h"
#include "GeometryCollection/GeometryCollectionParticlesData.h"
#include "GameFramework/CharacterMovementComponent.h"


ESmashCharacterStateID USmashCharacterStateRun::GetStateID()
{
	return ESmashCharacterStateID::Run;
}

void USmashCharacterStateRun::StateEnter(ESmashCharacterStateID PreviousStateID)
{
	Super::StateEnter(PreviousStateID);

	Character->PlayRunAnimMontage();

	GEngine->AddOnScreenDebugMessage(
		-1,
		3.f,
		FColor::Green,
		TEXT("Enter StateRun")
	);
}

void USmashCharacterStateRun::StateExit(ESmashCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);

	GEngine->AddOnScreenDebugMessage(
		-1,
		3.f,
		FColor::Red,
		TEXT("Exit StateRun")
	);
}

void USmashCharacterStateRun::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);

	if (Character && Character->GetCharacterMovement())
	{
		FVector CurrentVelocity = Character->GetVelocity();
		float CurrentSpeed = CurrentVelocity.Size();

		if (CurrentSpeed < Character->RunMoveSpeedMax)
		{
			FVector Direction = Character->GetActorForwardVector();
			Character->AddMovementInput(Direction, 1.0f);
		}

	}
	GEngine->AddOnScreenDebugMessage(
		-1,
		3.f,
		FColor::Green,
		TEXT("Tick State Run")
		);
}


