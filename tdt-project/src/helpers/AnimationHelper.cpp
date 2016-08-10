#include <map>
#include <Components.hpp>
#include <Cache.hpp>
#include <systems/EntitySystem.hpp>
#include <gui/gui.hpp>
#include "AnimationHelper.hpp"

#if CACHE_ALLOWED == 1
static tdt::cache::AnimationCache cache{Component::NO_ENTITY, nullptr};
#endif

const std::string& AnimationHelper::get_animation_name(ANIMATION_TYPE::VAL animation)
{
	static const std::map<int, std::string> ANIMATIONS{
		{ANIMATION_TYPE::WALK, "walk"},
		{ANIMATION_TYPE::IDLE, "idle"},
		{ANIMATION_TYPE::HIT, "hit"},
		{ANIMATION_TYPE::ACTIVATE, "activate"},
		{ANIMATION_TYPE::DEACTIVATE, "deactivate"}
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
	AnimationComponent* animation{nullptr};
	GET_COMPONENT(id, ents, animation, AnimationComponent);

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
	AnimationComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, AnimationComponent);
	if(comp && comp->current_animation)
	{
		comp->current_animation->setWeight(0.f);
		comp->current_animation->setEnabled(false);
		comp->current_animation = nullptr;
	}
}

void AnimationHelper::add_possible(EntitySystem& ents, tdt::uint id, ANIMATION_TYPE::VAL type)
{
	AnimationComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, AnimationComponent);
	if(comp)
		comp->possible_animations.set(type, true);
}

void AnimationHelper::delete_possible(EntitySystem& ents, tdt::uint id, ANIMATION_TYPE::VAL type)
{
	AnimationComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, AnimationComponent);
	if(comp)
		comp->possible_animations.set(type, false);
}

bool AnimationHelper::is_possible(EntitySystem& ents, tdt::uint id, ANIMATION_TYPE::VAL type)
{
	AnimationComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, AnimationComponent);
	if(comp)
		return comp->possible_animations.test(type);
	else
		return false;
}
