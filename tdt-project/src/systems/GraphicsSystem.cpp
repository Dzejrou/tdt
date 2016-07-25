#include "GraphicsSystem.hpp"
#include "EntitySystem.hpp"

GraphicsSystem::GraphicsSystem(EntitySystem& ents)
	: entities_{ents}, update_timer_{}, update_period_{1.f}
{ /* DUMMY BODY */ }

void GraphicsSystem::update(tdt::real delta)
{
	if(update_timer_ < update_period_)
		update_timer_ += delta;
	else
	{
		update_timer_ = REAL_ZERO;

		for(auto& ent : entities_.get_component_container<ExplosionComponent>())
		{
			if(ent.second.curr_radius >= ent.second.max_radius)
			{
				DestructorHelper::destroy(entities_, ent.first);
				continue;
			}

			auto comp = entities_.get_component<GraphicsComponent>(ent.first);
			if(comp && comp->node)
			{
				ent.second.curr_radius += ent.second.delta;
				if(comp->manual_scaling)
				{
					comp->scale += ent.second.delta;
					comp->node->setScale(comp->scale);
				}
				else
					comp->node->setScale(comp->node->getScale() + ent.second.delta);
			}
		}
	}
}

void GraphicsSystem::set_update_period(tdt::real val)
{
	update_period_ = val;
}

tdt::real GraphicsSystem::get_update_period() const
{
	return update_period_;
}
