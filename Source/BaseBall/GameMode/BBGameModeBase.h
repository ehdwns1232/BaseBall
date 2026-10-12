#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BBGameModeBase.generated.h"

class ABBPlayerController;

UCLASS()
class BASEBALL_API ABBGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ABBGameModeBase();
	virtual void BeginPlay() override;
	virtual void OnPostLogin(AController* NewPlayer) override;
public:
	FString GenerateSecretNumber();
	bool IsGuessNumberString(const FString& InNumberString);
	FString JudgeResult(const FString& InGuessNumberString);
	void PrintChatMessageString(ABBPlayerController* InChattingPlayerController, const FString& InChatMessageString);
	void ResetGame();
	void JudgeGame(class ABBPlayerState* PlayerState, const FString& JudgeResultString);

private:
	TArray<TObjectPtr<ABBPlayerController>> AllPlayerControllers;
	FString SecretNumberString;
	int32 MaxTryCount;
};
