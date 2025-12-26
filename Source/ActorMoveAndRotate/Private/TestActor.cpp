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

  GetWorldTimerManager().SetTimer(
      TimerHandle, this, &ATestActor::ExecuteRandomStep, 1.0f, true, 1.0f);
}

const float START_RANDOM_MOVEMENT_RANGE = -100.f;
const float END_RANDOM_MOVEMENT_RANGE = 100.f;

const float START_RANDOM_ROTATION_RANGE = -360.f;
const float END_RANDOM_ROTATION_RANGE = 360.f;

// Called every frame
void ATestActor::Tick(float DeltaTime) { Super::Tick(DeltaTime); }

// Turn() - 액터 회전 함수
void ATestActor::Turn() {
  // X, Y, Z에 랜덤한 회전 각도 생성
  float RandomRotatePitch =
      FMath::FRandRange(START_RANDOM_ROTATION_RANGE, END_RANDOM_ROTATION_RANGE);
  float RandomRotateYaw =
      FMath::FRandRange(START_RANDOM_ROTATION_RANGE, END_RANDOM_ROTATION_RANGE);
  float RandomRotateRoll =
      FMath::FRandRange(START_RANDOM_ROTATION_RANGE, END_RANDOM_ROTATION_RANGE);
  FRotator NewRotation(RandomRotatePitch, RandomRotateYaw, RandomRotateRoll);
  SetActorRotation(NewRotation);
}

// Move() - 액터 이동 함수
void ATestActor::Move() {
  // 이동 전 위치 저장
  FVector LocationBeforeMove = GetActorLocation();

  // X, Y, Z에 랜덤한 위치 생성
  float RandomMoveX =
      FMath::FRandRange(START_RANDOM_MOVEMENT_RANGE, END_RANDOM_MOVEMENT_RANGE);
  float RandomMoveY =
      FMath::FRandRange(START_RANDOM_MOVEMENT_RANGE, END_RANDOM_MOVEMENT_RANGE);
  float RandomMoveZ =
      FMath::FRandRange(START_RANDOM_MOVEMENT_RANGE, END_RANDOM_MOVEMENT_RANGE);
  FVector NewLocation(RandomMoveX, RandomMoveY, RandomMoveZ);
  SetActorLocation(NewLocation);

  // 매 스텝마다 이동 거리 누적
  float StepDistance = FVector::Dist(LocationBeforeMove, NewLocation);
  TotalDistance += StepDistance;
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

// ExecuteRandomStep() - 랜덤 이동 및 회전 실행 
// 실행 마다 카운트 증가 
// 10회 실행 후 최종 결과 출력
void ATestActor::ExecuteRandomStep() {
  if (Count >= 10) {
    GetWorldTimerManager().ClearTimer(TimerHandle);

    if (GEngine) {
      GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Green,
                                       TEXT("Finish!"));
      GEngine->AddOnScreenDebugMessage(
          -1, 20.f, FColor::Green, FString::Printf(TEXT("=== 최종 결과 ===")));
      GEngine->AddOnScreenDebugMessage(
          -1, 20.f, FColor::Green,
          FString::Printf(TEXT("총 이동 거리: %.2f"), TotalDistance));
      GEngine->AddOnScreenDebugMessage(
          -1, 20.f, FColor::Green,
          FString::Printf(TEXT("총 이벤트 발생 횟수: %d회"), EventCount));
    }
    return;
  }
  if (GEngine) {
    GEngine->AddOnScreenDebugMessage(
        -1, 10.f, FColor::Blue,
        FString::Printf(TEXT("< Move Count : %d >"), Count + 1));
  }
  Move();
  LogCurrentLocation();
  Turn();
  LogCurrentRotation();
  TriggerEvent();
  Count++;
}

// TriggerEvent() - 이벤트 발생 함수 (50% 확률로 메시지 출력)
void ATestActor::TriggerEvent() {
  float RandomValue = FMath::FRandRange(0.f, 1.f);

  if (RandomValue <= 0.5f) {
    if (GEngine) {
      GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow,
                                       TEXT("Event Triggered!!!"));
      EventCount++;
    } else {
      if (GEngine) {
        GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan,
                                         TEXT("No Event Triggered."));
      }
    }
  }
}