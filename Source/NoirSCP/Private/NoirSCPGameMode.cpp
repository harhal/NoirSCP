// Copyright Epic Games, Inc. All Rights Reserved.

#include "NoirSCPGameMode.h"
#include "TacticalGameMode/TacticalCursor/TacticalPlayerController.h"
#include "TacticalGameMode/TacticalCursor/TacticalPlayerCursorPawn.h"

ANoirSCPGameMode::ANoirSCPGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ATacticalPlayerController::StaticClass();
	
	// use our custom PlayerPawn class
	DefaultPawnClass = ATacticalPlayerCursorPawn::StaticClass();

	// set default pawn class to our Blueprinted character
	/*static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}*/
}