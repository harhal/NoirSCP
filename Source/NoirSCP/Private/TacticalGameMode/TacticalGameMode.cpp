// Fill out your copyright notice in the Description page of Project Settings.


#include "TacticalGameMode/TacticalGameMode.h"

#include "TacticalGameMode/TacticalCursor/TacticalPlayerController.h"
#include "TacticalGameMode/TacticalCursor/TacticalPlayerCursorPawn.h"


// Sets default values
ATacticalGameMode::ATacticalGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ATacticalPlayerController::StaticClass();
	
	// use our custom PlayerPawn class
	DefaultPawnClass = ATacticalPlayerCursorPawn::StaticClass();
}