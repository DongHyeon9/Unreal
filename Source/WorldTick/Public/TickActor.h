// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TickActor.generated.h"

class UTickObject;

UCLASS()
class WORLDTICK_API ATickActor : public AActor
{
	GENERATED_BODY()
	
public:

protected:

private:
	UPROPERTY()
	TObjectPtr<UTickObject> tickObj;

public:	
	ATickActor();

protected:
	virtual void BeginPlay() override;
	

private:

};
