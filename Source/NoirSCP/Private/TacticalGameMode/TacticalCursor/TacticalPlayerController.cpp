// Copyright Epic Games, Inc. All Rights Reserved.

#include "TacticalGameMode/TacticalCursor/TacticalPlayerController.h"

#include "DrawDebugHelpers.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NoirSCPCharacter.h"
#include "Kismet/KismetMathLibrary.h"

ATacticalPlayerController::ATacticalPlayerController()
{
	/*bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;*/
}

void ATacticalPlayerController::BeginPlay()
{
	Super::BeginPlay();

	CursorPawn = Cast<ATacticalPlayerCursorPawn>(GetPawn());

	for (int i = 0; i < CursorPawn->GetControllingPawnsCount(); i++)
	{
		const FTransform& SpawnTransform = FTransform(CursorPawn->GetActorRotation(),
		                                              CursorPawn->GetDefaultLocationForCharacter(i));

		ANoirSCPCharacter* NewCharacter = GetWorld()->SpawnActor<ANoirSCPCharacter>(CharactersClass, SpawnTransform);

		ATacticalSquadUnitAIController* NewController = GetWorld()->SpawnActor<ATacticalSquadUnitAIController>(
			ATacticalSquadUnitAIController::StaticClass(), SpawnTransform);
		NewController->Possess(NewCharacter);

		Squad.Add(NewController);
	}
}

void ATacticalPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	const FVector& SquadLocation = GetSquadCenterLocation();
	DrawDebugPoint(GetWorld(), SquadLocation, 10.0f, FColor::Red);
	
	const FVector& CursorLocation = GetPawn()->GetActorLocation();
	DrawDebugCircle(GetWorld(), FTransform(FRotator(90.0f, 0.0f, 0.0f), CursorLocation).ToMatrixNoScale(), DirectionDetectionDeadZone, 32, FColor::Green);

	if (FVector::Dist2D(SquadLocation, CursorLocation) > DirectionDetectionDeadZone)
	{
		const FRotator& TargetCursorControlRotation = UKismetMathLibrary::FindLookAtRotation(SquadLocation.Projection(), CursorLocation.Projection());

		
		const FRotator& NewCursorControlRotation = FMath::RInterpTo(GetPawn()->GetActorRotation(), TargetCursorControlRotation, DeltaTime, 5.0f);
		
		GetPawn()->SetActorRotation(NewCursorControlRotation);
	}

	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{
		MoveToCursor();
	}
}

void ATacticalPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();
}

void ATacticalPlayerController::MoveToCursor()
{
	for (int i = 0; i < Squad.Num(); i++)
	{
		AAIController* AIController = Squad[i];
		FVector DestLocation = CursorPawn->GetDefaultLocationForCharacter(i);
		float const Distance = FVector::Dist(DestLocation, AIController->GetPawn()->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if ((Distance > 120.0f))
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(AIController, DestLocation);
		}
	}
}

void ATacticalPlayerController::OnMovePressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
}

void ATacticalPlayerController::OnMoveReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}


FVector ATacticalPlayerController::GetSquadCenterLocation() const
{
	FVector SquadUnitsLocationSum = FVector::ZeroVector;
	for (int i = 0; i < Squad.Num(); i++)
	{
		const APawn* SquadUnit = Squad[i]->GetPawn();
		if (!IsValid(SquadUnit))
		{
			continue;
		}
		
		SquadUnitsLocationSum += SquadUnit->GetActorLocation();
	}

	return SquadUnitsLocationSum / Squad.Num();
}
