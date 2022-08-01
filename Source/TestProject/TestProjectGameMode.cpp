// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestProjectGameMode.h"
#include "TestProjectCharacter.h"
#include "TestProject/UI/HUDWidget.h"
#include "UObject/ConstructorHelpers.h"

ATestProjectGameMode::ATestProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ATestProjectGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
