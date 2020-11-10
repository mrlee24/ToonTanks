// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "PawnTank.h"

// Called when the game starts or when spawned
void APawnTurret::BeginPlay()
{
	Super::BeginPlay();
	
    GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandler, this, &APawnTurret::CheckFireCondition, FireRate, true);
    //GetWorldTimerManager()

    PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void APawnTurret::HandleDestruction() 
{
    // Call Base Pawn class HandleDestruction to play effects.
    Super::HandleDestruction();
    Destroy();
}

// Called every frame
void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (!PlayerPawn || ReturnDistanceToPlayer() > FireRange) {return;}

    RotateTurret(PlayerPawn->GetActorLocation());
}

void APawnTurret::CheckFireCondition() 
{
    // IF Player == null || is Dead THEN BAIL!!!
    if (!PlayerPawn || !PlayerPawn->GetIsPlayerAlive()) {return;}

    // IF Player IS in ranger THEN FIRE!!!
    if (ReturnDistanceToPlayer() <= FireRange)
        Fire();
}

float APawnTurret::ReturnDistanceToPlayer() 
{
    if (!PlayerPawn)
        return 0.f;

    return FVector::Dist(PlayerPawn->GetActorLocation(), this->GetActorLocation());
}
