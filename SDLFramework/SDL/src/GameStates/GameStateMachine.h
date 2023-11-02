#pragma once
#include "../GameManager/Singleton.h"
#include <list>
class GameStateBase;
enum class StateType
{
	STATE_INVALID = 0,
	STATE_INTRO,
	STATE_MENU,
	STATE_PLAY1,
	STATE_PLAY2,
	STATE_PLAY3,
	STATE_SETTING, 
	STATE_GUIDE,
	STATE_STORY,
	STATE_END,
	STATE_END2,
	STATE_END3,
	STATE_END4,
	STATE_END5,
	STATE_PICK,
	STATE_PAUSE,
	STATE_FINISH,



};
class GameStateMachine : public CSingleton<GameStateMachine>
{
public:
	GameStateMachine();
	~GameStateMachine();

	void	Cleanup();

	void	ChangeState(std::shared_ptr<GameStateBase> state);
	void	ChangeState(StateType stt);
	void	PushState(StateType stt);
	void	PopState();

	bool	isRunning() { return m_running; }
	void	Quit() { m_running = false; }
	void	PerformStateChange();

	void Resume();

	void Pause();

	inline std::shared_ptr<GameStateBase> CurrentState()const
	{
		return m_pActiveState;
	}

	inline bool NeedsToChangeState()const
	{
		return (m_pNextState != 0);
	}

	inline bool HasState()const
	{
		return m_StateStack.size() > 0;
	}

private:
	std::list < std::shared_ptr<GameStateBase>>	m_StateStack;
	std::shared_ptr<GameStateBase>				m_pActiveState;
	std::shared_ptr<GameStateBase>				m_pNextState;
	bool	m_running;
	bool	m_fullscreen;
};