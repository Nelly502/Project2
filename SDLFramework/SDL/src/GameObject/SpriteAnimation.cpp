	#include "SpriteAnimation.h"
	#include "TextureManager.h"
	SpriteAnimation::SpriteAnimation(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float frameTime) : BaseObject(texture)
	{
		m_pTexture = texture;
		m_spriteRow = spriteRow;
		m_frameCount = frameCount;
		m_numAction = numAction;
		//m_animSpeed = animSpeed;
		m_frameTime = frameTime;
		//m_flip = flip;
		m_currentFrame = 0;
		m_currentTicks = 0;
		m_lastUpdate = SDL_GetTicks();
		Init();
	}
	SpriteAnimation::~SpriteAnimation()
	{

	}

	void SpriteAnimation::Init()
	{

	}

	void SpriteAnimation::Draw(SDL_Renderer* renderer)
	{
		if (m_pTexture != nullptr)
		{
			m_pTexture->RenderFrame(m_position.x, m_position.y, m_iWidth, m_iHeight, m_spriteRow, m_currentFrame, m_frameCount, m_numAction, m_angle, m_flip);
		}
	}

	void SpriteAnimation::Update(float deltatime)
	{
		m_currentTicks += deltatime;
			if(m_currentTicks  >= m_frameTime) {
			m_currentFrame++;
			if (m_currentFrame >= m_frameCount) {
				m_currentFrame = 0;
			}
			m_currentTicks -= m_frameTime;
		}
	}
	void SpriteAnimation::Set2DPosition(float x, float y)
	{
		m_position = Vector3((float)x, (float)y, 0.0f);
	}

	void SpriteAnimation::SetRotation(double angle)
	{
		m_angle = angle;
	}
	void SpriteAnimation::SetSpriteRow(int row)
	{
		m_spriteRow = row;
	}
	void SpriteAnimation::SetFlip(SDL_RendererFlip flip)
	{ 
		m_flip = flip;
	}

	Vector2 SpriteAnimation::Get2DPosition()
	{
		return Vector2(m_position.x, m_position.y);
	}

	void SpriteAnimation::SetSize(int width, int height)
	{
		m_iWidth = width;
		m_iHeight = height;
		m_scale = Vector3((float)m_iWidth, (float)m_iHeight, 0.0f);
	}

	int SpriteAnimation::GetWidth()
	{
		return m_iWidth;
	}

	int SpriteAnimation::GetHeight()
	{
		return m_iHeight;
	}

	void SpriteAnimation::MoveLeft(float deltaTime)
	{
		m_position.x += 20 * deltaTime;
	}
	bool SpriteAnimation::collision2(float xIn, float yIn, float xWidth, float xHeight, float play1xIn, float play2yIn, float play1Width, float play1Height)
	{
		//

		
		float leftA = xIn;
		float rightA = xIn + xWidth;
		float topA = yIn;
		float bottomA = yIn + xHeight;

		//Calculate the sides of rect B
		float leftB = play1xIn;
		float rightB = play1xIn + play1Width;
		float topB = play2yIn;
		float bottomB = play2yIn + play1Height;
		//If any of the sides from A are outside of B
		if (bottomA <= topB)
		{
			return false;
		}

		if (topA >= bottomB)
		{
			return false;
		}

		if (rightA <= leftB)
		{
			return false;
		}

		if (leftA >= rightB)
		{
			return false;
		}

		//If none of the sides from A are outside B
		return true;
	}

	bool SpriteAnimation::collision1(float xIn, float yIn, float play1xIn, float play1yIn)
	{
		double dist = (play1xIn - xIn) * (play1xIn - xIn) + (play1yIn - yIn) * (play1yIn - yIn);
		if (dist < 400.0)
		{
			printf("Collision \n");
		}

		return dist < 400.0;
	}
	bool SpriteAnimation::collision3(float xIn, float yIn, float play1xIn, float play1yIn)
	{
		double dist = (play1xIn - xIn) * (play1xIn - xIn) + (play1yIn - yIn) * (play1yIn - yIn);
		return dist < 3000.0;
	}