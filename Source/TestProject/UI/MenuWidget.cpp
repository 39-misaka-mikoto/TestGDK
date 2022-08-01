// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "TestProject/Game/TestGameInstance.h"

bool UMenuWidget::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;
	if (CreateSessionButton)
	{
		CreateSessionButton->OnClicked.AddDynamic(this, &UMenuWidget::OnClick_CreateSession);
	}
	if (InviteFriendButton)
	{
		InviteFriendButton->OnClicked.AddDynamic(this, &UMenuWidget::OnClick_InviteFriend);
	}
	if (UpdateTextButton)
	{
		UpdateTextButton->OnClicked.AddDynamic(this, &UMenuWidget::OnClick_UpdateText);
	}
	if (CancelButton)
	{
		CancelButton->OnClicked.AddDynamic(this, &UMenuWidget::OnClick_CancelButton);
	}
	return true;
}

void UMenuWidget::Setup()
{
	this->AddToViewport();
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PC = World->GetFirstPlayerController();
		if (PC)
		{
			FInputModeUIOnly InputModeData;
			InputModeData.SetWidgetToFocus(this->TakeWidget());
			InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			PC->SetInputMode(InputModeData);
			PC->bShowMouseCursor = true;
		}
	}
}

void UMenuWidget::OnClick_CreateSession()
{
	UTestGameInstance* GI = GetGameInstance<UTestGameInstance>();
	if (GI)
	{
		GI->Login();
	}
}

void UMenuWidget::OnClick_InviteFriend()
{
	UTestGameInstance* GI = GetGameInstance<UTestGameInstance>();
	if (GI)
	{
		GI->Logout();
	}
}

void UMenuWidget::OnClick_UpdateText()
{
	UTestGameInstance* GI = GetGameInstance<UTestGameInstance>();
	if (GI)
	{
		if (UserNameText)
		{
			UserNameText->SetText(FText::FromString(GI->GetUserDisplayName()));
		}
	}
}

void UMenuWidget::OnClick_CancelButton()
{
	this->RemoveFromViewport();
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PC = World->GetFirstPlayerController();
		if (PC)
		{
			FInputModeGameOnly InputModeData;
			PC->SetInputMode(InputModeData);
			PC->bShowMouseCursor = false;
		}
	}
}

