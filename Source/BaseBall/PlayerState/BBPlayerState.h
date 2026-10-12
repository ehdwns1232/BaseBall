#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "BBPlayerState.generated.h"

UCLASS()
class BASEBALL_API ABBPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	ABBPlayerState();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	void SetPlayerNickName(const FString& NewNickName);
	void AddTryCount();
	int32 GetCurrentTryCount() { return CurrentTryCount; }
	int32 GetMaxTryCount() { return MaxTryCount; }
	bool GetIsFinish() { return bIsFinish; }
	void SetIsFinish(bool bIsFinished) { bIsFinish = bIsFinished; }


public:
	UPROPERTY(Replicated)
	FString PlayerNickName;
	UPROPERTY(Replicated)
	int32 CurrentTryCount;
	UPROPERTY(Replicated)
	int32 MaxTryCount;
	UPROPERTY(Replicated)
	bool bIsFinish;
};
