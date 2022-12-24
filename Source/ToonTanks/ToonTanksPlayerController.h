// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ToonTanksPlayerController.generated.h"


UCLASS()
class TOONTANKS_API AToonTanksPlayerController : public APlayerController {
	
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY()
	class AToonTanksGameMode* ToonTanksGameMode = nullptr;
	
public:
	void SetPlayerEnabled(bool enabled);
	
};
