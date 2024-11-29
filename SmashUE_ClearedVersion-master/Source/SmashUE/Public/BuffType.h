// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "BuffType.generated.h"

UENUM(BlueprintType)
enum EBuffType : uint8
{
	 Default UMETA(DisplayName = "Default"),
	Metal UMETA(DisplayName = "Metal"),

};
