// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Projectile.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"


// Constructor:
ATank::ATank() {	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));
	SpringArm->SetupAttachment(RootComponent);
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	Camera->SetupAttachment(SpringArm);
}

// Setup the player input component:
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
}

// Called when the game starts or when spawned
void ATank::BeginPlay() {
	Super::BeginPlay();

	PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController) {
		PlayerController_Exists = true;
		PlayerController->SetShowMouseCursor(true);
	}
	// Setup the projectile spawn parameters:
	Super::ProjectileSpawnParameters.Owner = this;
	Super::ProjectileSpawnParameters.Instigator = GetInstigator();
}

// Called every frame
void ATank::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	
	if (PlayerController_Exists) {
		PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
		DrawDebugSphere(Super::World, HitResult.ImpactPoint, 30, 12, FColor::Blue);
		RotateTurret(HitResult.ImpactPoint, true);
	}
}

// Move the tank
void ATank::Move(float value) {
	//LogInputValues(value);
	DeltaLocation = FVector::ZeroVector;
	DeltaLocation.X = value * MoveForwardSpeed * UGameplayStatics::GetWorldDeltaSeconds(Super::World);
	AddActorLocalOffset(DeltaLocation, true);
}

// Turn the tank
void ATank::Turn(float value) {
	//LogInputValues(value);
	DeltaRotation = FRotator::ZeroRotator;
	DeltaRotation.Yaw = value * RotationSpeed * UGameplayStatics::GetWorldDeltaSeconds(Super::World);
	AddActorLocalRotation(DeltaRotation, true);
}

// Overriden protected function from <ABasePawn>
void ATank::RotateTurret(FVector TargetLocation, bool Interpolate) {
	TargetDirection = TargetLocation - Super::GetTurretMesh_Location();
	TargetRotation = FRotator(0, TargetDirection.Rotation().Yaw, 0);
	if (!Interpolate) {
		Super::SetTurretMesh_Rotation(TargetRotation);
	}
	else {
		InterpolatedRotation = FMath::RInterpTo(
			Super::GetTurretMesh_Rotation(),
			TargetRotation,
			UGameplayStatics::GetWorldDeltaSeconds(Super::World),
			TurretInterpolationSpeed
		);
		Super::SetTurretMesh_Rotation(InterpolatedRotation);
	}	
}

// Overriden protected function from <ABasePawn>
void ATank::Fire() {
	DrawDebugSphere(Super::World, Super::GetProjectileSpawn_Location(), 20, 14, FColor::Green, false, 1);
	Super::World->SpawnActor<AProjectile>(
		Super::ProjectileClass,
		Super::GetProjectileSpawn_Location(),
		Super::GetProjectileSpawn_Rotation(),
		ProjectileSpawnParameters
	);
	UE_LOG(LogTemp, Warning, TEXT("Fired projectile"));
}

// Handle destruction of the Tank when health reaches 0
void ATank::HandleDestruction() {
	Super::HandleDestruction();
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
}

void ATank::LogInputValues(float value) {
	UE_LOG(LogTemp, Display, TEXT("Move Value: %f"), value);
}

