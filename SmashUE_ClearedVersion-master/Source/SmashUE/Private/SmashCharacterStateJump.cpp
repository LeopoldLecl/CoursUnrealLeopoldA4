
#include "SmashCharacterStateJump.h"
#include "SmashCharacterStateWalk.h"
#include "SmashCharacter.h"
#include "SmashCharacterStateMachine.h"
#include "SmashCharacterSettings.h"
#include "GameFramework/CharacterMovementComponent.h"

ESmashCharacterStateID USmashCharacterStateJump::GetStateID()
{
	return ESmashCharacterStateID::Jump;
}

void USmashCharacterStateJump::StateEnter(ESmashCharacterStateID PreviousStateID)
{
	Super::StateEnter(PreviousStateID);

	Character->PlayJumpAnimMontage();

	PerformJump();


	
	GEngine->AddOnScreenDebugMessage(
	-1,
	3.f,
	FColor::Green,
	TEXT("Enter StateJump")
	
);
}

void USmashCharacterStateJump::StateExit(ESmashCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);
	GEngine->AddOnScreenDebugMessage(
	-1,
	3.f,
	FColor::Red,
	TEXT("Exit StateRun")
);
}

void USmashCharacterStateJump::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);
	
	if (Character->GetCharacterMovement()->Velocity.Z <= 0.f)
	{
		StateMachine->ChangeState(ESmashCharacterStateID::Fall);
	}

	GEngine->AddOnScreenDebugMessage(
		-1,
		1.F,
		FColor::Green,
		TEXT("Jump")
	);


	
}

void USmashCharacterStateJump::PerformJump()
{
	float InitialVelocity = 2 * JumpMaxHeight / JumpDuration; //V0
	float Gravity = -2 * JumpMaxHeight / FMath::Square(JumpDuration); //Gravity

	Character->LaunchCharacter(FVector(0.f, 0.f, InitialVelocity), false, true);
	Character->GetCharacterMovement()->GravityScale = FMath::Abs(Gravity / GetWorld()->GetDefaultGravityZ());

	GEngine->AddOnScreenDebugMessage(
		-1,
		3.f,
		FColor::Blue,
		TEXT("Perform Jump")
	);
}



