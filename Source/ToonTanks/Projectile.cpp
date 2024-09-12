// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include <Kismet/GameplayStatics.h>

AProjectile::AProjectile()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	RootComponent = Mesh;

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement Component"));
	MovementComponent->InitialSpeed = 500.0f;
	MovementComponent->MaxSpeed = 1000.0f;

	TrailParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Trail particles"));
	TrailParticles->SetupAttachment(RootComponent);
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	Mesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

	if (LaunchSound)
		UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation());
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* OwnerActor = GetOwner();
	if (OwnerActor == nullptr)
	{
		Destroy();
		return;
	}

	AController* InstigatorActor = OwnerActor->GetInstigatorController();
	UClass* DamageClass = UDamageType::StaticClass();

	if (OtherActor && OtherActor != this && OtherActor != OwnerActor)
		UGameplayStatics::ApplyDamage(OtherActor, Damage, InstigatorActor, this, DamageClass);

	if (HitParticles)
		UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, Hit.ImpactPoint);

	if (HitSound)
		UGameplayStatics::PlaySoundAtLocation(this, HitSound, Hit.ImpactPoint);

	Destroy();
}
