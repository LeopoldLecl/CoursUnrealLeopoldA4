#include "CameraWorldSubsystem.h"
#include "CameraFollowTarget.h"
#include "EngineUtils.h"

void UCameraWorldSubsystem::PostInitialize()
{
	Super::PostInitialize();
}

void UCameraWorldSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	CameraMain = FindCameraByTag(TEXT("CameraMain"));
}

void UCameraWorldSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TickUpdateCameraPosition(DeltaTime);
}

void UCameraWorldSubsystem::AddFollowTarget(AActor* FollowTarget)
{
	FollowTargets.Add(FollowTarget);
}

void UCameraWorldSubsystem::RemoveFollowTarget(AActor* FollowTarget)
{
	FollowTargets.Remove(FollowTarget);
}

void UCameraWorldSubsystem::TickUpdateCameraPosition(float DeltaTime)
{
	FVector TargetPos = CalculateAveragePositionBetweenTargets();
	
	CameraMain->SetWorldLocation(TargetPos);
}

FVector UCameraWorldSubsystem::CalculateAveragePositionBetweenTargets()
{
	float FixedY = CameraMain ? CameraMain->GetComponentLocation().Y : 0.0f;

	if (FollowTargets.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("CalculateAveragePositionBetweenTargets: Aucun acteur dans FollowTargets."));
		return FVector::ZeroVector;
	}

	FVector SumPosition = FVector::ZeroVector;
	int32 ValidTargetsCount = 0;

	for (UObject* Target : FollowTargets)
	{
		if (Target && Target->GetClass()->ImplementsInterface(UCameraFollowTarget::StaticClass()))
		{
			// Cast implicite vers l'interface pour accéder aux fonctions
			ICameraFollowTarget* Followable = Cast<ICameraFollowTarget>(Target);

			if (Followable && Followable->IsFollowable())
			{
				SumPosition += Followable->GetFollowPosition();
				ValidTargetsCount++;
			}
		}
	}

	if (ValidTargetsCount == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("CalculateAveragePositionBetweenTargets: Aucun acteur valide trouvé."));
		return FVector::ZeroVector;
	}

	FVector AveragePos = SumPosition / ValidTargetsCount;
	AveragePos.Y = FixedY; // Fixer la composante Y
	return AveragePos;
}

UCameraComponent* UCameraWorldSubsystem::FindCameraByTag(const FName& Tag) const
{
	if (!GetWorld())
	{
		UE_LOG(LogTemp, Warning, TEXT("FindCameraByTag: GetWorld() retourne nullptr."));
		return nullptr;
	}

	for (TActorIterator<AActor> ActorIt(GetWorld()); ActorIt; ++ActorIt)
	{
		AActor* Actor = *ActorIt;
		if (Actor && Actor->ActorHasTag(Tag))
		{
			UCameraComponent* CameraComponent = Actor->FindComponentByClass<UCameraComponent>();
			if (CameraComponent)
			{
				return CameraComponent;
			}
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("FindCameraByTag: Aucun UCameraComponent trouvé avec le tag %s."), *Tag.ToString());
	return nullptr;
}

