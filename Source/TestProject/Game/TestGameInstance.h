// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "OnlineSubsystem.h"
#include "TestGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT_API UTestGameInstance : public UGameInstance
{
	GENERATED_BODY()
private:
	IOnlineSubsystem* OnlineSubsystem;
	IOnlineSessionPtr SessionInterface;
	IOnlineIdentityPtr IndentityInterface;
	TSharedPtr<class FOnlineSessionSearch> SessionSearch;
	void CreateSession(FName InSessionName);
	void OnCreateSessionComplete(FName InSessionName, bool IsSuccess);
	void OnDestroySessionComplete(FName InSessionName, bool IsSuccess);
	void OnFindSessionComplete(bool IsSuccess);
	void OnGDKLoginComplete(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error);
	void OnGDKLogoutComplete(int32 LocalUserNum, bool bWasSuccessful);
	void OnGDKLoginChangedComplete(int32 LocalUserNum);
	void OnLoginStatusChangedComplete(int32 LocalUserNum, ELoginStatus::Type OldStatus, ELoginStatus::Type NewStatus, const FUniqueNetId& NewId);
	void OnSessionUserInviteAccepted(bool bWasSuccessful, int32 ControllerId, FUniqueNetIdPtr UserId, const FOnlineSessionSearchResult& SearchResult);
public:
	UTestGameInstance(const FObjectInitializer& ObjectIniyializer);
	virtual void Init() override;
	virtual void Host();
	virtual void FindSession();
	virtual void Login();
	virtual void Logout();

	virtual FString GetUserDisplayName();
};
