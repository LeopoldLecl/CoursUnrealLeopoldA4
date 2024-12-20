#pragma once

#include "CoreMinimal.h"
#include "StateMachine/SmashCharacterState.h"

#include "SmashCharacterStateIdle.generated.h"  


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SMASHUE_API USmashCharacterStateIdle : public USmashCharacterState
{
	GENERATED_BODY()

public:
	virtual ESmashCharacterStateID GetStateID() override;

	UFUNCTION()
	void OnInputMoveXFast(float InputMoveX);

	UFUNCTION()
	void OnInputJump(float InputJump);
	
	virtual void StateEnter(ESmashCharacterStateID PreviousStateID) override;

	virtual void StateExit(ESmashCharacterStateID NextStateID) override;

	virtual void StateTick(float DeltaTime) override;


	private:
	UPROPERTY()
	bool bIsPlayingMontage;
};


