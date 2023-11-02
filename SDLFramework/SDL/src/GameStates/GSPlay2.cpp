	#include "GSPlay2.h"
	#include "GameObject/TextureManager.h"
	#include "GameObject/Sprite2D.h"
	#include "GameObject/MouseButton.h"
	#include "GameObject/SpriteAnimation.h"
	#include "GameObject/Camera.h"
	#include "KeyState.h"
	#include "CMath.h"
	#include"ResourceManagers.h"


	GSPlay2::GSPlay2()
	{
	}
	int bullet_X1;
	int bullet_Y1;
	int bullet_X2;
	int bullet_Y2;
	float play1_X;
	float play1_Y;
	GSPlay2::~GSPlay2()
	{
	}

	void GSPlay2::Init()
	{
		//auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
		auto texture = ResourceManagers::GetInstance()->GetTexture("map3.0.tga");

		// background
	
		m_background = std::make_shared<Sprite2D>( texture, SDL_FLIP_NONE);
		m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIDHT);
		m_background->Set2DPosition(0, 0);


	//pause
	texture = ResourceManagers::GetInstance()->GetTexture("btn_pause.tga");
	button = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	button->SetSize(40, 40);
	button->Set2DPosition(SCREEN_WIDTH - button->GetWidth() - 5, 10);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PAUSE);
		});
	m_listButton.push_back(button);

		// Animation 
		texture = ResourceManagers::GetInstance()->GetTexture("actor_ghost1.tga");
		play1 = std::make_shared<SpriteAnimation>(texture, 1, 8, 5, 0.2f);
		play1->SetFlip(SDL_FLIP_NONE);
		play1->SetSize(50,60);
		play1->Set2DPosition(200, 400);
		//Camera::GetInstance()->SetTarget(obj);
		m_listAnimation.push_back(play1);
		m_KeyPress = 0;

		//play2
		texture = ResourceManagers::GetInstance()->GetTexture("actor_ghost2.tga");
		play2 = std::make_shared<SpriteAnimation>(texture, 1, 8, 3, 0.2f);
		play2->SetFlip(SDL_FLIP_NONE);
		play2->SetSize(50, 60);
		play2->Set2DPosition(800, 400);
		//Camera::GetInstance()->SetTarget(obj);
		m_listAnimation2.push_back(play2);
		m_KeyPress2 = 0;

		//energy
		for (int i = 0; i < 10; i++)
			{ 
			texture = ResourceManagers::GetInstance()->GetTexture("btn_energy3.0.tga");
			eng = std::make_shared<SpriteAnimation>(texture, 2, 4, 2, 0.2f);
			eng->SetFlip(SDL_FLIP_HORIZONTAL);
			eng->SetSize(28, 28);
		
			// Randomly generate positions within the desired frame
			int x = 70 + (rand() % (44 * 32 - 40- eng->GetWidth()));
			int y = 120 + (rand() % (20 * 32 - 20 - eng->GetHeight()));

			eng->Set2DPosition(x, y);
			//eng->Set2DPosition(600, 600);
			//Camera::GetInstance()->SetTarget(obj);
			m_listEnergy.push_back(eng);
			eng->setActive(true);
			}
		//mana
				texture = ResourceManagers::GetInstance()->GetTexture("btn_mana.tga");
				mana1 = std::make_shared<Sprite2D>(texture, SDL_FLIP_HORIZONTAL);
				mana1->Set2DPosition(53, 56);
				m_listMana1.push_back(mana1);
				mana1->setActive(false);

				texture = ResourceManagers::GetInstance()->GetTexture("btn_mana.tga");
				mana2 = std::make_shared<Sprite2D>(texture, SDL_FLIP_HORIZONTAL);
				mana2->Set2DPosition(SCREEN_WIDTH - 40*6 - button->GetWidth() - 10, 56);
				m_listMana2.push_back(mana2);
				mana2->setActive(false);
		//healthy bar
		for(int i = 0; i < 5; i++)
		{
			texture = ResourceManagers::GetInstance()->GetTexture("heart.tga");
			auto heart1 = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
			heart1->SetSize(40, 38);
			heart1->Set2DPosition(53 + i * 50, 18);
			m_listHealth1.push_back(heart1);
		}
		for (int i = 0; i < 5; i++)
		{
			texture = ResourceManagers::GetInstance()->GetTexture("heart.tga");
			auto heart2 = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
			heart2->SetSize(40, 38);
			heart2->Set2DPosition(SCREEN_WIDTH - i * 50 - heart2->GetWidth() - button->GetWidth() - 10, 18);
			m_listHealth2.push_back(heart2);
		}
		//bullet
		for (int i = 0; i < 6; i++)
		{
			texture = ResourceManagers::GetInstance()->GetTexture("bullet_2.0.tga");
			bullet = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
			bullet->Set2DPosition(0, 0);
			bullet->SetSize(30,30);
			bullet->setActive(false);
			m_listBullet.push_back(bullet);
		}
		for (int i = 0; i < 6; i++)
		{
			texture = ResourceManagers::GetInstance()->GetTexture("bullet_2.0.tga");
			bullet2 = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
			bullet2->Set2DPosition(0, 0);
			bullet2->SetSize(30, 30);
			bullet2->setActive(false);
			m_listBullet2.push_back(bullet2);
		}
	// load sound

		energy_Sound = std::make_shared<Sound>();
		energy_Sound->LoadSfx("Data/Sounds/energy_collected.wav");
		shoot_Sound = std::make_shared<Sound>();
		shoot_Sound->LoadSfx("Data/Sounds/lazersound.wav");
		shoot_Sound = std::make_shared<Sound>();
		shoot_Sound->LoadSfx("Data/Sounds/lazersound.wav");
		damage1_Sound = std::make_shared<Sound>();
		damage1_Sound->LoadSfx("Data/Sounds/damage1.wav");
		damage2_Sound = std::make_shared<Sound>();
		damage2_Sound->LoadSfx("Data/Sounds/damage2.wav");
		energy_Sound = std::make_shared<Sound>();
		energy_Sound->LoadSfx("Data/Sounds/energy_collected.wav");
	}

	void GSPlay2::Exit()
	{
	}


	void GSPlay2::Pause()
	{

	}
	void GSPlay2::Resume()
	{
		// button close
		//auto texture = ResourceManagers::GetInstance()->GetTexture("btn_restart.tga");
		//button->SetTexture(texture);

	}
	void GSPlay2::MoveCharacter(std::shared_ptr<SpriteAnimation> player, int keyPressed, std::list<std::shared_ptr<Sprite2D>> bullets,int bullet_X, int bullet_Y)
	{
		float speed = 300.0f;
		float deltaTime = 0.016f; // Adjust this as needed
		time1 += 1;
		if (keyPressed & 1) // Left
		{	
			player->SetSpriteRow(2);
			if (player->GetPosition().x - deltaTime  *speed >= 46.0f)
			{
				player->Set2DPosition(player->GetPosition().x -  speed * deltaTime, player->GetPosition().y);
			}
		}
		else if (keyPressed & (1 << 1)) // Down
		{
			player->SetSpriteRow(1);
			if (player->GetPosition().y + deltaTime *  speed <= SCREEN_HEIDHT - 46.0f - player->GetHeight())
			{
				player->Set2DPosition(player->GetPosition().x, player->GetPosition().y +  speed * deltaTime);
			}
		}
		else if (keyPressed & (1 << 2)) // Right
		{	
			player->SetSpriteRow(3);
			if (player->GetPosition().x + deltaTime * speed <= SCREEN_WIDTH - 46.0f - player->GetWidth())
			{
				player->Set2DPosition(player->GetPosition().x +  speed * deltaTime, player->GetPosition().y);

			}
		}
		else if (keyPressed & (1 << 3)) // Up
		{	
			player->SetSpriteRow(1);
			if (player->GetPosition().y - deltaTime *  speed >= 90.0f)
			{
				player->Set2DPosition(player->GetPosition().x, player->GetPosition().y -  speed * deltaTime);
			}
		}
		else if (keyPressed & (1 << 4)) {
			if (manaLevel1 == 6) {
				if (bulletCount1 > 0) {
					if (time1 > 10)
					{
						player->SetSpriteRow(1);
						time1 = 0;

						for (auto it : bullets) {
							if (it->getActive() == false) {
								// load sound 
								if (ResourceManagers::GetInstance()->get_Music() == true) {

									
									shoot_Sound->PlaySfx(0, 0);
								}
								it->setActive(true);
								it->Set2DPosition(player->GetPosition().x + player->GetWidth() / 2 - 15.0f, player->GetPosition().y + player->GetHeight() / 2);
								it->SetBulletDirectionX(bullet_X);
								it->SetBulletDirectionY(bullet_Y);
								bulletCount1--;
								if (bulletCount1 == 0) {
									manaLevel1 = 0;
									mana1->setActive(false);
								}
								break;
							}
						}
					}
				}
			}
		}
	}
	void GSPlay2::MoveCharacter1(std::shared_ptr<SpriteAnimation> player1, int keyPressed1, std::list<std::shared_ptr<Sprite2D>> bullets1, int bullet_X1, int bullet_Y1)
	{
		float speed = 300.0f;
		float deltaTime = 0.016f; // Adjust this as needed
		time1 += 1;
		if (keyPressed1 & 1) // Left
		{
			player1->SetSpriteRow(2);
			if (player1->GetPosition().x - deltaTime * speed >= 46.0f)
			{
				player1->Set2DPosition(player1->GetPosition().x - speed * deltaTime, player1->GetPosition().y);
			}
		}
		else if (keyPressed1 & (1 << 1)) // Down
		{
			player1->SetSpriteRow(1);
			if (player1->GetPosition().y + deltaTime * speed <= SCREEN_HEIDHT - 46.0f - player1->GetHeight())
			{
				player1->Set2DPosition(player1->GetPosition().x, player1->GetPosition().y + speed * deltaTime);
			}
		}
		else if (keyPressed1 & (1 << 2)) // Right
		{
			player1->SetSpriteRow(3);
			if (player1->GetPosition().x + deltaTime * speed <= SCREEN_WIDTH - 46.0f - player1->GetWidth())
			{
				player1->Set2DPosition(player1->GetPosition().x + speed * deltaTime, player1->GetPosition().y);

			}
		}
		else if (keyPressed1 & (1 << 3)) // Up
		{
			player1->SetSpriteRow(1);
			if (player1->GetPosition().y - deltaTime * speed >= 90.0f)
			{
				player1->Set2DPosition(player1->GetPosition().x, player1->GetPosition().y - speed * deltaTime);
			}
		}
		else if (keyPressed1 & (1 << 4)) {
			if (manaLevel2 == 6) {
				if (bulletCount2 > 0) {
					if (time1 > 10)
					{
						player1->SetSpriteRow(1);
						time1 = 0;

						for (auto it : bullets1) {
							if (it->getActive() == false) {
								// load sound 
								if (ResourceManagers::GetInstance()->get_Music() == true) {

									
									shoot_Sound->PlaySfx(0, 0);
								}
								it->setActive(true);
								it->Set2DPosition(player1->GetPosition().x + player1->GetWidth() / 2 - 15.0f, player1->GetPosition().y + player1->GetHeight() / 2);
								it->SetBulletDirectionX(bullet_X1);
								it->SetBulletDirectionY(bullet_Y1);
								bulletCount2--;
								if (bulletCount2 == 0) {
									manaLevel2 = 0;
									mana2->setActive(false);
								}
								break;
							}
						}
					}
				}
			}
		}
	}
	void GSPlay2::HandleEvents()
	{
	}

	void GSPlay2::HandleKeyEvents(SDL_Event& e)
	{
		//If a key was pressed
		if (e.type == SDL_KEYDOWN)// && e.key.repeat == 0) //For e.key.repeat it's because key repeat is enabled by default and if you press and hold a key it will report multiple key presses. That means we have to check if the key press is the first one because we only care when the key was first pressed.
		{
			//Adjust the velocity
			switch (e.key.keysym.sym)
			{
			case SDLK_a:
				m_KeyPress |= 1;
				break;
			case SDLK_s:
				m_KeyPress |= 1 << 1;
				break;
			case SDLK_d:
				m_KeyPress |= 1 << 2;
				break;
			case SDLK_w:
				m_KeyPress |= 1 << 3;
				break;
			case SDLK_SPACE:
				m_KeyPress |= 1 << 4;
				break;
			default:
				break;
			}
		}
		////Key Up
		else if (e.type == SDL_KEYUP)//&& e.key.repeat == 0)
		{
			//Adjust the velocity
			switch (e.key.keysym.sym)
			{
			case SDLK_a:
				m_KeyPress ^= 1;
				bullet_X1 = -1;
				bullet_Y1 = 0;
				break;
			case SDLK_s:
				m_KeyPress ^= 1 << 1;
				bullet_X1 = 0;
				bullet_Y1 = 1;
				break;
			case SDLK_d:
				m_KeyPress ^= 1 << 2;
				bullet_X1 = 1;
				bullet_Y1 = 0;
				break;
			case SDLK_w:
				m_KeyPress ^= 1 << 3;
				bullet_X1 = 0;
				bullet_Y1 = -1;
				break;
			case SDLK_SPACE:
				m_KeyPress ^= 1 << 4;
				if (bullet->GetPosition().x < 0 || bullet->GetPosition().x >1200 || bullet->GetPosition().y < 0 || bullet->GetPosition().y>800) {
				}

				break;
			default:
				break;
			}
		}
		if (e.type == SDL_KEYDOWN)// && e.key.repeat == 0) //For e.key.repeat it's because key repeat is enabled by default and if you press and hold a key it will report multiple key presses. That means we have to check if the key press is the first one because we only care when the key was first pressed.
		{
			//Adjust the velocity
			switch (e.key.keysym.sym)
			{
			case SDLK_LEFT:
				m_KeyPress2 |= 1;
				break;
			case SDLK_DOWN:
				m_KeyPress2 |= 1 << 1;
				break;
			case SDLK_RIGHT:
				m_KeyPress2 |= 1 << 2;
				break;
			case SDLK_UP:
				m_KeyPress2 |= 1 << 3;
				break;
			case SDLK_RETURN:
				m_KeyPress2 |= 1 << 4;
				break;
			default:
				break;
			}
		}
		////Key Up
		else if (e.type == SDL_KEYUP)//&& e.key.repeat == 0)
		{
			//Adjust the velocity
			switch (e.key.keysym.sym)
			{
			case SDLK_LEFT:
				m_KeyPress2 ^= 1;
				bullet_X2 = -1;
				bullet_Y2 = 0;
				break;
			case SDLK_DOWN:
				m_KeyPress2 ^= 1 << 1;
				bullet_X2 = 0;
				bullet_Y2 = 1;
				break;
			case SDLK_RIGHT:
				m_KeyPress2 ^= 1 << 2;
				bullet_X2 = 1;
				bullet_Y2 = 0;
				break;
			case SDLK_UP:
				m_KeyPress2 ^= 1 << 3;
				bullet_X2 = 0;
				bullet_Y2 = -1;
				break;
			case SDLK_RETURN:
				m_KeyPress2 ^= 1 << 4;
				if (bullet2->GetPosition().x < 0 || bullet2->GetPosition().x >1200 || bullet2->GetPosition().y < 0 || bullet2->GetPosition().y>800) {
				}

				break;
			default:
				break;
			}
		}
	}


	void GSPlay2::HandleTouchEvents(SDL_Event& e)
	{
		for (auto button : m_listButton)
		{
			if (button->HandleTouchEvent(&e))
			{
				break;
			}
		}
	}

	void GSPlay2::HandleMouseMoveEvents(int x, int y)
	{
	}
	float metaTime = 0.0f;
	int time = 0;

	void GSPlay2::Update(float deltaTime)
	{
		speedP1 = 300;
		time += 1;
		float engTime = 0.0f;
		MoveCharacter(play1, m_KeyPress, m_listBullet, bullet_X1, bullet_Y1);
		MoveCharacter1(play2, m_KeyPress2, m_listBullet2, bullet_X2, bullet_Y2);
		float play1_X = play1->GetPosition().x + play1->GetWidth() / 2 - 15.0f;
		float play1_Y = play1->GetPosition().y + play1->GetHeight() / 2;
		float play2_X = play2->GetPosition().x + play2->GetWidth() / 2 - 15.0f;
		float play2_Y = play2->GetPosition().y + play2->GetHeight() / 2;
		// float manaX = 20.0f;
		for (auto it : m_listAnimation)
		{
			it->Update(deltaTime);
			for (auto kt : m_listBullet2)
			{
				if (kt->getActive() && kt->collision1(kt->GetPosition().x, kt->GetPosition().y, play1_X, play1_Y))
				{
					// Handle the collision here
					if (!m_listHealth1.empty())
					{
						// Remove a heart from the list
						m_listHealth1.pop_back();

						if (ResourceManagers::GetInstance()->get_Music() == true) {

							// load sound 
							
							damage1_Sound->PlaySfx(0, 0);
						}

						// Deactivate the bullet
						kt->setActive(false);
						play1->SetSpriteRow(5);
					}
				}
			}
		}
		for (auto it : m_listAnimation2)
		{
			it->Update(deltaTime);
			for (auto kt : m_listBullet)
			{
				if (kt->getActive() && kt->collision1(kt->GetPosition().x, kt->GetPosition().y, play2_X, play2_Y))
				{
					// Handle the collision here
					if (!m_listHealth2.empty())
					{
						// Remove a heart from the list
						m_listHealth2.pop_back();
						if (ResourceManagers::GetInstance()->get_Music() == true) {

							// load sound 
							
							damage2_Sound->PlaySfx(0, 0);
						}

					// Deactivate the bullet
					kt->setActive(false);
				}
			}
		}
	}
	if (m_listHealth2.empty())
	{
		ResourceManagers::GetInstance()->set_Play1Win(true);
		ResourceManagers::GetInstance()->set_Play2Win(false);
		ResourceManagers::GetInstance()->demWin1++;
		int i = ResourceManagers::GetInstance()->demWin1;
		printf("P1_%d", i);
			GameStateMachine::GetInstance()->ChangeState(StateType::STATE_END2);

	}
	if (m_listHealth1.empty())
	{
		ResourceManagers::GetInstance()->set_Play1Win(false);
		ResourceManagers::GetInstance()->set_Play2Win(true);
		ResourceManagers::GetInstance()->demWin2++;

			GameStateMachine::GetInstance()->ChangeState(StateType::STATE_END2);
		}

		for (auto it : m_listButton)
		{
			it->Update(deltaTime);

		}
		metaTime += deltaTime;
		//printf("%f", metaTime);
		engTime += deltaTime;

		//energy
		for (auto it : m_listEnergy) {
			if (it->getActive()) {

				for (auto kt : m_listAnimation) {
					if (it->collision1(it->GetPosition().x, it->GetPosition().y + it->GetHeight() / 2, play1_X, play1_Y))
					{
						// printf("Collision");
						it->setActive(false);
						engNumberplay1++;
						if (manaLevel1 < 6)
						{
							// load sound 
							if (ResourceManagers::GetInstance()->get_Music() == true) {
								energy_Sound->PlaySfx(0, 0);
							}
							manaLevel1++; 
							bulletCount1++;
							//printf("%d", bulletCount1);
							mana1->setActive(true);
						}
						 if (manaLevel1 == 6)
						{
							engNumberplay1 = 0;
						}
					}
				}
				for (auto kt : m_listAnimation2) 
				{
					if (it->collision1(it->GetPosition().x, it->GetPosition().y + it->GetHeight() / 2, play2_X, play2_Y))
					{
						it->setActive(false);
						engNumberplay2++;
						if (manaLevel2 < 6)
						{
							if (ResourceManagers::GetInstance()->get_Music() == true) {
								energy_Sound->PlaySfx(0, 0);
							}
							manaLevel2++;
							printf("manaLevel2: %d\n", manaLevel2);
							bulletCount2++;
							mana2->setActive(true);
							if (manaLevel2 == 6)
							{
								engNumberplay2 = 0;
							}
							/*printf("manaLevel2: %d\n", manaLevel2);
							printf("engNumberplay2: %d\n", engNumberplay2);
							printf("bulletCount2: %d\n", bulletCount2);*/
						}
					}
				}
			}
				// Randomly generate positions within the desired frame
				int x = 70 + (rand() % (44 * 32 - eng->GetWidth()));
				int y = 120 + (rand() % (20 * 32 - eng->GetHeight()));
				if (metaTime > 1.0f) {
					if (!it->getActive()) {
						it->setActive(true);
						it->Set2DPosition(x, y);
						metaTime = 0.0f;
					}
				}
				it->Update(deltaTime);
		}
		//bullet
		for (auto kt : m_listBullet) {
			
			if (kt->getActive() == true)
			{
					float directionX = kt->GetBulletDirectionX();
					float directionY = kt->GetBulletDirectionY();
					kt->Set2DPosition(kt->GetPosition().x + directionX * 5 * speedP1 * deltaTime, kt->GetPosition().y + directionY * 5 * speedP1 * deltaTime);
					if (kt->GetPosition().y < 100 || kt->GetPosition().y > 745 || kt->GetPosition().x > 1420 || kt->GetPosition().x < 40)
					{
						kt->setActive(false);
					}
				}
			}
		for (auto kt : m_listBullet2) {
			if (kt->getActive() == true) {

				float directionX2 = kt->GetBulletDirectionX();
				float directionY2 = kt->GetBulletDirectionY();
				kt->Set2DPosition(kt->GetPosition().x + directionX2 * 5 * speedP1 * deltaTime, kt->GetPosition().y + directionY2 * 5 * speedP1 * deltaTime);
			}
			if (kt->GetPosition().y < 100 || kt->GetPosition().y > 745 || kt->GetPosition().x > 1420 || kt->GetPosition().x < 40)
			{
				kt->setActive(false);
			}
		}
		//mana

		for (auto it : m_listMana1)
		{
			
			for (int i = 0; i < bulletCount1; i++) {
				if (it->getActive()) 
				{
					it->SetSize(40 + 40 * i, 40);
					
				}
				
			}
		}
		for (auto it : m_listMana2)
		{
			for (int i = 0; i < bulletCount2; i++)
			{
				if (it->getActive())
				{
					it->SetSize(40 + 40 * i, 40);
					
				}
				
			}
		}
	}
	void GSPlay2::Draw(SDL_Renderer* renderer)
	{
		m_background->Draw(renderer);
		//m_score->Draw();
		for (auto it : m_listButton)
		{
			it->Draw(renderer);
		}
	//	obj->Draw(renderer);
		for (auto it : m_listAnimation)
		{
			it->Draw(renderer);
		}
		for (auto it : m_listAnimation2)
		{
			it->Draw(renderer);
		}
		for (auto it : m_listEnergy) 
		{
			if (it->getActive() == true) 
			{
				it->Draw(renderer);
			}
		}
		for (auto it : m_listMana1)
		{
			if (it->getActive()) {
				it->Draw(renderer);
			}
		}
		for (auto it : m_listMana2)
		{
			if (it->getActive()) {
				it->Draw(renderer);
			}
		}
		for (auto it : m_listHealth1)
		{
			it->Draw(renderer);
		}
		for (auto it : m_listHealth2)
		{
			it->Draw(renderer);
		}
		for (auto it : m_listBullet)
		{

			if (it->getActive())
				{
					it->Draw(renderer);

				}
		}
		for (auto it : m_listBullet2) 
		{

			if (it->getActive()) 
			{
				it->Draw(renderer);

			}
		}
	}
