// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TOONTANKS_API AProjectile : public AActor {
	
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
private:
	AActor* Owner = nullptr;

	UPROPERTY(EditAnywhere)
	float DamageAmount = 25;
	
	UPROPERTY(EditDefaultsOnly)
	float DestroyAfterSeconds = 3;
	
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	class UStaticMeshComponent* ProjectileMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UProjectileMovementComponent* ProjectileMovement = nullptr;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* HitParticles = nullptr;
	UPROPERTY(EditAnywhere)
	float HitEffectScaleValue = 1.5;

	UPROPERTY(EditDefaultsOnly)
	class UParticleSystemComponent* TrailParticles = nullptr;

	UPROPERTY(EditAnywhere)
	class USoundBase* LaunchSound = nullptr;
	UPROPERTY(EditAnywhere)
	float LaunchSoundVolume = 0.25;
	UPROPERTY(EditAnywhere)
	float LaunchSoundPitch = 1;

	UPROPERTY(EditAnywhere)
	class USoundBase* HitSound = nullptr;
	UPROPERTY(EditAnywhere)
	float HitSoundVolume = 0.1;
	UPROPERTY(EditAnywhere)
	float HitSoundPitch = 1;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UCameraShakeBase> HitCameraShakeClass;
	
private:
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	void DestroyProjectile() { Destroy(); }
	
};
