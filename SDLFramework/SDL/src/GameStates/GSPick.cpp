#include "GameObject/TextureManager.h"
#include "GameObject/Sprite2D.h"
#include "GameObject/MouseButton.h"
#include "GameObject/SpriteAnimation.h"
#include "GameObject/Camera.h"
#include"ResourceManagers.h"
#include <GSPick.h>

GSPick::GSPick()
{
}


GSPick::~GSPick()
{
}


void GSPick::Init()
{
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_pick.tga");
		m_Sound = std::make_shared<Sound>();
		m_Sound->LoadSound("Data/Sounds/intro_music.mp3");
		
	// backgrounds
	m_background = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIDHT);
	m_background->Set2DPosition(0, 0);

	m_textColor = {255, 255, 0};
	m_textGameName = std::make_shared<Text>("Data/HalloweenGuises.ttf", m_textColor);
	m_textGameName->SetSize(600, 120);
	m_textGameName->Set2DPosition(SCREEN_WIDTH/2 - m_textGameName->GetWidth()/2, 30);
	m_textGameName->LoadFromRenderText("ARE YOU READY");

	m_textColor1 = { 255, 255, 0 };
	m_textGameName1 = std::make_shared<Text>("Data/HalloweenGuises.ttf", m_textColor);
	m_textGameName1->SetSize(300, 60);
	m_textGameName1->Set2DPosition(150, 120 + m_textGameName->GetHeight() + 275);
	m_textGameName1->LoadFromRenderText("SURVIVAL");

	m_textColor2 = { 255, 255, 0 };
	m_textGameName2 = std::make_shared<Text>("Data/HalloweenGuises.ttf", m_textColor);
	m_textGameName2->SetSize(300, 60);
	m_textGameName2->Set2DPosition(150 * 2 + 300, 120 + m_textGameName->GetHeight() + 275);
	m_textGameName2->LoadFromRenderText("PACMAN");

	m_textColor3 = { 255, 255, 0 };
	m_textGameName3 = std::make_shared<Text>("Data/HalloweenGuises.ttf", m_textColor);
	m_textGameName3->SetSize(300, 60);
	m_textGameName3->Set2DPosition(SCREEN_WIDTH - 150 - 300, 120 + m_textGameName->GetHeight() + 275);
	m_textGameName3->LoadFromRenderText("HEAVEN OR HELL");
	
	//button close
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	button = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	button->SetSize(50, 50);
	button->Set2DPosition(SCREEN_WIDTH - 60, 10);
	button->SetOnClick([this]() 
		{
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_MENU);
		});
	m_listButton.push_back(button);

	// map 1
	texture = ResourceManagers::GetInstance()->GetTexture("map3.0.tga");
	std::shared_ptr<MouseButton> map1 = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	map1->SetSize(300, 250);
	map1->Set2DPosition(150, (120 + m_textGameName->GetHeight()));
	map1->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY2);
		});
	m_listButton.push_back(map1);
    
	//map2
	texture = ResourceManagers::GetInstance()->GetTexture("map1.0.tga");
	std::shared_ptr<MouseButton> map2 = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);

	map2->SetSize(300, 250);
	map2->Set2DPosition(150*2 + map1 -> GetWidth() , (120 + m_textGameName->GetHeight()));
	map2->SetOnClick([]()
		{
			GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY1);
		});
	m_listButton.push_back(map2);
	//map 3

	texture = ResourceManagers::GetInstance()->GetTexture("map3.0.tga");
	std::shared_ptr<MouseButton> map3 = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);

	map3->SetSize(300, 250);
	map3->Set2DPosition(SCREEN_WIDTH - 150 - map3 -> GetWidth(), (120 + m_textGameName->GetHeight()));
	map3->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY3);
		});
	m_listButton.push_back(map3);

	texture = ResourceManagers::GetInstance()->GetTexture("right.tga");
	std::shared_ptr<MouseButton> start = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	start->SetSize(100, 100);
	start->Set2DPosition(SCREEN_WIDTH - 130, 680);
	start->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY2);
		});
	m_listButton.push_back(start);

	if (ResourceManagers::GetInstance()->get_Music())
	{
		m_Sound->PlaySound();
	}
	if (!ResourceManagers::GetInstance()->get_Music())
	{
		m_Sound->StopSound();
	}
		}
void GSPick::Exit()
{
}


void GSPick::Pause()
{

}
void GSPick::Resume()
{
}


void GSPick::HandleEvents()
{
}

void GSPick::HandleKeyEvents(SDL_Event& e)
{

}

void GSPick::HandleTouchEvents(SDL_Event& e)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvent(&e))
		{
			break;
		}
	}
}

void GSPick::HandleMouseMoveEvents(int x, int y)
{
}

void GSPick::Update(float deltaTime)
{
}

void GSPick::Draw(SDL_Renderer* renderer)
{
	m_background->Draw(renderer);
	for (auto it : m_listButton)
	{
		it->Draw(renderer);
	}
	 m_textGameName->Draw(renderer);
	 m_textGameName1->Draw(renderer);
	 m_textGameName2->Draw(renderer);
	 m_textGameName3->Draw(renderer);
}