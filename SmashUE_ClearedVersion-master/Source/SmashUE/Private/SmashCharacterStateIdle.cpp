

#include "SmashCharacterStateIdle.h"

#include "SmashCharacter.h"
#include "SmashCharacterStateMachine.h"


ESmashCharacterStateID USmashCharacterStateIdle::GetStateID()
{
	return ESmashCharacterStateID::Idle;
}

void USmashCharacterStateIdle::StateEnter(ESmashCharacterStateID PreviousStateID)
{
	Super::StateEnter(PreviousStateID);

	Character->PlayIdleAnimMontage();

	GEngine->AddOnScreenDebugMessage(
	-1,
	3.f,
	FColor::Green,
	TEXT("Enter StateIdle")
	);
}

void USmashCharacterStateIdle::StateExit(ESmashCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);

	GEngine->AddOnScreenDebugMessage(
		-1,
		3.f,
		FColor::Red,
		TEXT("Exit StateIdle")
		);
}

void USmashCharacterStateIdle::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);

	GEngine->AddOnScreenDebugMessage(
		-1,
		3.f,
		FColor::Green,
		TEXT("Tick StateIdle")
		);

	if(FMath::Abs(Character->GetInputMoveX())>0.1f)
	{
	StateMachine->ChangeState(ESmashCharacterStateID::Walk);
	}
}





