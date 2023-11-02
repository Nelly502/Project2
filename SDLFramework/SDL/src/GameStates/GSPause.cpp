#include "GameObject/TextureManager.h"
#include "GameObject/Sprite2D.h"
#include "GameObject/MouseButton.h"
#include "GameObject/SpriteAnimation.h"
#include "GameObject/Camera.h"
#include"ResourceManagers.h"
#include <GSPause.h>

GSPause::GSPause()
{
}


GSPause::~GSPause()
{
}


void GSPause::Init()
{

	//auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_pick.tga");
	if (ResourceManagers::GetInstance()->get_Music() == true) {

		m_Sound = std::make_shared<Sound>();
		m_Sound->LoadSound("Data/Sounds/intro_music.mp3");
		m_Sound->PlaySound();
	}
	// backgrounds

	m_background = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIDHT);
	m_background->Set2DPosition(0, 0);
	// text menu
	m_textColor = { 255, 255, 0 };
	m_textGameName = std::make_shared<Text>("Data/HalloweenGuises.ttf", m_textColor);
	m_textGameName->SetSize(300, 150);
	m_textGameName->Set2DPosition(225, 200);
	m_textGameName->LoadFromRenderText("MENU");
	// text pause
	m_textColor = { 255, 255, 0 };
	m_textGameName2 = std::make_shared<Text>("Data/HalloweenGuises.ttf", m_textColor);
	m_textGameName2->SetSize(300, 150);
	m_textGameName2->Set2DPosition(750+225, 200);
	m_textGameName2->LoadFromRenderText("RESUME");
	// button menu
		texture = ResourceManagers::GetInstance()->GetTexture("btn_menu.tga");
	button = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	button->SetSize(150, 150);
	button->Set2DPosition(300, SCREEN_HEIDHT - button->GetHeight() - 250);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_MENU);
		m_Sound->PauseSound();
		});
	m_listButton.push_back(button);
	// button pause
	texture = ResourceManagers::GetInstance()->GetTexture("btn_restart.tga");
	button = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	button->SetSize(150, 150);
	button->Set2DPosition(750+300, SCREEN_HEIDHT - button->GetHeight() - 250);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		m_Sound->StopSound();
		});
	m_listButton.push_back(button);
	



}

void GSPause::Exit()
{
}


void GSPause::Pause()
{

}
void GSPause::Resume()
{
}


void GSPause::HandleEvents()
{
}

void GSPause::HandleKeyEvents(SDL_Event& e)
{

}

void GSPause::HandleTouchEvents(SDL_Event& e)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvent(&e))
		{
			break;
		}
	}
}

void GSPause::HandleMouseMoveEvents(int x, int y)
{
}

void GSPause::Update(float deltaTime)
{
	for (auto it : m_listAnimation) {

		it->Update(deltaTime);
	}
	for (auto it : m_listAnimation2) {

		it->Update(deltaTime);
	}

}

void GSPause::Draw(SDL_Renderer* renderer)
{
	m_background->Draw(renderer);
	for (auto it : m_listButton)
	{
		it->Draw(renderer);
	}


	m_textGameName->Draw(renderer);
	m_textGameName2->Draw(renderer);



}