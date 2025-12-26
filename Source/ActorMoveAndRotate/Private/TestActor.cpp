// Fill out your copyright notice in the Description page of Project Settings.

#include "TestActor.h"

#include <vector>

#include "Engine/Engine.h"

// Sets default values
ATestActor::ATestActor() {
  // Set this actor to call Tick() every frame.  You can turn this off to
  // improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATestActor::BeginPlay() {
  Super::BeginPlay();

  LogCurrentLocation();
  LogCurrentRotation();

  Counter = 0;

  GetWorldTimerManager().SetTimer(
      TimerHandle, this, &ATestActor::ExecuteRandomStep, 1.0f, true, 1.0f);
}

const float START_RANDOM_MOVEMENT_RANGE = -50.f;
const float END_RANDOM_MOVEMENT_RANGE = 50.f;

const float START_RANDOM_ROTATION_RANGE = -360.f;
const float END_RANDOM_ROTATION_RANGE = 360.f;

// Called every frame
void ATestActor::Tick(float DeltaTime) { Super::Tick(DeltaTime); }

// Turn() - 액터 회전 함수
void ATestActor::Turn() {
  // X, Y, Z에 랜덤한 회전 각도 생성
  float RandomRotatePitch =
      FMath::RandRange(START_RANDOM_ROTATION_RANGE, END_RANDOM_ROTATION_RANGE);
  float RandomRotateYaw =
      FMath::RandRange(START_RANDOM_ROTATION_RANGE, END_RANDOM_ROTATION_RANGE);
  float RandomRotateRoll =
      FMath::RandRange(START_RANDOM_ROTATION_RANGE, END_RANDOM_ROTATION_RANGE);
  FRotator NewRotation = GetActorRotation();
  NewRotation.Pitch = RandomRotatePitch;
  NewRotation.Yaw = RandomRotateYaw;
  NewRotation.Roll = RandomRotateRoll;
  SetActorRotation(NewRotation);
}

// Move() - 액터 이동 함수
void ATestActor::Move() {
  // X, Y, Z에 랜덤한 위치 생성
  float RandomMoveX =
      FMath::RandRange(START_RANDOM_MOVEMENT_RANGE, END_RANDOM_MOVEMENT_RANGE);
  float RandomMoveY =
      FMath::RandRange(START_RANDOM_MOVEMENT_RANGE, END_RANDOM_MOVEMENT_RANGE);
  float RandomMoveZ =
      FMath::RandRange(START_RANDOM_MOVEMENT_RANGE, END_RANDOM_MOVEMENT_RANGE);
  FVector NewLocation = GetActorLocation();
  NewLocation.X = RandomMoveX;
  NewLocation.Y = RandomMoveY;
  NewLocation.Z = RandomMoveZ;
  SetActorLocation(NewLocation);
}

// LogCurrentLocation() - 액터의 현재 위치를 로깅
void ATestActor::LogCurrentLocation() {
  FVector CurrentLocation = GetActorLocation();

  if (GEngine) {
    GEngine->AddOnScreenDebugMessage(
        -1, 10.f, FColor::Blue,
        FString::Printf(TEXT("[ Current Location ] (%.2f, %.2f, %.2f)"),
                        CurrentLocation.X, CurrentLocation.Y,
                        CurrentLocation.Z));
  }
}

// LogCurrentRotation() - 액터의 현재 회전 각도를 로깅
void ATestActor::LogCurrentRotation() {
  FRotator CurrentRotation = GetActorRotation();

  if (GEngine) {
    GEngine->AddOnScreenDebugMessage(
        -1, 10.f, FColor::Red,
        FString::Printf(
            TEXT("[ Current Rotation ] Pitch=%.2f, Yaw=%.2f, Roll=%.2f"),
            CurrentRotation.Pitch, CurrentRotation.Yaw, CurrentRotation.Roll));
  }
}

void ATestActor::ExecuteRandomStep() {
  if (Counter >= 10) {
    GetWorldTimerManager().ClearTimer(TimerHandle);

    if (GEngine) {
      GEngine->AddOnScreenDebugMessage(
          -1, 10.f, FColor::Green, TEXT("Finish!"));
    }
    return;
  }
  Move();
  LogCurrentLocation();
  Turn();
  LogCurrentRotation();
  Counter++;
}