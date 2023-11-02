#pragma once
#pragma once
#include "GameStateBase.h"
#include "GameObject/MouseButton.h"
#include "Sound.h"
#include"GameObject/Text.h"
#include"ResourceManagers.h"

class Sprite2D;
class SpriteAnimation;

class GSPick :
	public GameStateBase
{
public:
	GSPick();
	~GSPick();

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
	std::shared_ptr<Text>	m_textGameName, m_textGameName1, m_textGameName2, m_textGameName3;					
	SDL_Color m_textColor, m_textColor1, m_textColor2, m_textColor3;
	TTF_Font* m_Font;
};

