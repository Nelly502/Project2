#include "GSPlay1.h"
#include "GameObject/TextureManager.h"
#include "GameObject/Sprite2D.h"
#include "GameObject/MouseButton.h"
#include "GameObject/SpriteAnimation.h"
#include "GameObject/Camera.h"
#include "KeyState.h"
#include "CMath.h"
#include"ResourceManagers.h"


GSPlay1::GSPlay1()
{
}
int bullet1_X1;
int bullet1_Y1;
int bullet1_X2;
int bullet1_Y2;
float play1m1_X;
float play1m1_Y;
GSPlay1::~GSPlay1()
{
}

void GSPlay1::Init()
{
	//auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("map1.0.tga");

	// background

	m_background = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
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
	play1->SetSize(50, 60);
	play1->Set2DPosition(200, 400);
	//Camera::GetInstance()->SetTarget(obj);
	m_listAnimation.push_back(play1);
	play1->setActive(true);
	m_KeyPress = 0;

	//play2
	texture = ResourceManagers::GetInstance()->GetTexture("actor_ghost2.tga");
	play2 = std::make_shared<SpriteAnimation>(texture, 1, 8, 3, 0.2f);
	play2->SetFlip(SDL_FLIP_NONE);
	play2->SetSize(50, 60);
	play2->Set2DPosition(800, 400);
	//Camera::GetInstance()->SetTarget(obj);
	m_listAnimation2.push_back(play2);
	play2->setActive(true);
	m_KeyPress2 = 0;

	//coin
	for (int i = 0; i < 100; i++)
	{ 
		texture = ResourceManagers::GetInstance()->GetTexture("btn_coin.tga");
		eng = std::make_shared<SpriteAnimation>(texture, 1, 7, 1, 0.15f);
		eng->SetFlip(SDL_FLIP_NONE);
		eng->SetSize(25, 25);

		// Randomly generate positions within the desired frame
		int x = 32*2 + (rand() % (42 * 32  - eng->GetWidth()));
		int y = 32*3 + (rand() % (19 * 32  - eng->GetHeight()));
		eng->Set2DPosition(x, y);
		m_listEnergy.push_back(eng);
		eng->setActive(true);
	}
	//healthy bar
	for (int i = 0; i < 1; i++)
	{
		texture = ResourceManagers::GetInstance()->GetTexture("heart.tga");
		auto heart1 = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
		heart1->SetSize(33, 30);
		heart1->Set2DPosition(4*32 + 14, 32 + 17);
		m_listHealth1.push_back(heart1);
	}
	for (int i = 0; i < 1; i++)
	{
		texture = ResourceManagers::GetInstance()->GetTexture("heart.tga");
		auto heart2 = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
		heart2->SetSize(33, 30);
		heart2->Set2DPosition(SCREEN_WIDTH - 4 * 32 + 12 - heart2->GetWidth() - button->GetWidth() - 115, 32 + 17);
		m_listHealth2.push_back(heart2);
	}
	//Score
	m_textColor = { 255,255,255 };
	m_textScore = std::make_shared<Text>("Data/CreditCard-26Me.ttf", m_textColor);
	m_textScore->SetSize(100, 30);
	m_textScore->Set2DPosition(6*32, 2*32 - 10);
	m_textScore->LoadFromRenderText(std::to_string(engNumberplay1) + "/" + std::to_string(maxcoin));

	m_textColor1 = { 255, 255, 255 };
	m_textScore1 = std::make_shared<Text>("Data/CreditCard-26Me.ttf", m_textColor1);
	m_textScore1->SetSize(100, 30);
	m_textScore1->Set2DPosition(SCREEN_WIDTH - 4 * 32 + 12 - m_textScore1->GetWidth() - button->GetWidth(), 2 * 32 - 10);
	m_textScore1->LoadFromRenderText(std::to_string(engNumberplay2) + "/" + std::to_string(maxcoin));
	//bullet
	for (int i = 0; i < 6; i++)
	{
		texture = ResourceManagers::GetInstance()->GetTexture("bullet_1.0.tga");
		bullet = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
		bullet->Set2DPosition(0, 0);
		bullet->SetSize(30, 30);
		bullet->setActive(false);
		m_listBullet.push_back(bullet);
	}
	for (int i = 0; i < 6; i++)
	{
		texture = ResourceManagers::GetInstance()->GetTexture("bullet_1.0.tga");
		bullet2 = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
		bullet2->Set2DPosition(0, 0);
		bullet2->SetSize(30, 30);
		bullet2->setActive(false);
		m_listBullet2.push_back(bullet2);
	}
	
		shoot_Sound = std::make_shared<Sound>();
		shoot_Sound->LoadSfx("Data/Sounds/lazersound.wav");

		damage1_Sound = std::make_shared<Sound>();
		damage1_Sound->LoadSfx("Data/Sounds/damage1.wav");

		damage2_Sound = std::make_shared<Sound>();
		damage2_Sound->LoadSfx("Data/Sounds/damage2.wav");

		// load sound 
		energy_Sound = std::make_shared<Sound>();
		energy_Sound->LoadSfx("Data/Sounds/energy_collected.wav");

		energy_Sound = std::make_shared<Sound>();
		energy_Sound->LoadSfx("Data/Sounds/energy_collected.wav");
}

void GSPlay1::Exit()
{
}


void GSPlay1::Pause()
{

}
void GSPlay1::Resume()
{
	// button close
	//auto texture = ResourceManagers::GetInstance()->GetTexture("btn_restart.tga");
	//button->SetTexture(texture);

}
void GSPlay1::MoveCharacter(std::shared_ptr<SpriteAnimation> player, int keyPressed, std::list<std::shared_ptr<Sprite2D>> bullets, int bullet1_X, int bullet1_Y)
{
	float speed = 300.0f;
	float deltaTime = 0.016f; // Adjust this as needed
	time1_1 += 1;
	if (keyPressed & 1) // Left
	{
		player->SetSpriteRow(2);
		if (player->GetPosition().x - deltaTime * speed >= 46.0f + player -> GetWidth() * 1/2)
		{
			player->Set2DPosition(player->GetPosition().x - speed * deltaTime, player->GetPosition().y);
		}
	}
	else if (keyPressed & (1 << 1)) // Down
	{
		player->SetSpriteRow(1);
		if (player->GetPosition().y + deltaTime * speed <= SCREEN_HEIDHT - 46.0f - player->GetHeight() * 3/2)
		{
			player->Set2DPosition(player->GetPosition().x, player->GetPosition().y + speed * deltaTime);
		}
	}
	else if (keyPressed & (1 << 2)) // Right
	{
		player->SetSpriteRow(3);
		if (player->GetPosition().x + deltaTime * speed <= SCREEN_WIDTH - 46.0f - player->GetWidth() * 3/2)
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

		if (time1_1 > 10)
		{
			player->SetSpriteRow(1);
			time1_1 = 0;

			for (auto it : bullets) {
				if (it->getActive() == false) {
					// load sound 
					if (ResourceManagers::GetInstance()->get_Music() == true) {
						shoot_Sound->PlaySfx(0, 0);
					}
					it->setActive(true);
					it->Set2DPosition(player->GetPosition().x + player->GetWidth() / 2 - 15.0f, player->GetPosition().y + player->GetHeight() / 2);
					it->SetBulletDirectionX(bullet1_X);
					it->SetBulletDirectionY(bullet1_Y);
					break;
				}
			}
		}
	}
}
void GSPlay1::HandleEvents()
{
}

void GSPlay1::HandleKeyEvents(SDL_Event& e)
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
			bullet1_X1 = -1;
			bullet1_Y1 = 0;
			break;
		case SDLK_s:
			m_KeyPress ^= 1 << 1;
			bullet1_X1 = 0;
			bullet1_Y1 = 1;
			break;
		case SDLK_d:
			m_KeyPress ^= 1 << 2;
			bullet1_X1 = 1;
			bullet1_Y1 = 0;
			break;
		case SDLK_w:
			m_KeyPress ^= 1 << 3;
			bullet1_X1 = 0;
			bullet1_Y1 = -1;
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
			bullet1_X2 = -1;
			bullet1_Y2 = 0;
			break;
		case SDLK_DOWN:
			m_KeyPress2 ^= 1 << 1;
			bullet1_X2 = 0;
			bullet1_Y2 = 1;
			break;
		case SDLK_RIGHT:
			m_KeyPress2 ^= 1 << 2;
			bullet1_X2 = 1;
			bullet1_Y2 = 0;
			break;
		case SDLK_UP:
			m_KeyPress2 ^= 1 << 3;
			bullet1_X2 = 0;
			bullet1_Y2 = -1;
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


void GSPlay1::HandleTouchEvents(SDL_Event& e)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvent(&e))
		{
			break;
		}
	}
}

void GSPlay1::HandleMouseMoveEvents(int x, int y)
{
}
float metaTimem1 = 0.0f;
int timem1 = 0;

void GSPlay1::Update(float deltaTime)
{
	speedP1 = 300;
	timem1 += 1;
	// float engTime = 0.0f;
	MoveCharacter(play1, m_KeyPress, m_listBullet, bullet1_X1, bullet1_Y1);
	MoveCharacter(play2, m_KeyPress2, m_listBullet2, bullet1_X2, bullet1_Y2);
	float play1m1_X = play1->GetPosition().x + play1->GetWidth() / 2 - 15.0f;
	float play1m1_Y = play1->GetPosition().y + play1->GetHeight() / 2;
	float play2m1_X = play2->GetPosition().x + play2->GetWidth() / 2 - 15.0f;
	float play2m1_Y = play2->GetPosition().y + play2->GetHeight() / 2;
	// float manaX = 20.0f;
	for (auto it : m_listAnimation)
	{
		it->Update(deltaTime);
		for (auto kt : m_listBullet2)
		{
			if (kt->getActive() && kt->collision1(kt->GetPosition().x, kt->GetPosition().y, play1m1_X, play1m1_Y))
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
				// init player again
				if (m_listHealth1.empty())
				{
					play1->setActive(false);
				}
			}
		}
		if (metaTimem1 > 1.0f) {
			if (!it->getActive()) {
				it->setActive(true);
				it->SetSpriteRow(1);
				it->Set2DPosition(50, 120);
				metaTimem1 = 0.0f;
			}
		}
	}
	for (auto it : m_listAnimation2)
	{
		it->Update(deltaTime);
		for (auto kt : m_listBullet)
		{
			if (kt->getActive() && kt->collision1(kt->GetPosition().x, kt->GetPosition().y, play2m1_X, play2m1_Y))
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
				if (m_listHealth2.empty())
				{
					play2->setActive(false);
				}
			}
		}
		if (metaTimem1 > 1.0f) {
			if (!it->getActive()) {
				it->setActive(true);
				it->SetSpriteRow(1);
				it->Set2DPosition(SCREEN_WIDTH - it -> GetWidth() - 50, 120);
				metaTimem1 = 0.0f;
			}
		}
	}

	for (auto it : m_listButton)
	{
		it->Update(deltaTime);

	}
	metaTimem1 += deltaTime;
	// engTime += deltaTime;

	//coin
	for (auto it : m_listEnergy) {
		if (it -> getActive()) { 
		for (auto kt : m_listAnimation) {
			if (it->collision1(it->GetPosition().x + it->GetWidth() / 2, it->GetPosition().y, play1m1_X, play1m1_Y))
			{
				if (ResourceManagers::GetInstance()->get_Music() == true) {
					energy_Sound->PlaySfx(0, 0);
				}
				it->setActive(false);
				engNumberplay1++;
				m_textScore->LoadFromRenderText(std::to_string(engNumberplay1) + "/" + std::to_string(maxcoin));
			}
		}
		for (auto kt : m_listAnimation2) {
			if (it->collision1(it->GetPosition().x + it->GetWidth() / 2, it->GetPosition().y + it->GetHeight() / 2, play2m1_X, play2m1_Y))
			{
				if (ResourceManagers::GetInstance()->get_Music() == true) {
					energy_Sound->PlaySfx(0, 0);
				}
				it->setActive(false);
				engNumberplay2++;
				m_textScore1->LoadFromRenderText(std::to_string(engNumberplay2) + "/" + std::to_string(maxcoin));
			}
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
			kt->Set2DPosition(kt->GetPosition().x + directionX * 4 * speedP1 * deltaTime, kt->GetPosition().y + directionY * 4 * speedP1 * deltaTime);
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
			kt->Set2DPosition(kt->GetPosition().x + directionX2 * 4 * speedP1 * deltaTime, kt->GetPosition().y + directionY2 * 4 * speedP1 * deltaTime);
		}
		if (kt->GetPosition().y < 100 || kt->GetPosition().y > 745 || kt->GetPosition().x > 1420 || kt->GetPosition().x < 40)
		{
			kt->setActive(false);
		}
	}
	//overgame
	if (engNumberplay1 == maxcoin)
	{
		ResourceManagers::GetInstance()->set_Play1Win(true);
		ResourceManagers::GetInstance()->set_Play2Win(false);
		ResourceManagers::GetInstance()->demWin1++;
		int i = ResourceManagers::GetInstance()->demWin1;
		printf("P1_%d", i);

		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_END);
	}
	if (engNumberplay2 == maxcoin)
	{
		ResourceManagers::GetInstance()->set_Play2Win(true);
		ResourceManagers::GetInstance()->set_Play1Win(false);
		ResourceManagers::GetInstance()->demWin2++;
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_END);
	}
	}
void GSPlay1::Draw(SDL_Renderer* renderer)
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
		if (it->getActive()) { 
		it->Draw(renderer);
		}
	}
	for (auto it : m_listAnimation2)
	{
		if (it->getActive()) {
			it->Draw(renderer);
		}
	}
	for (auto it : m_listEnergy)
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
	m_textScore->Draw(renderer);
	m_textScore1->Draw(renderer);
}

