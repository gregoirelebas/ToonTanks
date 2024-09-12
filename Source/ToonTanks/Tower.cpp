// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include <Kismet/GameplayStatics.h>
#include "Tank.h"

bool ATower::IsTankInFireRange()
{
	if (Tank && Tank->bIsAlive)
	{
		float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());

		return Distance <= FireRange;
	}

	return false;
}

void ATower::CheckFireCondition()
{
	if (bIsTankInRange)
		Fire();
}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorldTimerManager().SetTimer(FireTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	bIsTankInRange = IsTankInFireRange();
	if (bIsTankInRange)
		RotateTurret(Tank->GetActorLocation());
}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();

	Destroy();
}
