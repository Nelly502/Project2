#include "GSPlay3.h"
#include "GameObject/TextureManager.h"
#include "GameObject/Sprite2D.h"
#include "GameObject/MouseButton.h"
#include "GameObject/SpriteAnimation.h"
#include "GameObject/Camera.h"

#include "KeyState.h"
#include "CMath.h"
#include"ResourceManagers.h"


GSPlay3::GSPlay3()
{
}
int bulletm2_X1;
int bulletm2_Y1;
int bulletm2_X2;
int bulletm2_Y2;
float play1m2_X;
float play1m2_Y;
GSPlay3::~GSPlay3()
{
}

void  GSPlay3::Init()
{
	//auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("map3.0.tga");

	// background

	m_background = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIDHT);
	m_background->Set2DPosition(0, 0);

	//load sound
	/*if (ResourceManagers::GetInstance()->get_Music() == true) {
		m_Sound = std::make_shared<Sound>();
		m_Sound->LoadSound("Data/Sounds/evolution.mp3");
		m_Sound->PlaySound();
	}*/
	shoot_Sound = std::make_shared<Sound>();
	shoot_Sound->LoadSfx("Data/Sounds/Monster.wav");
	if (ResourceManagers::GetInstance()->get_Music() == true) {
		shoot_Sound->PlaySfx(0, 0);
	}
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
	play1->SetSize(50, 60);
	play1->Set2DPosition(200, 70);
	play1->setActive(true);
	m_listAnimation.push_back(play1);
	m_KeyPress = 0;
	

	//play2
	texture = ResourceManagers::GetInstance()->GetTexture("actor_ghost2.tga");
	play2 = std::make_shared<SpriteAnimation>(texture, 1, 8, 3, 0.2f);
	play2->SetFlip(SDL_FLIP_NONE);
	play2->SetSize(50, 60);
	play2->Set2DPosition(1200, 600);
	play2->setActive(true);
	m_listAnimation2.push_back(play2);
	m_KeyPress2 = 0;
	
	for (int i = 0; i < 5; i++)
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
	for (int i = 0; i < 40; i++)
	{
		texture = ResourceManagers::GetInstance()->GetTexture("btn_mana_Mon.tga");
		auto heart2 = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
		heart2->SetSize(10, 50);
		heart2->Set2DPosition(620 + i * 5, 18);
		m_listHPM.push_back(heart2);
		heart2->setActive(false);
	}
	//bullet
	for (int i = 0; i < 15; i++)
	{
		texture = ResourceManagers::GetInstance()->GetTexture("bullet_2.0.tga");
		bullet = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
		bullet->Set2DPosition(0, 0);
		bullet->SetSize(30, 30);
		bullet->setActive(false);
		m_listBullet.push_back(bullet);
	}
	for (int i = 0; i < 15; i++)
	{
		texture = ResourceManagers::GetInstance()->GetTexture("bullet_2.0.tga");
		bullet2 = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
		bullet2->Set2DPosition(0, 0);
		bullet2->SetSize(30, 30);
		bullet2->setActive(false);
		m_listBullet2.push_back(bullet2);
	}
	for (int i = 0; i < 15; i++)
	{
		texture = ResourceManagers::GetInstance()->GetTexture("bullet_monter.0.tga");
		bulletMonster = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
		bulletMonster->Set2DPosition(0, 0);
		bulletMonster->SetSize(30, 30);
		bulletMonster->setActive(false);
		m_listBulletMonster.push_back(bulletMonster);
	}
	for (int i = 0; i < 15; i++)
	{
		texture = ResourceManagers::GetInstance()->GetTexture("bullet_monter.0.tga");
		bulletMonster2 = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
		bulletMonster2->Set2DPosition(0, 0);
		bulletMonster2->SetSize(30, 30);
		bulletMonster2->setActive(false);
		m_listBulletMonster2.push_back(bulletMonster2);
	}
	texture = ResourceManagers::GetInstance()->GetTexture("btn_die.tga");
	blow = std::make_shared<SpriteAnimation>(texture, 3, 4, 3, 0.2f);
	blow->SetFlip(SDL_FLIP_NONE);
	blow->Set2DPosition(-80, -80);
	blow->SetSize(120, 120);
	m_listBlow.push_back(blow);
	blow->setActive(false);
	//monster
	texture = ResourceManagers::GetInstance()->GetTexture("monster.tga");
	monster = std::make_shared<SpriteAnimation>(texture, 1, 4, 4, 0.2f);
	monster->SetFlip(SDL_FLIP_NONE);
	monster->SetSize(150, 150);
	int x = rand() % 20 + 40;;
	monster->Set2DPosition(650, -100);
	m_listMonster.push_back(monster);
	monster->setActive(false);
	// load all sounds
	shoot_Sound = std::make_shared<Sound>();
	shoot_Sound->LoadSfx("Data/Sounds/lazersound.wav");

	damage1_Sound = std::make_shared<Sound>();
	damage1_Sound->LoadSfx("Data/Sounds/damage1.wav");

	damage1_Sound = std::make_shared<Sound>();
	damage1_Sound->LoadSfx("Data/Sounds/damage1.wav");

	damage1_Sound = std::make_shared<Sound>();
	damage1_Sound->LoadSfx("Data/Sounds/damage1.wav");
	shoot_Sound = std::make_shared<Sound>();
	shoot_Sound->LoadSfx("Data/Sounds/chickdie.wav");

	damage2_Sound = std::make_shared<Sound>();
	damage2_Sound->LoadSfx("Data/Sounds/damage2.wav");

	damage2_Sound = std::make_shared<Sound>();
	damage2_Sound->LoadSfx("Data/Sounds/damage2.wav");

	damage1_Sound = std::make_shared<Sound>();
	damage1_Sound->LoadSfx("Data/Sounds/damage1.wav");

	shoot_Sound = std::make_shared<Sound>();
	shoot_Sound->LoadSfx("Data/Sounds/chickdie.wav");
}

void  GSPlay3::Exit()
{
}


void  GSPlay3::Pause()
{

}
void  GSPlay3::Resume()
{

}
void GSPlay3::MoveCharacter(std::shared_ptr<SpriteAnimation> player, int keyPressed, std::list<std::shared_ptr<Sprite2D>> bullets, int bulletm2_X, int bulletm2_Y)
{
	float speed = 300.0f;
	float deltaTime = 0.016f; // Adjust this as needed
	time1 += 1;
	if (keyPressed & 1) // Left
	{
		player->SetSpriteRow(2);
		if (player->GetPosition().x - deltaTime * speed >= 46.0f)
		{
			player->Set2DPosition(player->GetPosition().x - speed * deltaTime, player->GetPosition().y);
		}
	}
	else if (keyPressed & (1 << 1)) // Down
	{
		player->SetSpriteRow(1);
		if (player->GetPosition().y + deltaTime * speed <= SCREEN_HEIDHT - 46.0f - player->GetHeight())
		{
			player->Set2DPosition(player->GetPosition().x, player->GetPosition().y + speed * deltaTime);
		}
	}
	else if (keyPressed & (1 << 2)) // Right
	{
		player->SetSpriteRow(3);
		if (player->GetPosition().x + deltaTime * speed <= SCREEN_WIDTH - 46.0f - player->GetWidth())
		{
			player->Set2DPosition(player->GetPosition().x + speed * deltaTime, player->GetPosition().y);

		}
	}
	else if (keyPressed & (1 << 3)) // Up
	{
		player->SetSpriteRow(1);
		if (player->GetPosition().y - deltaTime * speed >= 90.0f)
		{
			player->Set2DPosition(player->GetPosition().x, player->GetPosition().y - speed * deltaTime);
		}
	}
	else if (keyPressed & (1 << 4)) {
		if (time1 > 10)
		{
			player->SetSpriteRow(1);
			time1 = 0;
			for (auto it : bullets) {
				if (it->getActive() == false) {
					if (ResourceManagers::GetInstance()->get_Music() == true) {
						// load sound 
						shoot_Sound->PlaySfx(0, 0);
					}
					it->setActive(true);
					it->Set2DPosition(player->GetPosition().x + player->GetWidth() / 2 - 15.0f, player->GetPosition().y + player->GetHeight() / 2);
					it->SetBulletDirectionX(bulletm2_X);
					it->SetBulletDirectionY(bulletm2_Y);
					break;
				}
			}
		}
	}
}
void  GSPlay3::HandleEvents()
{
}

void  GSPlay3::HandleKeyEvents(SDL_Event& e)
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
			bulletm2_X1 = -1;
			bulletm2_Y1 = 0;
			break;
		case SDLK_s:
			m_KeyPress ^= 1 << 1;
			bulletm2_X1 = 0;
			bulletm2_Y1 = 1;
			break;
		case SDLK_d:
			m_KeyPress ^= 1 << 2;
			bulletm2_X1 = 1;
			bulletm2_Y1 = 0;
			break;
		case SDLK_w:
			m_KeyPress ^= 1 << 3;
			bulletm2_X1 = 0;
			bulletm2_Y1 = -1;
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
	if (e.type == SDL_KEYDOWN) 
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
	else if (e.type == SDL_KEYUP)
	{
		
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			m_KeyPress2 ^= 1;
			bulletm2_X2 = -1;
			bulletm2_Y2 = 0;
			break;
		case SDLK_DOWN:
			m_KeyPress2 ^= 1 << 1;
			bulletm2_X2 = 0;
			bulletm2_Y2 = 1;
			break;
		case SDLK_RIGHT:
			m_KeyPress2 ^= 1 << 2;
			bulletm2_X2 = 1;
			bulletm2_Y2 = 0;
			break;
		case SDLK_UP:
			m_KeyPress2 ^= 1 << 3;
			bulletm2_X2 = 0;
			bulletm2_Y2 = -1;
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


void  GSPlay3::HandleTouchEvents(SDL_Event& e)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvent(&e))
		{
			break;
		}
	}
}

void  GSPlay3::HandleMouseMoveEvents(int x, int y)
{
}
float metaTimem2 = 0.0f;
int timem2 = 0;

void  GSPlay3::Update(float deltaTime)
{
	timem2 += 1;
	float engTime = 0.0f;

	MoveCharacter(play1, m_KeyPress, m_listBullet, bulletm2_X1, bulletm2_Y1);
	MoveCharacter(play2, m_KeyPress2, m_listBullet2, bulletm2_X2, bulletm2_Y2);
	float play1_X = play1->GetPosition().x + play1->GetWidth() / 2 - 15.0f;
	float play1_Y = play1->GetPosition().y + play1->GetHeight() / 2;
	float play2_X = play2->GetPosition().x + play2->GetWidth() / 2 - 15.0f;
	float play2_Y = play2->GetPosition().y + play2->GetHeight() / 2;
	// float manaX = 20.0f;
	
	for (auto it : m_listAnimation)
	{
		it->Update(deltaTime);
		for (auto kt : m_listBulletMonster)
		{
			if (kt->getActive() && kt->collision1(kt->GetPosition().x, kt->GetPosition().y, play1_X, play1_Y))
			{
				// Handle the collision here
				if (!m_listHealth1.empty())
				{
					// Remove a heart from the list
					m_listHealth1.pop_back();


					// load sound 
					if (ResourceManagers::GetInstance()->get_Music() == true) {
						damage1_Sound->PlaySfx(0, 0);
					}
					// Deactivate the bullet
					kt->setActive(false);
					play1->SetSpriteRow(5);
				}
			}
		}
		for (auto kt : m_listBullet2)
		{
			if (kt->getActive() && kt->collision1(kt->GetPosition().x, kt->GetPosition().y, play1_X, play1_Y))
			{
				// Handle the collision here
				if (!m_listHealth1.empty())
				{
					// Remove a heart from the list
					m_listHealth1.pop_back();


					// load sound 
					if (ResourceManagers::GetInstance()->get_Music() == true) {
						damage1_Sound->PlaySfx(0, 0);
					}


					// Deactivate the bullet
					kt->setActive(false);
					play1->SetSpriteRow(5);
				}
			}
		}
		for (auto kt : m_listBulletMonster2)
		{
			if (kt->getActive() && kt->collision1(kt->GetPosition().x, kt->GetPosition().y, play1_X, play1_Y))
			{
				// Handle the collision here
				if (!m_listHealth1.empty())
				{
					// Remove a heart from the list
					m_listHealth1.pop_back();
					if (ResourceManagers::GetInstance()->get_Music() == true) {
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
		for (auto kt : m_listBulletMonster)
		{
			if (kt->getActive() && kt->collision1(kt->GetPosition().x, kt->GetPosition().y, play2_X, play2_Y))
			{
				// Handle the collision here
				if (!m_listHealth2.empty())
				{
					// Remove a heart from the list
					m_listHealth2.pop_back();

					// load sound 
					if (ResourceManagers::GetInstance()->get_Music() == true) {
						damage2_Sound->PlaySfx(0, 0);
					}

					// Deactivate the bullet
					kt->setActive(false);
				}
			}
		}
		for (auto kt : m_listBulletMonster2)
		{
			if (kt->getActive() && kt->collision1(kt->GetPosition().x, kt->GetPosition().y, play2_X, play2_Y))
			{
				// Handle the collision here
				if (!m_listHealth2.empty())
				{
					// Remove a heart from the list
					m_listHealth2.pop_back();

					// load sound 
					if (ResourceManagers::GetInstance()->get_Music() == true) {
						damage2_Sound->PlaySfx(0, 0);
					}
					// Deactivate the bullet
					kt->setActive(false);
				}
			}
		}
		for (auto kt : m_listBullet)
		{
			if (kt->getActive() && kt->collision1(kt->GetPosition().x, kt->GetPosition().y, play2_X, play2_Y))
			{
				// Handle the collision here
				if (!m_listHealth2.empty())
				{
					// Remove a heart from the list
					m_listHealth2.pop_back();


					// load sound 
					if (ResourceManagers::GetInstance()->get_Music() == true) {
						damage1_Sound->PlaySfx(0, 0);
					}

					// Deactivate the bullet
					kt->setActive(false);
					play1->SetSpriteRow(5);
				}
			}
		}
	}
	//
	for (auto it : m_listAnimation) {
		for (auto kt : m_listMonster) {
			if (m_listHealth1.empty()&& kt->getActive()) {
				it->setActive(false);
				for (auto ht : m_listBulletMonster) {
					if (!it->getActive()) {
						ht->setActive(false);
					}
				}
			}
		}
	}
	for (auto it : m_listAnimation2) {
		for (auto kt : m_listMonster) {
			if (m_listHealth2.empty() && kt->getActive()) {
				it->setActive(false);
				for (auto ht : m_listBulletMonster2) {
					if (!it->getActive()) {
						ht->setActive(false);
					}
				}
			}
		}
	}

	for (auto it : m_listMonster) {
		for (auto kt : m_listBulletMonster) {
				if (m_listHealth1.empty() && m_listHealth2.empty()&& it->getActive()) {
					kt->setActive(false);
					it->setActive(false);
				}
			}
		
	}
	for (auto it : m_listMonster) {
		for (auto kt : m_listBulletMonster2) {
			if (m_listHealth1.empty() && m_listHealth2.empty() && it->getActive()) {
				kt->setActive(false);
				it->setActive(false);
			}
		}

	}
	//
	for (auto it : m_listMonster) {
		if (m_listHealth2.empty() && !it->getActive() && !m_listHealth1.empty())
		{
			ResourceManagers::GetInstance()->set_Play1Win(true);
			ResourceManagers::GetInstance()->set_Play2Win(false);
			ResourceManagers::GetInstance()->demWin1++;
			int i = ResourceManagers::GetInstance()->demWin1;
			printf("P1_%d", i);
			GameStateMachine::GetInstance()->ChangeState(StateType::STATE_END3);

		}
		if (m_listHealth1.empty()&& !it->getActive() && !m_listHealth2.empty())
		{
			ResourceManagers::GetInstance()->set_Play1Win(false);
			ResourceManagers::GetInstance()->set_Play2Win(true);
			ResourceManagers::GetInstance()->demWin2++;

			GameStateMachine::GetInstance()->ChangeState(StateType::STATE_END3);
		}
		if (m_listHealth1.empty() && m_listHealth2.empty() && !it->getActive()) {
			ResourceManagers::GetInstance()->set_Play1Win(false);
			ResourceManagers::GetInstance()->set_Play2Win(false);
			GameStateMachine::GetInstance()->ChangeState(StateType::STATE_END4);
		}
	}
	
	if (m_listHPM.empty())
	{
		for (auto it : m_listMonster) {
			it->setActive(false);

		}
		for (auto it : m_listBulletMonster) {
			it->setActive(false);
		}
		for (auto it : m_listBulletMonster2) {
			it->setActive(false);
		}
		check = false;
	}

	for (auto it : m_listButton)
	{
		it->Update(deltaTime);

	}
	metaTimem2 += deltaTime;
	engTime += deltaTime;

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

	

	timeMStop += deltaTime;
	mateTime += deltaTime;
	
		for (auto it : m_listMonster) {
			if (mateTime < 10.0f)
			{
			      float vt;
			         it->setActive(true);
					if (it->getActive()) {
						it->Set2DPosition(it->GetPosition().x ,  it->GetPosition().y + speedP2 * deltaTime ) ;
						 vt = it->GetPosition(). y;
						if (350.0f < vt) {
							mateTime = 11.0f;
							check = true;
							for (auto kt : m_listHPM) {
								kt->setActive(true);
							}
						
						}
				
					}
			
		
			}

		}

	float bulletMonsterInterval = 0.2f;
			for (auto it : m_listMonster) {
				bulletMonterTime += deltaTime;
				if (bulletMonterTime >= bulletMonsterInterval) {
					for (auto kt : m_listBulletMonster) {
						if (!kt->getActive() && check == true) {
							kt->Set2DPosition(it->GetPosition().x + it->GetWidth() / 2, it->GetPosition().y + it->GetHeight() / 2);
							kt->setActive(true);
							
							
							float distanceX = (it->GetPosition().x-play1_X);
							float distanceY = (it->GetPosition().y - play1_Y);

							//float angle = atan2(distanceX, distanceY);
							float directionX = -(it->GetPosition().x - play1_X);
							float directionY = -(it->GetPosition().y - play1_Y);

							kt->SetBulletDirectionX(directionX);
							kt->SetBulletDirectionY(directionY);
							break;
						}
					}
					for (auto kt : m_listBulletMonster2) {
						if (!kt->getActive() && check == true) {
							kt->Set2DPosition(it->GetPosition().x + it->GetWidth() / 2, it->GetPosition().y + it->GetHeight() / 2);
							kt->setActive(true);


							float distanceX2 = (it->GetPosition().x - play2_X);
							float distanceY2 = (it->GetPosition().y - play2_Y);

							//float angle = atan2(distanceX, distanceY);
							float directionX2 = -(it->GetPosition().x - play2_X) ;
							float directionY2 = -(it->GetPosition().y - play2_Y);

							kt->SetBulletDirectionX(directionX2);
							kt->SetBulletDirectionY(directionY2);
							break;
						}
					}
					bulletMonterTime = 0.0f;
				}
				
			}

		
			
			for (auto it : m_listBulletMonster) {
				
					if (it->getActive()) {
						float directionX = it->GetBulletDirectionX();

						float directionY = it->GetBulletDirectionY(); 
						//printf("%f__%f", directionX, directionY);

						it->Set2DPosition(it->GetPosition().x + directionX*deltaTime , it->GetPosition().y + directionY*deltaTime );
					}
					if (it->GetPosition().y < 100 || it->GetPosition().y > 745 || it->GetPosition().x > 1420 || it->GetPosition().x < 40)
					{
						it->setActive(false);
					}
				
				
			}
			for (auto it : m_listBulletMonster2) {

				if (it->getActive()) {
					float directionX2 = it->GetBulletDirectionX();

					float directionY2 = it->GetBulletDirectionY();
					//printf("%f__%f", directionX, directionY);

					it->Set2DPosition(it->GetPosition().x + directionX2 *  deltaTime, it->GetPosition().y + directionY2 *  deltaTime);
				}
				if (it->GetPosition().y < 100 || it->GetPosition().y > 745 || it->GetPosition().x > 1420 || it->GetPosition().x < 40)
				{
					it->setActive(false);
				}


			}
			
		
		
		
		
		for (auto it : m_listMonster) {
			
			for (auto kt : m_listBullet) {
				if (it->getActive() && it->collision3(it->GetPosition().x + it->GetWidth() / 2, it->GetPosition().y + it->GetHeight()/2, kt->GetPosition().x, kt->GetPosition().y) && kt->getActive()) {
					kt->setActive(false);
					if (ResourceManagers::GetInstance()->get_Music() == true)
					{
					
						shoot_Sound->PlaySfx(0, 0);
					}
					if (!m_listHPM.empty())
					{
						// Remove a heart from the list
						m_listHPM.pop_back();
					}
					kt->Set2DPosition(0, 0);
					for (auto ht : m_listBlow) {
						ht->Set2DPosition(it->GetPosition().x + it->GetWidth() / 6, it->GetPosition().y + it->GetHeight() / 6);
						if (it->getActive()) {
							ht->setActive(true);

						}
						else
						{
							ht->setActive(false);
						}
						
					}
				
				}

			}
			for (auto kt : m_listBullet2) {
				if (it->getActive() && it->collision3(it->GetPosition().x + it->GetWidth() / 2, it->GetPosition().y + it->GetHeight() / 2, kt->GetPosition().x, kt->GetPosition().y) && kt->getActive()) {
					kt->setActive(false);
					if (ResourceManagers::GetInstance()->get_Music() == true)
					{
						shoot_Sound->PlaySfx(0, 0);
					}
					if (!m_listHPM.empty())
					{
						// Remove a heart from the list
						m_listHPM.pop_back();
					}
					kt->Set2DPosition(0, 0);
					for (auto ht : m_listBlow) {
						ht->Set2DPosition(it->GetPosition().x + it->GetWidth() / 6, it->GetPosition().y + it->GetHeight() / 6);
						if (it->getActive()) {
							ht->setActive(true);

						}
						else
						{
							ht->setActive(false);
						}
						


					}

				}

			}
			
		}
	for (auto it : m_listBlow) {
		it->Update(deltaTime);
		if (it->getActive()) {
			animationTime += deltaTime;
			if (animationTime >= 0.2f) {
				it->setActive(false);
				animationTime = 0.0f;
			}
		}
			
	}

	
	for (auto it : m_listMonster) {
		
		it->Update(deltaTime);
	}
}

	
	
	
void  GSPlay3::Draw(SDL_Renderer* renderer)
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
		if (it->getActive())
		{
			it->Draw(renderer);

		}
	}
	for (auto it : m_listAnimation2)
	{
		if (it->getActive())
		{
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
	for (auto it : m_listHPM)
	{
		if (it->getActive())
		{
			it->Draw(renderer);

		}
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
	for (auto it : m_listMonster) {
		if (it->getActive()) {
			it->Draw(renderer);
		}

	}
	for (auto it : m_listBlow) {
		
		if (it->getActive()) {
			it->Draw(renderer);

		}
		

	}
	for (auto it : m_listBulletMonster) {
		if (it->getActive()) {
			it->Draw(renderer);
		}

	}
	for (auto it : m_listBulletMonster2) {
		if (it->getActive()) {
			it->Draw(renderer);
		}

	}
}
