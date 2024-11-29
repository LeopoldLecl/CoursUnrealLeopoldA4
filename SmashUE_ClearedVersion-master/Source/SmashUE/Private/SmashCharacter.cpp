// Fill out your copyright notice in the Description page of Project Settings.


#include "SmashCharacter.h"

#include "BuffComponent.h"
#include "CameraWorldSubsystem.h"
#include "EnhancedInputSubsystems.h"
#include "SmashCharacterInputData.h"
#include "EnhancedInputComponent.h"
#include "MetalBuff.h"
#include "SmashCharacterState.h"
#include "SmashCharacterStateMachine.h"

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

void ASmashCharacter::ApplyMetalBuff()
{
	UMetalBuff* NewBuff = NewObject<UMetalBuff>();
	NewBuff->Initialize(EBuffType::Metal, 10.0f, this);
	BuffComponent->ApplyBuff(NewBuff);
}


void ASmashCharacter::ChangeMaterial(UMaterialInterface* NewMaterial)
{
	if (NewMaterial && GetMesh())
	{
		// Change le matériau de l'index 0 (par défaut, c'est souvent l'index principal)
		GetMesh()->SetMaterial(0, NewMaterial);
	}
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
	BuffComponent = CreateDefaultSubobject<UBuffComponent>(TEXT("BuffComponent"));
	//ApplyMetalBuff();
	GetWorld()->GetSubsystem<UCameraWorldSubsystem>()->AddFollowTarget(this);
}

// Called every frame
void ASmashCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TickStateMachine(DeltaTime);
	RotateMeshUsingOrientX();
}

// Called to bind functionality to input
void ASmashCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	SetupMappingContextIntoController();

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if(EnhancedInputComponent == nullptr) return;

	BindInputMoveXAxisAndActions(EnhancedInputComponent);
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

void ASmashCharacter::PlayJumpAnimMontage()
{
	PlayAnimMontage(JumpAnimMontage);
}

void ASmashCharacter::PlayFallAnimMontage()
{
	PlayAnimMontage(FallAnimMontage);
}

void ASmashCharacter::SetupMappingContextIntoController()
{
	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	if(PlayerController == nullptr) return;

	ULocalPlayer* Player = PlayerController->GetLocalPlayer();
	if(Player == nullptr) return;

	UEnhancedInputLocalPlayerSubsystem* InputSystem = Player->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	if(InputSystem == nullptr) return;

	InputSystem->AddMappingContext(InputMappingContext,0);
}

float ASmashCharacter::GetInputMoveX() const
{
	return  InputMoveX;
}

float ASmashCharacter::GetInputMoveY() const
{
	return InputJump;
}

void ASmashCharacter::OnInputMoveXFast(const FInputActionValue& InputActionValue)
{
	InputMoveX = InputActionValue.Get<float>();
	InputMoveXFastEvent.Broadcast(InputMoveX);
}

void ASmashCharacter::BindInputMoveXAxisAndActions(UEnhancedInputComponent* EnhancedInputComponent)
{
	if(InputData == nullptr) return;

	if(InputData->InputActionMoveX)
	{
		EnhancedInputComponent->BindAction(
			InputData->InputActionMoveX,
			ETriggerEvent::Started,
			this,
			&ASmashCharacter::OnInputMoveX);

		EnhancedInputComponent->BindAction(
			InputData->InputActionMoveX,
			ETriggerEvent::Triggered,
			this,
			&ASmashCharacter::OnInputMoveX);

		EnhancedInputComponent->BindAction(
			InputData->InputActionMoveX,
			ETriggerEvent::Completed,
			this,
			&ASmashCharacter::OnInputMoveX);
	}

	if(InputData->InputActionMoveXFast)
	{
		EnhancedInputComponent->BindAction(
			InputData->InputActionMoveXFast,
			ETriggerEvent::Triggered,
			this,
			&ASmashCharacter::OnInputMoveXFast);
	}

	if(InputData->InputActionJump)
	{
		EnhancedInputComponent->BindAction(
			InputData->InputActionJump,
			ETriggerEvent::Started,
			this,
			&ASmashCharacter::OnInputJump
		);
	}

	
}

void ASmashCharacter::OnInputMoveX(const FInputActionValue& InputActionValue)
{
		InputMoveX = InputActionValue.Get<float>();
}

void ASmashCharacter::OnInputJump(const FInputActionValue& InputActionValue)
{
	InputJump = InputActionValue.Get<bool>();
	InputJumpEvent.Broadcast(InputJump);
}

FVector ASmashCharacter::GetFollowPosition()
{
	return GetActorLocation();
}

bool ASmashCharacter::IsFollowable()
{
	return true;
}


