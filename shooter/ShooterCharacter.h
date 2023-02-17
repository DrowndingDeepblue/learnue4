// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

UCLASS()
class SHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	/* 在向前/向后的输入时被调用 */
	void MoveForward(float Value);

	/* 在侧边移动的输入时被调用 （called for side to side input） */
	void MoveRight(float Value);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	/* Camera boom 将摄像机固定在角色之后的机械臂 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/* 跟随角色的摄像机 */
	class UCameraComponent * FollowCamera;


public:
	/* 返回 CameraBoom  子类 */
	FORCEINLINE USpringArmComponent*GetCameraBoom() const { return CameraBoom; }
	/* 返回  FollowCamera 子类 */
	FORCEINLINE UCameraComponent * GetFollowCamera() const { return FollowCamera; }
};
