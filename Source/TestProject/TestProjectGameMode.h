// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TestProjectGameMode.generated.h"


UCLASS(minimalapi)
class ATestProjectGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATestProjectGameMode();
	virtual void Tick(float DeltaSeconds) override;
	UFUNCTION(Exec, Category = "Commands")
		void Test(float TestFloat);
};



