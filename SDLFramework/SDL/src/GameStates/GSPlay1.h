#pragma once
#include "GameStateBase.h"
#include "GameObject/MouseButton.h"
#include "Sound.h"
#include "ResourceManagers.h"
#include"GameObject/Text.h"
class Sprite2D;
class SpriteAnimation;

class GSPlay1 :
	public GameStateBase
{
public:
	GSPlay1();
	~GSPlay1();

	void	Init() override;
	void	Exit() override;

	void	Pause() override;
	void	Resume() override;
	void	MoveCharacter(std::shared_ptr<SpriteAnimation> player, int keyPressed, std::list<std::shared_ptr<Sprite2D>> bullets, int bullet1_X, int bullet1_Y);
	void	HandleEvents() override;
	void	HandleKeyEvents(SDL_Event& e) override;
	void	HandleTouchEvents(SDL_Event& e) override;
	void	HandleMouseMoveEvents(int x, int y) override;
	void	Update(float deltaTime) override;
	void	Draw(SDL_Renderer* renderer) override;
	int m_KeyPress, m_KeyPress2;

private:
	std::shared_ptr<Sprite2D>	m_background;
	//std::shared_ptr<Text>		m_score;
	std::list<std::shared_ptr<MouseButton>>	m_listButton;
	std::shared_ptr<MouseButton> button;
	std::list<std::shared_ptr<SpriteAnimation>>	m_listAnimation;
	std::shared_ptr<Sound>	 energy_Sound, shoot_Sound, damage1_Sound, damage2_Sound;

	std::shared_ptr<SpriteAnimation> play1;
	std::list<std::shared_ptr<SpriteAnimation>>	m_listAnimation2;
	std::shared_ptr<SpriteAnimation> play2;
	std::shared_ptr<SpriteAnimation> eng;
	std::list<std::shared_ptr<SpriteAnimation>> m_listEnergy;
	std::shared_ptr<Sprite2D> bullet;
	std::list<std::shared_ptr<Sprite2D>> m_listBullet;
	std::shared_ptr<Sprite2D> currentBullet;

	std::shared_ptr<Sprite2D> bullet2;
	std::list<std::shared_ptr<Sprite2D>> m_listBullet2;
	std::shared_ptr<Sprite2D> currentBullet2;

	std::list<std::shared_ptr<Sprite2D>> m_listHealth1;
	std::list<std::shared_ptr<Sprite2D>> m_listHealth2;

	std::shared_ptr<Text>	m_textScore;
	SDL_Color m_textColor;
	std::shared_ptr<Text>	m_textScore1;
	SDL_Color m_textColor1;

	float time1_1 = 0.0f;
	float time1_2 = 0.0f;
	float m_Velocity = 10.0f;
	int speedP1 = 300;
	int speedP2 = 300;
	int engNumberplay1 = 0;
	int engNumberplay2 = 0;
	int maxcoin = 52;
	int space = 0;
};

