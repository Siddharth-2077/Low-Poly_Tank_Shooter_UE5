// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOONTANKS_API UHealthComponent : public UActorComponent {
	
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	// Increase current health
	void IncreaseHealthBy(float HealthValue);
	
	float GetHealth() const { return Health; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess = true))
	float MaxHealth = 100;
	
	float Health = 0;

	float IncreasedHealthAmount = 0;
	
	UPROPERTY()
	AActor* Owner = nullptr;

	UPROPERTY()
	class AToonTanksGameMode* ToonTanksGameMode = nullptr;

private:
	UFUNCTION()
	void DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Instigator, AActor* DamageCauser);
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
