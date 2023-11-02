#include "GSEnd.h"
#include "GameObject/TextureManager.h"
#include "GameObject/Sprite2D.h"
#include "GameObject/MouseButton.h"
#include "GameObject/SpriteAnimation.h"
#include "GameObject/Camera.h"
#include"ResourceManagers.h"

GSEnd::GSEnd()
{
}


GSEnd::~GSEnd()
{
}


void GSEnd::Init()
{
	
	//auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	if (ResourceManagers::GetInstance()->get_Music() == true) {
		m_Sound = std::make_shared<Sound>();
		m_Sound->LoadSound("Data/Sounds/intro_music.mp3");
		m_Sound->PlaySound();
	}
	// backgrounds
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_end1.tga");
	m_background = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIDHT);
	m_background->Set2DPosition(0, 0);
	m_background->setActive(false);

	texture = ResourceManagers::GetInstance()->GetTexture("bg_end2.tga");
	m_background2 = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_background2->SetSize(SCREEN_WIDTH, SCREEN_HEIDHT);
	m_background2->Set2DPosition(0, 0);
	m_background2->setActive(false);

	m_textColor1 = { 255, 255, 0 };
	m_textGameName1 = std::make_shared<Text>("Data/HalloweenGuises.ttf", m_textColor1);
	m_textGameName1->SetSize(300, 200);
	//m_textGameName1->Set2DPosition(225,45 );
	m_textGameName1->LoadFromRenderText("VICTORY");

	m_textColor2 = { 0, 0, 0 };
	m_textGameName2 = std::make_shared<Text>("Data/HalloweenGuises.ttf", m_textColor2);
	m_textGameName2->SetSize(300, 200);
	//m_textGameName2->Set2DPosition(SCREEN_WIDTH - 525, 45);
	m_textGameName2->LoadFromRenderText("DEFEAT");
	// button close
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	button = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	button->SetSize(50, 50);
	button->Set2DPosition(SCREEN_WIDTH - 60, 10);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_MENU);
		});
	m_listButton.push_back(button);

	texture = ResourceManagers::GetInstance()->GetTexture("right.tga");
	buttonCon = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	buttonCon->SetSize(100, 100);
	buttonCon->Set2DPosition(SCREEN_WIDTH - 130, 680);
	buttonCon->SetOnClick([this]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY3);
		});
	m_listButtonCon.push_back(buttonCon);

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
	play2->Set2DPosition(SCREEN_WIDTH - 500, 500);
	//Camera::GetInstance()->SetTarget(obj);
	m_listAnimation2.push_back(play2);
	play2->setActive(true);
	

}

void GSEnd::Exit()
{
}


void GSEnd::Pause()
{

}
void GSEnd::Resume()
{
}


void GSEnd::HandleEvents()
{
}

void GSEnd::HandleKeyEvents(SDL_Event& e)
{

}

void GSEnd::HandleTouchEvents(SDL_Event& e)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvent(&e))
		{
			break;
		}
	}
	for (auto button : m_listButtonCon)
	{
		if (button->HandleTouchEvent(&e))
		{
			break;
		}
	}
}

void GSEnd::HandleMouseMoveEvents(int x, int y)
{
}

void GSEnd::Update(float deltaTime)
{
	
		if (ResourceManagers::GetInstance()->get_Play1Win() && !ResourceManagers::GetInstance()->get_Play2Win()) {
		
			m_textGameName1->Set2DPosition(225, 45);//win
			m_textGameName2->Set2DPosition(SCREEN_WIDTH - 525, 45);//loss
			m_background->setActive(true);
		}
		
		if (!ResourceManagers::GetInstance()->get_Play1Win() && ResourceManagers::GetInstance()->get_Play2Win()) {
			
			m_textGameName1->Set2DPosition(SCREEN_WIDTH - 525, 45);
			m_textGameName2->Set2DPosition(225, 45); 
			m_background2->setActive(true);
		}
		for (auto it : m_listAnimation) {
			it->Update(deltaTime);
		}
		for (auto it : m_listAnimation2) {
			it->Update(deltaTime);
		}
	
}

void GSEnd::Draw(SDL_Renderer* renderer)
{
	if (m_background->getActive()) {
		m_background->Draw(renderer);
	}
	if(m_background2->getActive()) {
		m_background2->Draw(renderer);
	}
	for (auto it : m_listButton)
	{
		it->Draw(renderer);
	}
	for (auto it : m_listButtonCon)
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
	m_textGameName1->Draw(renderer);
	m_textGameName2->Draw(renderer);


}