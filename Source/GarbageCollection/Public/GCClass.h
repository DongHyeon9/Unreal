// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class UGCObjectNN;

/**
 * 
 */
class GARBAGECOLLECTION_API FGCClass : public FGCObject
{
public:

protected:

private:
	TObjectPtr<UGCObjectNN> obj;

public:
	FGCClass(TObjectPtr<UGCObjectNN> _GCObj);
	~FGCClass();
	virtual void AddReferencedObjects(FReferenceCollector& _Collector) override;
	virtual FString GetReferencerName() const override;
	FORCEINLINE TObjectPtr<UGCObjectNN> GetObj()const { return obj; }

protected:

private:

};