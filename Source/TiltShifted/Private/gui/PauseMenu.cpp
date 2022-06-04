// Fill out your copyright notice in the Description page of Project Settings.

#include "gui/PauseMenu.h"

void UPauseMenu::ResumeGame()
{
    ResumeBtnClicked.Broadcast();
    ResumeBtnClicked.RemoveAll(this);
}
