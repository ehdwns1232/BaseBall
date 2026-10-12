#include "GameMode/BBGameModeBase.h"
#include "Controller/BBPlayerController.h"
#include "PlayerState/BBPlayerState.h"

ABBGameModeBase::ABBGameModeBase()
	: SecretNumberString("")
	, MaxTryCount(3)
{
}

void ABBGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	SecretNumberString = GenerateSecretNumber();
	
}

void ABBGameModeBase::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);

	ABBPlayerController* BBPlayerController = Cast<ABBPlayerController>(NewPlayer);
	if (IsValid(BBPlayerController))
	{
		AllPlayerControllers.Add(BBPlayerController);

		ABBPlayerState* BBPlayerState = BBPlayerController->GetPlayerState<ABBPlayerState>();
		if (IsValid(BBPlayerState) == true)
		{
			BBPlayerState->MaxTryCount = MaxTryCount;
			BBPlayerState->CurrentTryCount = 0;
		}
	}
}

FString ABBGameModeBase::GenerateSecretNumber()
{
	TArray<int32> Numbers;
	for (int32 i = 1; i <= 9; ++i)
	{
		Numbers.Add(i);
	}

	FString Result;
	for (int32 i = 0; i < 3; ++i)
	{
		int32 Index = FMath::RandRange(0, Numbers.Num() - 1);
		Result.Append(FString::FromInt(Numbers[Index]));
		Numbers.RemoveAt(Index);
	}

	return Result;
}

bool ABBGameModeBase::IsGuessNumberString(const FString& InNumberString)
{
	if (InNumberString.Len() != 3)
	{
		return false;
	}

	TSet<TCHAR> UniqueDigit;

	for (TCHAR C : InNumberString)
	{
		if (FChar::IsDigit(C) == false || C == '0')
		{
			return false;
		}

		if (UniqueDigit.Contains(C) == true)
		{
			return false;
		}

		UniqueDigit.Add(C);
	}

	return true;
}

FString ABBGameModeBase::JudgeResult(const FString& InGuessNumberString)
{
	int32 StrikeCount = 0, BallCount = 0;

	for (int32 i = 0; i < 3; ++i)
	{
		if (SecretNumberString[i] == InGuessNumberString[i])
		{
			StrikeCount++;
		}
		else
		{
			if (SecretNumberString.Contains(FString::Chr(InGuessNumberString[i])))
			{
				BallCount++;
			}
		}
	}

	if (StrikeCount == 3)
	{
		return TEXT("정답입니다 !");
	}
	else if (StrikeCount == 0 && BallCount == 0)
	{
		return TEXT("OUT !");
	}
	else
	{
		return FString::Printf(TEXT("Strike : %d, Ball : %d"), StrikeCount, BallCount);
	}
}

void ABBGameModeBase::PrintChatMessageString(ABBPlayerController* InChattingPlayerController, const FString& InChatMessageString)
{
	if (IsValid(InChattingPlayerController) == false)
	{
		return;
	}

	ABBPlayerState* BBPlayerState = InChattingPlayerController->GetPlayerState<ABBPlayerState>();
	if (IsValid(BBPlayerState) == false)
	{
		return;
	}

	if (BBPlayerState->GetIsFinish() == true)
	{
		return;
	}

	FString PlayerNickName = BBPlayerState->PlayerNickName;
	FString FinalMessage = InChatMessageString;
	FString NotifyMessage = TEXT("");

	if (IsGuessNumberString(InChatMessageString) == true)
	{
		BBPlayerState->AddTryCount();
		FString JudgeResultString = JudgeResult(InChatMessageString);
		FinalMessage = FString::Printf(TEXT("[%d / %d] %s -> %s"), BBPlayerState->GetCurrentTryCount(), MaxTryCount, *InChatMessageString, *JudgeResultString);
		JudgeGame(BBPlayerState, JudgeResultString);
	}
	else
	{
		FinalMessage = FString::Printf(TEXT("%s -> 다시 입력하세요"), *InChatMessageString);
	}

	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		ABBPlayerController* BBPlayerController = Cast<ABBPlayerController>(It->Get());
		if (IsValid(BBPlayerController) == true)
		{
			BBPlayerController->ClinetRPCPrintChatMessageString(PlayerNickName, FinalMessage);
		}
	}

}

void ABBGameModeBase::ResetGame()
{
	SecretNumberString = GenerateSecretNumber();

	for (const auto& BBPlayerController : AllPlayerControllers)
	{
		ABBPlayerState* BBPlayerState = BBPlayerController->GetPlayerState<ABBPlayerState>();
		if (IsValid(BBPlayerState) == true)
		{
			BBPlayerState->CurrentTryCount = 0;
			BBPlayerState->SetIsFinish(false);
		}
		BBPlayerController->ClientRPCResetUI();
	}
}

void ABBGameModeBase::JudgeGame(class ABBPlayerState* PlayerState, const FString& JudgeResultString)
{
	if (IsValid(PlayerState) == false)
	{
		return;
	}

	FString PlayerNickName = PlayerState->PlayerNickName;
	FString NotifyMessage = TEXT("");
	bool bIsGameFinish = false;

	if (JudgeResultString == TEXT("정답입니다 !"))
	{
		PlayerState->SetIsFinish(true);
		NotifyMessage = FString::Printf(TEXT("%s 승리 !"), *PlayerNickName);
		bIsGameFinish = true;
	}
	else if (PlayerState->GetCurrentTryCount() >= MaxTryCount)
	{
		PlayerState->SetIsFinish(true);
		bool bIsAllFinish = true;
		for (const auto& BBPlayerController : AllPlayerControllers)
		{
			if (IsValid(BBPlayerController) == true)
			{
				ABBPlayerState* BBPlayerState = BBPlayerController->GetPlayerState<ABBPlayerState>();
				if (IsValid(BBPlayerState) == true)
				{
					if (BBPlayerState->GetIsFinish() == false)
					{
						bIsAllFinish = false;
						break;
					}
				}
			}
		}

		if (bIsAllFinish == true)
		{
			NotifyMessage = FString::Printf(TEXT("무승부 !"));
			bIsGameFinish = true;
		}
	}

	if (bIsGameFinish == true)
	{
		for (const auto& BBPlayerController : AllPlayerControllers)
		{
			if (IsValid(BBPlayerController) == true)
			{
				BBPlayerController->ClientRPCShowGameNotify(NotifyMessage);
			}
		}

		FTimerHandle ResetTimerHandle;
		GetWorld()->GetTimerManager().SetTimer(ResetTimerHandle, this, &ABBGameModeBase::ResetGame, 3.0f, false);
	}
}

