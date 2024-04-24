// Fill out your copyright notice in the Description page of Project Settings.


#include "GCObjectNN.h"

UGCObjectNN::UGCObjectNN()
{

}

void UGCObjectNN::SetStringData(FString _StringData)
{
	stringData = MoveTemp(_StringData);
}