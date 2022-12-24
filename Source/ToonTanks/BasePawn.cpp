// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"


// Sets default values
ABasePawn::ABasePawn() {
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Construct the default subobjects:
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));

	// Make the capsule component the root:
	RootComponent = CapsuleComponent;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComponent);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));	
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay() {
	Super::BeginPlay();
	
	World = GetWorld();
}


// Handle destruction of the object
void ABasePawn::HandleDestruction() {
	if (DeathCameraShake) {
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraShake);
	}
}

// Return the world space location of the turret mesh
UStaticMeshComponent* ABasePawn::GetTurret() const {
	return TurretMesh;
}

FVector ABasePawn::GetTurretMesh_Location() const {
	if (!TurretMesh) {
		UE_LOG(LogTemp, Error, TEXT("Turret Mesh missing!"));
		return FVector::ZeroVector;
	}	
	return TurretMesh->GetComponentLocation();
}

FRotator ABasePawn::GetTurretMesh_Rotation() const {
	if (!TurretMesh) {
		UE_LOG(LogTemp, Error, TEXT("Turret Mesh missing!"));
		return FRotator::ZeroRotator;
	}
	return TurretMesh->GetComponentRotation();
}

void ABasePawn::SetTurretMesh_Rotation(FRotator Rotation) {
	if (!TurretMesh)
		return;
	TurretMesh->SetWorldRotation(Rotation);
}

FVector ABasePawn::GetProjectileSpawn_Location() const {
	if (!ProjectileSpawnPoint)
		return FVector::ZeroVector;
	return ProjectileSpawnPoint->GetComponentLocation();
}

FRotator ABasePawn::GetProjectileSpawn_Rotation() const {
	if (!ProjectileSpawnPoint)
		return FRotator::ZeroRotator;
	return ProjectileSpawnPoint->GetComponentRotation();
}


// Will be overriden by the child classes
void ABasePawn::RotateTurret(FVector TargetLocation, bool Interpolate) {}
void ABasePawn::Fire() {}
