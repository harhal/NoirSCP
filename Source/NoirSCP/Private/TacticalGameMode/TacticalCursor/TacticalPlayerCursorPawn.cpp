// Fill out your copyright notice in the Description page of Project Settings.


#include "TacticalGameMode/TacticalCursor/TacticalPlayerCursorPawn.h"

#include "Engine/CollisionProfile.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/FloatingPawnMovement.h"


// Sets default values
ATacticalPlayerCursorPawn::ATacticalPlayerCursorPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	CapsuleComponent->InitCapsuleSize(34.0f, 88.0f);
	CapsuleComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);

	CapsuleComponent->CanCharacterStepUpOn = ECB_No;
	CapsuleComponent->SetShouldUpdatePhysicsVolume(true);
	CapsuleComponent->SetCanEverAffectNavigation(false);
	CapsuleComponent->bDynamicObstacle = true;
	RootComponent = CapsuleComponent;
	
	PawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingMovementComponent"));
	PawnMovement->UpdatedComponent = CapsuleComponent;

	for (int i = 0; i < ControllingPawnsCount; i++)
	{
		USpringArmComponent* DefaultPawnLocationsArm = CreateDefaultSubobject<USpringArmComponent>(FName(FString::Printf(TEXT("Pawn%dDefaultLocationArm"), i)));
		DefaultPawnLocationsArm->SetupAttachment(RootComponent);
		DefaultPawnLocationsArm->bEditableWhenInherited = true;
		DefaultPawnLocationsArms.Add(DefaultPawnLocationsArm);

		USceneComponent* DefaultPawnLocation = CreateDefaultSubobject<USceneComponent>(FName(FString::Printf(TEXT("Pawn%dDefaultLocation"), i)));
		DefaultPawnLocation->SetupAttachment(DefaultPawnLocationsArm);
		DefaultPawnLocation->bEditableWhenInherited = true;
		DefaultPawnLocations.Add(DefaultPawnLocation);
	}
}

// Called when the game starts or when spawned
void ATacticalPlayerCursorPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATacticalPlayerCursorPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ATacticalPlayerCursorPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

UPawnMovementComponent* ATacticalPlayerCursorPawn::GetMovementComponent() const
{
	return PawnMovement;
}

