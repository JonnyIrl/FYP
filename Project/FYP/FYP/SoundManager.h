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
	void PlayKillingSpreeSoundEffect(int noOfKills);
	void PlayComebackKillSoundEffect();
	void PlaySniperShotSoundEffect();

private:
	sf::SoundBuffer mainMenuBuffer;
	sf::Sound mainMenuSound;
	bool mainMenuSoundPlaying;
	float savedMasterVolume;
	float savedCurrentSFXVolume;

	//KILLING SPREE SOUNDS
	sf::SoundBuffer m_killingSpreeBuffer, m_rampageBuffer, m_killingFrenzyBuffer, m_runningRiotBuffer, m_invincibleBuffer;
	sf::Sound m_killingSpreeSound, m_rampageSound, m_killingFrenzySound, m_runningRiotSound, m_invincibleSound;
	sf::SoundBuffer m_comebackKillBuffer;
	sf::Sound m_comebackKillSound;

	//Sniper Gun Shots
	sf::SoundBuffer m_sniperShot1Buffer, m_sniperShot2Buffer, m_sniperShot3Buffer, m_sniperShot4Buffer;
	sf::Sound m_sniperShot1Sound, m_sniperShot2Sound, m_sniperShot3Sound, m_sniperShot4Sound;
};
