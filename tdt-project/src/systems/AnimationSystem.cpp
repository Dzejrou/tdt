#include <Components.hpp>
#include "AnimationSystem.hpp"
#include "EntitySystem.hpp"

AnimationSystem::AnimationSystem(EntitySystem& ents)
	: entities_{ents}
{ /* DUMMY BODY */ }

void AnimationSystem::update(tdt::real delta)
{
	for(auto& ent : entities_.get_component_container<AnimationComponent>())
	{
		if(ent.second.current_animation)
		{
			ent.second.current_animation->addTime(delta);
			if(!ent.second.current_animation->getLoop() && ent.second.current_animation->hasEnded)
				ent.second.current_animation = nullptr;
		}
	}
}
