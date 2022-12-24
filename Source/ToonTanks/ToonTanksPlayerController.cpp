// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksPlayerController.h"
#include "Tank.h"
#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"


void AToonTanksPlayerController::BeginPlay() {
	Super::BeginPlay();
	// Get the pointer to the game mode
	ToonTanksGameMode = Cast<AToonTanksGameMode>(UGameplayStatics::GetGameMode(this));
}

void AToonTanksPlayerController::SetPlayerEnabled(bool enabled) {
	if (ToonTanksGameMode)
		ToonTanksGameMode->SetGameStarted(true);
	if (enabled) {
		UGameplayStatics::GetPlayerPawn(this, 0)->EnableInput(this);
	} else {
		UGameplayStatics::GetPlayerPawn(this, 0)->DisableInput(this);
	}
	SetShowMouseCursor(enabled);
}
