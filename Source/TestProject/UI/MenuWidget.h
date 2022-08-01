// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget.generated.h"

class UButton;
class UTextBlock;
/**
 * 
 */
UCLASS()
class TESTPROJECT_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(meta = (BindWidget))
		UTextBlock* UserNameText;
	UPROPERTY(meta = (BindWidget))
		UButton* CreateSessionButton;
	UPROPERTY(meta = (BindWidget))
		UButton* InviteFriendButton;
	UPROPERTY(meta = (BindWidget))
		UButton* UpdateTextButton;
	UPROPERTY(meta = (BindWidget))
		UButton* CancelButton;
protected:
	UFUNCTION()
		void OnClick_CreateSession();
	UFUNCTION()
		void OnClick_InviteFriend();
	UFUNCTION()
		void OnClick_UpdateText();
	UFUNCTION()
		void OnClick_CancelButton();
public:
	virtual bool Initialize() override;
	UFUNCTION(BlueprintCallable)
	void Setup();
};
