// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"


UCLASS()
class TOONTANKS_API ATank : public ABasePawn {

	GENERATED_BODY()

public:
	// Constructor:
	ATank();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Handle destruction of this object
	virtual void HandleDestruction() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void RotateTurret(FVector TargetLocation, bool Interpolate) override;
	virtual void Fire() override;

private:
	// Visible Private Members:
	UPROPERTY(EditAnywhere)
	float MoveForwardSpeed = 420;

	UPROPERTY(EditAnywhere)
	float RotationSpeed = 45;

	UPROPERTY(EditAnywhere)
	float TurretInterpolationSpeed = 5;

	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArm = nullptr;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera = nullptr;

	UPROPERTY()
	class APlayerController* PlayerController = nullptr;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* DeathParticles = nullptr;

public:
	// Getters:
	APlayerController* GetPlayerController() const { return PlayerController; }

	UParticleSystem* GetDeathParticles() const { return DeathParticles; }	

private:
	// Private Members:
	bool PlayerController_Exists = false;

	FVector DeltaLocation{};
	FRotator DeltaRotation{};

	FHitResult HitResult{};

	FVector TargetDirection{};
	FRotator TargetRotation{};
	FRotator InterpolatedRotation{};

private:
	// Private Methods:
	void Move(float value);
	void Turn(float value);

	// Debug Methods:
	void LogInputValues(float MoveForwardValue);
	
};
