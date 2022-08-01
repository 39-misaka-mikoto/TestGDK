// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDWidget.h"
#include "Components/TextBlock.h"

bool UHUDWidget::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;
	SetCredentialText(TEXT("Credential:"));
	return true;
}
void UHUDWidget::SetCredentialText(FString Text)
{
	if (CredentialText)
	{
		CredentialText->SetText(FText::FromString(FString::Printf(TEXT("Credential: %s"), *Text)));
	}
}
