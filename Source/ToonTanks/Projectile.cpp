// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include <Kismet/GameplayStatics.h>

AProjectile::AProjectile()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	RootComponent = Mesh;

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement Component"));
	MovementComponent->InitialSpeed = 500.0f;
	MovementComponent->MaxSpeed = 1000.0f;
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	Mesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* OwnerActor = GetOwner();
	if (OwnerActor == nullptr) return;

	AController* InstigatorActor = OwnerActor->GetInstigatorController();
	UClass* DamageClass = UDamageType::StaticClass();

	if (OtherActor && OtherActor != this && OtherActor != OwnerActor)
		UGameplayStatics::ApplyDamage(OtherActor, Damage, InstigatorActor, this, DamageClass);

	Destroy();
}
