// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
private:
	class ATank* Tank;
	class AToonTanksPlayerController* ToonTanksPlayerController;

	float StartDelay = 3.0f;

protected:
	virtual void BeginPlay() override;

private:
	void HandleGameStart();

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

public:
	void ActorDied(AActor* DeadActor);
};
