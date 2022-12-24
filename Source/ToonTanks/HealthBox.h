// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HealthBox.generated.h"


UENUM()
enum class Pickup { Health, Speed, FireRate };


UCLASS()
class TOONTANKS_API AHealthBox : public AActor {
	
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHealthBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Handle what happens when the box is destroyed
	void HandleDestruction();

	// Getters:
	float GetHealthContained() const { return HealthContained; }

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Components", meta=(AllowPrivateAccess = "true"))
	class UBoxComponent* BoxComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Components", meta=(AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BoxMesh = nullptr;
	
	UPROPERTY(EditAnywhere)
	class UHealthComponent* HealthComponent = nullptr;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Components", meta=(AllowPrivateAccess = "true"))
	Pickup ContainedItem = Pickup::Health;

	UPROPERTY(EditAnywhere, Category="Components")
	float HealthContained = 20;
	
	UPROPERTY(EditAnywhere, Category="Components")
	class UParticleSystem* DestroyedParticles = nullptr;
	UPROPERTY(EditAnywhere, Category="Components")
	float DeathParticlesSize = 0.5;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Components", meta=(AllowPrivateAccess = "true"))
	// Store a child class (TSubclassof<>) of a PickupItem to spawn on destruction of this box...

};
