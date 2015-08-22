#pragma once

enum class ENTITY_STATE
{
	NONE, NORMAL, TURNING,
	COUNT
};

enum class FACTION
{
	FRIENDLY, ENEMY, NEUTRAL
};

enum class ENTITY_TYPE
{
	NONE = 0,
	WALL = 1 << 0,
	MINION = 1 << 1,
	ENEMY = 1 << 2,
	BUILDING = 1 << 3,
	MISC = 1 << 4
};

enum class EVENT_TYPE
{
	NONE,
	COUNT
};

enum class TASK_TYPE
{
	NONE, GO_TO, GO_NEAR, GO_KILL, KILL, GET_IN_RANGE,
	COUNT
};

enum class ATTACK_TYPE
{
	NONE, MELEE, RANGED,
	COUNT
};

enum class GAME_STATE
{
	RUNNING, ENDED, PAUSED, MENU
};

enum class TIME_EVENT
{
	NONE, START_EVENT, END_EVENT,
	COUNT
};