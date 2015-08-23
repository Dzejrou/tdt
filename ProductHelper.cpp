#include "ProductHelper.hpp"
#include "Components.hpp"
#include "EntitySystem.hpp"

void ProductHelper::set_producer(EntitySystem& ents, std::size_t id, std::size_t producer)
{
	auto comp = ents.get_component<ProductComponent>(id);
	if(comp)
		comp->producer = producer;
}

std::size_t ProductHelper::get_producer(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<ProductComponent>(id);
	if(comp)
		return comp->producer;
	else
		return Component::NO_ENTITY;
}