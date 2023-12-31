#pragma once
#include "BaseObject.h"
#include <SDL_render.h>
class TextureManager;
class SpriteAnimation : public BaseObject{
protected:
	Vector2			m_Vec2DPos;
	int			m_iHeight;
	int			m_iWidth;
	float			m_numFrames;
	int			m_currentFrame;
	float		m_frameTime;
	float		m_currentTime;
	int			m_spriteRow; //start 1,2,3
	int		m_frameCount; // start from 1,2,3...
	float  m_currentTicks;
	Uint32 m_lastUpdate;
	int			m_animSpeed;
	int m_numAction; //start from 1,2,3...
	//SDL_RendererFlip m_flip;
	//std::shared_ptr<TextureManager> m_texture;
	bool active;

public:
	SpriteAnimation(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float  frameTime);
	~SpriteAnimation();

	void		Init() override;
	void		Draw(SDL_Renderer* renderer) override;
	void		Update(float deltatime) override;
	void		Set2DPosition(float x, float y);
	void		SetRotation(double angle);
	void		SetSpriteRow(int row);
	void SetFlip (SDL_RendererFlip flip);

	Vector2		Get2DPosition();
	void		SetSize(int width, int height);
	int GetWidth();
	int GetHeight();
	void MoveLeft(float deltaTime);
	bool collision2(float xIn, float yIn,float xWidth, float xHeight, float play1xIn, float play2yIn, float play1Width, float play1Height );
	bool collision1(float xIn, float yIn, float play1xIn, float play1yIn);
	bool collision3(float xIn, float yIn, float play1xIn, float play1yIn);
	bool getActive() {
		return active;
	}
	void setActive(bool a) {
		active = a;
	}
};