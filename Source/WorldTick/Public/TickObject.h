// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Tickable.h"
#include "TickObject.generated.h"

/**
 * 
 */
UCLASS()
class WORLDTICK_API UTickObject :
	public UObject,
	public FTickableGameObject
{
	GENERATED_BODY()
public:


protected:

private:
	//PrimaryActorTick.bCanEverTick = false;
	//이거처럼 구현할려고 넣어봤다
	bool bUseTick;

public:
	UTickObject();
	virtual TStatId GetStatId() const override;
	virtual UWorld* GetWorld()const override final;
	void RecursiveLog(TObjectPtr<UObject> _Outer);

protected:	
	void Tick(float _DeltaTime) override;
	//액터처럼 BP사용할수 있게 구현할려고 넣어봤다
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Tick"))
	void ReceiveTick(float _DeltaTime);

private:
	ULevel* GetLevel() const;
	AWorldSettings* GetWorldSettings() const;

};
