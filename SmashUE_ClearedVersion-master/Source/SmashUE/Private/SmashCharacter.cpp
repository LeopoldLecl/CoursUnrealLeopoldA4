// Fill out your copyright notice in the Description page of Project Settings.


#include "SmashCharacter.h"

#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "StateMachine/SmashCharacterStateMachine.h"

void ASmashCharacter::CreateStateMachine()
{
	StateMachine = NewObject<USmashCharacterStateMachine>(this);
}

void ASmashCharacter::InitStateMachine()
{
	if(StateMachine==nullptr)
	{
		return;
	}
	StateMachine->Init(this);
}

void ASmashCharacter::TickStateMachine(float DeltaTime) const
{
	if(StateMachine==nullptr)
	{
		return;
	}
	StateMachine->Tick(DeltaTime);
}

// Sets default values
ASmashCharacter::ASmashCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASmashCharacter::BeginPlay()
{
	Super::BeginPlay();
	CreateStateMachine();
	InitStateMachine();

}

// Called every frame
void ASmashCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TickStateMachine(DeltaTime);
	RotateMeshUsingOrientX();
}



float ASmashCharacter::GetOrientX() const
{
	return OrientX;
}

void ASmashCharacter::SetOrientX(float NewOrientX)
{
	OrientX = NewOrientX;
}

void ASmashCharacter::RotateMeshUsingOrientX() const
{
	FRotator Rotation = GetMesh()->GetRelativeRotation();
	Rotation.Yaw = -90.f * OrientX;
	GetMesh()->SetRelativeRotation(Rotation);
}

void ASmashCharacter::PlayWalkAnimMontage()
{
	PlayAnimMontage(WalkAnimMontage);
}

void ASmashCharacter::PlayIdleAnimMontage()
{
	PlayAnimMontage(IdleAnimMontage);
}

void ASmashCharacter::PlayRunAnimMontage()
{
	PlayAnimMontage(RunAnimMontage);
}

void ASmashCharacter::SetupMappingContextIntoController() const
{
	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	if(PlayerController== nullptr)
	{
		return;
	}

	ULocalPlayer* Player = PlayerController->GetLocalPlayer();
	if(Player == nullptr)
	{
		return;
	}

	UEnhancedInputLocalPlayerSubsystem* InputSystem = Player->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	if(InputSystem == nullptr)
	{
		return;
	}
	InputSystem->AddMappingContext(InputMappingContext,0);
}

void ASmashCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	SetupMappingContextIntoController();
}

// void USmashCharacterState::StateInit(USmashCharacterState* InStateMachine)
// {
// 		StateMachine = InStateMachine;
// }

