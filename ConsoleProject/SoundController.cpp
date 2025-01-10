#include "SoundController.h"

void SoundController::PlayMainBGM()
{
	if (lastMusic == "Title") return;

	PlaySound(TEXT("Title.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	lastMusic = "Title";
}

void SoundController::PlayMapBGM()
{
	if (lastMusic == "CursedTown") return;

	PlaySound(TEXT("CursedTown.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	lastMusic = "CursedTown"; 
}

void SoundController::PlayBattleBGM()
{
	if (lastMusic == "Eureka") return;

	PlaySound(TEXT("Eureka.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	lastMusic = "Eureka";
}

void SoundController::PlayShopBGM()
{
	if (lastMusic == "ChocoboTheme") return;

	PlaySound(TEXT("ChocoboTheme.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	lastMusic = "ChocoboTheme";
}

void SoundController::PlayVictoryBGM()
{
	if (lastMusic == "Victory") return;

	PlaySound(TEXT("Victory.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	lastMusic = "Victory";

}
