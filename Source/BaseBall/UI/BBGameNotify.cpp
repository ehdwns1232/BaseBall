#include "UI/BBGameNotify.h"
#include "Components/TextBlock.h"

void UBBGameNotify::ShowNotifyMessage(const FString& ResultMessage)
{
	if (IsValid(TextBlock_NotifyMessage) == true)
	{
		TextBlock_NotifyMessage->SetText(FText::FromString(ResultMessage));
	}
}
