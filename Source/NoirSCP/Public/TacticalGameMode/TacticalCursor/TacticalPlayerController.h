// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "NoirSCPCharacter.h"
#include "TacticalPlayerCursorPawn.h"
#include "GameFramework/PlayerController.h"
#include "TacticalGameMode/TacticalSquadUnitAIController.h"
#include "TacticalPlayerController.generated.h"

UCLASS()
class ATacticalPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATacticalPlayerController();

protected:

	virtual void BeginPlay() override;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

	void MoveToCursor();

	UFUNCTION(BlueprintCallable)
	void OnMovePressed();
	
	UFUNCTION(BlueprintCallable)
	void OnMoveReleased();
	
	UFUNCTION(BlueprintCallable)
	FVector GetSquadCenterLocation() const;

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ANoirSCPCharacter> CharactersClass;
	
	UPROPERTY(EditDefaultsOnly)
	float DirectionDetectionDeadZone = 10.0f;
	
	UPROPERTY()
	ATacticalPlayerCursorPawn* CursorPawn;
	
	UPROPERTY()
	TArray<ATacticalSquadUnitAIController*> Squad;
	
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;
};


