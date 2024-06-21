// Fill out your copyright notice in the Description page of Project Settings.


#include "CppEditorUtilityWidget.h"

#include "Components/Button.h"

void UCppEditorUtilityWidget::NativeConstruct()
{
	Super::NativeConstruct();

	btn_Button->OnClicked.AddDynamic(this, &UCppEditorUtilityWidget::OnClickedButton);
}

void UCppEditorUtilityWidget::OnClickedButton()
{
	GEngine->AddOnScreenDebugMessage(2, 30.f, FColor::Red, TEXT("C++ 호출!"));
}
