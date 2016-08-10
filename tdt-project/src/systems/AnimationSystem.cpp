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
			if(!ent.second.current_animation->hasEnded())
				ent.second.current_animation->addTime(delta);
			else if(!ent.second.current_animation->getLoop() && !ent.second.stop_current_animation)
			{
				ent.second.current_animation->setWeight(0.f);
				ent.second.current_animation->setEnabled(false);
				ent.second.current_animation = nullptr;
			}
		}
	}
}
