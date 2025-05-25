#include "Items/Item.h"
// #include "Slash/DebugMacros.h"
#include "Components/SphereComponent.h"
#include "Characters/SlashCharacter.h"
#include "NiagaraComponent.h"

AItem::AItem() {
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMeshComponent"));
	RootComponent = ItemMesh;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(GetRootComponent());

	EmbersEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Embers"));
	EmbersEffect->SetupAttachment(GetRootComponent());
}

void AItem::BeginPlay() {
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnSphereOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AItem::OnSphereEndOverlap);
	
  // UE_LOG is a alias
	// UE_LOG(LogTemp, Warning, TEXT("Hello World!"));

	// GEngine is a pointer for global engine, call functions with -> syntax
	// if (GEngine) {
	// 	GEngine->AddOnScreenDebugMessage(2, 60.f, FColor::Cyan, FString("Hello World!!!"));
	// }

	// SetActorLocation(FVector(0.f, 0.f , 15.f));
	// SetActorRotation(FRotator(0.f, 45.f , 0.f));
	// FVector const Location = GetActorLocation();
	// FVector const Forward = GetActorForwardVector();

	// No need to ; since the macro has it
	// DRAW_DEBUG_SPHERE(Location)
	// DRAW_DEBUG_LINE(Location, Location + Forward * 100.f)
	// DRAW_DEBUG_POINT(Location + Forward * 100.f)
	// DRAW_DEBUG_VECTOR(Location, Location + Forward * 100.f)

	// Template function call
	// int32 AndInt = Avg<int32>(1, 3);
	// UE_LOG(LogTemp, Warning, TEXT("Avg of 1 and 3: %d"), AndInt);
	//
	// float AvgFloat = Avg<float>(3.45f, 7.86f);
	// UE_LOG(LogTemp, Warning, TEXT("AvgFloat of 3.45 and 7.86: %f"), AvgFloat);
}

float AItem::TransformedSin() {
	return Amplitude * FMath::Sin(RunningTime * TimeConstant);
}

float AItem::TransformedCos() {
	return Amplitude * FMath::Cos(RunningTime * TimeConstant);
}

void AItem::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	ASlashCharacter* SlashCharacter = Cast<ASlashCharacter>(OtherActor);
	if (SlashCharacter) {
		SlashCharacter->SetOverlappingItem(this);
	}
}

void AItem::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	ASlashCharacter* SlashCharacter = Cast<ASlashCharacter>(OtherActor);
	if (SlashCharacter) {
		SlashCharacter->SetOverlappingItem(nullptr);
	}
}


void AItem::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	RunningTime += DeltaTime;

	// UE_LOG(LogTemp, Warning, TEXT("DeltaTime: %f"), DeltaTime);
	// FString Message = FString::Printf(TEXT("DeltaTime: %f"), DeltaTime);

	// Movement rate in units of cm/s
	// float const MovementRate = 50.f;
	// float const RotationRate = 45.f;

	// MovementRate * DeltaTime -> (cm/s) * (s/frame) = (cm/frame)
	// AddActorWorldOffset(FVector(MovementRate * DeltaTime, 0.f, 0.f));
	// AddActorWorldRotation(FRotator(0.f, RotationRate * DeltaTime, 0.f));
	// DRAW_DEBUG_SPHERE_SINGLE_FRAME(GetActorLocation());
	// DRAW_DEBUG_VECTOR_SINGLE_FRAME(GetActorLocation(), GetActorLocation() + GetActorForwardVector() * 100.f);

	// FVector AvgVector = Avg<FVector>(GetActorLocation(), FVector::ZeroVector);
	//DRAW_DEBUG_POINT_SINGLE_FRAME(AvgVector);

	// This will not work since rotator is not divisible, this can happen when using template functions
	// FRotator AvgRotator  = Avg<FRotator>(GetActorRotation(), FRotator::ZeroRotator);
	
	// Use sin to change the offset
	// RunningTime += DeltaTime;
	// float const DeltaZ = Amplitude * FMath::Sin(RunningTime * TimeConstant);
	// AddActorWorldOffset(FVector(0.f, 0.f, DeltaZ));

	// if (GEngine) {
	// 	FString const Name = GetName(); 
	// 	FString const NameMessage = FString::Printf(TEXT("Item Name: %s"), *Name);
	// 	GEngine->AddOnScreenDebugMessage(3, 60.f, FColor::Emerald, FString::SanitizeFloat(DeltaTime));
	// 	GEngine->AddOnScreenDebugMessage(3, 60.f, FColor::Silver, NameMessage);
	// }

	if (ItemState == EItemState::EIS_Hovering) {
		AddActorWorldOffset(FVector(0.0f, 0.f, TransformedSin()));
	}
}
