// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidget.h"
#include "CppEditorUtilityWidget.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class CUSTOMEDITOREXTENSION_API UCppEditorUtilityWidget : public UEditorUtilityWidget
{
	GENERATED_BODY()
public:

protected:

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,category="DefaultConfig",meta=(AllowPrivateAccess=true,BindWidget))
	TObjectPtr<UButton> btn_Button;

public:

protected:
	virtual void NativeConstruct()override;

private:
	UFUNCTION()
	void OnClickedButton();
};
