// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()
	
private:
	class ATank* Tank = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	float FireRange = 500.0f;

	FTimerHandle FireTimerHandle;
	float FireRate = 2.0f;

	bool bIsTankInRange = false;

private:
	bool IsTankInFireRange();

	void CheckFireCondition();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
