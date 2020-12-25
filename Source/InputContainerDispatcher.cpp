// Fill out your copyright notice in the Description page of Project Settings.


#include "InputContainerDispatcher.h"

// Push / Pop
void UInputContainerDispatcher::PushFunction(const FFuncParam binder)
{
	FunctionStack.Push(binder);
	UE_LOG(LogTemp, Warning, TEXT("push"));

	//BindLastFunction();
}

FFuncParam UInputContainerDispatcher::PopFunction()
{
	FFuncParam tmp = {};

	if (FunctionStack.Num() <= 1)
	{
		return tmp;
	}

	tmp = FunctionStack.Pop();
	UE_LOG(LogTemp, Warning, TEXT("pop"));

	return tmp;
}

void UInputContainerDispatcher::PushEmptyFunction()
{
	FunctionStack.Push({});
	BindLastFunction();
}

// Binding
void UInputContainerDispatcher::BindLastFunction()
{
	if (!bAllowBind) return;
	inputPress = FunctionStack.Last();
	UE_LOG(LogTemp, Warning, TEXT("bind"));
}

void UInputContainerDispatcher::UnbindFunction()
{
	inputPress = {};
	UE_LOG(LogTemp, Warning, TEXT("unbind"));
}

void UInputContainerDispatcher::AbleBinding()
{
	BindLastFunction();
	bAllowBind = true;
}

void UInputContainerDispatcher::DisableBinding()
{
	UnbindFunction();
	bAllowBind = false;
}

// Execution
void UInputContainerDispatcher::Execute()
{
	inputPress.ExecuteIfBound();
}