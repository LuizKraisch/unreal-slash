#include "Pawns/Bird.h"
// Forward declaration: Keep the component includes on the file that really use this include, to avoid extra load.
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Camera/CameraComponent.h"

ABird::ABird() {
	PrimaryActorTick.bCanEverTick = true;

	// TEXT = Internal name of the subobject
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	Capsule->SetCapsuleHalfHeight(20.f);
	Capsule->SetCapsuleRadius(15.f);
	// Capsule is usually the root component
	SetRootComponent(Capsule);

	BirdMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BirdMesh"));
	// Set it up to the root component
	BirdMesh->SetupAttachment(GetRootComponent());
	
	BirdMesh->SetSimulatePhysics(true);
	BirdMesh->SetEnableGravity(false);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 300.f;

	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
	ViewCamera->SetupAttachment(CameraBoom);
	
	FloatingMovement = FindComponentByClass<UFloatingPawnMovement>();

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void ABird::BeginPlay() {
	Super::BeginPlay();
}

void ABird::MoveForward(float Value) {
	if (Controller && Value != 0.f) {
		FVector Forward = GetActorForwardVector();
		AddMovementInput(Forward, Value);
	}
}

void ABird::Turn(float Value) {
	if (Controller && Value != 0.f) {
		AddControllerYawInput(Value);
	}
}

void ABird::LookUp(float Value) {
	if (Controller && Value != 0.f) {
		AddControllerPitchInput(Value);
	}
}

void ABird::Boost(float Value) {
	// if (FloatingMovement) {
	// 	FloatingMovement->MaxSpeed = (Value > 0.f) ? 2400.0f : 1200.0f;
	// }
	if (Controller && Value != 0.f)
	{
		UE_LOG(LogTemp, Display, TEXT("Boost"));
	}
}

void ABird::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

// Called to bind functionally to input
void ABird::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// & -> Address operator
	PlayerInputComponent->BindAxis(FName("MoveForward"), this, &ABird::MoveForward);
	PlayerInputComponent->BindAxis(FName("Turn"), this, &ABird::Turn);
	PlayerInputComponent->BindAxis(FName("LookUp"), this, &ABird::LookUp);
	PlayerInputComponent->BindAxis(FName("Boost"), this, &ABird::Boost);
}
