// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "GameFramework/Actor.h"
#include "Tower.generated.h"

UCLASS()
class TOONTANKS_API ATower : public ABasePawn {
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATower();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void RotateTurret(FVector TargetLocation, bool Interpolate) override;
	virtual void Fire() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void HandleDestruction() override;

private:
	void UpdateDistanceToPlayer();
	void CheckFireCondition();
	
private:
	bool PlayerTank_Exists = false;
	bool TurretMesh_Exists = false;
	
	float Distance{};
	
	FVector PlayerDirection{};
	FRotator RequiredRotation{};
	FRotator InterpolatedRotation{};

	FTimerHandle TimerHandle{};

private:	
	UPROPERTY()
	class ATank* PlayerTank = nullptr;

	UPROPERTY(EditAnywhere)
	float FireRate = 2;
	
	UPROPERTY(EditAnywhere)
	float AttackRange = 700;

	UPROPERTY(EditAnywhere)
	float RotationInterpolationSpeed = 5;

	UPROPERTY()
	class AToonTanksGameMode* ToonTanksGameMode = nullptr;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* DeathParticles = nullptr;
	
};
