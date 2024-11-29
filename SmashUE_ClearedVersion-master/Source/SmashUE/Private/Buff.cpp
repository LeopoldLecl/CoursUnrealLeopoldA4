// Fill out your copyright notice in the Description page of Project Settings.


#include "Buff.h"

UBuff::UBuff() : BuffType(EBuffType::Metal),Duration(10.0f),TimeElapsed(0.0f)
{
	
}

void UBuff::Initialize(EBuffType InBuffType, float Induration,ASmashCharacter* InCharacter)
{
	BuffType = InBuffType;
	Duration = Induration;
	TimeElapsed = 0.0f;
	Character = InCharacter;
}

void UBuff::OnBuffEnter(AActor* Target)
{
}

void UBuff::BuffTick(AActor* Target, float deltaTime)
{
	TimeElapsed += deltaTime;
}

void UBuff::OnBuffExit(AActor* Target)
{
}

bool UBuff::isExpired() const
{
	return TimeElapsed >= Duration;
}


