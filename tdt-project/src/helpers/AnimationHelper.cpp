#include <map>
#include <Components.hpp>
#include <systems/EntitySystem.hpp>
#include "AnimationHelper.hpp"

const std::string& AnimationHelper::get_animation_name(ANIMATION_TYPE::VAL animation)
{
	static const std::map<int, std::string> ANIMATIONS{
		{ANIMATION_TYPE::WALK, "walk"},
		{ANIMATION_TYPE::IDLE, "idle"},
		{ANIMATION_TYPE::HIT, "hit"},
	};

	static const std::string NO_ANIMATION{"ERROR"}; // Not looped and short.

	auto res = ANIMATIONS.find(animation);
	if(res != ANIMATIONS.end())
		return res->second;
	else
		return NO_ANIMATION;
}
