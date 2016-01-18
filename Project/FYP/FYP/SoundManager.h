#include "ExtraIncludes.h"
#include <SFML/Audio.hpp>
#include <fstream>
#include <iostream> 
#include <vector>
#include <string>

class SoundManager
{
public:
	SoundManager();
	bool LoadSound();
	void PlayMenuMusic();
	sf::Sound GetMainMenuSound();
	void CheckAudio(int number);
	static std::vector<std::string> LoadFromTextFile(std::string name);
	void LoadTextFile(std::string name);
	void WriteToTextFile();
	float MasterVolume();
	float SFXVolume();
	float newMasterVolume;

private:
	sf::SoundBuffer mainMenuBuffer;
	sf::Sound mainMenuSound;
	bool mainMenuSoundPlaying;
	float savedMasterVolume;
	float savedCurrentSFXVolume;
};
