// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BuffType.h"
#include "SmashCharacter.h"
#include "UObject/Object.h"
#include "Buff.generated.h"


UCLASS()
class SMASHUE_API UBuff : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Buff")
	TEnumAsByte<EBuffType> BuffType;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category="Buff")
	float Duration;

	float TimeElapsed;



public:
	UBuff();

	virtual void Initialize(EBuffType InBuffType, float Induration, ASmashCharacter* InCharacter);

	virtual void OnBuffEnter(AActor* Target);

	virtual void BuffTick(AActor* Target,float deltaTime);

	virtual void OnBuffExit(AActor* Target);

	bool isExpired() const;

	TObjectPtr<ASmashCharacter> Character;

};
