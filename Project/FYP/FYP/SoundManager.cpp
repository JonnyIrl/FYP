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

		//KILLING SPREE SFXS
		m_killingSpreeSound.setBuffer(m_killingSpreeBuffer);
		m_killingFrenzySound.setBuffer(m_killingFrenzyBuffer);
		m_rampageSound.setBuffer(m_rampageBuffer);
		m_runningRiotSound.setBuffer(m_runningRiotBuffer);
		m_invincibleSound.setBuffer(m_invincibleBuffer);
		m_comebackKillSound.setBuffer(m_comebackKillBuffer);

		//Sniper Shots SFX
		m_sniperShot1Sound.setBuffer(m_sniperShot1Buffer);
		m_sniperShot1Sound.setVolume(80.0f);
		m_sniperShot2Sound.setBuffer(m_sniperShot2Buffer);
		m_sniperShot2Sound.setVolume(80.0f);
		m_sniperShot3Sound.setBuffer(m_sniperShot3Buffer);
		m_sniperShot3Sound.setVolume(80.0f);
		m_sniperShot4Sound.setBuffer(m_sniperShot4Buffer);
		m_sniperShot4Sound.setVolume(80.0f);


	}
}

void SoundManager::PlaySniperShotSoundEffect()
{
	int num = (rand() % 4) + 1;
	std::cout << "Random = " << num << std::endl;
	if (num == 1)
	{
		//If its playing then re roll
		if (m_sniperShot1Sound.getStatus() == sf::SoundSource::Playing)
		{
			if (m_sniperShot2Sound.getStatus() == sf::SoundSource::Playing &&
				m_sniperShot3Sound.getStatus() == sf::SoundSource::Playing &&
				m_sniperShot4Sound.getStatus() == sf::SoundSource::Playing)
			{
				std::cout << "All sounds playing.." << std::endl;
			}

			else
			PlaySniperShotSoundEffect();
		}

		else
		m_sniperShot1Sound.play();
	}

	if (num == 2)
	{
		//If its playing then re roll
		if (m_sniperShot2Sound.getStatus() == sf::SoundSource::Playing)
		{
			if (m_sniperShot1Sound.getStatus() == sf::SoundSource::Playing &&
				m_sniperShot3Sound.getStatus() == sf::SoundSource::Playing &&
				m_sniperShot4Sound.getStatus() == sf::SoundSource::Playing)
			{
				std::cout << "All sounds playing.." << std::endl;
			}

			else
				PlaySniperShotSoundEffect();

		}

		else
		m_sniperShot2Sound.play();
	}

	if (num == 3)
	{
		//If its playing then re roll
		if (m_sniperShot3Sound.getStatus() == sf::SoundSource::Playing)
		{
			if (m_sniperShot2Sound.getStatus() == sf::SoundSource::Playing &&
				m_sniperShot1Sound.getStatus() == sf::SoundSource::Playing &&
				m_sniperShot4Sound.getStatus() == sf::SoundSource::Playing)
			{
				std::cout << "All sounds playing.." << std::endl;
			}

			else
				PlaySniperShotSoundEffect();
		}

		else
		m_sniperShot3Sound.play();
	}

	if (num == 4)
	{
		//If its playing then re roll
		if (m_sniperShot4Sound.getStatus() == sf::SoundSource::Playing)
		{
			if (m_sniperShot2Sound.getStatus() == sf::SoundSource::Playing &&
				m_sniperShot3Sound.getStatus() == sf::SoundSource::Playing &&
				m_sniperShot1Sound.getStatus() == sf::SoundSource::Playing)
			{
				std::cout << "All sounds playing.." << std::endl;
			}

			else
				PlaySniperShotSoundEffect();
		}

		else
		m_sniperShot4Sound.play();
	}
}

bool SoundManager::LoadSound()
{
	if (!mainMenuBuffer.loadFromFile("Assets/Audio/mainMenuMusic.ogg"))
	{
		std::cout << "Couldnt load sound file.. Main Menu" << std::endl;
		return false;
	}

	if (!m_killingSpreeBuffer.loadFromFile("Assets/Audio/KILLING/KillingSpree.ogg"))
	{
		std::cout << "Couldnt load KillingSpree sound file.. Main Menu" << std::endl;
		return false;
	}

	if (!m_killingFrenzyBuffer.loadFromFile("Assets/Audio/KILLING/KillingFrenzy.ogg"))
	{
		std::cout << "Couldnt load KillingFrenzy sound file.. Main Menu" << std::endl;
		return false;
	}

	if (!m_invincibleBuffer.loadFromFile("Assets/Audio/KILLING/Invincible.ogg"))
	{
		std::cout << "Couldnt load Invincible sound file.. Main Menu" << std::endl;
		return false;
	}

	if (!m_rampageBuffer.loadFromFile("Assets/Audio/KILLING/Rampage.ogg"))
	{
		std::cout << "Couldnt load Rampage sound file.. Main Menu" << std::endl;
		return false;
	}

	if (!m_runningRiotBuffer.loadFromFile("Assets/Audio/KILLING/RunningRiot.ogg"))
	{
		std::cout << "Couldnt load RunningRiot sound file.. Main Menu" << std::endl;
		return false;
	}

	if (!m_comebackKillBuffer.loadFromFile("Assets/Audio/KILLING/Comeback.ogg"))
	{
		std::cout << "Couldnt load Comeback sound file.. Main Menu" << std::endl;
		return false;
	}

	if (!m_sniperShot1Buffer.loadFromFile("Assets/Audio/GUNS/SNIPER/shot1.ogg"))
	{
		std::cout << "Couldnt load shot1 sound file.. Main Menu" << std::endl;
		return false;
	}

	if (!m_sniperShot2Buffer.loadFromFile("Assets/Audio/GUNS/SNIPER/shot2.ogg"))
	{
		std::cout << "Couldnt load shot1 sound file.. Main Menu" << std::endl;
		return false;
	}

	if (!m_sniperShot3Buffer.loadFromFile("Assets/Audio/GUNS/SNIPER/shot3.ogg"))
	{
		std::cout << "Couldnt load shot1 sound file.. Main Menu" << std::endl;
		return false;
	}

	if (!m_sniperShot4Buffer.loadFromFile("Assets/Audio/GUNS/SNIPER/shot4.ogg"))
	{
		std::cout << "Couldnt load shot1 sound file.. Main Menu" << std::endl;
		return false;
	}


	return true;
}

void SoundManager::PlayKillingSpreeSoundEffect(int amountOfKills)
{
	//KILLING SPREE SFX
	if (amountOfKills == 3)
	{
		m_killingSpreeSound.play();
	}

	//RAMPAGE SPREE SFX
	if (amountOfKills == 4)
	{
		m_rampageSound.play();
	}

	//KILLING FRENZY SFX
	if (amountOfKills == 5)
	{
		m_killingFrenzySound.play();
	}

	//RUNNING RIOT SFX
	if (amountOfKills == 6)
	{
		m_runningRiotSound.play();
	}

	//INVINCIBLE
	if (amountOfKills >= 7)
	{
		m_invincibleSound.play();
	}
}

void SoundManager::PlayComebackKillSoundEffect()
{
	m_comebackKillSound.play();
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

	if (savedMasterVolume != 1 || savedMasterVolume != 2 || savedMasterVolume != 3 || savedMasterVolume != 4)
		savedMasterVolume = 1;
}

void SoundManager::WriteToTextFile()
{
	if (newMasterVolume != 1 || newMasterVolume != 2 || newMasterVolume != 3 || newMasterVolume != 4)
		newMasterVolume = 1;

	if (savedCurrentSFXVolume != 1 || savedCurrentSFXVolume != 2 || savedCurrentSFXVolume != 3 || savedCurrentSFXVolume != 4)
		savedCurrentSFXVolume = 1;
	
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
