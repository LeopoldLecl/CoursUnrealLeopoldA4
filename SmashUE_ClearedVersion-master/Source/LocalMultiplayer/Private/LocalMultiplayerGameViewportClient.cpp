// Fill out your copyright notice in the Description page of Project Settings.


#include "LocalMultiplayerGameViewportClient.h"

#include "EnhancedInputSubsystems.h"
#include "LocalMultiplayerSubsystem.h"

void ULocalMultiplayerGameViewportClient::PostInitProperties()
{
	Super::PostInitProperties();

	MaxSplitscreenPlayers = 8;
	UE_LOG(LogTemp, Log, TEXT("MaxSplitscreenPlayers set to %d"), MaxSplitscreenPlayers);
}

bool ULocalMultiplayerGameViewportClient::InputKey(const FInputKeyEventArgs& EventArgs)
{
    if (EventArgs.Event == IE_Pressed) 
    {
        ULocalMultiplayerSubsystem* MultiplayerSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<ULocalMultiplayerSubsystem>();
        if (!MultiplayerSubsystem)
        {
            UE_LOG(LogTemp, Error, TEXT("LocalMultiplayerSubsystem not found."));
            return Super::InputKey(EventArgs);
        }

        const ULocalMultiplayerSettings* Settings = GetDefault<ULocalMultiplayerSettings>();
        if (!Settings)
        {
            UE_LOG(LogTemp, Error, TEXT("LocalMultiplayerSettings not found."));
            return Super::InputKey(EventArgs);
        }

        const FKey& PressedKey = EventArgs.Key;
        
        const int32 KeyboardProfileIndex = Settings->FindKeyboardProfileIndexFromKey(
            PressedKey, ELocalMultiplayerInputMappingType::InGame);

        if (KeyboardProfileIndex == -1)
        {
            UE_LOG(LogTemp, Warning, TEXT("No keyboard profile found for key %s"), *PressedKey.ToString());
            return Super::InputKey(EventArgs);
        }

        const int32 PlayerIndex = MultiplayerSubsystem->GetAssignedPlayerIndexFromKeyboardProfileIndex(KeyboardProfileIndex);

        if (PlayerIndex == -1) 
        {
            const int32 NewPlayerIndex = MultiplayerSubsystem->AssignNewPlayerToKeyboardProfile(KeyboardProfileIndex);
            UE_LOG(LogTemp, Log, TEXT("New player assigned: %d for key %s"), NewPlayerIndex, *PressedKey.ToString());
        }
    }

    return Super::InputKey(EventArgs);
}

bool ULocalMultiplayerGameViewportClient::InputAxis(FViewport* InViewport, FInputDeviceId InputDeviceId, FKey Key,float Delta, float DeltaTime, int32 NumSamples, bool bGamepad)
{
    if (bGamepad && FMath::Abs(Delta) > KINDA_SMALL_NUMBER) 
    {
        ULocalMultiplayerSubsystem* MultiplayerSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<ULocalMultiplayerSubsystem>();
        if (!MultiplayerSubsystem)
        {
            UE_LOG(LogTemp, Error, TEXT("LocalMultiplayerSubsystem not found."));
            return Super::InputAxis(InViewport, InputDeviceId, Key, Delta, DeltaTime, NumSamples, bGamepad);
        }

        int32 DeviceId = InputDeviceId.GetId(); 
        
        const int32 PlayerIndex = MultiplayerSubsystem->GetAssignedPlayerIndexFromGamePadDeviceID(DeviceId);

        if (PlayerIndex == -1)
        {
            const int32 NewPlayerIndex = MultiplayerSubsystem->AssignNewPlayerToGamePadDeviceID(DeviceId);
            UE_LOG(LogTemp, Log, TEXT("New player assigned: %d for Gamepad Device ID: %d"), NewPlayerIndex, DeviceId);
        }
    }

    return Super::InputAxis(InViewport, InputDeviceId, Key, Delta, DeltaTime, NumSamples, bGamepad);
}


