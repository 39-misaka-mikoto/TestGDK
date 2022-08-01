// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
		class UTextBlock* CredentialText;
	virtual bool Initialize() override;
	void SetCredentialText(FString Text);
};
