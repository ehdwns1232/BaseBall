#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BBChatLine.generated.h"

UCLASS()
class BASEBALL_API UBBChatLine : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetChatText(const FString& ChatString);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> TextBlock_ChatString;
};
