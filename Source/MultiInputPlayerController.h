// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputContainerDispatcher.h"
#include "MultiInputPlayerController.generated.h"

/**
 * 
 */

// Here are contained InputCntainerDispatchers, one for each button,
// that execute the last function from their stack, if enabled

// This, with UInputContainerDispatcher files, could be used for every project.
// You just need to make the properly changes to the enum, and the quantity of containers

UCLASS()
class PROJECTNAME_API AMultiInputPlayerController : public APlayerController
{
	GENERATED_BODY()

	protected:

	// BeginPlay
	virtual void BeginPlay() override;
	
	public:

// Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UInputContainerDispatcher*> InputMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EInputButtonType, UInputContainerDispatcher*> InputPressMap;

	// Used to exclude containers, by given button types, to be executed
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSet<EInputButtonType> ButtonExclusionMap;

// Functions

	// Initialization of the containers
	UFUNCTION(BlueprintCallable)
	void MakeMap();

	// Push / Pop
	// Same as the container base, but given a button type
	UFUNCTION(BlueprintCallable)
	void PushNewFunction(const EInputButtonType type, const FFuncParam binder);

	UFUNCTION(BlueprintCallable)
	void PushNullFunction(const EInputButtonType type);

	UFUNCTION(BlueprintCallable)
	FFuncParam PopLastFunction(const EInputButtonType type);

	// Binding
	UFUNCTION(BlueprintCallable)
	void BindLastFunction(const EInputButtonType type);

	UFUNCTION(BlueprintCallable)
	void UnbindFunction(const EInputButtonType type);

	// Execution
	UFUNCTION(BlueprintCallable)
	void Execute(const EInputButtonType type);

	// Exclusion
	// Function used to manage the button exclusion system
	UFUNCTION(BlueprintCallable)
	void SetExclusion(const TSet< EInputButtonType> map);

	UFUNCTION(BlueprintCallable)
	void AddExclusion(const TSet< EInputButtonType> map);

	UFUNCTION(BlueprintCallable)
	void ShrinkExclusion(const TSet< EInputButtonType> map);

	UFUNCTION(BlueprintCallable)
	void ResetExclusion();

	UFUNCTION(BlueprintCallable)
	void UpdateMapAvaliability();
};
