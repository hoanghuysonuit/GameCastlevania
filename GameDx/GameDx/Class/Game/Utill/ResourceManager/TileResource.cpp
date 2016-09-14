#include "TileResource.h"
#include "Class\Game\Utill\stdafx.h"

CTileResource::CTileResource()
{
}


CTileResource::CTileResource(int type) {
	m_TypeObject = type;
}

CTileResource::~CTileResource()
{
}

wchar_t* CTileResource::getImage(int tag, int state) {
	switch (tag)
	{
	case TYPEOFTILE::TOF_CASTTLE:
		return L"Resource//Image//Game//Sprites//Items//lau_dai.png";
	case TYPEOFTILE::TOF_CASTLE_FLAG:
		return L"Resource//Image//Game//Sprites//Items//co_sao.png";
	case TYPEOFTILE::TOF_CEMENT_BARRIER_BLUE:
		return L"Resource//Image//Game//Tile//map-2//chan_cot_co_xanh.png";
	case TYPEOFTILE::TOF_CEMENT_BARRIER_RED:
		return L"Resource//Image//Game//Tile//map-1//flag_pole_tail.png";
	case TYPEOFTILE::TOF_CEMENT_LANE_BLE:
		return L"Resource//Image//Game//Tile//map-2//xi_mang_xanh_1.png";
	case TYPEOFTILE::TOF_CEMENT_LANE_RED:
		return L"Resource//Image//Game//Tile//map-1//xi_mang_1.png";
	case TYPEOFTILE::TOF_CEMENT_PIPE:
		return L"Resource//Image//Game//Tile//map-3//dat_co.png";
	case TYPEOFTILE::TOF_CLOUND_ONE_MEMBER:
		return L"Resource//Image//Game//Tile//map-1//1_dam_may.png";
	case TYPEOFTILE::TOF_CLOUND_THREE_MEMBER:
		return L"Resource//Image//Game//Tile//map-1//3_dam_may.png";
	case TYPEOFTILE::TOF_CLOUND_TOW_MEMBER:
		return L"Resource//Image//Game//Tile//map-1//2_dam_may.png";
	case TYPEOFTILE::TOF_GRASS_LEFT:
		return L"Resource//Image//Game//Tile//map-3//grass_first.png";
	case TYPEOFTILE::TOF_GRASS_MIDDLE:
		return L"Resource//Image//Game//Tile//map-3//grass_mid.png";
	case TYPEOFTILE::TOF_GRASS_ONE_BUSH:
		return L"Resource//Image//Game//Tile//map-1//1_cay_co.png";
	case TYPEOFTILE::TOF_GRASS_RIGHT:
		return L"Resource//Image//Game//Tile//map-3//grass_last.png";
	case TYPEOFTILE::TOF_GRASS_THREE_BUSH:
		return L"Resource//Image//Game//Tile//map-1//1_cay_co.png";
	case TYPEOFTILE::TOF_GRASS_TOW_BUSH:
		return L"Resource//Image//Game//Tile//map-1//1_cay_co.png";
	case TYPEOFTILE::TOF_MOUNTAIN_BIG:
		return L"Resource//Image//Game//Tile//map-1//chan_nui.png";
	case TYPEOFTILE::TOF_MOUNTAIN_SMALL:
		return L"Resource//Image//Game//Tile//map-1//dinh_nui.png";
	case TYPEOFTILE::TOF_PIPE_BODY_DOWN:
		return L"Resource//Image//Game//Tile//map-1//than_ong_cong.png";
	case TYPEOFTILE::TOF_PIPE_BODY_RIGHT:
		return L"Resource//Image//Game//Tile//mpa-2//dau_than_ong_ngang.png";
	case TYPEOFTILE::TOF_PIPE_HEAD_BODY_DOWN:
		return  L"Resource//Image//Game//Tile//map-1//dau_than_ong_cong.png";
	case TYPEOFTILE::TOF_PIPE_HEAD_DOWN:
		return L"Resource//Image//Game//Tile//map-1//mieng_ong.png";
	case TYPEOFTILE::TOF_PIPE_HEAD_RIGHT:
		return L"Resource//Image//Game//Tile//map-2//mieng_ong_ngang.png";
	case TYPEOFTILE::TOF_ELEVATOR:
		return L"Resource//Image//Game//Tile//map-2//thang_may.png";
	case TYPEOFTILE::TOF_FLAG:
		return L"Resource//Image//Game//Sprites//Items//green_flag.png";
	case TYPEOFTILE::TOF_FLAG_POLE_HEAD:
		return L"Resource//Image//Game//Sprites//Items//flag_pole_head.png";
	case TYPEOFTILE::TOF_FLAG_POLE:
		return L"Resource//Image//Game//Sprites//Items//flag_pole.png";
	case TYPEOFTILE::TOF_FLAG_POLE_TAIL:
		return L"Resource//Image//Game//Sprites//Items//flag_pole_tail.png";
	case TYPEOFTILE::TOF_BRICK_TILE:
		return L"Resource//Image//Game//Tile//map-2//gach_xanh.png";
	default:
		return nullptr;
		break;
	}

	return nullptr;
}

