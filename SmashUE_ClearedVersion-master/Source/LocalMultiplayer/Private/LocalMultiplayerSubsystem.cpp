// Fill out your copyright notice in the Description page of Project Settings.


#include "LocalMultiplayerSubsystem.h"

#include "EnhancedInputSubsystems.h"

void ULocalMultiplayerSubsystem::CreateAndInitPlayer(ELocalMultiplayerInputMappingType MappingType)
{
	const ULocalMultiplayerSettings* Settings = GetDefault<ULocalMultiplayerSettings>();
	if (!Settings)
	{
		UE_LOG(LogTemp, Error, TEXT("LocalMultiplayerSettings not found."));
		return;
	}

	for (int i = 0; i < Settings->GetNbKeyboardProfiles(); ++i)
	{
		AssignNewPlayerToKeyboardProfile(i);
	}

	for (int i = 0; i < Settings->NbMaxGamepads; ++i)
	{
		AssignPlayerToGamePadDeviceID(i);
	}
}

int ULocalMultiplayerSubsystem::GetAssignedPlayerIndexFromKeyboardProfileIndex(int KeyboardProfileIndex)
{
	if (PlayerIndexFromKeyboardProfileIndex.Contains(KeyboardProfileIndex))
	{
		return PlayerIndexFromKeyboardProfileIndex[KeyboardProfileIndex];
	}
	return -1; 
}

int ULocalMultiplayerSubsystem::AssignNewPlayerToKeyboardProfile(int KeyboardProfileIndex)
{
	if (PlayerIndexFromKeyboardProfileIndex.Contains(KeyboardProfileIndex))
	{
		UE_LOG(LogTemp, Warning, TEXT("Keyboard profile %d is already assigned."), KeyboardProfileIndex);
		return PlayerIndexFromKeyboardProfileIndex[KeyboardProfileIndex];
	}

	int NewPlayerIndex = LastAssignedPlayerIndex++;
	PlayerIndexFromKeyboardProfileIndex.Add(KeyboardProfileIndex, NewPlayerIndex);

	return NewPlayerIndex;
}

void ULocalMultiplayerSubsystem::AssignKeyboardMapping(int PlayerIndex, int KeyProfileIndex,ELocalMultiplayerInputMappingType MappingType) const
{
	const ULocalMultiplayerSettings* Settings = GetDefault<ULocalMultiplayerSettings>();
	if (!Settings)
	{
		UE_LOG(LogTemp, Error, TEXT("LocalMultiplayerSettings not found."));
		return;
	}

	APlayerController* PlayerController = GetGameInstance()->GetFirstLocalPlayerController();
	if (!PlayerController || PlayerIndex < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid PlayerIndex or PlayerController."));
		return;
	}

	const FLocalMultiplayerProfileData& Profile = Settings->KeyboardProfilesData[KeyProfileIndex];
	UInputMappingContext* IMC = Profile.GetIMCFromType(MappingType);

	if (IMC)
	{
		UEnhancedInputLocalPlayerSubsystem* InputSubsystem = PlayerController->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
		InputSubsystem->AddMappingContext(IMC, 1);
		UE_LOG(LogTemp, Log, TEXT("Mapping context assigned for Player %d with Keyboard Profile %d."), PlayerIndex, KeyProfileIndex);
	}
}

int ULocalMultiplayerSubsystem::GetAssignedPlayerIndexFromGamePadDeviceID(int DeviceID)
{
	if (PlayerIndexFromGamepadProfileIndex.Contains(DeviceID))
	{
		return PlayerIndexFromGamepadProfileIndex[DeviceID];
	}
	return -1;
}

int ULocalMultiplayerSubsystem::AssignPlayerToGamePadDeviceID(int DeviceID)
{
	if (PlayerIndexFromGamepadProfileIndex.Contains(DeviceID))
	{
		UE_LOG(LogTemp, Warning, TEXT("Gamepad Device %d is already assigned."), DeviceID);
		return PlayerIndexFromGamepadProfileIndex[DeviceID];
	}

	int NewPlayerIndex = LastAssignedPlayerIndex++;
	PlayerIndexFromGamepadProfileIndex.Add(DeviceID, NewPlayerIndex);

	UE_LOG(LogTemp, Log, TEXT("Assigned Player %d to Gamepad Device %d."), NewPlayerIndex, DeviceID);
	return NewPlayerIndex;
}

void ULocalMultiplayerSubsystem::AssignGamepadInputMapping(int PlayerIndex,ELocalMultiplayerInputMappingType MappingType) const
{
	const ULocalMultiplayerSettings* Settings = GetDefault<ULocalMultiplayerSettings>();
	if (!Settings)
	{
		UE_LOG(LogTemp, Error, TEXT("LocalMultiplayerSettings not found."));
		return;
	}

	APlayerController* PlayerController = GetGameInstance()->GetFirstLocalPlayerController();
	if (!PlayerController || PlayerIndex < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid PlayerIndex or PlayerController."));
		return;
	}

	const FLocalMultiplayerProfileData& GamepadProfile = Settings->GamepadProfileData;
	UInputMappingContext* IMC = GamepadProfile.GetIMCFromType(MappingType);

	if (IMC)
	{
		UEnhancedInputLocalPlayerSubsystem* InputSubsystem = PlayerController->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
		InputSubsystem->AddMappingContext(IMC, 1);

		UE_LOG(LogTemp, Log, TEXT("Gamepad mapping context assigned for Player %d."), PlayerIndex);
	}
}






