#include "SoundManager.h"


SoundManager::SoundManager()
{
	LoadTextFile("Assets/Settings/settings.txt");
	if (LoadSound())
	{
		mainMenuSound.setBuffer(mainMenuBuffer);
		mainMenuSoundPlaying = false;
		CheckAudio(savedMasterVolume);
		newMasterVolume = 0;
		//CheckAudio(savedCurrentSFXVolume + 4);

	}
}

bool SoundManager::LoadSound()
{
	if (!mainMenuBuffer.loadFromFile("Assets/Audio/mainMenuMusic.ogg"))
	{
		std::cout << "Couldnt load sound file.. Main Menu" << std::endl;
		return false;
	}

	return true;
}

void SoundManager::PlayMenuMusic()
{
	if (!mainMenuSoundPlaying)
	{
		mainMenuSound.setLoop(true);
		mainMenuSound.play();		
		mainMenuSoundPlaying = true;
	}
}

void SoundManager::CheckAudio(int number)
{
	if (number == 4)
	{
		mainMenuSound.setVolume(10.0f);
	}

	if (number == 3)
	{
		mainMenuSound.setVolume(6.0f);
	}

	if (number == 2)
	{
		mainMenuSound.setVolume(3.0f);
	}

	if (number == 1)
	{
		mainMenuSound.setVolume(1.0f);
	}

	if (number == 8)
	{
		
	}

	if (number == 7)
	{

	}

	if (number == 6)
	{

	}

	if (number == 5)
	{

	}

}

sf::Sound SoundManager::GetMainMenuSound()
{
	return mainMenuSound;
}

void SoundManager::LoadTextFile(std::string name)
{
	std::vector<std::string> map = SoundManager::LoadFromTextFile(name);
	const int mapX = 2;
	const int mapY = 2;
	int count = 0;


	for (int y = 0; y < mapY; y++)
	{
		for (int x = 0; x < mapX; x++)
		{
			
			char c = (char)map[y][x];

			if (c == '4' && count == 0)
			{
				savedMasterVolume = 4;			
			}

			if (c == '4' && count == 2)
			{
				savedCurrentSFXVolume = 4;
			}

			if (c == '3' && count == 0)
			{
				savedMasterVolume = 3;
			}

			if (c == '3' && count == 2)
			{
				savedCurrentSFXVolume = 3;
			}

			if (c == '2' && count == 0)
			{
				savedMasterVolume = 2;
			}

			if (c == '2' && count == 2)
			{
				savedCurrentSFXVolume = 2;
			}

			if (c == '1' && count == 0)
			{
				savedMasterVolume = 1;
			}

			if (c == '1' && count == 2)
			{
				savedCurrentSFXVolume = 1;
			}

			count++;
		}
	}
}

void SoundManager::WriteToTextFile()
{
	std::ofstream myfile;
	myfile.open("Assets/Settings/settings.txt");
	myfile << newMasterVolume << "\n" << savedCurrentSFXVolume;
	myfile.close();
}

std::vector<std::string> SoundManager::LoadFromTextFile(std::string name)
{

	std::vector<std::string > mystringvector;
	std::ifstream myfile;
	myfile.open(name);
	std::string c = "";
	while (myfile >> c)
	{
		mystringvector.push_back(c);
	}

	myfile.close();
	return mystringvector;

	return std::vector<std::string>();
}

float SoundManager::MasterVolume()
{
	return savedMasterVolume;
}

float SoundManager::SFXVolume()
{
	return savedCurrentSFXVolume;
}
