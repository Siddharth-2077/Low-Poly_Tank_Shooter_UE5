// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent() {	
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	
}


// Increase the health of this parent Actor
void UHealthComponent::IncreaseHealthBy(float HealthValue) {
	float MaxAddition = MaxHealth - Health;
	if (HealthValue <= MaxAddition) {
		Health += HealthValue;
		IncreasedHealthAmount = HealthValue;
		return;
	}
	Health += MaxAddition;
	IncreasedHealthAmount = MaxAddition;
}


// Called when the game starts
void UHealthComponent::BeginPlay() {	
	Super::BeginPlay();

	Owner = GetOwner();
	ToonTanksGameMode = Cast<AToonTanksGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	
	// Set health to max health
	Health = MaxHealth;
	if (Owner) {
		// Bind the callback function to the 'OnTakeAnyDamage' delegate:
		Owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);	
	}
}


// Callback function called in OnDamageTaken:
void UHealthComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Instigator, AActor* DamageCauser) {
	if (Health <= 0)
		return;
	Health -= Damage;
	UE_LOG(LogTemp, Display, TEXT("%s damaged %s | HEALTH = %f"), *DamageCauser->GetActorNameOrLabel(), *DamagedActor->GetActorNameOrLabel(), Health);
	if (Health <= 0) {
		Health = 0;
		if (ToonTanksGameMode)
			ToonTanksGameMode->ActorDied(DamagedActor);
		else
			UE_LOG(LogTemp, Error, TEXT("ToontanksGameMode is NULL!"));
	}
} 

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

