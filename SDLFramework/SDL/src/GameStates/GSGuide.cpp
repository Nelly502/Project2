#include "GSGuide.h"

GSGuide::GSGuide()
{
}


GSGuide::~GSGuide()
{
}


void GSGuide::Init()
{
	//auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_guide.png");
	if (ResourceManagers::GetInstance()->get_Music() == true) {
		m_Sound = std::make_shared<Sound>();
		m_Sound->LoadSound("Data/Sounds/intro_music.mp3");
		m_Sound->PlaySound();
	}

	

	// background

	m_background = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIDHT);
	m_background->Set2DPosition(0, 0);

	// button close
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	button = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	button->SetSize(50, 50);
	button->Set2DPosition(SCREEN_WIDTH - 60, 10);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);

	// button right
	texture = ResourceManagers::GetInstance()->GetTexture("right.tga");
	button = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	button->SetSize(75, 75);
	button->Set2DPosition(SCREEN_WIDTH - 100, (SCREEN_HEIDHT - button->GetHeight()) / 2 - 50);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_STORY);
		});
	m_listButton.push_back(button);


}

void GSGuide::Exit()
{
}


void GSGuide::Pause()
{

}
void GSGuide::Resume()
{
	// button close
	//auto texture = ResourceManagers::GetInstance()->GetTexture("btn_restart.tga");
	//button->SetTexture(texture);

}


void GSGuide::HandleEvents()
{
}

void GSGuide::HandleKeyEvents(SDL_Event& e)
{
	
}

void GSGuide::HandleTouchEvents(SDL_Event& e)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvent(&e))
		{
			break;
		}
	}
}

void GSGuide::HandleMouseMoveEvents(int x, int y)
{
}

void GSGuide::Update(float deltaTime)
{
}

void GSGuide::Draw(SDL_Renderer* renderer)
{
	m_background->Draw(renderer);
	for (auto it : m_listButton)
	{
		it->Draw(renderer);
	}
}