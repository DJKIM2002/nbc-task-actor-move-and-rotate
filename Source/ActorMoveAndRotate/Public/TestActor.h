// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestActor.generated.h"

UCLASS()
class ACTORMOVEANDROTATE_API ATestActor : public AActor {
  GENERATED_BODY()

 public:
  // Sets default values for this actor's properties
  ATestActor();

 protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

 public:
  // Called every frame
  virtual void Tick(float DeltaTime) override;

 public:
  // Rotate the actor
  void Turn();
  // Move the actor
  void Move();
  // Log the current location of the actor
  void LogCurrentLocation();
  // Log the current rotation of the actor
  void LogCurrentRotation();
  // Execute a random step of movement and rotation
  void ExecuteRandomStep();

 private:
  // Timer handle for scheduling movements and rotations
  FTimerHandle TimerHandle;
  // Counter to track the number of movements and rotations
  int32 Counter = 0;
};
