// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BBPlayerController.generated.h"

/**
 * 
 */

class UBBHUD;

UCLASS()
class BASEBALL_API ABBPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

public:
	UFUNCTION(Client, Reliable)
	void ClinetRPCPrintChatMessageString(const FString& PlayerNickName, const FString& ChatMessage);
	UFUNCTION(Server, Reliable)
	void ServerRPCPrintChatMessageString(const FString& ChatMessage);
	UFUNCTION(Client, Reliable)
	void ClientRPCPlayerNickNameDecided();
	UFUNCTION(Server, Reliable)
	void ServerRPCPlayerNickNameDecided(const FString& NewNickName);
	UFUNCTION(Client, Reliable)
	void ClientRPCShowGameNotify(const FString& NotifyMessage);
	UFUNCTION(Client, Reliable)
	void ClientRPCResetUI();
public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UBBHUD> HUDWidgetClass;
	UPROPERTY()
	TObjectPtr<UBBHUD> HUDWidgetInstance;

	FString ChatMessageString;
};
