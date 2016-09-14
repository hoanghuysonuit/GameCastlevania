#include "EnermyResource.h"
#include "Class\Game\Utill\stdafx.h"

CEnermyResource::CEnermyResource()
{
}

CEnermyResource::CEnermyResource(int type) {
	this->m_TypeObject = type;
}

CEnermyResource::~CEnermyResource()
{
}

wchar_t* CEnermyResource::getImage(int tag, int state) {
	if (m_TypeObject != TAGNODE::TURTLE) {
		switch (tag)
		{
		case TAGNODE::CARNIVOROUS_PLANT:
			switch (state)
			{
			case CARNIVOROUS_PLANT_TYPE::GREEN_CARNIVOROUS_PLANT:
				return L"Resource//Image//Game//Enemies//cay_xanh.png";
			case CARNIVOROUS_PLANT_TYPE::RED_CARNIVOROUS_PLANT:
				return L"Resource//Image//Game//Enemies//cay_do.png";
			case CARNIVOROUS_PLANT_TYPE::BLUE_CARNIVOROUS_PLANT:
				return L"Resource//Image//Game//Enemies//cay_lam.png";
			default:
				break;
			}
		case TAGNODE::MUSHROOM:
			switch (state)
			{
			case MUSHROOM_STATE::MUSH_RUN:
				return L"Resource//Image//Game//Enemies//nam_run.png";
			case MUSHROOM_STATE::MUSH_IS_ACTTACKED:
				return L"Resource//Image//Game//Enemies//nam_die.png";
			default:
				break;
			}
		default:
			break;
		}
	}
	else {
		switch (tag)
		{
		case TURTLE_TAG::GREEN:
			switch (state)
			{
			case TURTLE_STATE::TURTLE_RUN:
				return L"Resource//Image//Game//Enemies//green_turtle_run.png";
			case TURTLE_STATE::TURTLE_ENSCONSE:
				return L"Resource//Image//Game//Enemies//green_turtle_ensconse.png";
			case TURTLE_STATE::TURTLE_INDENT:
				return L"Resource//Image//Game//Enemies//rua_xanh_loi_chan.png";
			case TURTLE_STATE::TURTLE_FLY:
				return L"Resource//Image//Game//Enemies//rua_xanh_bay.png";
			default:
				break;
			}
		case TURTLE_TAG::RED:
			switch (state)
			{
			case TURTLE_STATE::TURTLE_RUN:
				return L"Resource//Image//Game//Enemies//rua_do_run.png";
			case TURTLE_STATE::TURTLE_ENSCONSE:
				return L"Resource//Image//Game//Enemies//rua_do_thut_dau.png";
			case TURTLE_STATE::TURTLE_INDENT:
				return L"Resource//Image//Game//Enemiescaserua_do_loi_chan.png";
			case TURTLE_STATE::TURTLE_FLY:
				return L"Resource//Image//Game//Enemies//rua_do_bay.png";
			default:
				break;
			}
		case TURTLE_TAG::NAVI:
			switch (state)
			{
			case TURTLE_STATE::TURTLE_RUN:
				return L"Resource//Image//Game//Enemies//rua_lam_run.png";
			case TURTLE_STATE::TURTLE_ENSCONSE:
				return L"Resource//Image//Game//Enemies//rua_lam_thut_dau.png";
			case TURTLE_STATE::TURTLE_INDENT:
				return L"Resource//Image//Game//Enemies//rua_lam_loi_chan.png";
			case TURTLE_STATE::TURTLE_FLY:
				return L"Resource//Image//Game//Enemies//rua_lam_bay.png";
			default:
				break;
			}
		case TURTLE_TAG::THORN:
			switch (state)
			{
			case TURTLE_STATE::TURTLE_RUN:
				return L"Resource//Image//Game//Enemies//rua_gai_run.png";
			case TURTLE_STATE::TURTLE_ENSCONSE:
				return L"Resource//Image//Game//Enemies//rua_gai_tron.png";
			default:
				break;
			}
		default:
			break;
		}
	}
}


