// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "HealthBox.h"
#include "HealthComponent.h"
#include "Tank.h"
#include "ToonTanksPlayerController.h"
#include "Tower.h"
#include "Kismet/GameplayStatics.h"


void AToonTanksGameMode::BeginPlay() {
	Super::BeginPlay();

	World = GetWorld();
	HandleGameStart();	
}

// Enable Player after countdown timer
void AToonTanksGameMode::HandleGameStart() {
	PlayerTank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(World, 0));
	ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	StartGame();
	
	// Disable the player till countdown ends
	if (ToonTanksPlayerController) {
		ToonTanksPlayerController->SetPlayerEnabled(false);
		
		// Create the delegate for enabling player
		EnablePlayerDelegate = FTimerDelegate::CreateUObject(
			ToonTanksPlayerController,
			&AToonTanksPlayerController::SetPlayerEnabled,
			true
		);

		// Set the timer to enable player
		GetWorldTimerManager().SetTimer(TimerHandle, EnablePlayerDelegate, TimeBeforeStart, false);
		
	} else {
		UE_LOG(LogTemp, Error, TEXT("Custom game mode: ToonTanksPlayerController doesn't exist!"));
	}
}


// Called from HealthComponent class when an Actor dies
void AToonTanksGameMode::ActorDied(AActor* DeadActor) {
	if (!DeadActor)
		return;
	// If it's the Player Tank that died
	if (DeadActor == PlayerTank) {
		// Player Lost
		PlayerTank->HandleDestruction();
		if (ToonTanksPlayerController) {
			ToonTanksPlayerController->SetPlayerEnabled(false);			
		}
		PlayerDead = true;
		if (PlayerTank->GetDeathParticles()) {
			UGameplayStatics::SpawnEmitterAtLocation(
				GetWorld(),
				PlayerTank->GetDeathParticles(),
				PlayerTank->GetActorLocation(),
				FRotator::ZeroRotator,
				FVector::OneVector * 1.5
			);
		}
		if (LoseSound) {
			UGameplayStatics::PlaySoundAtLocation(
				GetWorld(),
				LoseSound,
				PlayerTank->GetActorLocation(),
				LoseSoundVolume,
				LoseSoundPitch
			);
		}		
		GameOver(false);
		
	// If its an Enemy Tower that died	
	} else if (ATower* Tower = Cast<ATower>(DeadActor)) {
		Tower->HandleDestruction();
		DecrementTowerCount();
		if (NumberOfTowersInWorld == 0) {
			// Player Won
			if (WinSound) {
				UGameplayStatics::PlaySoundAtLocation(
					GetWorld(),
					WinSound,
					PlayerTank->GetActorLocation(),
					WinSoundVolume,
					WinSoundPitch
				);
			}
			GameOver(true);
		}

	// If a health-box was destroyed	
	} else if (AHealthBox* HealthBox = Cast<AHealthBox>(DeadActor)) {		
		if (!PlayerTank)
			return;
		UHealthComponent* PlayerHealth = PlayerTank->FindComponentByClass<UHealthComponent>();
		if (PlayerHealth) {
			PlayerHealth->IncreaseHealthBy(HealthBox->GetHealthContained());
			UpdatePlayerHealth(PlayerHealth->GetHealth());
		}
		HealthBox->HandleDestruction();
	}
}
