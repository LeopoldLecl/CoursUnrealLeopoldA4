
#include "SmashCharacterStateFall.h"

#include "SmashCharacter.h"
#include "SmashCharacterStateMachine.h"
#include "GameFramework/CharacterMovementComponent.h"


ESmashCharacterStateID USmashCharacterStateFall::GetStateID()
{
	return ESmashCharacterStateID::Fall;
}

void USmashCharacterStateFall::StateEnter(ESmashCharacterStateID PreviousStateID)
{
	Super::StateEnter(PreviousStateID);

	Character->GetCharacterMovement()->GravityScale = FallGravityScale;
	Character->PlayFallAnimMontage();

	GEngine->AddOnScreenDebugMessage(
		-1,
		3.f,
		FColor::Blue,
		TEXT("Entering Fall State")
	);
}

void USmashCharacterStateFall::StateExit(ESmashCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);
}

void USmashCharacterStateFall::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);

	if (Character->IsFallingFast())
	{
		Character->GetCharacterMovement()->GravityScale = FallFastGravityScale;
	}

	if (Character->GetCharacterMovement()->IsMovingOnGround())
	{
		StateMachine->ChangeState(ESmashCharacterStateID::Idle);
	}

	GEngine->AddOnScreenDebugMessage(
		-1,
		DeltaTime,
		FColor::Yellow,
		TEXT("Falling...")
	);}

bool ASmashCharacter::IsFallingFast() const
{
	return GetInputAxisValue("FastFall") > 0.1f; // Par exemple, en lisant une entrée utilisateur
}
