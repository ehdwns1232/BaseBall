#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BBHUD.generated.h"

class UBBChatInput;
class UBBChatShow;
class UBBGameNotify;
class UBBNickNameInput;

UCLASS()
class BASEBALL_API UBBHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

public:
	UBBChatShow* GetChatShowWidget() { return ChatShowWidget; }
	UBBGameNotify* GetGameNotifyWidget() { return GameNotifyWidget; }
	void InitializeVisibility();
	void SetWidgetVisibility();
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBBChatInput> ChatInputWidget;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBBChatShow> ChatShowWidget;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBBGameNotify> GameNotifyWidget;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBBNickNameInput> NickNameInputWidget;
};
