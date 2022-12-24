// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"


UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase {
	
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	void HandleGameStart();

	void DecrementTowerCount() { --NumberOfTowersInWorld; }
	
	// Events called in BP
	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();
	
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool PlayerWon);
	
public:
	UFUNCTION(BlueprintImplementableEvent)
	void UpdatePlayerHealth(float HealthAmount);
	
	// Will be called from the HealthComponent class
	void ActorDied(AActor* DeadActor);

	bool IsPlayerDead() const { return PlayerDead; }

	void IncrementNumTowersInWorld() { ++NumberOfTowersInWorld;	}

	void SetGameStarted(bool value) { GameStarted = value; }
	bool GetGameStarted() { return GameStarted; }

private:
	UPROPERTY()
	UWorld* World = nullptr;

	UPROPERTY()
	bool GameStarted = false;
	
	UPROPERTY()
	class ATank* PlayerTank = nullptr;

	UPROPERTY()
	int NumberOfTowersInWorld = 0;
	
	UPROPERTY(VisibleAnywhere)
	bool PlayerDead = false;

	UPROPERTY(EditAnywhere)
	float TimeBeforeStart = 3;

	FTimerHandle TimerHandle;
	FTimerDelegate EnablePlayerDelegate;

	UPROPERTY()
	class AToonTanksPlayerController* ToonTanksPlayerController = nullptr;
	
	UPROPERTY(EditAnywhere)
	class USoundBase* WinSound = nullptr;
	UPROPERTY(EditAnywhere)
	float WinSoundVolume = 1;
	UPROPERTY(EditAnywhere)
	float WinSoundPitch = 1;

	UPROPERTY(EditAnywhere)
	class USoundBase* LoseSound = nullptr;
	UPROPERTY(EditAnywhere)
	float LoseSoundVolume = 1;
	UPROPERTY(EditAnywhere)
	float LoseSoundPitch = 1;
	
};
