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
	NONE, WALL_BASIC,
	COUNT
};

enum class EVENT_TYPE
{
	NONE,
	COUNT
};

enum class TASK_TYPE
{
	NONE, GO_TO, GO_NEAR,
	COUNT
};