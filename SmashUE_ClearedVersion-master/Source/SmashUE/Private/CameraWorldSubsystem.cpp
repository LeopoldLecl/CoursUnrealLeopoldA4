#include "CameraWorldSubsystem.h"
#include "CameraFollowTarget.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"

void UCameraWorldSubsystem::PostInitialize()
{
	Super::PostInitialize();
}

void UCameraWorldSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);

	CameraMain = FindCameraByTag(TEXT("CameraMain"));

	AActor* CameraBoundsActor = FindCameraBoundsActor();
	if (CameraBoundsActor)
	{
		InitCameraBounds(CameraBoundsActor);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("OnWorldBeginPlay: Aucun CameraBoundsActor trouvé."));
	}	
	
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
	
	TargetPos.X = FMath::Clamp(TargetPos.X, CameraBoundsMin.X, CameraBoundsMax.X);
	TargetPos.Z = FMath::Clamp(TargetPos.Z, CameraBoundsMin.Y, CameraBoundsMax.Y);
	
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
	AveragePos.Y = FixedY; 
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

AActor* UCameraWorldSubsystem::FindCameraBoundsActor()
{
	if (!GetWorld())
	{
		UE_LOG(LogTemp, Warning, TEXT("FindCameraBoundsActor: GetWorld() retourne nullptr."));
		return nullptr;
	}

	for (TActorIterator<AActor> ActorIt(GetWorld()); ActorIt; ++ActorIt)
	{
		AActor* Actor = *ActorIt;
		if (Actor && Actor->ActorHasTag(TEXT("CameraBounds"))) 
		{
			return Actor;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("FindCameraBoundsActor: Aucun acteur trouvé avec le tag 'CameraBounds'."));
	return nullptr;


}

void UCameraWorldSubsystem::InitCameraBounds(AActor* CameraBoundsActor)
{
	if (!CameraBoundsActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("InitCameraBounds: CameraBoundsActor est nul."));
		return;
	}

	FVector BoundsCenter;
	FVector BoundsExtent;
	CameraBoundsActor->GetActorBounds(false, BoundsCenter, BoundsExtent);

	CameraBoundsMin = FVector2D(BoundsCenter.X - BoundsExtent.X, BoundsCenter.Z - BoundsExtent.Z);
	CameraBoundsMax = FVector2D(BoundsCenter.X + BoundsExtent.X, BoundsCenter.Z + BoundsExtent.Z);

	CameraBoundsYProjectionCenter = BoundsCenter.Y;

	UE_LOG(LogTemp, Log, TEXT("InitCameraBounds: BoundsMin=(%f, %f), BoundsMax=(%f, %f), YProjectionCenter=%f"),
		CameraBoundsMin.X, CameraBoundsMin.Y, CameraBoundsMax.X, CameraBoundsMax.Y, CameraBoundsYProjectionCenter);
}

void UCameraWorldSubsystem::ClampPositionIntoCameraBounds(FVector2d& OutViewPortBoundsMin,
	FVector2d& OutViewPortBoundsMax)
{
	FVector2D ViewPortBoundsMin, ViewPortBoundsMax;
	GetViewportBounds(ViewPortBoundsMin, ViewPortBoundsMax);

	FVector WorldBoundsMin = CalculateWorldPositionFromViewPortPosition(ViewPortBoundsMin);
	FVector WorldBoundsMax = CalculateWorldPositionFromViewPortPosition(ViewPortBoundsMax);

	FVector2D CameraBoundsOffset = FVector2D(
		FMath::Abs((WorldBoundsMax.X - WorldBoundsMin.X) / 2),
		FMath::Abs((WorldBoundsMax.Z - WorldBoundsMin.Z) / 2)
	);

	FVector2D ClampedMin = CameraBoundsMin + CameraBoundsOffset;
	FVector2D ClampedMax = CameraBoundsMax - CameraBoundsOffset;

	WorldBoundsMin.X = FMath::Clamp(WorldBoundsMin.X, ClampedMin.X, ClampedMax.X);
	WorldBoundsMin.Z = FMath::Clamp(WorldBoundsMin.Z, ClampedMin.Y, ClampedMax.Y);

	WorldBoundsMax.X = FMath::Clamp(WorldBoundsMax.X, ClampedMin.X, ClampedMax.X);
	WorldBoundsMax.Z = FMath::Clamp(WorldBoundsMax.Z, ClampedMin.Y, ClampedMax.Y);

	OutViewPortBoundsMin = FVector2D(WorldBoundsMin.X, WorldBoundsMin.Z);
	OutViewPortBoundsMax = FVector2D(WorldBoundsMax.X, WorldBoundsMax.Z);
}


void UCameraWorldSubsystem::GetViewportBounds(FVector2D& OutViewportBoundsMin, FVector2D& OutViewportBoundsMax)
{
	UGameViewportClient* ViewportClient = GetWorld()->GetGameViewport();
	if(ViewportClient == nullptr) return;

	FViewport* Viewport = ViewportClient->Viewport;
	if(Viewport == nullptr) return;

	FIntRect ViewRect(
		Viewport->GetInitialPositionXY(),
		Viewport->GetInitialPositionXY() + Viewport->GetSizeXY()
		);
	FIntRect ViewportRect = Viewport->CalculateViewExtents(CameraMain->AspectRatio,ViewRect);

	OutViewportBoundsMin.X = ViewportRect.Min.X;
	OutViewportBoundsMin.Y = ViewportRect.Min.Y;

	OutViewportBoundsMax.X = ViewportRect.Max.X;
	OutViewportBoundsMax.Y = ViewportRect.Max.Y;
}

FVector UCameraWorldSubsystem::CalculateWorldPositionFromViewPortPosition(const FVector2d& ViewPortPosition)
{
	if(CameraMain == nullptr) return FVector::Zero();

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(),0);
	if(PlayerController == nullptr) return FVector::Zero();

	float YDistanceToCenter = CameraMain->GetOwner()->GetActorLocation().Y + CameraBoundsYProjectionCenter;

	FVector CameraWorldProjectionDir;
	FVector WorldPostion;

	UGameplayStatics::DeprojectScreenToWorld(
		PlayerController,
		ViewPortPosition,
		WorldPostion,
		CameraWorldProjectionDir
		);

	WorldPostion += CameraWorldProjectionDir * YDistanceToCenter;

	return WorldPostion;
}

