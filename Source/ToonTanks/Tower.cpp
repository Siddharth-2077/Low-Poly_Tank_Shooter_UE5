// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Projectile.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanksGameMode.h"


// Sets default values
ATower::ATower() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATower::BeginPlay() {
	Super::BeginPlay();

	// Get the game mode
	ToonTanksGameMode = Cast<AToonTanksGameMode>(UGameplayStatics::GetGameMode(this));
	if (ToonTanksGameMode)
		ToonTanksGameMode->IncrementNumTowersInWorld();
	
	PlayerTank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (PlayerTank != nullptr)
		PlayerTank_Exists = true;
	if (Super::GetTurret() != nullptr)
		TurretMesh_Exists = true;
	
	// Setup the projectile spawn parameters:
	Super::ProjectileSpawnParameters.Owner = this;
	Super::ProjectileSpawnParameters.Instigator = GetInstigator();
	
	// Set the timer to loop
	GetWorldTimerManager().SetTimer(
		TimerHandle,
		this,
		&ATower::CheckFireCondition,
		FireRate,
		true
	);	
}

// Called every frame
void ATower::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	
	if (!PlayerTank_Exists || !TurretMesh_Exists)
		return;
	UpdateDistanceToPlayer();
	RotateTurret(PlayerTank->GetActorLocation(), true);
}

void ATower::UpdateDistanceToPlayer() {
	if (!PlayerTank_Exists)
		return;
	Distance = FVector::Dist(GetActorLocation(), PlayerTank->GetActorLocation());
}

// Rotate the tower's turret to face the player tank 
void ATower::RotateTurret(FVector TargetLocation, bool Interpolate) {
	if (!PlayerTank_Exists || !TurretMesh_Exists) {
		UE_LOG(LogTemp, Error, TEXT("Turret.cpp | Missing components on the turret!"));
		return;
	}	
	if (Distance > AttackRange)
		return;
	PlayerDirection = PlayerTank->GetActorLocation() - GetActorLocation();
	RequiredRotation = PlayerDirection.Rotation();
	if (!Interpolate) {
		Super::SetTurretMesh_Rotation(RequiredRotation);
	} else {
		InterpolatedRotation = FMath::RInterpTo(
			Super::GetTurretMesh_Rotation(),
			RequiredRotation,
			UGameplayStatics::GetWorldDeltaSeconds(Super::World),
			RotationInterpolationSpeed
		);
		Super::SetTurretMesh_Rotation(InterpolatedRotation);
	}
}

// Called every 2 seconds
void ATower::CheckFireCondition() {
	if (!PlayerTank_Exists || !TurretMesh_Exists || !ToonTanksGameMode)
		return;
	if (Distance > AttackRange)
		return;
	if (ToonTanksGameMode->GetGameStarted() == false || ToonTanksGameMode->IsPlayerDead() == true)
		return;
	Fire();
}

// Function to fire at the player
void ATower::Fire() {
	DrawDebugSphere(Super::World, Super::GetProjectileSpawn_Location(), 20, 14, FColor::Red, false, 1);
	Super::World->SpawnActor<AProjectile>(
		Super::ProjectileClass,
		Super::GetProjectileSpawn_Location(),
		Super::GetProjectileSpawn_Rotation(),
		ProjectileSpawnParameters
	);
}

// Handle destruction of the Tower when health reaches 0
void ATower::HandleDestruction() {
	Super::HandleDestruction();
	if (DeathParticles) {
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			DeathParticles,
			GetActorLocation()
		);
	}
	Destroy();
}


