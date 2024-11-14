#include "SmashCharacterStateWalk.h"

#include "SmashCharacter.h"
#include "SmashCharacterStateMachine.h"
#include "SmashCharacterSettings.h"
#include "GeometryCollection/GeometryCollectionParticlesData.h"
#include "GameFramework/CharacterMovementComponent.h"

ESmashCharacterStateID USmashCharacterStateWalk::GetStateID()
{
	return ESmashCharacterStateID::Walk;
}

void USmashCharacterStateWalk::OnInputMoveXFast(float InputMoveX)
{
	StateMachine->ChangeState(ESmashCharacterStateID::Walk);
}

void USmashCharacterStateWalk::StateEnter(ESmashCharacterStateID PreviousStateID)
{
	Super::StateEnter(PreviousStateID);

	Character->PlayWalkAnimMontage();

	Character->InputMoveXFastEvent.AddDynamic(this,&USmashCharacterStateWalk::OnInputMoveXFast);
}

void USmashCharacterStateWalk::StateExit(ESmashCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);

	Character->InputMoveXFastEvent.RemoveDynamic(this,&USmashCharacterStateWalk::OnInputMoveXFast);

}

void USmashCharacterStateWalk::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);

	float InputMoveXThreshold = GetDefault<USmashCharacterSettings>()->InputMoveXThreshold;
	GEngine->AddOnScreenDebugMessage(
		-1,
		3.f,
		FColor::Green,
		TEXT("Tick State Walk")
		);

	if(FMath::Abs(Character->GetInputMoveX())<InputMoveXThreshold)
	{
		StateMachine->ChangeState(ESmashCharacterStateID::Idle);
	}
	else
	{
		Character->SetOrientX(Character->GetInputMoveX());
		Character->AddMovementInput(FVector::ForwardVector,Character->GetOrientX());
	}
}
