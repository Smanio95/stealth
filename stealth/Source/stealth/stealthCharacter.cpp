// Copyright Epic Games, Inc. All Rights Reserved.

#include "stealthCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Enemy.h"
#include <Kismet/KismetMathLibrary.h>
#include <Kismet/GameplayStatics.h>
#include "stealthGameMode.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AstealthCharacter

AstealthCharacter::AstealthCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Create Focus Box Collision
	FocusBox = CreateDefaultSubobject<UBoxComponent>(TEXT("FocusBox"));
	FocusBox->SetupAttachment(RootComponent);

	// Noise emitter
	PawnNoiseEmitter = CreateDefaultSubobject<UPawnNoiseEmitterComponent>(TEXT("Noise Emitter"));

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void AstealthCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	FocusBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &AstealthCharacter::OnOverlapBegin);
	FocusBox->OnComponentEndOverlap.AddUniqueDynamic(this, &AstealthCharacter::OnOverlapExit);

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	AstealthGameMode* GM = Cast<AstealthGameMode>(GetWorld()->GetAuthGameMode());

	if (GM)
	{
		GM->OnEndGame.AddUniqueDynamic(this, &AstealthCharacter::Deactivate);
	}
}

void AstealthCharacter::Tick(float DeltaSeconds)
{
	if (!CurrentFocused) return;

	CurrentFocused->ToggleFocus(FVector::DotProduct(GetActorForwardVector(), CurrentFocused->GetActorForwardVector()) >= AttackMinDotValue);
}

void AstealthCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AEnemy* Enemy = Cast<AEnemy>(OtherActor);

	if (!Enemy) return;

	CurrentFocused = GetLookClosestEnemy(Enemy);
}

void AstealthCharacter::OnOverlapExit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == CurrentFocused && !GetMesh()->GetAnimInstance()->Montage_IsPlaying(AttackMontage))
	{
		CurrentFocused->ToggleFocus(false);
		CurrentFocused = nullptr;
	}
}

void AstealthCharacter::OnMontageEnd(UAnimMontage* Montage, bool bInterrupted)
{
	GetController()->SetIgnoreMoveInput(false);
}

void AstealthCharacter::OnNotify(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload)
{
	if (NotifyName != KillNotify) return;

	CurrentFocused->Die();

	CurrentFocused = nullptr;
}

void AstealthCharacter::PlayAttack()
{
	UAnimInstance* Instance = GetMesh()->GetAnimInstance();

	if (!Instance || !AttackMontage) return;

	float MontageLength = Instance->Montage_Play(AttackMontage);

	if (MontageLength <= 0) return;

	GetController()->SetIgnoreMoveInput(true);

	CurrentFocused->Immobilize();

	Instance->OnPlayMontageNotifyBegin.AddUniqueDynamic(this, &AstealthCharacter::OnNotify);
	Instance->OnMontageEnded.AddUniqueDynamic(this, &AstealthCharacter::OnMontageEnd);

}

AEnemy* AstealthCharacter::GetLookClosestEnemy(AEnemy* Other)
{
	if (!CurrentFocused)
	{
		return Other;
	}

	FVector CameraForward = GetFollowCamera()->GetForwardVector();

	FVector Dir1 = CurrentFocused->GetActorLocation() - GetActorLocation();
	Dir1.Normalize();
	float Angle1 = FMath::Acos(FVector::DotProduct(CameraForward, Dir1));

	FVector Dir2 = Other->GetActorLocation() - GetActorLocation();
	Dir2.Normalize();
	float Angle2 = FMath::Acos(FVector::DotProduct(CameraForward, Dir2));

	if (Angle1 > Angle2)
	{
		// switch focus
		CurrentFocused->ToggleFocus(false);

		return Other;
	}

	return CurrentFocused;
}

void AstealthCharacter::Attack()
{
	UAnimInstance* Instance = GetMesh()->GetAnimInstance();

	if (!Instance || !AttackMontage || Instance->Montage_IsPlaying(AttackMontage)) return;

	if (!CurrentFocused || FVector::DotProduct(GetActorForwardVector(), CurrentFocused->GetActorForwardVector()) < AttackMinDotValue) return;

	FTransform StartTransform = FTransform(
		UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), GetActorLocation() + GetActorForwardVector()),
		GetActorLocation(),
		FVector::OneVector
	);

	FVector EndLoc = CurrentFocused->GetActorLocation() - CurrentFocused->GetActorForwardVector() * RepositionDistance;

	FTransform EndTransform = FTransform(
		UKismetMathLibrary::FindLookAtRotation(EndLoc, CurrentFocused->GetActorLocation()),
		EndLoc,
		FVector::OneVector
	);

	CustomReposition(StartTransform, EndTransform);

	PlayAttack();
}

void AstealthCharacter::Deactivate(bool Success)
{
	GetController()->SetIgnoreMoveInput(true);
	GetController()->SetIgnoreLookInput(true);

	if (!Success)
	{
		bIsDead = true;
	}
	else
	{
		bHasWon = true;
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void AstealthCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AstealthCharacter::ToggleCrouch);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AstealthCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AstealthCharacter::Look);

		// Attack
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &AstealthCharacter::Attack);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AstealthCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);

		// make noise while moving
		PawnNoiseEmitter->MakeNoise(this, (bIsCrouched ? CrouchVolume : StandVolume) * GetWorld()->DeltaTimeSeconds, GetActorLocation());
	}
}

void AstealthCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AstealthCharacter::ToggleCrouch()
{
	if (bIsCrouched)
	{
		UnCrouch();
	}
	else
	{
		Crouch();
	}
}
