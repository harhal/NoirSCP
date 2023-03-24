// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "TacticalPlayerCursorPawn.generated.h"

USTRUCT(BlueprintType)
struct FSquadCharacterHandle
{
	GENERATED_BODY()
	
	UPROPERTY()
	int Id = -1;

	FSquadCharacterHandle() = default;

	FSquadCharacterHandle(int inId): Id(inId) { }
};

UENUM()
enum class ECursorRotationState
{
	VelocityBased,
	EnemyBased,
	SquadOppositeBased
};

UCLASS()
class NOIRSCP_API ATacticalPlayerCursorPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATacticalPlayerCursorPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//virtual UPawnMovementComponent* GetMovementComponent() const override;

	UFUNCTION(BlueprintPure)
	int GetControllingPawnsCount() const
	{
		return ControllingPawnsCount;
	}

	UFUNCTION(BlueprintPure)
	FVector GetDefaultLocationForCharacter(const FSquadCharacterHandle& SquadCharacterHandle) const
	{
		if (!ensureAlways(DefaultPawnLocations.IsValidIndex(SquadCharacterHandle.Id)))
		{
			return FVector();
		}
		
		return DefaultPawnLocations[SquadCharacterHandle.Id]->GetComponentLocation();
	}
	
	virtual UPawnMovementComponent* GetMovementComponent() const override;

private:
	/** Movement component used for movement logic, containing relevant settings and functions to control movement. */
	UPROPERTY(Category=Pawn, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UPawnMovementComponent* PawnMovement;
	
	/** The CapsuleComponent being used for movement collision (by CharacterMovement). Always treated as being vertically aligned in simple collision check functions. */
	UPROPERTY(Category=Pawn, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UCapsuleComponent* CapsuleComponent;
	
	UPROPERTY(Category=Pawn, EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TArray<USceneComponent*> DefaultPawnLocations;
	
	UPROPERTY(Category=Pawn, EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TArray<USpringArmComponent*> DefaultPawnLocationsArms;
	
	int ControllingPawnsCount = 4;
};
