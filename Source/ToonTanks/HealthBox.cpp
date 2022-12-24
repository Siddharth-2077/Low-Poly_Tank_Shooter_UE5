// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthBox.h"
#include "HealthComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AHealthBox::AHealthBox() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	RootComponent = BoxComponent;
	
	BoxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Box Mesh"));
	BoxMesh->SetupAttachment(RootComponent);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
}

// Called when the game starts or when spawned
void AHealthBox::BeginPlay() {
	Super::BeginPlay();
	
}

// Called every frame
void AHealthBox::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

// Called when health is zero
void AHealthBox::HandleDestruction() {
	DrawDebugSphere(GetWorld(), GetActorLocation(), 60, 14, FColor::Green, true);
	if (DestroyedParticles) {
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			DestroyedParticles,
			GetActorLocation(),
			GetActorRotation(),
			FVector::OneVector * DeathParticlesSize
		);
	}
	Destroy();
}

