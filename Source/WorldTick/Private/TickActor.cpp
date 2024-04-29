// Fill out your copyright notice in the Description page of Project Settings.
#include "TickActor.h"
#include "TickObject.h"

ATickActor::ATickActor()
{
	PrimaryActorTick.bCanEverTick = false;

}

void ATickActor::BeginPlay()
{
	Super::BeginPlay();
	
	tickObj = NewObject< UTickObject>();
	tickObj->RecursiveLog(tickObj);
}