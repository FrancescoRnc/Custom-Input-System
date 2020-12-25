// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiInputControlComponent.h"

// Sets default values for this component's properties
UMultiInputControlComponent::UMultiInputControlComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMultiInputControlComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	MakeMap();
}


// Called every frame
void UMultiInputControlComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMultiInputControlComponent::MakeMap()
{	
	InputPressMap.Add(EInputButtonType::PadRight, NewObject<UInputContainerDispatcher>());
	InputPressMap[EInputButtonType::PadRight]->PushFunction({});
	InputPressMap.Add(EInputButtonType::PadLeft, NewObject<UInputContainerDispatcher>());
	InputPressMap[EInputButtonType::PadLeft]->PushFunction({});

	InputReleaseMap.Add(EInputButtonType::PadRight, NewObject<UInputContainerDispatcher>());
	InputReleaseMap[EInputButtonType::PadRight]->PushFunction({});
	InputReleaseMap.Add(EInputButtonType::PadLeft, NewObject<UInputContainerDispatcher>());
	InputReleaseMap[EInputButtonType::PadLeft]->PushFunction({});

}

// Push / Pop
void UMultiInputControlComponent::PushNewFunction(const EInputButtonType type, const FFuncParam binder)
{
	//auto container = InputMap[(uint8)type];
	auto container = InputPressMap[type];
	container->PushFunction(binder);
	container->BindLastFunction();
}

void UMultiInputControlComponent::PushNullFunction(const EInputButtonType type)
{
	//auto container = InputMap[(uint8)type];
	auto container = InputPressMap[type];
	container->PushEmptyFunction();
	container->UnbindFunction();
}

FFuncParam UMultiInputControlComponent::PopLastFunction(const EInputButtonType type)
{
	//auto container = InputMap[(uint8)type];
	auto container = InputPressMap[type];
	auto func = container->PopFunction();
	container->BindLastFunction();
	return func;
}

// Binding
void UMultiInputControlComponent::BindLastFunction(const EInputButtonType type)
{
	//auto container = InputMap[(uint8)type];
	auto container = InputPressMap[type];
	container->BindLastFunction();
}

void UMultiInputControlComponent::UnbindFunction(const EInputButtonType type)
{
	//auto container = InputMap[(uint8)type];
	auto container = InputPressMap[type];
	container->UnbindFunction();
}

// Execution
void UMultiInputControlComponent::Execute(const EInputButtonType type)
{
	//auto container = InputMap[(uint8)type];
	auto container = InputPressMap[type];
	container->Execute();
}

// Exclusion
void UMultiInputControlComponent::SetExclusion(const TSet< EInputButtonType> map)
{
	ButtonExclusionMap = map;
}

void UMultiInputControlComponent::AddExclusion(const TSet< EInputButtonType> map)
{
	for (auto item : map)
		ButtonExclusionMap.Add(item);
}

void UMultiInputControlComponent::ShrinkExclusion(const TSet< EInputButtonType> map)
{
	for (auto item : map)
		ButtonExclusionMap.Remove(item);
}

void UMultiInputControlComponent::ResetExclusion()
{
	int32 tmp = ButtonExclusionMap.Num();
	ButtonExclusionMap.Empty(tmp);
}

void UMultiInputControlComponent::UpdateMapAvaliability()
{
	//for (uint8 i = 0; i < (uint8)EInputButtonType::TOTAL; i++)
	//{
	//	if (ButtonExclusionMap.Contains((EInputButtonType)i))
	//		InputMap[i]->DisableBinding();
	//	else InputMap[i]->AbleBinding();
	//}

	//TArray<EInputButtonType> keys;
	//InputPressMap.GetKeys(keys);
	//for (auto item : keys)
	//{
	//	if (ButtonExclusionMap.Contains(item))
	//		InputPressMap[item]->DisableBinding();
	//	else InputPressMap[item]->AbleBinding();
	//}
}