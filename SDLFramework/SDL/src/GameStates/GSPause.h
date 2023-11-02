#pragma once
#pragma once
#include "GameStateBase.h"
#include "GameObject/MouseButton.h"
#include "Sound.h"
#include"GameObject/Text.h"
#include"ResourceManagers.h"

class Sprite2D;
class SpriteAnimation;

class GSPause :
	public GameStateBase
{
public:
	GSPause();
	~GSPause();

	void	Init() override;
	void	Exit() override;

	void	Pause() override;
	void	Resume() override;

	void	HandleEvents() override;
	void	HandleKeyEvents(SDL_Event& e) override;
	void	HandleTouchEvents(SDL_Event& e) override;
	void	HandleMouseMoveEvents(int x, int y) override;
	void	Update(float deltaTime) override;
	void	Draw(SDL_Renderer* renderer) override;
	int m_KeyPress;

private:
	std::shared_ptr<Sprite2D>	m_background;

	std::list<std::shared_ptr<MouseButton>>	m_listButton;

	std::shared_ptr<SpriteAnimation> obj;
	std::shared_ptr<MouseButton> button;
	std::shared_ptr<Sound>					m_Sound;
	std::shared_ptr<SpriteAnimation> play1;
	std::list<std::shared_ptr<SpriteAnimation>>	m_listAnimation;
	std::list<std::shared_ptr<SpriteAnimation>>	m_listAnimation2;
	std::shared_ptr<SpriteAnimation> play2;
	std::shared_ptr<Text>					m_textGameName;
	std::shared_ptr<Text>					m_textGameName2;

	SDL_Color m_textColor;
	TTF_Font* m_Font;
};

