// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn {

	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/// Rotate the turret mesh to face the TargetLocation
	virtual void RotateTurret(FVector TargetLocation, bool Interpolate);
	
	// Fire the projectile
	virtual void Fire();

	// Handle destruction mechanics of the object
	virtual void HandleDestruction();

	// Getters:
	UStaticMeshComponent* GetTurret() const;
	FVector GetTurretMesh_Location() const;
	FRotator GetTurretMesh_Rotation() const;

	FVector GetProjectileSpawn_Location() const;
	FRotator GetProjectileSpawn_Rotation() const;

	// Setters:
	void SetTurretMesh_Rotation(FRotator);

protected:
	// Protected Members:
	UPROPERTY()
	class UWorld* World = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TSubclassOf<class UCameraShakeBase> DeathCameraShake;

	// Spawn parameters for the projectile
	FActorSpawnParameters ProjectileSpawnParameters{};

private:
	// Private members:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BaseMesh = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* TurretMesh = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* ProjectileSpawnPoint = nullptr;

};
