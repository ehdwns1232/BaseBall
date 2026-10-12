#include "UI/BBChatLine.h"
#include "Components/TextBlock.h"

void UBBChatLine::SetChatText(const FString& ChatString)
{
	if (IsValid(TextBlock_ChatString) == true)
	{
		TextBlock_ChatString->SetText(FText::FromString(ChatString));
	}
}
