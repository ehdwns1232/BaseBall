#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BBNickNameInput.generated.h"

UCLASS()
class BASEBALL_API UBBNickNameInput : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

protected:
	UFUNCTION()
	void OnNickNameCommited(const FText& Text, ETextCommit::Type CommitMethod);

public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UEditableTextBox> EditableTextBox_NickNameInput;
};
