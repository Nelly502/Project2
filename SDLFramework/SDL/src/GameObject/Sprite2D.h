#pragma once
#include"BaseObject.h"
#include"CMath.h"

class Sprite2D : public BaseObject
{
protected:
	int m_iWidth;
	int m_iHeight;
	SDL_RendererFlip m_flip;
	bool isBullet = false;
	Vector2 direction;

public:
	Sprite2D() : BaseObject(), m_iWidth(0), m_iHeight(0) {}
	Sprite2D( std::shared_ptr<TextureManager> texture, SDL_RendererFlip flip);
	void Init() override;
	void Draw(SDL_Renderer * renderer) override;

	void Update(float deltatime) override;
	void Set2DPosition(float x, float y);
	Vector3		Get2DPosition();
	void SetSize(int width, int height);
	int GetWidth();
	int GetHeight();
	void SetRotation(double angle);
	void SetFlip(SDL_RendererFlip flip);
	bool collision1(float xIn, float yIn, float play1xIn, float play2yIn);
	bool collision2(float xIn, float yIn, float play1xIn, float play1yIn);
	bool collision(float xIn, float yIn, float planexIn, float planeyIn);
	bool getActive();
	void setActive(bool a);
	void SetBulletDirectionX(float directionX);

	void SetBulletDirectionY(float directionY);

	
	float GetBulletDirectionX() const;

	float GetBulletDirectionY() const;
private:
	float m_bulletDirectionX;
	float m_bulletDirectionY;
};

