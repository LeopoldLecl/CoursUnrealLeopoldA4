// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Buff.h"
#include "Components/ActorComponent.h"
#include "BuffComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SMASHUE_API UBuffComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TArray<UBuff*> ActiveBuffs;

public:
	UBuffComponent();

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ApplyBuff(UBuff* Buff);

	void RemoveExpiredBuff();
	

};
