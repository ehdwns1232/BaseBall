#include "UI/BBChatShow.h"
#include "Components/ScrollBox.h"
#include "Components/VerticalBox.h"
#include "UI/BBChatLine.h"

void UBBChatShow::AddChatMessage(const FString& PlayerNickName, const FString& ChatMessage)
{
	if (IsValid(ChatLineWidgetClass) == true)
	{
		UBBChatLine* ChatLineInstance = CreateWidget<UBBChatLine>(this, ChatLineWidgetClass);
		if (IsValid(ChatLineInstance) == true)
		{
			FString FormatString = FString::Printf(TEXT("[%s] : %s"), *PlayerNickName, *ChatMessage);
			ChatLineInstance->SetChatText(FormatString);
	
			if (IsValid(VerticalBox_ChatString) == true)
			{
				VerticalBox_ChatString->AddChild(ChatLineInstance);
			}

			if (IsValid(ScrollBox_ChatList) == true)
			{
				ScrollBox_ChatList->ScrollToEnd();
			}
		}
	}
}
