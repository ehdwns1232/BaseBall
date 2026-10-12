#include "PlayerState/BBPlayerState.h"
#include "Net/UnrealNetwork.h"

ABBPlayerState::ABBPlayerState()
	: PlayerNickName("")
	, CurrentTryCount(0)
	, MaxTryCount(0)
	, bIsFinish(false)
{
	bReplicates = true;
}

void ABBPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, PlayerNickName);
	DOREPLIFETIME(ThisClass, CurrentTryCount);
	DOREPLIFETIME(ThisClass, MaxTryCount);
	DOREPLIFETIME(ThisClass, bIsFinish);
}

void ABBPlayerState::SetPlayerNickName(const FString& NewNickName)
{
	PlayerNickName = NewNickName;
}

void ABBPlayerState::AddTryCount()
{
	CurrentTryCount++;
}


