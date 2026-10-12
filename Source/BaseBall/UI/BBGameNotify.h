#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BBGameNotify.generated.h"

UCLASS()
class BASEBALL_API UBBGameNotify : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void ShowNotifyMessage(const FString& ResultMessage);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> TextBlock_NotifyMessage;
};
