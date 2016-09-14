/****************************************************************************/
/* Create by Michael Le*/
/* 07/07/2015 */
/***************************************************************************/

#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <tchar.h>
#include <iostream>

/*DEFINE*/
#define FPS							60
#define GAME_RATE					(1000.0f/60.0f)
#define WINDOWS_NAME				L"Oishi"
#define DRAWCENTER_LEFT_TOP			1					
#define DRAWCENTER_LEFT_MIDDLE		2			
#define DRAWCENTER_LEFT_BOTTOM		3					
#define DRAWCENTER_MIDDLE_TOP		4				
#define DRAWCENTER_MIDDLE_MIDDLE	5					
#define DRAWCENTER_MIDDLE_BOTTOM	6		
#define DRAWCENTER_RIGHT_TOP		7
#define DRAWCENTER_RIGHT_MIDDLE		8
#define DRAWCENTER_RIGHT_BOTTOM		9

#define KEYBOARD_BUFFER_SIZE		1024
#define ISKEYDOWN(keystatus)		(keystatus & 0x80)

#define directDevice				LPDIRECT3DDEVICE9

#define vector3d					D3DXVECTOR3
#define vector3dZero				D3DXVECTOR3(0.0f,0.0f,0.5f)
#define	vector3dMinimum				D3DXVECTOR3(-10000, -10000, 0.5f)
#define vector2d					D3DXVECTOR2
#define vector2dZero				D3DXVECTOR2(0.0f,0.0f)
#define vector4d					D3DXVECTOR4

#define CBoxZero					CBox2D(0, 0, 0, 0)			

#define matrix						D3DXMATRIX

#define PI							3.14
#define GRAVITATION					-9.8
#define VEL_DEFAULT_X			0
#define VEL_DEFAULT_Y				9.8

#define SIGN(A)						(A >= 0 ? 1 : -1)
#define DIRECT_COORDINATE(A)		{-(A)}
#define CHANGE_DIRECTION(A)			{-(A)}
#define SAFE_RELEASE(A)				{if (A) {delete A; A = 0;}}

#define BACKBUFFER_WIDTH			256
#define	BACKBUFFER_HEIGHT			240

#define SCREEN_SIZE					CBox2D()
#define deltaBoundingBox			vector2d(5.0f, 5.0f)

#define DEFAULT_FONT_SIZE			8
#define DEFAULT_FONTNAME			_T("MegaMan 2")
#define DEFAULT_FONTPATH			_T("Resource//Font//megaman_2.ttf")
#define DEFAULT_FONT_COLOR			0xFFFFFFFF
#define DAFAULT_TEXT_COLOR_STAGE	0x9AFEFFFF

#define START_GAME_STRING			"PRESS START"
#define PRODUCTOR					"PROJECT GAME UIT"
#define TM							"TM"

#define SELECT_CUTMAN_STRING		"CUTMAN"
#define SELECT_GUTMAN_STRING		"GUTMAN"
#define	SELECT_ICEMAN_STRING		"ICEMAN"
#define	SELECT_BOMBMAN_STRING		"BOMBMAN"
#define	SELECT_FIREMAN_STRING		"FIREMAN"
#define	SELECT_ELECMAN				"ELECMAN"
#define SELECT_STAGE_STRING			"SELECT\nSTAGE"
#define PRESS_START_GAME_STRING		"PRESS\nSTART"

#define DEFAULT_POINT_STRING		L"0000"
#define CUTMAN_STAGE_INFO_STRING	L"CUTMAN\n\nCLEAR POINT"
#define BOMBMAN_STAGE_INFO_STRING	L"BOMBMAN\n\nCLEAR POINT"
#define FIREMAN_STAGE_INFO_STRING	L"FIREMAN\n\nCLEAR POINT"

#define VEL_PLAYER_X 5.8
#define VEL_DEFAULT_Y 9.8
#define VEL_PLAYER_Y 9.8

#define VEL_PLAYER_X_MIN 0
#define VEL_PLAYER_Y_MIN 0
#define ACCEL_PLAYER_X 0.5f
#define ACCEL_PLAYER_Y 1

#define PLAYER_JUMP_LIMIT 32
#define PLAYER_JUMP_HIGH_LIMIT 70

#define PLAYER_UNDYING_TIME	10000
#define SMALL_PLAYER_UNDYING_TIME 5000

#define BRICK_VELOCITY_MAX_Y 9.8

#define STAR_VELOCITY_MAX 5
#define ADD_POS_Y         5

#define COIN_NUM_MAX   12

#define GIFTBOX_VELOCITY_MAX_Y 9.8
 

//#define FLOWER_POSITION_Y_MAX 86
#define FLOWER_VELOCITY_MAX   5

//#define REDMUSHROOM_POSITION_Y_MAX 86
#define REDMUSHROOM_VELOCITY_MAX   5

#define BRICKMINI_UP_VELOCITY 6
#define BRICKMINI_DOWN_VELOCITY 8

#define ELEVATOR_VELOCITY_X 5
#define ELEVATOR_VELOCITY_Y  5

//#define ELEVATOR_POSITION_Y_MAX 200
//#define ELEVATOR_POSITION_Y_MIN 0
#define ELEVATOR_POSITION_X_MAX 200
#define ELEVATOR_POSITION_X_MIN 10

#define POOLSIZE					5
#define LEVELPOOL(A)				(A*POOLSIZE)		
#define GAME_OVER_STRING			"GAME  OVER"
#define CONTINUE_STRING				"CONTINUE"
#define SELECT_STAGE_STRING_GV		"SELECT  STAGE"
/************************************/

/*ENUM*/

enum OBJECT_TYPE {
	TYPE_PLAYER = 1,
	TYPE_TILE = 2,
	TYPE_BONUS = 3,
	TYPE_ENERMY = 4
};

enum MAP_NUM {
	MAP_1 = 1,
	MAP_2 = 2,
	MAP_3 = 3
};

enum GAMESTATE
{
	STATE_END,
	STATE_RUN
};


enum CAMERASTATE
{
	CAMERA_NORMAL,						// with rockman, this mean is update for X asix
	CAMERA_AUTO,						// with rockman, this mean is update for Y asix
	CAMERA_STOP
};


enum KEYSTATE
{
	KEY_PRESS = 0,
	KEY_RELEASE,
	KEY_UP,
	KEY_DOWN
};

enum BULLETSTATE
{
	BULLET_STATE_SHOW,
	BULLET_STATE_DIE
};


enum STAGESELECTED
{
	CUTMAN,
	GUTSMAN,
	ICEMAN,
	BOMBMAN,
	FIREMAN,
	ELECMAN
};

enum DIRECTIONINDEX {
	DIRECTION_X = 0,
	DIRECTION_Y = 1
};

enum DIRECTION
{
	DIRECTION_NONE	=  0,
	DIRECTION_RIGHT =  1,
	DIRECTION_UP	=  1,
	DIRECTION_DOWN	= -1,
	DIRECTION_LEFT	= -1
};

enum COLDIRECTION
{
	COLDIRECTION_NONE,
	COLDIRECTION_TOP,
	COLDIRECTION_BOTTOM,
	COLDIRECTION_LEFT,
	COLDIRECTION_RIGHT
};

enum GRASSSTRUCT
{
	CRASS_SMALL = 0,
	CRASS_NORMAL,
	CRASS_BIG,
	GRASS_LEFT,
	GRASS_MIDDLE,
	GRASS_RIGHT
};

enum CLOUNDSTRUCT
{
	ONE_CLOUND   = 0,
	TWO_CLOUND,
	THREE_CLOUND
};

/******************/

/*STRUCT*/

struct MapIntro
{
	std::string		m_mapName;
	int				m_point;
	int				m_timer;
	int				m_coin;
	int				m_helths;
};

struct MapInfo
{
	std::string				m_mapName;
	std::string				m_pathData;
	float					m_sizeX;
	float					m_sizeY;

	MapInfo(){
		m_mapName	= "NOPE";
		m_pathData	= "NOPE";
		m_sizeX		= 0;
		m_sizeY		= 0;
	}

	MapInfo(std::string mapName, std::string pathData){
		m_mapName	= mapName;
		m_pathData	= pathData;
		m_sizeX		= 0;
		m_sizeY		= 0;
	}

	MapInfo(std::string mapName, std::string pathData, float sizeX, float sizeY){
		m_mapName	= mapName;
		m_pathData	= pathData;
		m_sizeX		= sizeX;
		m_sizeY		= sizeY;
	}
};

struct KeyState
{
	int KeyCode;
	KEYSTATE KeyStates;
};

enum PLAYERSTATES
{
	START = 0,
	STAND = 1,
	RUN = 2,
	JUMP = 3,
	DIE = 4,
	CLIMB = 5,
	SIT = 6,
	STAND_SHOOT = 7,
	MOVE_SHOOT = 8,
	JUMP_SHOOT = 9
};

enum PLAYERTAGS
{
	SMALL = 0,
	BIG = 1,
	FIRE = 2,
	SMALL_UNDYING = 3,
	UNDYING = 4,
};

enum MUSHROOM_STATE
{
	MUSH_RUN = 0,
	MUSH_IS_ACTTACKED,
};


enum ITEMINBOX_TYPE
{
	REDMUSHROOM = 0,
	ITEM_FLOWER = 1

};
enum TAGNODE
{
	NONE = 0,
	PLAYER = 1,
	RED_MUSHROOM = 2,
	GREEN_MUSHROOM = 3,
	STAR = 4,
	FLOWER = 5,
	COIN = 6,
	BRICK = 7,
	GIFT_BOX = 8,
	TILE = 9,
	PIPE = 10,
	FLAG = 11,
	FLAG_POLE = 12,
	FLAG_POLE_TAIL = 13,
	MUSHROOM = 14,
	TURTLE = 15,
	CARNIVOROUS_PLANT = 16,
	COININBOX = 17,
	BRICKMINI = 18,
	ELEVATOR = 19
};

enum CARNIVOROUS_PLANT_TYPE {
	GREEN_CARNIVOROUS_PLANT = 0,
	RED_CARNIVOROUS_PLANT = 1,
	BLUE_CARNIVOROUS_PLANT = 2
};

enum TURTLE_STATE
{
	TURTLE_RUN = 0,
	TURTLE_ENSCONSE =1,
	TURTLE_DIE = 1,
	TURTLE_SURGING = 1,
	TURTLE_FLY = 3,
	TURTLE_INDENT = 2

};

enum TURTLE_TAG
{
	GREEN = 0,
	RED = 1,
	NAVI = 2,
	THORN = 3
};

enum ELEVATOR_STATE
{
	UP = 1,
	DOWN = 2,
	UP_DOWN = 3,
	RIGHT_LEFT = 4
};

enum BRICK_TYPE
{
	BRICK_NONE = 0,
	BRICK_STAR = 1,
	BRICK_COIN = 2,
	BRICK_GREENMUSHROOM= 3
};

enum GIFTBOX_BRICK_EVENT
{
	EVENT_NONE = 0,
	EVENT_PROCCESSING = 1,
	EVENT_DONE = 2
};

enum BRICK_STATE
{
	BRICK_BOX = 0,
	BRICK_NORMAL = 1,
};

enum GIFTBOX_TYPE
{
	GIFTBOX_COIN = 0,
	GIFTBOX_ITEMINBOX_TYPE = 1,
	GIFTBOX_NONE = 2
};

enum GIFTBOX_STATE
{
	GIFTBOX = 0,
	GIFTBOX_NORMAL = 1
};

enum BRICKMINI_TYPE
{
	BRICKMINI_LEFT_UP = 0,
	BRICKMINI_LEFT_DOWN =1,
	BRICKMINI_RIGHT_UP =2,
	BRICKMINI_RIGHT_DOWN
};

/******************************/

/*CONST*/
/******************/

/******************************/

/*VLD*/
#ifndef __VLD_H__
#define __VLD_H__
//#include <vld.h>
#endif
/********************/

#define				SIZE_MAP_WIDTH			20000
#define				SIZE_MAP_HIGHT			700

#define				MAX_OBJECT_OF_NODE		10
#define				MAX_LEVEL_OF_NODE		1000

#endif