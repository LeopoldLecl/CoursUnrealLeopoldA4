// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Buff.h"
#include "MetalBuff.generated.h"


UCLASS()
class SMASHUE_API UMetalBuff : public UBuff
{
	GENERATED_BODY()

public:
	virtual void OnBuffEnter(AActor* Target) override;
	virtual void BuffTick(AActor* Target, float deltaTime) override;
	virtual void OnBuffExit(AActor* Target) override;

	
	UPROPERTY(EditDefaultsOnly, Category="Materials")
	UMaterial* DefaultMaterial;
	UPROPERTY(EditDefaultsOnly, Category="Materials")
	UMaterial* MetalMaterial;
	
};
