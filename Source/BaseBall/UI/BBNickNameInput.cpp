#include "UI/BBNickNameInput.h"
#include "Components/EditableTextBox.h"
#include "Controller/BBPlayerController.h"

void UBBNickNameInput::NativeConstruct()
{
	Super::NativeConstruct();

	if (EditableTextBox_NickNameInput->OnTextCommitted.IsAlreadyBound(this, &UBBNickNameInput::OnNickNameCommited) == false)
	{
		EditableTextBox_NickNameInput->OnTextCommitted.AddDynamic(this, &UBBNickNameInput::OnNickNameCommited);
	}
}

void UBBNickNameInput::NativeDestruct()
{
	Super::NativeDestruct();

	if (EditableTextBox_NickNameInput->OnTextCommitted.IsAlreadyBound(this, &UBBNickNameInput::OnNickNameCommited) == true)
	{
		EditableTextBox_NickNameInput->OnTextCommitted.RemoveDynamic(this, &UBBNickNameInput::OnNickNameCommited);
	}
}

void UBBNickNameInput::OnNickNameCommited(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (CommitMethod == ETextCommit::OnEnter)
	{
		FString NewNickName = Text.ToString().TrimStartAndEnd();
		APlayerController* OwningPlayerController = GetOwningPlayer();
		if (IsValid(OwningPlayerController) == true)
		{
			ABBPlayerController* BBPlayerController = Cast<ABBPlayerController>(OwningPlayerController);
			if (IsValid(BBPlayerController) == true)
			{
				BBPlayerController->ServerRPCPlayerNickNameDecided(NewNickName);
			}
		}
	}
}
