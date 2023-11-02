#include "GameStateBase.h"
#include "GameStates/GSIntro.h"
#include "GSMenu.h"
#include "GSPlay1.h"
#include "GSPlay2.h"
#include "GSPlay3.h"
#include "GSGuide.h"
#include "GSStory.h"
#include <GSEnd.h>
#include <GSEnd2.h>
#include <GSEnd3.h>
#include <GSEnd4.h>
#include <GSEnd5.h>

#include <GSPick.h>
#include <GSPause.h>
#include <GSFinish.h>
GameStateBase::GameStateBase(StateType stateType) : m_stateType(stateType)
{}

std::shared_ptr<GameStateBase> GameStateBase::CreateState(StateType stt)
{
	std::shared_ptr<GameStateBase> gs = nullptr;
	switch (stt)
	{
	case StateType::STATE_INVALID:
		break;
	case StateType::STATE_INTRO:
		gs = std::make_shared<GSIntro>();
		//GSINTRO;
		break;
	case StateType::STATE_MENU:
		gs = std::make_shared<GSMenu>();
		//GSMENU
		break;
	 case StateType::STATE_PLAY1:
		gs = std::make_shared<GSPlay1>();
		//GSPLAY1 
		break;
	case StateType::STATE_PLAY2:
		gs = std::make_shared<GSPlay2>();
		//GSPLAY2
		break;
	case StateType::STATE_PLAY3:
		gs = std::make_shared<GSPlay3>();
		//GSPLAY3
		break;
	case StateType::STATE_GUIDE:
		gs = std::make_shared<GSGuide>();
		//GSGUIDE
		break;
	case StateType::STATE_STORY:
		gs = std::make_shared<GSStory>();
		//GSGUIDE
		break;
	case StateType::STATE_END:
		gs = std::make_shared<GSEnd>();
		//GSGUIDE
		break;
	case StateType::STATE_END2:
		gs = std::make_shared<GSEnd2>();
		//GSGUIDE
		break;
	case StateType::STATE_END3:
		gs = std::make_shared<GSEnd3>();
		//GSGUIDE
		break;
	case StateType::STATE_END4:
		gs = std::make_shared<GSEnd4>();
		//GSGUIDE
		break;
	case StateType::STATE_END5:
		gs = std::make_shared<GSEnd5>();
		//GSGUIDE
		break;
	case StateType::STATE_PICK:
		gs = std::make_shared<GSPick>();
		//GSGUIDE
		break;
	case StateType::STATE_PAUSE:
		gs = std::make_shared<GSPause>();
		//GSGUIDE
		break;
	case StateType::STATE_FINISH:
		gs = std::make_shared<GSFinish>();
		//GSGUIDE
		break;
	default:
		break;
	}
	return gs;
}

StateType GameStateBase::GetGameStateType()
{
	return m_stateType;
}
