// Fill out your copyright notice in the Description page of Project Settings.

#include "PSObject.h"

UPSObject::UPSObject()
{
	data = TEXT("기본 값");
}

void UPSObject::PrintData(int32 _OtherData)
{
	UE_LOG(LogTemp, Warning, TEXT("%s : %d"), *data, _OtherData);
}
