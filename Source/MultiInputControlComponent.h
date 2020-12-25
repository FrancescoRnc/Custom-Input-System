// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InputContainerDispatcher.h"
#include "MultiInputControlComponent.generated.h"

// A Component version of my actual Input System.
// This simplifies it by not being a Player Controller,
// this means that you can attach two of this in order to handle Pressed and Released input events.

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTNAME_API UMultiInputControlComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMultiInputControlComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

// Properties

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UInputContainerDispatcher*> InputMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EInputButtonType, UInputContainerDispatcher*> InputPressMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EInputButtonType, UInputContainerDispatcher*> InputReleaseMap;

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
