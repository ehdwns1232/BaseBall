#include "Controller/BBPlayerController.h"
#include "UI/BBHUD.h"
#include "UI/BBChatShow.h"
#include "UI/BBGameNotify.h"
#include "PlayerState/BBPlayerState.h"
#include "GameState/BBGameStateBase.h"
#include "GameMode/BBGameModeBase.h"
#include "Kismet/GameplayStatics.h"

void ABBPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalController() == false)
	{
		return;
	}

	if (IsValid(HUDWidgetClass) == true)
	{
		HUDWidgetInstance = CreateWidget<UBBHUD>(this, HUDWidgetClass);
		if (IsValid(HUDWidgetInstance) == true)
		{
			HUDWidgetInstance->AddToViewport();
			SetInputMode(FInputModeUIOnly());
			bShowMouseCursor = true;
		}
	}
}

void ABBPlayerController::ClientRPCResetUI_Implementation()
{
	if (IsValid(HUDWidgetInstance) == true)
	{
		UBBGameNotify* NotifyWidget = HUDWidgetInstance->GetGameNotifyWidget();
		if (IsValid(NotifyWidget) == true)
		{
			NotifyWidget->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

void ABBPlayerController::ClientRPCShowGameNotify_Implementation(const FString& NotifyMessage)
{
	if (IsValid(HUDWidgetInstance) == true)
	{
		UBBGameNotify* NotifyWidget = HUDWidgetInstance->GetGameNotifyWidget();
		if (IsValid(NotifyWidget) == true)
		{
			NotifyWidget->SetVisibility(ESlateVisibility::Visible);
			NotifyWidget->ShowNotifyMessage(NotifyMessage);
		}
	}
}

void ABBPlayerController::ClientRPCPlayerNickNameDecided_Implementation()
{
	if (IsValid(HUDWidgetInstance) == true)
	{
		HUDWidgetInstance->SetWidgetVisibility();
	}
}

void ABBPlayerController::ServerRPCPlayerNickNameDecided_Implementation(const FString& NewNickName)
{
	ABBPlayerState* BBPlayerState = GetPlayerState<ABBPlayerState>();
	if (IsValid(BBPlayerState) == true)
	{
		BBPlayerState->SetPlayerNickName(NewNickName);
	}

	ClientRPCPlayerNickNameDecided();
}

void ABBPlayerController::ClinetRPCPrintChatMessageString_Implementation(const FString& PlayerNickName, const FString& ChatMessage)
{
	if (IsValid(HUDWidgetInstance) == true)
	{
		HUDWidgetInstance->GetChatShowWidget()->AddChatMessage(PlayerNickName, ChatMessage);
	}
}

void ABBPlayerController::ServerRPCPrintChatMessageString_Implementation(const FString& ChatMessage)
{
	AGameModeBase* GameModeBase = UGameplayStatics::GetGameMode(this);
	if (IsValid(GameModeBase) == true)
	{
		ABBGameModeBase* BBGameModeBase = Cast<ABBGameModeBase>(GameModeBase);
		if (IsValid(BBGameModeBase) == true)
		{
			BBGameModeBase->PrintChatMessageString(this, ChatMessage);
		}
	}
}
