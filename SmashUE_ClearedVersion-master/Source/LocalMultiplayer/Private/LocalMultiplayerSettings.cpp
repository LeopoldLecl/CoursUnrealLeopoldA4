// Fill out your copyright notice in the Description page of Project Settings.


#include "LocalMultiplayerSettings.h"

bool FLocalMultiplayerProfileData::ContainsKey(const FKey& Key, ELocalMultiplayerInputMappingType MappingType) const
{
	UInputMappingContext* MappingContext = GetIMCFromType(MappingType);
	if (MappingContext)
	{
		for (const FEnhancedActionKeyMapping& Mapping : MappingContext->GetMappings())
		{
			if (Mapping.Key == Key)
			{
				return true; 
			}
		}
	}
	return false; 
}

UInputMappingContext* FLocalMultiplayerProfileData::GetIMCFromType(ELocalMultiplayerInputMappingType MappingType) const
{
	switch (MappingType)
	{
	case InGame:
		return IMCInGame;

	case Menu:
		return IMCMenu;
	}

	return nullptr;
}

int ULocalMultiplayerSettings::GetNbKeyboardProfiles() const
{
	return KeyboardProfilesData.Num();
}

int ULocalMultiplayerSettings::FindKeyboardProfileIndexFromKey(const FKey& Key,ELocalMultiplayerInputMappingType MappingType) const
{
	for (int32 Index = 0; Index < KeyboardProfilesData.Num(); ++Index)
	{
		const FLocalMultiplayerProfileData& Profile = KeyboardProfilesData[Index];

		if (Profile.ContainsKey(Key, MappingType))
		{
			return Index; 
		}
	}
	return -1; 
}



