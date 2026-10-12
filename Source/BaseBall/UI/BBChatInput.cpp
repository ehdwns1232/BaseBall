#include "UI/BBChatInput.h"
#include "Components/EditableTextBox.h"
#include "Controller/BBPlayerController.h"

void UBBChatInput::NativeConstruct()
{
	Super::NativeConstruct();

	if (EditableTextBox_ChatInput->OnTextCommitted.IsAlreadyBound(this, &UBBChatInput::OnChatInputTextCommited) == false)
	{
		EditableTextBox_ChatInput->OnTextCommitted.AddDynamic(this, &UBBChatInput::OnChatInputTextCommited);
	}
}

void UBBChatInput::NativeDestruct()
{
	Super::NativeDestruct();

	if (EditableTextBox_ChatInput->OnTextCommitted.IsAlreadyBound(this, &UBBChatInput::OnChatInputTextCommited) == true)
	{
		EditableTextBox_ChatInput->OnTextCommitted.RemoveDynamic(this, &UBBChatInput::OnChatInputTextCommited);
	}
}

void UBBChatInput::OnChatInputTextCommited(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (CommitMethod == ETextCommit::OnEnter)
	{
		APlayerController* OwningPlayerController = GetOwningPlayer();
		if (IsValid(OwningPlayerController) == true)
		{
			ABBPlayerController* BBPlayerController = Cast<ABBPlayerController>(OwningPlayerController);
			if (IsValid(BBPlayerController) == true)
			{
				BBPlayerController->ServerRPCPrintChatMessageString(Text.ToString());
				EditableTextBox_ChatInput->SetText(FText());
			}
		}
	}
}
