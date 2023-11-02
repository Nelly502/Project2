#include "GameObject/TextureManager.h"
#include "GameObject/Sprite2D.h"
#include "GameObject/MouseButton.h"
#include "GameObject/SpriteAnimation.h"
#include "GameObject/Camera.h"
#include"ResourceManagers.h"
#include <GSFinish.h>

GSFinish::GSFinish()
{
}


GSFinish::~GSFinish()
{
}


void GSFinish::Init()
{
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

	/*m_textColor = { 255, 255, 0 };
	m_textGameName = std::make_shared<Text>("Data/DripinkpersonaluseBlack.otf", m_textColor);
	m_textGameName->SetSize(500, 200);
	m_textGameName->Set2DPosition(SCREEN_WIDTH / 2 - m_textGameName->GetWidth() / 2, 30);
	m_textGameName->LoadFromRenderText("ARE YOU READY");*/

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


	texture = ResourceManagers::GetInstance()->GetTexture("	right.tga");
	std::shared_ptr<MouseButton> start = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	start->SetSize(100, 100);
	start->Set2DPosition(SCREEN_WIDTH - 130, 680);
	start->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_MENU);
		});
	m_listButton.push_back(start);
	// Animation 
	texture = ResourceManagers::GetInstance()->GetTexture("idle.tga");
	play1 = std::make_shared<SpriteAnimation>(texture, 1, 8, 1, 0.2f);
	play1->SetFlip(SDL_FLIP_NONE);
	play1->SetSize(250, 260);
	play1->Set2DPosition(250, 500);
	//Camera::GetInstance()->SetTarget(obj);
	m_listAnimation.push_back(play1);
	play1->setActive(true);

	//play2
	texture = ResourceManagers::GetInstance()->GetTexture("idle2.tga");
	play2 = std::make_shared<SpriteAnimation>(texture, 1, 8, 1, 0.2f);
	play2->SetFlip(SDL_FLIP_HORIZONTAL);
	play2->SetSize(250, 260);
	play2->Set2DPosition(SCREEN_WIDTH - 250 - play2 -> GetWidth(), 500);
	//Camera::GetInstance()->SetTarget(obj);
	m_listAnimation2.push_back(play2);
	play2->setActive(true);
	//play3
	texture = ResourceManagers::GetInstance()->GetTexture("acto1_win.tga");
	play3 = std::make_shared<SpriteAnimation>(texture, 1, 4, 3, 0.2f);
	play3->SetFlip(SDL_FLIP_NONE);
	play3->SetSize(250, 260);
	//play3->Set2DPosition(800, 500);
	//Camera::GetInstance()->SetTarget(obj);
	m_listAnimation3.push_back(play3);
	play3->setActive(false);

	texture = ResourceManagers::GetInstance()->GetTexture("locxoay.tga");
	bienhinh = std::make_shared<SpriteAnimation>(texture, 1, 2, 1, 0.2f);
	bienhinh->SetFlip(SDL_FLIP_HORIZONTAL);
	bienhinh->SetSize(350, 350);
	bienhinh->setActive(false);
	//Camera::GetInstance()->SetTarget(obj);
	m_listBienhinh.push_back(bienhinh);
}
void GSFinish::Exit()
{
}


void GSFinish::Pause()
{

}
void GSFinish::Resume()
{
}


void GSFinish::HandleEvents()
{
}

void GSFinish::HandleKeyEvents(SDL_Event& e)
{

}

void GSFinish::HandleTouchEvents(SDL_Event& e)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvent(&e))
		{
			break;
		}
	}
}

void GSFinish::HandleMouseMoveEvents(int x, int y)
{
}

void GSFinish::Update(float deltaTime)
{
	timebienhinh += deltaTime;
	if (timebienhinh > 1.5f) {
		for (auto it : m_listBienhinh) {
			it->setActive(true);
		}
	}
	if (timebienhinh > 2.0f) {
		for (auto it : m_listBienhinh) {
			it->setActive(false);
		}
		for (auto it : m_listAnimation3) {
			it->setActive(true);
			if (ResourceManagers::GetInstance()->demWin1 > ResourceManagers::GetInstance()->demWin2) {

				it->Set2DPosition(250, 500);
			}
			if (ResourceManagers::GetInstance()->demWin1 < ResourceManagers::GetInstance()->demWin2) {

				it->Set2DPosition(SCREEN_WIDTH - 550, 500);
				it->SetFlip(SDL_FLIP_HORIZONTAL);
			}
		}
		if (ResourceManagers::GetInstance()->demWin1 > ResourceManagers::GetInstance()->demWin2) {
			for (auto it : m_listAnimation) {
				it->setActive(false);
			}
		}
		if (ResourceManagers::GetInstance()->demWin1 < ResourceManagers::GetInstance()->demWin2) {
			for (auto it : m_listAnimation2) {
				it->setActive(false);
			}
		}
	}

	for (auto it : m_listBienhinh) {
		if (ResourceManagers::GetInstance()->demWin1 > ResourceManagers::GetInstance()->demWin2) {
		
			it->Set2DPosition(250, 500);
		}
		if (ResourceManagers::GetInstance()->demWin1 < ResourceManagers::GetInstance()->demWin2) {

			it->Set2DPosition(SCREEN_WIDTH - 500, 500);
		}
	}

	for (auto it : m_listAnimation) {
		it->Update(deltaTime);
	}
	for (auto it : m_listAnimation2) {
		it->Update(deltaTime);
	}
	for (auto it : m_listAnimation3) {
		it->Update(deltaTime);
	}
	for (auto it : m_listBienhinh) {
		it->Update(deltaTime);
	}
}

void GSFinish::Draw(SDL_Renderer* renderer)
{
	m_background->Draw(renderer);
	for (auto it : m_listButton)
	{
		it->Draw(renderer);
	}
	for (auto it : m_listAnimation) {
		if (it->getActive()) {
			it->Draw(renderer);

		}

	}
	for (auto it : m_listAnimation2) {

		if (it->getActive()) {
			it->Draw(renderer);

		}


	}
	for (auto it : m_listAnimation3) {


		if (it->getActive()) {
			it->Draw(renderer);

		}


	}
	for (auto it : m_listBienhinh) {

		if (it->getActive()) {
			it->Draw(renderer);

		}


	}
}