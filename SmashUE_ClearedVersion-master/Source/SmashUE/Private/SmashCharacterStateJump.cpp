
#include "SmashCharacterStateJump.h"
#include "SmashCharacterStateWalk.h"
#include "SmashCharacter.h"
#include "SmashCharacterStateMachine.h"
#include "SmashCharacterSettings.h"

ESmashCharacterStateID USmashCharacterStateJump::GetStateID()
{
	return ESmashCharacterStateID::Jump;
}

void USmashCharacterStateJump::StateEnter(ESmashCharacterStateID PreviousStateID)
{
	Super::StateEnter(PreviousStateID);

	Character->PlayJumpAnimMontage();

	
}

void USmashCharacterStateJump::StateExit(ESmashCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);
	
}

void USmashCharacterStateJump::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);

	GEngine->AddOnScreenDebugMessage(
	-1,
	3.f,
	FColor::Green,
	TEXT("Tick Jump")
	);
}
