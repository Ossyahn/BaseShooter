// Copyright 2020 Alberto Romero Garcia, all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ArrowComponent.h"
#include "DeathCamComponent.generated.h"

/**
 * 
 */
UCLASS()
class BASESHOOTER_API UDeathCamComponent : public UArrowComponent
{
	GENERATED_BODY()
	
public:
	UDeathCamComponent();

	UPROPERTY(EditDefaultsOnly, Category = "DeathCam")
	float BlendTime = 3.f;

	UPROPERTY(EditDefaultsOnly, Category = "DeathCam")
	TEnumAsByte<EViewTargetBlendFunction> BlendFunction = EViewTargetBlendFunction::VTBlend_EaseOut;

	UPROPERTY(EditDefaultsOnly, Category = "DeathCam")
	float BlendExponent = 5.f;

	UPROPERTY(EditDefaultsOnly, Category = "DeathCam")
	bool LockOutgoing = false;

	void ExecuteDeathCam(APlayerController* PlayerController);
};
