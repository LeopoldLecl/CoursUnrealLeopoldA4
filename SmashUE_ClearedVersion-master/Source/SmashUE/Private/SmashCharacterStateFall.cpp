
#include "SmashCharacterStateFall.h"

#include "SmashCharacter.h"


ESmashCharacterStateID USmashCharacterStateFall::GetStateID()
{
	return Super::GetStateID();
}

void USmashCharacterStateFall::StateEnter(ESmashCharacterStateID PreviousStateID)
{
	Super::StateEnter(PreviousStateID);

	Character->PlayJumpAnimMontage();
}

void USmashCharacterStateFall::StateExit(ESmashCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);
}

void USmashCharacterStateFall::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);
}
