// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 创建摄像机吊杆（如果发生碰撞，则向角色拉入{什么意思，没看懂}pulls in towards the character if there is a collision ）
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.f; // 摄像机跟随在角色距离吊杆长度的位置
	CameraBoom->bUsePawnControlRotation = true; // 根据玩家控制器旋转跟随相机吊杆（我真是不知道arm这个词除了翻译成胳膊之外还有啥别的翻译）

	// 创造一个跟随摄像机
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // 将相机链接到摄像机吊杆末端
	FollowCamera->bUsePawnControlRotation = false;   // 相机不相对于摄像机吊杆旋转
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
		// 首先要找到哪个方向是前方
		//const  FRotator Rotation{ GetControlRotation() };
		//为什么下面的方式写会报错
		const FRotator Rotation{ Controller->GetControlRotation() };
		const  FRotator YawRotation{ 0,Rotation.Yaw,0 };

		const FVector Direction{ FRotationMatrix{YawRotation}.GetUnitAxis(EAxis::X) };
		//上面的函数 先是通过从旋转矩阵（FRotationMatrix{YawRotation}）中获得X轴的方向（GetUnitAxis(EAxis::X)）
		//然后方向（Direction）便指向了控制器相对应的方向
		AddMovementInput(Direction, Value);
		//移动方向
	}
}

void AShooterCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// 首先要找到哪个方向是右方
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

