#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BBChatShow.generated.h"

UCLASS()
class BASEBALL_API UBBChatShow : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void AddChatMessage(const FString& PlayerNickName, const FString& ChatMessage);

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UBBChatLine> ChatLineWidgetClass;

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UScrollBox> ScrollBox_ChatList;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UVerticalBox> VerticalBox_ChatString;
};
