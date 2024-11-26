// Fill out your copyright notice in the Description page of Project Settings.


#include "LocalMultiplayerGameViewportClient.h"

void ULocalMultiplayerGameViewportClient::PostInitProperties()
{
	Super::PostInitProperties();

	MaxSplitscreenPlayers = 8;
	UE_LOG(LogTemp, Log, TEXT("MaxSplitscreenPlayers set to %d"), MaxSplitscreenPlayers);
}

bool ULocalMultiplayerGameViewportClient::InputKey(const FInputKeyEventArgs& EventArgs)
{
	// Super pour gérer l'entrée de base
	if (Super::InputKey(EventArgs))
	{
		return true;
	}

	// Détection de l'entrée clavier ou manette
	FKey Key = EventArgs.Key;
	FInputDeviceId DeviceId = EventArgs.InputDeviceId;

	if (Key.IsGamepadKey())
	{
		UE_LOG(LogTemp, Log, TEXT("Gamepad key detected: %s on DeviceId %d"), *Key.GetFName().ToString(), DeviceId.GetId());

		// Assigner un PlayerIndex pour ce DeviceId
		// Exemple : liaison entre l'identifiant et un PlayerIndex à travers le système
		// Appel à une méthode dans votre Subsystem pour gérer cette logique
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Keyboard key detected: %s"), *Key.GetFName().ToString());

		// Gestion des touches clavier pour attribuer des PlayerIndex
	}

	return true;}

bool ULocalMultiplayerGameViewportClient::InputAxis(FViewport* InViewport, FInputDeviceId InputDeviceId, FKey Key,float Delta, float DeltaTime, int32 NumSamples, bool bGamepad)
{
	if (Super::InputAxis(InViewport, InputDeviceId, Key, Delta, DeltaTime, NumSamples, bGamepad))
	{
		return true;
	}

	if (bGamepad)
	{
		UE_LOG(LogTemp, Log, TEXT("Gamepad axis detected: %s with Delta: %f on DeviceId %d"), *Key.GetFName().ToString(), Delta, InputDeviceId.GetId());

		// Logique pour lier cet axe à un PlayerIndex
		// Exemple : récupérer ou assigner un joueur à ce périphérique
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Keyboard axis detected: %s with Delta: %f"), *Key.GetFName().ToString(), Delta);

		// Logique pour gérer les axes clavier, si applicable
	}

	return true;}


