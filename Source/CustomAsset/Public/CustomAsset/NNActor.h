// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NNActor.generated.h"

class UStaticMeshComponent;

/*
* UNNAsset�� ������ ��ġ������ ������ ����
*/
UCLASS()
class CUSTOMASSET_API ANNActor : public AActor
{
	GENERATED_BODY()
public:

protected:

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "NNActorConfig", meta = (AllowPrivateAccess = true))
	TObjectPtr<USceneComponent> rootComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "NNActorConfig", meta = (AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> mesh;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Interp, category = "NNColor", meta = (AllowPrivateAccess = true))
	FColor meshColor;

	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> dynamicMaterial;

public:	
	ANNActor();
	//�����Ϳ��� ƽ Ȱ��ȭ�� ���� �Լ�
	virtual bool ShouldTickIfViewportsOnly() const override { return true; }

protected:
	virtual void Tick(float DeltaTime) override;

private:

};
