// Fill out your copyright notice in the Description page of Project Settings.


#include "BuffComponent.h"


UBuffComponent::UBuffComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UBuffComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	for(UBuff* Buff : ActiveBuffs)
	{
		if(Buff)
		{
			Buff->BuffTick(GetOwner(),DeltaTime);
		}
	}

	RemoveExpiredBuff();
}

void UBuffComponent::ApplyBuff(UBuff* Buff)
{
	if (Buff)
	{
		Buff->OnBuffEnter(GetOwner());
		ActiveBuffs.Add(Buff);
	}
}

void UBuffComponent::RemoveExpiredBuff()
{
	for (int32 i =ActiveBuffs.Num()-1; i >= 0; --i)
	{
		if(ActiveBuffs[i] && ActiveBuffs[i]->isExpired())
		{
			ActiveBuffs[i]->OnBuffExit(GetOwner());
			ActiveBuffs.RemoveAt(i);
		}
	}
}

