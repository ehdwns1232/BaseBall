#include "UI/BBHUD.h"
#include "UI/BBNickNameInput.h"
#include "UI/BBChatInput.h"
#include "UI/BBChatShow.h"
#include "UI/BBGameNotify.h"

void UBBHUD::NativeConstruct()
{
    Super::NativeConstruct();

    InitializeVisibility();
}

void UBBHUD::InitializeVisibility()
{
    if (IsValid(NickNameInputWidget) == true)
    {
        NickNameInputWidget->SetVisibility(ESlateVisibility::Visible);
    }

    if (IsValid(ChatShowWidget) == true)
    {
        ChatShowWidget->SetVisibility(ESlateVisibility::Collapsed);
    }
    if (IsValid(ChatInputWidget) == true)
    {
        ChatInputWidget->SetVisibility(ESlateVisibility::Collapsed);
    }
    if (IsValid(GameNotifyWidget) == true)
    {
        GameNotifyWidget->SetVisibility(ESlateVisibility::Collapsed);
    }
}

void UBBHUD::SetWidgetVisibility()
{
    if (IsValid(NickNameInputWidget) == true)
    {
        NickNameInputWidget->SetVisibility(ESlateVisibility::Collapsed);
    }

    if (IsValid(ChatShowWidget) == true)
    {
        ChatShowWidget->SetVisibility(ESlateVisibility::Visible);
    }
    if (IsValid(ChatInputWidget) == true)
    {
        ChatInputWidget->SetVisibility(ESlateVisibility::Visible);
    }
}
