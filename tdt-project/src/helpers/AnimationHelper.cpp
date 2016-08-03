#include <map>
#include <Components.hpp>
#include <systems/EntitySystem.hpp>
#include <gui/gui.hpp>
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

void AnimationHelper::play(EntitySystem& ents, tdt::uint id, ANIMATION_TYPE::VAL type, bool loop)
{
	auto animation = ents.get_component<AnimationComponent>(id);
	auto graphics = ents.get_component<GraphicsComponent>(id);

	if(animation && graphics && graphics->entity && animation->possible_animations.test(type))
	{
		if(animation->current_animation)
		{
			animation->current_animation->setEnabled(false);
			animation->current_animation->setWeight(0.f);
			animation->current_animation = nullptr;
		}

		const auto& animation_name = get_animation_name(type);
		if(animation_name != "ERROR")
		{
			animation->current_animation = graphics->entity->getAnimationState(animation_name);
			if(animation->current_animation)
			{
				animation->current_animation->setWeight(1.f);
				animation->current_animation->setTimePosition(0.f);
				animation->current_animation->setEnabled(true);
				animation->current_animation->setLoop(loop);
			}
		}
	}
}

void AnimationHelper::stop(EntitySystem& ents, tdt::uint id)
{
	auto comp = ents.get_component<AnimationComponent>(id);
	if(comp && comp->current_animation)
	{
		comp->current_animation->setWeight(0.f);
		comp->current_animation->setEnabled(false);
		comp->current_animation = nullptr;
	}
}

void AnimationHelper::add_possible(EntitySystem& ents, tdt::uint id, ANIMATION_TYPE::VAL type)
{
	auto comp = ents.get_component<AnimationComponent>(id);
	if(comp)
		comp->possible_animations.set(type, true);
}

void AnimationHelper::delete_possible(EntitySystem& ents, tdt::uint id, ANIMATION_TYPE::VAL type)
{
	auto comp = ents.get_component<AnimationComponent>(id);
	if(comp)
		comp->possible_animations.set(type, false);
}

bool AnimationHelper::is_possible(EntitySystem& ents, tdt::uint id, ANIMATION_TYPE::VAL type)
{
	auto comp = ents.get_component<AnimationComponent>(id);
	if(comp)
		return comp->possible_animations.test(type);
	else
		return false;
}
