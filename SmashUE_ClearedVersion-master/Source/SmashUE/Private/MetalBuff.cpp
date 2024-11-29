// Fill out your copyright notice in the Description page of Project Settings.


#include "MetalBuff.h"

#include "SmashCharacter.h"

void UMetalBuff::OnBuffEnter(AActor* Target)
{
	Super::OnBuffEnter(Target);

	if (MetalMaterial)
	{
		Character->ChangeMaterial(MetalMaterial);
	}
}

void UMetalBuff::BuffTick(AActor* Target, float deltaTime)
{
	Super::BuffTick(Target, deltaTime);
}

void UMetalBuff::OnBuffExit(AActor* Target)
{
	Super::OnBuffExit(Target);

	if (DefaultMaterial)
	{
		Character->ChangeMaterial(DefaultMaterial);
	}
}

