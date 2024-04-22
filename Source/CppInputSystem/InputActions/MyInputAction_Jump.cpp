// Fill out your copyright notice in the Description page of Project Settings.


#include "../InputActions/MyInputAction_Jump.h"

UMyInputAction_Jump::UMyInputAction_Jump()
{
	Triggers.Reserve(2);

	auto pressed = UInputTriggerPressed::StaticClass()->GetDefaultObject<UInputTriggerPressed>();
	auto released = UInputTriggerReleased::StaticClass()->GetDefaultObject<UInputTriggerReleased>();
	Triggers.Emplace(pressed);
	Triggers.Emplace(released);
}
