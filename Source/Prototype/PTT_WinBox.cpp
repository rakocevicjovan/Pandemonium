// Fill out your copyright notice in the Description page of Project Settings.

#include "PTT_WinBox.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"


// Sets default values
APTT_WinBox::APTT_WinBox()
{
	triggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	triggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	triggerBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	triggerBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	triggerBox->SetBoxExtent(FVector(64.f));
	RootComponent = triggerBox;
}


// Called when the game starts or when spawned
void APTT_WinBox::BeginPlay()
{
	Super::BeginPlay();

	triggerBox->OnComponentBeginOverlap.AddDynamic(this, &APTT_WinBox::AppleTopple);
}


void APTT_WinBox::AppleTopple(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp,
								int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	UE_LOG(LogTemp, Log, TEXT("Overlapped with win box."));

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), woosh, GetActorLocation());
}

