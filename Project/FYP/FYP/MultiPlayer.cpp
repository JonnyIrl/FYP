#include "MultiPlayer.h"


MultiPlayer::MultiPlayer()
{
	m_position = sf::Vector2f(500, 500);
	m_rect.setSize(sf::Vector2f(46, 50));
	m_rect.setPosition(m_position);
	m_moving = false;
	m_health = 100;

	//Load in the textures, and assign them to each animation.
	if (LoadTexture())
	{
		m_playerDownAnimation.setSpriteSheet(m_pDownTexture);
		m_playerDownAnimation.addFrame(sf::IntRect(0, 0, 46, 50));
		m_playerDownAnimation.addFrame(sf::IntRect(46, 0, 46, 50));
		m_playerDownAnimation.addFrame(sf::IntRect(92, 0, 46, 50));

		m_playerUpAnimation.setSpriteSheet(m_pUpTexture);
		m_playerUpAnimation.addFrame(sf::IntRect(0, 0, 46, 50));
		m_playerUpAnimation.addFrame(sf::IntRect(46, 0, 46, 50));
		m_playerUpAnimation.addFrame(sf::IntRect(92, 0, 46, 50));

		m_playerRightAnimation.setSpriteSheet(m_pRightTexture);
		m_playerRightAnimation.addFrame(sf::IntRect(0, 0, 46, 50));
		m_playerRightAnimation.addFrame(sf::IntRect(46, 0, 46, 50));
		m_playerRightAnimation.addFrame(sf::IntRect(92, 0, 46, 50));

		m_playerLeftAnimation.setSpriteSheet(m_pLeftTexture);
		m_playerLeftAnimation.addFrame(sf::IntRect(0, 0, 46, 50));
		m_playerLeftAnimation.addFrame(sf::IntRect(46, 0, 46, 50));
		m_playerLeftAnimation.addFrame(sf::IntRect(92, 0, 46, 50));

		m_playerAnimation = AnimatedSprite(sf::seconds(0.15f));
		m_playerAnimation.setAnimation(m_playerDownAnimation);

		LoadTextFile("Assets/Settings/id.txt");
		if (m_Name.size() <= 0)
		{
			m_Name = "PLAYER1";
		}

		m_speed = 5;

		AssignGunRectangles();

		countDownTrap = false;
		trapCoolDown = 10.0f;
	}
}

void MultiPlayer::AssignGunRectangles()
{
	//Deagle
	m_deagleLeftRectangle.setSize(sf::Vector2f(27, 16));
	m_deagleLeftRectangle.setTexture(&m_deagleLeftTexture);
	m_deagleRightRectangle.setSize(sf::Vector2f(27, 16));
	m_deagleRightRectangle.setTexture(&m_deagleRightTexture);

	//SNIPER
	m_sniperRightRectangle.setSize(sf::Vector2f(50, 13));
	m_sniperRightRectangle.setTexture(&m_sniperRightTexture);
	m_sniperLeftRectangle.setSize(sf::Vector2f(50, 13));
	m_sniperLeftRectangle.setTexture(&m_sniperLeftTexture);


	//MINIGUN
	m_miniGunRightRectangle.setSize(sf::Vector2f(55, 23));
	m_miniGunRightRectangle.setTexture(&m_miniGunRightTexture);
	m_miniGunLeftRectangle.setSize(sf::Vector2f(55, 23));
	m_miniGunLeftRectangle.setTexture(&m_miniGunLeftTexture);

	//AK47
	m_AK47RightRectangle.setSize(sf::Vector2f(47, 15));
	m_AK47RightRectangle.setTexture(&m_AK47RightTexture);
	m_AK47LeftRectangle.setSize(sf::Vector2f(47, 15));
	m_AK47LeftRectangle.setTexture(&m_AK47LeftTexture);

	//Trap
	m_trapRectangle.setSize(sf::Vector2f(35, 25));
	m_trapRectangle.setTexture(&m_trapTexture);

	//Assign font etc.
	trapCDText.setFont(trapFont);
	trapCDText.setCharacterSize(35);
	trapCDText.setColor(sf::Color::White);
	trapCDText.setPosition(sf::Vector2f(243, 670));

	m_killingSpree = 0;
	m_deathsWithoutKill = 0;

}


void MultiPlayer::ShootBullet(sf::Vector2f converted, int gun)
{

#pragma region Current Room == 1

	if (m_currentRoom == 1)
	{
		//SNIPER
		if (GetWeapon() == gun)
		{
			SetEnergy(true, 15);
			if (converted.x > GetPosition().x && converted.y > GetPosition().y || converted.x > GetPosition().x && converted.y < GetPosition().y)
			{
				b = new Bullet(sf::Vector2f(GetPosition().x + 22, GetPosition().y + 28), converted, GetWeapon());
				Room1Bullets.push_back(b);
			}

			else if (converted.x < GetPosition().x && converted.y > GetPosition().y || converted.x < GetPosition().x && converted.y < GetPosition().y)
			{
				b = new Bullet(sf::Vector2f(GetPosition().x - 20, GetPosition().y + 28), converted, GetWeapon());
				Room1Bullets.push_back(b);
			}

			//Play SFX
			//soundManager.PlaySniperShotSoundEffect();
		}

		//MINIGUN
		if (GetWeapon() == gun)
		{
			SetEnergy(true, 2);
			if (converted.x > GetPosition().x && converted.y > GetPosition().y || converted.x > GetPosition().x && converted.y < GetPosition().y)
			{
				b = new Bullet(sf::Vector2f(GetPosition().x + 22, GetPosition().y + 28), converted, GetWeapon());
				Room1Bullets.push_back(b);
			}

			else if (converted.x < GetPosition().x && converted.y > GetPosition().y || converted.x < GetPosition().x && converted.y < GetPosition().y)
			{
				b = new Bullet(sf::Vector2f(GetPosition().x - 20, GetPosition().y + 28), converted, GetWeapon());
				Room1Bullets.push_back(b);
			}
		}

		//DEAGLE
		if (GetWeapon() == gun)
		{
			SetEnergy(true, 8);
			if (converted.x > GetPosition().x && converted.y > GetPosition().y || converted.x > GetPosition().x && converted.y < GetPosition().y)
			{
				b = new Bullet(sf::Vector2f(GetPosition().x + 22, GetPosition().y + 28), converted, GetWeapon());
				Room1Bullets.push_back(b);
			}

			else if (converted.x < GetPosition().x && converted.y > GetPosition().y || converted.x < GetPosition().x && converted.y < GetPosition().y)
			{
				b = new Bullet(sf::Vector2f(GetPosition().x - 20, GetPosition().y + 28), converted, GetWeapon());
				Room1Bullets.push_back(b);
			}
		}

		//TRAP
		if (GetWeapon() == gun)
		{
			//If the trap is not on cool down..
			if (!GetTrapCoolDown())
			{
				AddNewTrap(sf::Vector2f(GetPosition().x, GetPosition().y + 10));
				SetTrapCoolDown(true);
			}
		}

		//AK
		if (GetWeapon() == gun)
		{
			SetEnergy(true, 4);
			if (converted.x > GetPosition().x && converted.y > GetPosition().y || converted.x > GetPosition().x && converted.y < GetPosition().y)
			{
				b = new Bullet(sf::Vector2f(GetPosition().x + 22, GetPosition().y + 28), converted, GetWeapon());
				Room1Bullets.push_back(b);
				b = new Bullet(sf::Vector2f(GetPosition().x + 4, GetPosition().y + 28), converted, GetWeapon());
				Room1Bullets.push_back(b);
				b = new Bullet(sf::Vector2f(GetPosition().x + 40, GetPosition().y + 28), converted, GetWeapon());
				Room1Bullets.push_back(b);


			}


			else if (converted.x < GetPosition().x && converted.y > GetPosition().y || converted.x < GetPosition().x && converted.y < GetPosition().y)
			{
				int countDown = 0;
				int timer = 0;
				cout << "BEFORE WHILE = " << timer << endl;

				cout << "TIMER++ = " << timer << endl;
				b = new Bullet(sf::Vector2f(GetPosition().x - 20, GetPosition().y + 28), converted, GetWeapon());
				Room1Bullets.push_back(b);
				b = new Bullet(sf::Vector2f(GetPosition().x - 22, GetPosition().y + 28), converted, GetWeapon());
				Room1Bullets.push_back(b);
				b = new Bullet(sf::Vector2f(GetPosition().x - 18, GetPosition().y + 28), converted, GetWeapon());
				Room1Bullets.push_back(b);
			}

			//soundManager.PlayAKShotSoundEffect();
		}
	}

#pragma endregion Current Room == 1

#pragma region Current Room == 2
	if (m_currentRoom == 2)
	{
		//SNIPER
		if (GetWeapon() == gun)
		{
			SetEnergy(true, 15);
			if (converted.x > GetPosition().x && converted.y > GetPosition().y || converted.x > GetPosition().x && converted.y < GetPosition().y)
			{
				b = new Bullet(sf::Vector2f(GetPosition().x + 22, GetPosition().y + 28), converted, GetWeapon());
				Room1Bullets.push_back(b);
			}

			else if (converted.x < GetPosition().x && converted.y > GetPosition().y || converted.x < GetPosition().x && converted.y < GetPosition().y)
			{
				b = new Bullet(sf::Vector2f(GetPosition().x - 20, GetPosition().y + 28), converted, GetWeapon());
				Room1Bullets.push_back(b);
			}

			//Play SFX
			//soundManager.PlaySniperShotSoundEffect();
		}

		//MINIGUN
		if (GetWeapon() == 4)
		{
			SetEnergy(true, gun);
			if (converted.x > GetPosition().x && converted.y > GetPosition().y || converted.x > GetPosition().x && converted.y < GetPosition().y)
			{
				b = new Bullet(sf::Vector2f(GetPosition().x + 22, GetPosition().y + 28), converted, GetWeapon());
				Room1Bullets.push_back(b);
			}

			else if (converted.x < GetPosition().x && converted.y > GetPosition().y || converted.x < GetPosition().x && converted.y < GetPosition().y)
			{
				b = new Bullet(sf::Vector2f(GetPosition().x - 20, GetPosition().y + 28), converted, GetWeapon());
				Room1Bullets.push_back(b);
			}
		}

		//DEAGLE
		if (GetWeapon() == gun)
		{
			SetEnergy(true, 8);
			if (converted.x > GetPosition().x && converted.y > GetPosition().y || converted.x > GetPosition().x && converted.y < GetPosition().y)
			{
				b = new Bullet(sf::Vector2f(GetPosition().x + 22, GetPosition().y + 28), converted, GetWeapon());
				Room1Bullets.push_back(b);
			}

			else if (converted.x < GetPosition().x && converted.y > GetPosition().y || converted.x < GetPosition().x && converted.y < GetPosition().y)
			{
				b = new Bullet(sf::Vector2f(GetPosition().x - 20, GetPosition().y + 28), converted, GetWeapon());
				Room1Bullets.push_back(b);
			}
		}

		//TRAP
		if (GetWeapon() == gun)
		{
			//If the trap is not on cool down..
			if (!GetTrapCoolDown())
			{
				AddNewTrap(sf::Vector2f(GetPosition().x, GetPosition().y + 10));
				SetTrapCoolDown(true);
			}
		}

		//AK
		if (GetWeapon() == gun)
		{
			SetEnergy(true, 4);
			if (converted.x > GetPosition().x && converted.y > GetPosition().y || converted.x > GetPosition().x && converted.y < GetPosition().y)
			{
				b = new Bullet(sf::Vector2f(GetPosition().x + 22, GetPosition().y + 28), converted, GetWeapon());
				Room1Bullets.push_back(b);
				b = new Bullet(sf::Vector2f(GetPosition().x + 4, GetPosition().y + 28), converted, GetWeapon());
				Room1Bullets.push_back(b);
				b = new Bullet(sf::Vector2f(GetPosition().x + 40, GetPosition().y + 28), converted, GetWeapon());
				Room1Bullets.push_back(b);


			}


			else if (converted.x < GetPosition().x && converted.y > GetPosition().y || converted.x < GetPosition().x && converted.y < GetPosition().y)
			{
				int countDown = 0;
				int timer = 0;
				cout << "BEFORE WHILE = " << timer << endl;

				cout << "TIMER++ = " << timer << endl;
				b = new Bullet(sf::Vector2f(GetPosition().x - 20, GetPosition().y + 28), converted, GetWeapon());
				Room1Bullets.push_back(b);
				b = new Bullet(sf::Vector2f(GetPosition().x - 22, GetPosition().y + 28), converted, GetWeapon());
				Room1Bullets.push_back(b);
				b = new Bullet(sf::Vector2f(GetPosition().x - 18, GetPosition().y + 28), converted, GetWeapon());
				Room1Bullets.push_back(b);
			}

			//soundManager.PlayAKShotSoundEffect();
		}
	}

#pragma endregion Current Room == 2

#pragma region Current Room == 3
	if (m_currentRoom == 3)
	{
		//SNIPER
		if (GetWeapon() == gun)
		{
			SetEnergy(true, 15);
			if (converted.x > GetPosition().x && converted.y > GetPosition().y || converted.x > GetPosition().x && converted.y < GetPosition().y)
			{
				b = new Bullet(sf::Vector2f(GetPosition().x + 22, GetPosition().y + 28), converted, GetWeapon());
				Room3Bullets.push_back(b);
			}

			else if (converted.x < GetPosition().x && converted.y > GetPosition().y || converted.x < GetPosition().x && converted.y < GetPosition().y)
			{
				b = new Bullet(sf::Vector2f(GetPosition().x - 20, GetPosition().y + 28), converted, GetWeapon());
				Room3Bullets.push_back(b);
			}

			//Play SFX
			//soundManager.PlaySniperShotSoundEffect();
		}

		//MINIGUN
		if (GetWeapon() == gun)
		{
			SetEnergy(true, 2);
			if (converted.x > GetPosition().x && converted.y > GetPosition().y || converted.x > GetPosition().x && converted.y < GetPosition().y)
			{
				b = new Bullet(sf::Vector2f(GetPosition().x + 22, GetPosition().y + 28), converted, GetWeapon());
				Room3Bullets.push_back(b);
			}

			else if (converted.x < GetPosition().x && converted.y > GetPosition().y || converted.x < GetPosition().x && converted.y < GetPosition().y)
			{
				b = new Bullet(sf::Vector2f(GetPosition().x - 20, GetPosition().y + 28), converted, GetWeapon());
				Room3Bullets.push_back(b);
			}
		}

		//DEAGLE
		if (GetWeapon() == gun)
		{
			SetEnergy(true, 8);
			if (converted.x > GetPosition().x && converted.y > GetPosition().y || converted.x > GetPosition().x && converted.y < GetPosition().y)
			{
				b = new Bullet(sf::Vector2f(GetPosition().x + 22, GetPosition().y + 28), converted, GetWeapon());
				Room3Bullets.push_back(b);
			}

			else if (converted.x < GetPosition().x && converted.y > GetPosition().y || converted.x < GetPosition().x && converted.y < GetPosition().y)
			{
				b = new Bullet(sf::Vector2f(GetPosition().x - 20, GetPosition().y + 28), converted, GetWeapon());
				Room3Bullets.push_back(b);
			}
		}

		//TRAP
		if (GetWeapon() == gun)
		{
			//If the trap is not on cool down..
			if (!GetTrapCoolDown())
			{
				AddNewTrap(sf::Vector2f(GetPosition().x, GetPosition().y + 10));
				SetTrapCoolDown(true);
			}
		}

		//AK
		if (GetWeapon() == gun)
		{
			SetEnergy(true, 4);
			if (converted.x > GetPosition().x && converted.y > GetPosition().y || converted.x > GetPosition().x && converted.y < GetPosition().y)
			{
				b = new Bullet(sf::Vector2f(GetPosition().x + 22, GetPosition().y + 28), converted, GetWeapon());
				Room3Bullets.push_back(b);
				b = new Bullet(sf::Vector2f(GetPosition().x + 4, GetPosition().y + 28), converted, GetWeapon());
				Room3Bullets.push_back(b);
				b = new Bullet(sf::Vector2f(GetPosition().x + 40, GetPosition().y + 28), converted, GetWeapon());
				Room3Bullets.push_back(b);


			}


			else if (converted.x < GetPosition().x && converted.y > GetPosition().y || converted.x < GetPosition().x && converted.y < GetPosition().y)
			{
				int countDown = 0;
				int timer = 0;
				cout << "BEFORE WHILE = " << timer << endl;

				cout << "TIMER++ = " << timer << endl;
				b = new Bullet(sf::Vector2f(GetPosition().x - 20, GetPosition().y + 28), converted, GetWeapon());
				Room3Bullets.push_back(b);
				b = new Bullet(sf::Vector2f(GetPosition().x - 22, GetPosition().y + 28), converted, GetWeapon());
				Room3Bullets.push_back(b);
				b = new Bullet(sf::Vector2f(GetPosition().x - 18, GetPosition().y + 28), converted, GetWeapon());
				Room3Bullets.push_back(b);
			}

			//soundManager.PlayAKShotSoundEffect();
		}
	}

#pragma endregion Current Room == 3

#pragma region Current Room == 4
	if (m_currentRoom == 4)
	{
		//SNIPER
		if (GetWeapon() == gun)
		{
			SetEnergy(true, 15);
			if (converted.x > GetPosition().x && converted.y > GetPosition().y || converted.x > GetPosition().x && converted.y < GetPosition().y)
			{
				b = new Bullet(sf::Vector2f(GetPosition().x + 22, GetPosition().y + 28), converted, GetWeapon());
				Room4Bullets.push_back(b);
			}

			else if (converted.x < GetPosition().x && converted.y > GetPosition().y || converted.x < GetPosition().x && converted.y < GetPosition().y)
			{
				b = new Bullet(sf::Vector2f(GetPosition().x - 20, GetPosition().y + 28), converted, GetWeapon());
				Room4Bullets.push_back(b);
			}

			//Play SFX
			//soundManager.PlaySniperShotSoundEffect();
		}

		//MINIGUN
		if (GetWeapon() == gun)
		{
			SetEnergy(true, 2);
			if (converted.x > GetPosition().x && converted.y > GetPosition().y || converted.x > GetPosition().x && converted.y < GetPosition().y)
			{
				b = new Bullet(sf::Vector2f(GetPosition().x + 22, GetPosition().y + 28), converted, GetWeapon());
				Room4Bullets.push_back(b);
			}

			else if (converted.x < GetPosition().x && converted.y > GetPosition().y || converted.x < GetPosition().x && converted.y < GetPosition().y)
			{
				b = new Bullet(sf::Vector2f(GetPosition().x - 20, GetPosition().y + 28), converted, GetWeapon());
				Room4Bullets.push_back(b);
			}
		}

		//DEAGLE
		if (GetWeapon() == gun)
		{
			SetEnergy(true, 8);
			if (converted.x > GetPosition().x && converted.y > GetPosition().y || converted.x > GetPosition().x && converted.y < GetPosition().y)
			{
				b = new Bullet(sf::Vector2f(GetPosition().x + 22, GetPosition().y + 28), converted, GetWeapon());
				Room4Bullets.push_back(b);
			}

			else if (converted.x < GetPosition().x && converted.y > GetPosition().y || converted.x < GetPosition().x && converted.y < GetPosition().y)
			{
				b = new Bullet(sf::Vector2f(GetPosition().x - 20, GetPosition().y + 28), converted, GetWeapon());
				Room4Bullets.push_back(b);
			}
		}

		//TRAP
		if (GetWeapon() == gun)
		{
			//If the trap is not on cool down..
			if (!GetTrapCoolDown())
			{
				AddNewTrap(sf::Vector2f(GetPosition().x, GetPosition().y + 10));
				SetTrapCoolDown(true);
			}
		}

		//AK
		if (GetWeapon() == gun)
		{
			SetEnergy(true, 4);
			if (converted.x > GetPosition().x && converted.y > GetPosition().y || converted.x > GetPosition().x && converted.y < GetPosition().y)
			{
				b = new Bullet(sf::Vector2f(GetPosition().x + 22, GetPosition().y + 28), converted, GetWeapon());
				Room4Bullets.push_back(b);
				b = new Bullet(sf::Vector2f(GetPosition().x + 4, GetPosition().y + 28), converted, GetWeapon());
				Room4Bullets.push_back(b);
				b = new Bullet(sf::Vector2f(GetPosition().x + 40, GetPosition().y + 28), converted, GetWeapon());
				Room4Bullets.push_back(b);


			}


			else if (converted.x < GetPosition().x && converted.y > GetPosition().y || converted.x < GetPosition().x && converted.y < GetPosition().y)
			{
				int countDown = 0;
				int timer = 0;
				cout << "BEFORE WHILE = " << timer << endl;

				cout << "TIMER++ = " << timer << endl;
				b = new Bullet(sf::Vector2f(GetPosition().x - 20, GetPosition().y + 28), converted, GetWeapon());
				Room4Bullets.push_back(b);
				b = new Bullet(sf::Vector2f(GetPosition().x - 22, GetPosition().y + 28), converted, GetWeapon());
				Room4Bullets.push_back(b);
				b = new Bullet(sf::Vector2f(GetPosition().x - 18, GetPosition().y + 28), converted, GetWeapon());
				Room4Bullets.push_back(b);
			}

			//soundManager.PlayAKShotSoundEffect();
		}
	}

#pragma endregion Current Room == 4

#pragma region Current Room == 5
	if (m_currentRoom == gun)
	{
		//SNIPER
		if (GetWeapon() == 3)
		{
			SetEnergy(true, 15);
			if (converted.x > GetPosition().x && converted.y > GetPosition().y || converted.x > GetPosition().x && converted.y < GetPosition().y)
			{
				b = new Bullet(sf::Vector2f(GetPosition().x + 22, GetPosition().y + 28), converted, GetWeapon());
				Room5Bullets.push_back(b);
			}

			else if (converted.x < GetPosition().x && converted.y > GetPosition().y || converted.x < GetPosition().x && converted.y < GetPosition().y)
			{
				b = new Bullet(sf::Vector2f(GetPosition().x - 20, GetPosition().y + 28), converted, GetWeapon());
				Room5Bullets.push_back(b);
			}

			//Play SFX
			//soundManager.PlaySniperShotSoundEffect();
		}

		//MINIGUN
		if (GetWeapon() == gun)
		{
			SetEnergy(true, 2);
			if (converted.x > GetPosition().x && converted.y > GetPosition().y || converted.x > GetPosition().x && converted.y < GetPosition().y)
			{
				b = new Bullet(sf::Vector2f(GetPosition().x + 22, GetPosition().y + 28), converted, GetWeapon());
				Room5Bullets.push_back(b);
			}

			else if (converted.x < GetPosition().x && converted.y > GetPosition().y || converted.x < GetPosition().x && converted.y < GetPosition().y)
			{
				b = new Bullet(sf::Vector2f(GetPosition().x - 20, GetPosition().y + 28), converted, GetWeapon());
				Room5Bullets.push_back(b);
			}
		}

		//DEAGLE
		if (GetWeapon() == gun)
		{
			SetEnergy(true, 8);
			if (converted.x > GetPosition().x && converted.y > GetPosition().y || converted.x > GetPosition().x && converted.y < GetPosition().y)
			{
				b = new Bullet(sf::Vector2f(GetPosition().x + 22, GetPosition().y + 28), converted, GetWeapon());
				Room5Bullets.push_back(b);
			}

			else if (converted.x < GetPosition().x && converted.y > GetPosition().y || converted.x < GetPosition().x && converted.y < GetPosition().y)
			{
				b = new Bullet(sf::Vector2f(GetPosition().x - 20, GetPosition().y + 28), converted, GetWeapon());
				Room5Bullets.push_back(b);
			}
		}

		//TRAP
		if (GetWeapon() == gun)
		{
			//If the trap is not on cool down..
			if (!GetTrapCoolDown())
			{
				AddNewTrap(sf::Vector2f(GetPosition().x, GetPosition().y + 10));
				SetTrapCoolDown(true);
			}
		}

		//AK
		if (GetWeapon() == gun)
		{
			SetEnergy(true, 4);
			if (converted.x > GetPosition().x && converted.y > GetPosition().y || converted.x > GetPosition().x && converted.y < GetPosition().y)
			{
				b = new Bullet(sf::Vector2f(GetPosition().x + 22, GetPosition().y + 28), converted, GetWeapon());
				Room5Bullets.push_back(b);
				b = new Bullet(sf::Vector2f(GetPosition().x + 4, GetPosition().y + 28), converted, GetWeapon());
				Room5Bullets.push_back(b);
				b = new Bullet(sf::Vector2f(GetPosition().x + 40, GetPosition().y + 28), converted, GetWeapon());
				Room5Bullets.push_back(b);


			}


			else if (converted.x < GetPosition().x && converted.y > GetPosition().y || converted.x < GetPosition().x && converted.y < GetPosition().y)
			{
				int countDown = 0;
				int timer = 0;
				cout << "BEFORE WHILE = " << timer << endl;

				cout << "TIMER++ = " << timer << endl;
				b = new Bullet(sf::Vector2f(GetPosition().x - 20, GetPosition().y + 28), converted, GetWeapon());
				Room5Bullets.push_back(b);
				b = new Bullet(sf::Vector2f(GetPosition().x - 22, GetPosition().y + 28), converted, GetWeapon());
				Room5Bullets.push_back(b);
				b = new Bullet(sf::Vector2f(GetPosition().x - 18, GetPosition().y + 28), converted, GetWeapon());
				Room5Bullets.push_back(b);
			}

			//soundManager.PlayAKShotSoundEffect();
		}
	}

#pragma endregion Current Room == 5

#pragma region Current Room == 6
	if (m_currentRoom == 6)
	{
		//SNIPER
		if (GetWeapon() == gun)
		{
			SetEnergy(true, 15);
			if (converted.x > GetPosition().x && converted.y > GetPosition().y || converted.x > GetPosition().x && converted.y < GetPosition().y)
			{
				b = new Bullet(sf::Vector2f(GetPosition().x + 22, GetPosition().y + 28), converted, GetWeapon());
				Room6Bullets.push_back(b);
			}

			else if (converted.x < GetPosition().x && converted.y > GetPosition().y || converted.x < GetPosition().x && converted.y < GetPosition().y)
			{
				b = new Bullet(sf::Vector2f(GetPosition().x - 20, GetPosition().y + 28), converted, GetWeapon());
				Room6Bullets.push_back(b);
			}

			//Play SFX
			//soundManager.PlaySniperShotSoundEffect();
		}

		//MINIGUN
		if (GetWeapon() == gun)
		{
			SetEnergy(true, 2);
			if (converted.x > GetPosition().x && converted.y > GetPosition().y || converted.x > GetPosition().x && converted.y < GetPosition().y)
			{
				b = new Bullet(sf::Vector2f(GetPosition().x + 22, GetPosition().y + 28), converted, GetWeapon());
				Room6Bullets.push_back(b);
			}

			else if (converted.x < GetPosition().x && converted.y > GetPosition().y || converted.x < GetPosition().x && converted.y < GetPosition().y)
			{
				b = new Bullet(sf::Vector2f(GetPosition().x - 20, GetPosition().y + 28), converted, GetWeapon());
				Room6Bullets.push_back(b);
			}
		}

		//DEAGLE
		if (GetWeapon() == gun)
		{
			SetEnergy(true, 8);
			if (converted.x > GetPosition().x && converted.y > GetPosition().y || converted.x > GetPosition().x && converted.y < GetPosition().y)
			{
				b = new Bullet(sf::Vector2f(GetPosition().x + 22, GetPosition().y + 28), converted, GetWeapon());
				Room6Bullets.push_back(b);
			}

			else if (converted.x < GetPosition().x && converted.y > GetPosition().y || converted.x < GetPosition().x && converted.y < GetPosition().y)
			{
				b = new Bullet(sf::Vector2f(GetPosition().x - 20, GetPosition().y + 28), converted, GetWeapon());
				Room6Bullets.push_back(b);
			}
		}

		//TRAP
		if (GetWeapon() == gun)
		{
			//If the trap is not on cool down..
			if (!GetTrapCoolDown())
			{
				AddNewTrap(sf::Vector2f(GetPosition().x, GetPosition().y + 10));
				SetTrapCoolDown(true);
			}
		}

		//AK
		if (GetWeapon() == gun)
		{
			SetEnergy(true, 4);
			if (converted.x > GetPosition().x && converted.y > GetPosition().y || converted.x > GetPosition().x && converted.y < GetPosition().y)
			{
				b = new Bullet(sf::Vector2f(GetPosition().x + 22, GetPosition().y + 28), converted, GetWeapon());
				Room6Bullets.push_back(b);
				b = new Bullet(sf::Vector2f(GetPosition().x + 4, GetPosition().y + 28), converted, GetWeapon());
				Room6Bullets.push_back(b);
				b = new Bullet(sf::Vector2f(GetPosition().x + 40, GetPosition().y + 28), converted, GetWeapon());
				Room6Bullets.push_back(b);


			}


			else if (converted.x < GetPosition().x && converted.y > GetPosition().y || converted.x < GetPosition().x && converted.y < GetPosition().y)
			{
				int countDown = 0;
				int timer = 0;
				cout << "BEFORE WHILE = " << timer << endl;

				cout << "TIMER++ = " << timer << endl;
				b = new Bullet(sf::Vector2f(GetPosition().x - 20, GetPosition().y + 28), converted, GetWeapon());
				Room6Bullets.push_back(b);
				b = new Bullet(sf::Vector2f(GetPosition().x - 22, GetPosition().y + 28), converted, GetWeapon());
				Room6Bullets.push_back(b);
				b = new Bullet(sf::Vector2f(GetPosition().x - 18, GetPosition().y + 28), converted, GetWeapon());
				Room6Bullets.push_back(b);
			}

			//soundManager.PlayAKShotSoundEffect();
		}
	}

#pragma endregion Current Room == 6

#pragma region Current Room == 7
	if (m_currentRoom == 7)
	{
		//SNIPER
		if (GetWeapon() == gun)
		{
			SetEnergy(true, 15);
			if (converted.x > GetPosition().x && converted.y > GetPosition().y || converted.x > GetPosition().x && converted.y < GetPosition().y)
			{
				b = new Bullet(sf::Vector2f(GetPosition().x + 22, GetPosition().y + 28), converted, GetWeapon());
				Room7Bullets.push_back(b);
			}

			else if (converted.x < GetPosition().x && converted.y > GetPosition().y || converted.x < GetPosition().x && converted.y < GetPosition().y)
			{
				b = new Bullet(sf::Vector2f(GetPosition().x - 20, GetPosition().y + 28), converted, GetWeapon());
				Room7Bullets.push_back(b);
			}

			//Play SFX
			//soundManager.PlaySniperShotSoundEffect();
		}

		//MINIGUN
		if (GetWeapon() == gun)
		{
			SetEnergy(true, 2);
			if (converted.x > GetPosition().x && converted.y > GetPosition().y || converted.x > GetPosition().x && converted.y < GetPosition().y)
			{
				b = new Bullet(sf::Vector2f(GetPosition().x + 22, GetPosition().y + 28), converted, GetWeapon());
				Room7Bullets.push_back(b);
			}

			else if (converted.x < GetPosition().x && converted.y > GetPosition().y || converted.x < GetPosition().x && converted.y < GetPosition().y)
			{
				b = new Bullet(sf::Vector2f(GetPosition().x - 20, GetPosition().y + 28), converted, GetWeapon());
				Room7Bullets.push_back(b);
			}
		}

		//DEAGLE
		if (GetWeapon() == gun)
		{
			SetEnergy(true, 8);
			if (converted.x > GetPosition().x && converted.y > GetPosition().y || converted.x > GetPosition().x && converted.y < GetPosition().y)
			{
				b = new Bullet(sf::Vector2f(GetPosition().x + 22, GetPosition().y + 28), converted, GetWeapon());
				Room7Bullets.push_back(b);
			}

			else if (converted.x < GetPosition().x && converted.y > GetPosition().y || converted.x < GetPosition().x && converted.y < GetPosition().y)
			{
				b = new Bullet(sf::Vector2f(GetPosition().x - 20, GetPosition().y + 28), converted, GetWeapon());
				Room7Bullets.push_back(b);
			}
		}

		//TRAP
		if (GetWeapon() == gun)
		{
			//If the trap is not on cool down..
			if (!GetTrapCoolDown())
			{
				AddNewTrap(sf::Vector2f(GetPosition().x, GetPosition().y + 10));
				SetTrapCoolDown(true);
			}
		}

		//AK
		if (GetWeapon() == gun)
		{
			SetEnergy(true, 4);
			if (converted.x > GetPosition().x && converted.y > GetPosition().y || converted.x > GetPosition().x && converted.y < GetPosition().y)
			{
				b = new Bullet(sf::Vector2f(GetPosition().x + 22, GetPosition().y + 28), converted, GetWeapon());
				Room7Bullets.push_back(b);
				b = new Bullet(sf::Vector2f(GetPosition().x + 4, GetPosition().y + 28), converted, GetWeapon());
				Room7Bullets.push_back(b);
				b = new Bullet(sf::Vector2f(GetPosition().x + 40, GetPosition().y + 28), converted, GetWeapon());
				Room7Bullets.push_back(b);


			}


			else if (converted.x < GetPosition().x && converted.y > GetPosition().y || converted.x < GetPosition().x && converted.y < GetPosition().y)
			{
				int countDown = 0;
				int timer = 0;
				cout << "BEFORE WHILE = " << timer << endl;

				cout << "TIMER++ = " << timer << endl;
				b = new Bullet(sf::Vector2f(GetPosition().x - 20, GetPosition().y + 28), converted, GetWeapon());
				Room7Bullets.push_back(b);
				b = new Bullet(sf::Vector2f(GetPosition().x - 22, GetPosition().y + 28), converted, GetWeapon());
				Room7Bullets.push_back(b);
				b = new Bullet(sf::Vector2f(GetPosition().x - 18, GetPosition().y + 28), converted, GetWeapon());
				Room7Bullets.push_back(b);
			}

			//soundManager.PlayAKShotSoundEffect();
		}
	}

#pragma endregion Current Room == 7

}

bool MultiPlayer::LoadTexture()
{
	if (!m_pDownTexture.loadFromFile("Assets/Player/pDown.png"))
		return false;

	if (!m_pUpTexture.loadFromFile("Assets/Player/pUp.png"))
		return false;

	if (!m_pRightTexture.loadFromFile("Assets/Player/pRight.png"))
		return false;

	if (!m_pLeftTexture.loadFromFile("Assets/Player/pLeft.png"))
		return false;

	//Guns Textures
	if (!m_deagleLeftTexture.loadFromFile("Assets/Guns/Deagle/leftDeagle.png"))
	{
		std::cout << "Couldnt load Deagle Texture" << endl;
		return false;
	}

	if (!m_deagleRightTexture.loadFromFile("Assets/Guns/Deagle/rightDeagle.png"))
	{
		std::cout << "Couldnt load Deagle Texture" << endl;
		return false;
	}

	if (!m_sniperLeftTexture.loadFromFile("Assets/Guns/Sniper/leftSniper.png"))
	{
		std::cout << "Couldnt load Sniper Texture" << endl;
		return false;
	}

	if (!m_sniperRightTexture.loadFromFile("Assets/Guns/Sniper/rightSniper.png"))
	{
		std::cout << "Couldnt load Sniper Texture" << endl;
		return false;
	}

	if (!m_miniGunLeftTexture.loadFromFile("Assets/Guns/MiniGun/leftMiniGun.png"))
	{
		std::cout << "Couldnt load MiniGun Texture" << endl;
		return false;
	}

	if (!m_miniGunRightTexture.loadFromFile("Assets/Guns/MiniGun/rightMiniGun.png"))
	{
		std::cout << "Couldnt load MiniGun Texture" << endl;
		return false;
	}

	if (!m_AK47LeftTexture.loadFromFile("Assets/Guns/AK/leftAK.png"))
	{
		std::cout << "Couldnt load AK Texture" << endl;
		return false;
	}

	if (!m_AK47RightTexture.loadFromFile("Assets/Guns/AK/rightAK.png"))
	{
		std::cout << "Couldnt load AK Texture" << endl;
		return false;
	}

	if (!m_trapTexture.loadFromFile("Assets/Guns/Trap/trap.png"))
	{
		std::cout << "Couldnt load Trap Texture" << endl;
		return false;
	}

	if (!trapFont.loadFromFile("Assets/Font/font.ttf")) {
		std::cout << "No font file found!" << std::endl;
	}

	else
		return true;
}

//This timer should refresh when the player has more than 3 kills, it will start and then announce result
bool MultiPlayer::CheckKillSoundEffect()
{
	int timer = soundEffectClock.getElapsedTime().asSeconds();
	if (m_killingSpree >= 3 && timer > 0)
	{
		cout << "Killing Spree is " << m_killingSpree << endl;
		soundEffectCountDown++;

		cout << "Count Down = " << soundEffectCountDown << endl;

		if (soundEffectCountDown >= 3)
		{
			cout << "RETURNED TRUE TO PLAY SOUND EFFECT" << endl << endl;
			soundEffectCountDown = 0;
			return true;
		}

		soundEffectClock.restart();
	}

	return false;
}

bool MultiPlayer::CreateAKBullet()
{
	int timer = 0;
	if (m_AKDelay <= 2 && timer > 0)
	{
		m_AKCountDown++;

		if (m_AKCountDown >= 3)
		{
			m_AKCountDown = 0;
			return true;
		}
	}

	return false;
}

//Checks if the player died more than 3 times without a kill..
bool MultiPlayer::CheckDeathStreakOver()
{
	if (m_deathsWithoutKill >= 3)
	{
		if (m_killingSpree >= 1)
		{
			m_deathsWithoutKill = 0;
			return true;
		}
	}

	return false;
}

void MultiPlayer::IncreaseDecreaseKillingSpress(bool state)
{
	//If true then increase
	if (state)
	{
		m_killingSpree++;
		cout << "Increased KS = " << m_killingSpree << endl;
	}

	else
	{
		m_killingSpree--;
		cout << "Decreased KS = " << m_killingSpree << endl;
	}
}

void MultiPlayer::LoadTextFile(string name)
{
	ifstream file(name);
	string str;
	while (getline(file, str))
	{
		m_Name = str;
		m_PlayerID = str;
	}
}

void MultiPlayer::AddNewTrap(sf::Vector2f position)
{
	m_trapRectangle.setPosition(position);
	m_TrapRectangles.push_back(m_trapRectangle);
}

int MultiPlayer::FindWhichRoomToUpdate()
{
	if (m_currentRoom == 1)
	{
		return 1;
	}

	if (m_currentRoom == 2)
	{
		return 2;
	}

	if (m_currentRoom == 3)
	{
		return 3;
	}

	if (m_currentRoom == 4)
	{
		return 4;
	}

	if (m_currentRoom == 5)
	{
		return 5;
	}

	if (m_currentRoom == 6)
	{
		return 6;
	}

	if (m_currentRoom == 7)
	{
		return 7;
	}
}

void MultiPlayer::UpdateRoom1(sf::Time time)
{
	if (m_dir == 1 && m_playerAnimation.getAnimation() != &m_playerUpAnimation)
	{
		m_playerAnimation.setAnimation(m_playerUpAnimation);
		m_playerAnimation.update(time);
		m_dir = 1;
	}

	else if (m_dir == 2 && m_playerAnimation.getAnimation() != &m_playerDownAnimation)
	{
		m_playerAnimation.setAnimation(m_playerDownAnimation);
		m_playerAnimation.update(time);
		m_dir = 2;
	}

	else if (m_dir == 3 && m_playerAnimation.getAnimation() != &m_playerLeftAnimation)
	{
		m_playerAnimation.setAnimation(m_playerLeftAnimation);
		m_playerAnimation.update(time);
		m_dir = 3;
	}

	else if (m_dir == 4 && m_playerAnimation.getAnimation() != &m_playerRightAnimation)
	{
		m_playerAnimation.setAnimation(m_playerRightAnimation);
		m_playerAnimation.update(time);
		m_dir = 4;
	}

	m_playerAnimation.setPosition(m_position);
	m_rect.setPosition(m_position);
}

void MultiPlayer::Draw(sf::RenderWindow &window)
{

	window.draw(m_playerAnimation);

	if (currentWeapon == DEAGLE)
	{
		if (m_dir == 4)
		{
			m_deagleRightRectangle.setPosition(sf::Vector2f((m_position.x + 17), m_position.y + 28));
			window.draw(m_deagleRightRectangle);
		}

		else if (m_dir == 3)
		{
			m_deagleLeftRectangle.setPosition(sf::Vector2f((m_position.x), m_position.y + 28));
			window.draw(m_deagleLeftRectangle);
		}
	}

	else if (currentWeapon == SNIPER)
	{
		if (m_dir == 4)
		{
			m_sniperRightRectangle.setPosition(sf::Vector2f((m_position.x + 17), m_position.y + 28));
			window.draw(m_sniperRightRectangle);
		}

		else if (m_dir == 3)
		{
			m_sniperLeftRectangle.setPosition(sf::Vector2f((m_position.x - 15), m_position.y + 28));
			window.draw(m_sniperLeftRectangle);
		}
	}

	else if (currentWeapon == MINIGUN)
	{
		if (m_dir == 4)
		{
			m_miniGunRightRectangle.setPosition(sf::Vector2f((m_position.x + 17), m_position.y + 20));
			window.draw(m_miniGunRightRectangle);
		}

		else if (m_dir == 3)
		{
			m_miniGunLeftRectangle.setPosition(sf::Vector2f((m_position.x - 27), m_position.y + 20));
			window.draw(m_miniGunLeftRectangle);
		}
	}

	else if (currentWeapon == AK47)
	{
		if (m_dir == 4)
		{
			m_AK47RightRectangle.setPosition(sf::Vector2f((m_position.x + 14), m_position.y + 28));
			window.draw(m_AK47RightRectangle);
		}

		else if (m_dir == 3)
		{
			m_AK47LeftRectangle.setPosition(sf::Vector2f((m_position.x - 18), m_position.y + 28));
			window.draw(m_AK47LeftRectangle);
		}
	}

	else if (currentWeapon == TRAP)
	{
		if (m_dir == 4)
		{
			m_trapRectangle.setPosition(sf::Vector2f((m_position.x + 14), m_position.y + 28));
			window.draw(m_trapRectangle);
		}

		else if (m_dir == 3)
		{
			m_trapRectangle.setPosition(sf::Vector2f((m_position.x - 18), m_position.y + 28));
			window.draw(m_trapRectangle);
		}
	}


	if (m_TrapRectangles.size() > 0)
	{
		for each (sf::RectangleShape rect in m_TrapRectangles)
		{
			window.draw(rect);
		}
	}

	if (countDownTrap)
	{
		window.draw(trapCDText);
	}

}

void MultiPlayer::updateTex(sf::Texture texture)
{ //creates a copy of your texture you pass

	m_rect.setTexture(&texture); //actually takes the address of your texture 
}

sf::RectangleShape MultiPlayer::GetShape()
{
	return m_rect;
}

sf::Vector2f MultiPlayer::GetPosition()
{
	return m_position;
}

void MultiPlayer::SetPosition(sf::Vector2f position)
{
	m_position = position;
}

//Destructor
MultiPlayer::~MultiPlayer()
{
}