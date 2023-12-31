﻿#include "GSMenu.h"

GSMenu::GSMenu() : GameStateBase(StateType::STATE_MENU),
m_background(nullptr), m_listButton(std::list<std::shared_ptr<MouseButton>>{}), m_textGameName(nullptr)
{
}


GSMenu::~GSMenu()
{
}



void GSMenu::Init()
{
	//auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("background_main_menu.tga");

	// background
	//auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIDHT);
	m_background->Set2DPosition(0, 0);

	
	// play button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_play.tga");
	std::shared_ptr<MouseButton> btnPlay = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	
	btnPlay->SetSize(450, 150);
	btnPlay->Set2DPosition((SCREEN_WIDTH - btnPlay->GetWidth())/2, (SCREEN_HEIDHT - btnPlay->GetHeight()) / 2);
	btnPlay->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PICK);
		});
	m_listButton.push_back(btnPlay);

	// exit button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	std::shared_ptr<MouseButton> btnClose = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	//btnClose = std::make_shared<MouseButton>(texture);
	btnClose->SetSize(50, 50);
	btnClose->Set2DPosition(SCREEN_WIDTH - btnClose->GetWidth() - 10, 10);
	btnClose->SetOnClick([]() {
		exit(0);
		});
	m_listButton.push_back(btnClose);
	//CREDIT game
	texture = ResourceManagers::GetInstance()->GetTexture("btn_guide.tga");
	std::shared_ptr<MouseButton> btnCredit = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	btnCredit->SetSize(300, 100);
	btnCredit->Set2DPosition((SCREEN_WIDTH - btnCredit->GetWidth()) / 2, SCREEN_HEIDHT / 2 + 170);
	btnCredit->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_GUIDE);
		});
	m_listButton.push_back(btnCredit);

	// game title
	///Set Font
	m_textColor = { 255, 255, 0 };
	m_textGameName = std::make_shared<Text>("Data/HalloweenGuises.ttf", m_textColor);
	m_textGameName->SetSize(600, 100);
	m_textGameName->Set2DPosition((SCREEN_WIDTH - m_textGameName->GetWidth())/2, SCREEN_HEIDHT / 2 - 315);
	m_textGameName->LoadFromRenderText("Hello Ween");

	// Mute and Unmute buttons
	texture = ResourceManagers::GetInstance()->GetTexture("btn_unmute.tga");
	std::shared_ptr<MouseButton> btnToggleMute = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	btnToggleMute->SetSize(75, 75);
	btnToggleMute->Set2DPosition(10, 10);

	bool& isMuted = m_isMuted; // Add reference variable
	isMuted = false;
	m_Sound = std::make_shared<Sound>();
	m_Sound->LoadSound("Data/Sounds/intro_music.mp3");
	btnToggleMute->SetOnClick([this, &isMuted, btnToggleMute]() {
		isMuted = !isMuted;
		if (isMuted) {
			m_Sound->StopSound();
			btnToggleMute->SetTexture(ResourceManagers::GetInstance()->GetTexture("btn_mute.tga"));// Change the texture using the correct member function
			ResourceManagers::GetInstance()->set_Music(false);

		}
		else {
			m_Sound->PlaySound();
			btnToggleMute->SetTexture(ResourceManagers::GetInstance()->GetTexture("btn_unmute.tga")); // Change the texture using the correct member function
			ResourceManagers::GetInstance()->set_Music(true);

		}
		});

	m_listButton.push_back(btnToggleMute);
	
	//load sound
	
		if (ResourceManagers::GetInstance()->get_Music())
		{
			m_Sound->PlaySound();
		}
		if (!ResourceManagers::GetInstance()->get_Music())
		{
		m_Sound->StopSound();
		}
	
}

void GSMenu::Exit()
{
	ResourceManagers::FreeInstance();
}


void GSMenu::Pause()
{
	m_Sound->StopSound();
	// button close
	
}

void GSMenu::Resume()
{
	m_Sound->PlaySound();
}


void GSMenu::HandleEvents()
{
}

void GSMenu::HandleKeyEvents(SDL_Event& e)
{
}

void GSMenu::HandleTouchEvents(SDL_Event& e)
{
	for (auto button : m_listButton)
	{
		if (button ->HandleTouchEvent(&e))
		{
			break;
		}
	}
}

void GSMenu::HandleMouseMoveEvents(int x, int y)
{
}

void GSMenu::Update(float deltaTime)
{
	m_background->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
	

}

void GSMenu::Draw(SDL_Renderer* renderer)
{
	m_background->Draw(renderer);
	for (auto it : m_listButton)
	{
		it->Draw(renderer);
	}
	
	m_textGameName->Draw(renderer);
}
