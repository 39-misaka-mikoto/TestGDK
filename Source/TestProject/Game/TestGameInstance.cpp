// Fill out your copyright notice in the Description page of Project Settings.


#include "TestGameInstance.h"
#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Interfaces/OnlineIdentityInterface.h"


UTestGameInstance::UTestGameInstance(const FObjectInitializer& ObjectIniyializer)
{
}

void UTestGameInstance::Init()
{
	OnlineSubsystem = IOnlineSubsystem::Get();
	if (OnlineSubsystem)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("Subsystem: ") + OnlineSubsystem->GetSubsystemName().ToString() + TEXT(" Platform: ") + OnlineSubsystem->GetLocalPlatformName());
		}
		SessionInterface = OnlineSubsystem->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("SessionInterface.IsValid()"));
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UTestGameInstance::OnCreateSessionComplete);
			SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UTestGameInstance::OnDestroySessionComplete);
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UTestGameInstance::OnFindSessionComplete);
			SessionInterface->OnSessionUserInviteAcceptedDelegates.AddUObject(this, &UTestGameInstance::OnSessionUserInviteAccepted);
			//SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UTestGameInstance::OnJoinSessionComplete);
			//SessionInterface->OnSessionUserInviteAcceptedDelegates.AddUObject(this, &UTestGameInstance::OnSessionUserInviteAccepted);
		}
		IndentityInterface = OnlineSubsystem->GetIdentityInterface();
		if (IndentityInterface.IsValid())
		{
			if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("IndentityInterface.IsValid()"));
			for (int i = 0; i < MAX_LOCAL_PLAYERS; i++)
			{
				IndentityInterface->OnLoginCompleteDelegates[i].AddUObject(this, &UTestGameInstance::OnGDKLoginComplete);
				IndentityInterface->OnLogoutCompleteDelegates[i].AddUObject(this, &UTestGameInstance::OnGDKLogoutComplete);
				IndentityInterface->OnLoginStatusChangedDelegates[i].AddUObject(this, &UTestGameInstance::OnLoginStatusChangedComplete);
			}
			IndentityInterface->OnLoginChangedDelegates.AddUObject(this, &UTestGameInstance::OnGDKLoginChangedComplete);
		}
	}

}

void UTestGameInstance::Host()
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Host"));
	if (SessionInterface.IsValid())
	{
		FName SessionName = "PvPSession";
		FNamedOnlineSession* ExistingSession = SessionInterface->GetNamedSession(SessionName);
		if (ExistingSession)
		{
			SessionInterface->DestroySession(SessionName);
		}
		else
		{
			CreateSession(SessionName);
		}
	}
}

void UTestGameInstance::FindSession()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("FindSession"));
	}
	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	if (SessionSearch)
	{
		//SessionSearch->bIsLanQuery = true;
		// make sure can find session of this game, because we're using shared AppID
		SessionSearch->MaxSearchResults = 1000;
		SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
		SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
	}
}

void UTestGameInstance::Login()
{
	if (IndentityInterface.IsValid())
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("AutoLogin()"));
		for (int i = 0; i < MAX_LOCAL_PLAYERS; i++)
		{
			UE_LOG(LogClass, Log, TEXT("THINHGDK AutoLogin()"));
			IndentityInterface->AutoLogin(i);
		}
	}
}

void UTestGameInstance::Logout()
{
	if (IndentityInterface.IsValid())
	{
		UE_LOG(LogClass, Log, TEXT("THINHGDK Logout()"));
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Logout()"));
		IndentityInterface->Logout(0);
	}
}

FString UTestGameInstance::GetUserDisplayName()
{
	if (IndentityInterface.IsValid())
	{
		for (int i = 0; i < MAX_LOCAL_PLAYERS; i++)
		{
			switch (IndentityInterface->GetLoginStatus(i))
			{
			case ELoginStatus::LoggedIn:
				UE_LOG(LogClass, Log, TEXT("THINHGDK User %i -  %s LoggedIn"), i, *IndentityInterface->GetPlayerNickname(i));
				break;
			case ELoginStatus::NotLoggedIn:
				UE_LOG(LogClass, Log, TEXT("THINHGDK User %i -  %s NotLoggedIn"), i, *IndentityInterface->GetPlayerNickname(i));
				break;
			case ELoginStatus::UsingLocalProfile:
				UE_LOG(LogClass, Log, TEXT("THINHGDK User %i -  %s UsingLocalProfile"), i, *IndentityInterface->GetPlayerNickname(i));
			default:
				break;
			}
		}
		if (IndentityInterface->GetLoginStatus(0) == ELoginStatus::LoggedIn)
		{
			return IndentityInterface->GetUserAccount(IndentityInterface->GetUniquePlayerId(0).ToSharedRef().Get())->GetDisplayName();
		}
		else if(IndentityInterface->GetLoginStatus(0) == ELoginStatus::NotLoggedIn)//test 0123
		{
			return TEXT("NotLoggedIn");
		}
		else
		{
			return TEXT("UsingLocalProfile");
		}
			
	}
	return TEXT("!IndentityInterface.IsValid()");
}

void UTestGameInstance::CreateSession(FName InSessionName)
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Begin Creating Session"));
	if (SessionInterface.IsValid())
	{
		FOnlineSessionSettings SessionSettings;
		/*if (OnlineSubsystem && OnlineSubsystem->GetSubsystemName() == "NULL")
		{*/
			//SessionSettings.bIsLANMatch = false;
		/*}
		else
		{
			SessionSettings.bIsLANMatch = false;
		}*/
		/*SessionSettings.bIsDedicated = false;
		SessionSettings.NumPublicConnections = 5;
		SessionSettings.bShouldAdvertise = true;
		SessionSettings.bUsesPresence = true;
		SessionSettings.bUseLobbiesIfAvailable = true;
		SessionSettings.NumPrivateConnections = 2;
		SessionSettings.bAllowJoinViaPresenceFriendsOnly = true;
		SessionSettings.bAllowInvites = true;*/
		SessionSettings.bIsLANMatch = false;
		SessionSettings.bUsesPresence = true;
		SessionSettings.NumPublicConnections = 2;
		SessionSettings.bAllowInvites = true;
		SessionSettings.bAllowJoinInProgress = true;
		SessionSettings.bShouldAdvertise = true;
		SessionSettings.bAllowJoinViaPresence = true;
		SessionSettings.Settings.Add(FName("SESSIONTEMPLATENAME"), InSessionName.ToString());
		SessionSettings.Settings.Add(
			SETTING_MAPNAME,
			FOnlineSessionSetting(InSessionName.ToString(), EOnlineDataAdvertisementType::ViaOnlineService));
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Creating Session"));
		if (!SessionInterface->CreateSession(0, InSessionName, SessionSettings))
		{
			if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Failed Creating Session"));
		}
	}
}

void UTestGameInstance::OnCreateSessionComplete(FName InSessionName, bool IsSuccess)
{
	if (IsSuccess)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("OnCreateSessionComplete: ") + InSessionName.ToString());
		}
	}
}

void UTestGameInstance::OnDestroySessionComplete(FName InSessionName, bool IsSuccess)
{
	if (IsSuccess)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("OnDestroySessionComplete:") + InSessionName.ToString());
		}
		CreateSession(InSessionName);
	}
}

void UTestGameInstance::OnFindSessionComplete(bool IsSuccess)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("OnFindSessionComplete"));
	}
	if (IsSuccess && SessionSearch)
	{
		TArray<FOnlineSessionSearchResult> SearchResults = SessionSearch->SearchResults;
		if (SearchResults.Num() > 0)
		{
			for (const FOnlineSessionSearchResult& Result : SearchResults)
			{
				UE_LOG(LogClass, Log, TEXT("Found Session: %s"), *Result.Session.OwningUserName);
			}
		}
	}
}

void UTestGameInstance::OnGDKLoginComplete(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error)
{
	if (bWasSuccessful)
	{
		UE_LOG(LogClass, Log, TEXT("THINHGDK OnLoginComplete: %i success - %s"), LocalUserNum, *Error);
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("OnLoginComplete: success"));
	}
	else
	{
		UE_LOG(LogClass, Log, TEXT("THINHGDK OnLoginComplete: %i failed - %s"), LocalUserNum, *Error);
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("OnLoginComplete: failed - ") + Error);
	}
}

void UTestGameInstance::OnGDKLogoutComplete(int32 LocalUserNum, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		UE_LOG(LogClass, Log, TEXT("THINHGDK OnGDKLogoutComplete: success"));
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("OnGDKLogoutComplete: success"));
	}
	else
	{
		UE_LOG(LogClass, Log, TEXT("THINHGDK OnGDKLogoutComplete: failed"));
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("OnGDKLogoutComplete: failed"));
	}
}

void UTestGameInstance::OnGDKLoginChangedComplete(int32 LocalUserNum)
{
	UE_LOG(LogClass, Log, TEXT("THINHGDK OnGDKLoginChangedComplete"));
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("OnGDKLoginChangedComplete"));
}

void UTestGameInstance::OnLoginStatusChangedComplete(int32 LocalUserNum, ELoginStatus::Type OldStatus, ELoginStatus::Type NewStatus, const FUniqueNetId& NewId)
{
	UE_LOG(LogClass, Log, TEXT("THINHGDK OnLoginStatusChangedComplete"));
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("OnLoginStatusChangedComplete"));
}

void UTestGameInstance::OnSessionUserInviteAccepted(bool bWasSuccessful, int32 ControllerId, FUniqueNetIdPtr UserId, const FOnlineSessionSearchResult& SearchResult)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("OnSessionUserInviteAccepted"));
	}
	if (bWasSuccessful)
	{
		if (SearchResult.IsValid())
		{
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("OnSessionUserInviteAccepted bWasSuccessful"));
			}
			//SessionInterface->JoinSession(*UserId, NAME_GameSession, SearchResult);
		}
	}
}