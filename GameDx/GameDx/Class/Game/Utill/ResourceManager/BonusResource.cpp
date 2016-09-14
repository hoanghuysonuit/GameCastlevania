#include "BonusResource.h"
#include "Class\Game\Utill\stdafx.h"

CBonusResource::CBonusResource()
{
}

CBonusResource::CBonusResource(int type) {
	m_TypeObject = type;
}

CBonusResource::~CBonusResource()
{
}

wchar_t* CBonusResource::getImage(int tag, int state) {
	switch (tag)
	{
	case TAGNODE::STAR:
		return  L"Resource//Image//Game//Sprites//Mario//Bonus//star.png";
	case TAGNODE::BRICK:
		switch (state)
		{
		case BRICK_STATE::BRICK_NORMAL:
			if (this->m_TypeObject == MAP_NUM::MAP_1 || this->m_TypeObject == MAP_NUM::MAP_3){
				return L"Resource//Image//Game//Sprites//Mario//Bonus//gach.png";
			}
			else if (this->m_TypeObject == MAP_NUM::MAP_2)
			{
				return L"Resource//Image//Game//Sprites//Mario//Bonus//gach_xanh.png";
			}
		case BRICK_STATE::BRICK_BOX:
			if (this->m_TypeObject == MAP_NUM::MAP_1 || this->m_TypeObject == MAP_NUM::MAP_3){
				return L"Resource//Image//Game//Sprites//Mario//Bonus//gach_mat_cham_hoi.png";
			}
			else if (this->m_TypeObject == MAP_NUM::MAP_2)
			{
				return L"Resource//Image//Game//Sprites//Mario//Bonus//gach_xanh_0_cham_hoi.png";
			}
		}
		break;
	case TAGNODE::RED_MUSHROOM:
		return L"Resource//Image//Game//Sprites//Mario//Bonus//nam_do_nho.png";
	case TAGNODE::GREEN_MUSHROOM:
		return L"Resource//Image//Game//Sprites//Mario//Bonus//nam_xanh_nho.png";
	case TAGNODE::COIN:
		return L"Resource//Image//Game//Sprites//Mario//Bonus//coin_dung.png";
	case TAGNODE::COININBOX:
		return L"Resource//Image//Game//Sprites//Mario//Bonus//coin_xoay.png";
	case TAGNODE::GIFT_BOX:
		switch (state)
		{
		case GIFTBOX_STATE::GIFTBOX_NORMAL:
			return L"Resource//Image//Game//Sprites//Mario//Bonus//gach_cham_hoi.png";
		case GIFTBOX_STATE::GIFTBOX:
			return L"Resource//Image//Game//Sprites//Mario//Bonus//gach_mat_cham_hoi.png";
		default:
			break;
		}
		break;
	case TAGNODE::FLOWER:
		return L"Resource//Image//Game//Sprites//Mario//Bonus//hoa.png";
	case TAGNODE::BRICKMINI:
		switch (state)
		{
		case BRICKMINI_TYPE::BRICKMINI_LEFT_DOWN:case BRICKMINI_TYPE::BRICKMINI_RIGHT_DOWN:
			if (this->m_TypeObject == MAP_NUM::MAP_1 || this->m_TypeObject == MAP_NUM::MAP_3)
			{
				return L"Resource//Image//Game//Sprites//Mario//Bonus//gach_vo_phai.png";
			}
			else if (this->m_TypeObject == MAP_NUM::MAP_2)
			{
				return L"Resource//Image//Game//Sprites//Mario//Bonus//gach_vo_phai_map2.png";
			}
		case BRICKMINI_TYPE::BRICKMINI_LEFT_UP: case BRICKMINI_TYPE::BRICKMINI_RIGHT_UP:
			if (this->m_TypeObject == MAP_NUM::MAP_1 || this->m_TypeObject == MAP_NUM::MAP_3)
			{
				return L"Resource//Image//Game//Sprites//Mario//Bonus//gach_vo_trai.png";
			}
			else if (this->m_TypeObject == MAP_NUM::MAP_2)
			{
				return L"Resource//Image//Game//Sprites//Mario//Bonus//gach_vo_trai_map2.png";
			}
		default:
			break;
		}
		break;
	default:
		break;
	}
}
