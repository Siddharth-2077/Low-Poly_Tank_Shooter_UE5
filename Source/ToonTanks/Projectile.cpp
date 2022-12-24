// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values
AProjectile::AProjectile() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	RootComponent = ProjectileMesh;
	
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));

	TrailParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Trail Particle Component"));
	TrailParticles->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay() {
	Super::BeginPlay();
	
	// Get owner of this projectile
	Owner = GetOwner();
	// Bind the function to generate hit events
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	// Play the projectile launch sound
	if (LaunchSound) {
		UGameplayStatics::PlaySoundAtLocation(
			GetWorld(),
			LaunchSound,
			GetActorLocation(),
			LaunchSoundVolume,
			LaunchSoundPitch
		);
	}
}

// Called every frame
void AProjectile::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	// Won't tick (set to false)
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	//UE_LOG(LogTemp, Display, TEXT("Object: %s -> HIT: %s | OtherComp = %s"), *HitComp->GetName(), *OtherActor->GetName(), *OtherComp->GetName());
	//UE_LOG(LogTemp, Display, TEXT("Owner = %s"), *Owner->GetActorNameOrLabel());

	// Play the hit sound
	UGameplayStatics::PlaySoundAtLocation(
		GetWorld(),
		HitSound,
		OtherActor->GetActorLocation(),
		HitSoundVolume,
		HitSoundPitch
	);
	
	if (OtherActor && OtherActor != Owner) {
		// Apply damage triggers the OnTakeAnyDamage delegate
		UGameplayStatics::ApplyDamage(
			OtherActor,
			DamageAmount,
			GetInstigatorController(),
			this,
			UDamageType::StaticClass()
		);

		// Spawn the hit effect particles on the damaged actor
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			HitParticles,
			Hit.ImpactPoint,
			OtherActor->GetActorRotation(),
			FVector::OneVector * HitEffectScaleValue
		);

		// Play camera shake when hit
		if (HitCameraShakeClass) {
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);
		}

		// Destroy the projectile 0.5 seconds after hitting
		ProjectileMesh->SetHiddenInGame(true);
		ProjectileMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		FTimerHandle DestroyTimerHandle;
		GetWorldTimerManager().SetTimer(DestroyTimerHandle, this, &AProjectile::DestroyProjectile, 0.5f, false);
		
	}	
	
}




