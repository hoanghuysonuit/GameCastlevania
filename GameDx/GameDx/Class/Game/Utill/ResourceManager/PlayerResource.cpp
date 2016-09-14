#include "PlayerResource.h"
#include "Class\Game\Utill\stdafx.h"

CPlayerResource::CPlayerResource()
{
}

CPlayerResource::CPlayerResource(int type)
{
	m_TypeObject = type;
}

CPlayerResource::~CPlayerResource()
{
}

wchar_t* CPlayerResource::getImage(int tag, int state) {
	switch (tag)
	{
	case PLAYERTAGS::SMALL:
		switch (state)
		{
		case PLAYERSTATES::STAND:
			return L"Resource//Image//Game//Sprites//Mario//SmallMario//smallmario_stand.png";
			break;
		case PLAYERSTATES::RUN:
			return  L"Resource//Image//Game//Sprites//Mario//SmallMario//smallmario_run.png";
			break;
		case PLAYERSTATES::JUMP:
			return L"Resource//Image//Game//Sprites//Mario//SmallMario//smallmario_jum.png";
			break;
		case PLAYERSTATES::CLIMB:
			return L"Resource//Image//Game//Sprites//Mario//SmallMario//smallmario_ducot.png";
			break;
		case PLAYERSTATES::DIE:
			return L"Resource//Image//Game//Sprites//Mario//SmallMario//smallmario_die.png";
			break;
		default:
			break;
		}
		break;
	case PLAYERTAGS::BIG:
		switch (state)
		{
		case PLAYERSTATES::STAND:
			return L"Resource//Image//Game//Sprites//Mario//BigMario//bigmario_stand.png";
		case PLAYERSTATES::RUN:
			return  L"Resource//Image//Game//Sprites//Mario//BigMario//bigmario_run.png";
		case PLAYERSTATES::JUMP:
			return L"Resource//Image//Game//Sprites//Mario//BigMario//bigmario_jum.png";
		case PLAYERSTATES::CLIMB:
			return L"Resource//Image//Game//Sprites//Mario//BigMario//bigmario_ducot.png";
		case PLAYERSTATES::DIE:
			return L"Resource//Image//Game//Sprites//Mario//SmallMario//smallmario_die.png";
		case PLAYERSTATES::SIT:
			return L"Resource//Image//Game//Sprites//Mario//BigFireMario//bigfiremario_sit.png";
		default:
			return L"";
		}
		break;
	case PLAYERTAGS::FIRE:
		switch (state)
		{
		case PLAYERSTATES::STAND:
			return L"Resource//Image//Game//Sprites//Mario//BigFireMario//bigfiremario_stand.png";
		case PLAYERSTATES::RUN:
			return L"Resource//Image//Game//Sprites//Mario//BigFireMario//bigfiremario_run.png";
		case PLAYERSTATES::JUMP:
			return L"Resource//Image//Game//Sprites//Mario//BigFireMario//bigfiremario_jum.png";
		case PLAYERSTATES::CLIMB:
			return L"Resource//Image//Game//Sprites//Mario//BigFireMario//mario_white_climb.png";
		case PLAYERSTATES::DIE:
			return L"Resource//Image//Game//Sprites//Mario//SmallMario//smallmario_die.png";
		case PLAYERSTATES::STAND_SHOOT:
			break;
		case PLAYERSTATES::MOVE_SHOOT:
			break;
		case PLAYERSTATES::JUMP_SHOOT:
			break;
		default:
			break;
		}
		break;
	case PLAYERTAGS::SMALL_UNDYING:
		switch (state)
		{
		case PLAYERSTATES::STAND:
			return L"Resource//Image//Game//Sprites//Mario//UndyingMario//bat_tu_be_dung.png";
		case PLAYERSTATES::RUN:
			return L"Resource//Image//Game//Sprites//Mario//UndyingMario//bat_tu_be_run.png";
		case PLAYERSTATES::JUMP:
			return L"Resource//Image//Game//Sprites//Mario//UndyingMario//bat_tu_be_jum.png";
		case PLAYERSTATES::CLIMB:
			return L"Resource//Image//Game//Sprites//Mario//BigMario//bigmario_ducot.png";
		case PLAYERSTATES::DIE:
			return L"Resource//Image//Game//Sprites//Mario//SmallMario//smallmario_die.png";
		default:
			break;
		}
		break;
	case PLAYERTAGS::UNDYING:
		switch (state)
		{
		case PLAYERSTATES::STAND:
			return L"Resource//Image//Game//Sprites//Mario//UndyingMario//bat_tu_lon_dung.png";
		case PLAYERSTATES::RUN:
			return L"Resource//Image//Game//Sprites//Mario//UndyingMario//bat_tu_lon_run.png";
		case PLAYERSTATES::JUMP:
			return L"Resource//Image//Game//Sprites//Mario//UndyingMario//bat_tu_lon_jum.png";
		case PLAYERSTATES::CLIMB:
			return L"Resource//Image//Game//Sprites//Mario//BigMario//bigmario_ducot.png";
		case PLAYERSTATES::DIE:
			return L"Resource//Image//Game//Sprites//Mario//SmallMario//smallmario_die.png";
		default:
			break;
		}
		break;
	default:
		break;
	}
}