// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ������������ˣ����������ײ�������ɫ����{ʲô��˼��û����}pulls in towards the character if there is a collision ��
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.f; // ����������ڽ�ɫ������˳��ȵ�λ��
	CameraBoom->bUsePawnControlRotation = true; // ������ҿ�������ת����������ˣ������ǲ�֪��arm����ʳ��˷���ɸ첲֮�⻹��ɶ��ķ��룩

	// ����һ�����������
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // ��������ӵ����������ĩ��
	FollowCamera->bUsePawnControlRotation = false;   // ���������������������ת
}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();


}

void AShooterCharacter::MoveForward(float Value)
{
	if ((Controller!=nullptr)&&(Value!=0.0f))
	{
		// ����Ҫ�ҵ��ĸ�������ǰ��
		//const  FRotator Rotation{ GetControlRotation() };
		//Ϊʲô����ķ�ʽд�ᱨ��
		const FRotator Rotation{ Controller->GetControlRotation() };
		const  FRotator YawRotation{ 0,Rotation.Yaw,0 };

		const FVector Direction{ FRotationMatrix{YawRotation}.GetUnitAxis(EAxis::X) };
		//����ĺ��� ����ͨ������ת����FRotationMatrix{YawRotation}���л��X��ķ���GetUnitAxis(EAxis::X)��
		//Ȼ����Direction����ָ���˿��������Ӧ�ķ���
		AddMovementInput(Direction, Value);
		//�ƶ�����
	}
}

void AShooterCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// ����Ҫ�ҵ��ĸ��������ҷ�
		const  FRotator Rotation{ GetControlRotation() };
		const  FRotator YawRotation{ 0,Rotation.Yaw,0 };

		const FVector Direction{ FRotationMatrix{YawRotation}.GetUnitAxis(EAxis::Y) };
		AddMovementInput(Direction, Value);
	}
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	
}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AShooterCharacter::MoveRight);
}

