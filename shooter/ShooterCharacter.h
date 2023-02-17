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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	/* Camera boom ��������̶��ڽ�ɫ֮��Ļ�е�� */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/* �����ɫ������� */
	class UCameraComponent * FollowCamera;


public:
	/* ���� CameraBoom  ���� */
	FORCEINLINE USpringArmComponent*GetCameraBoom() const { return CameraBoom; }
	/* ����  FollowCamera ���� */
	FORCEINLINE UCameraComponent * GetFollowCamera() const { return FollowCamera; }
};
