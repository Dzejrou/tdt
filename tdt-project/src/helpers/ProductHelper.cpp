#include <Components.hpp>
#include <systems/EntitySystem.hpp>
#include "ProductHelper.hpp"

void ProductHelper::set_producer(EntitySystem& ents, tdt::uint id, tdt::uint producer)
{
	auto comp = ents.get_component<ProductComponent>(id);
	if(comp)
		comp->producer = producer;
}

tdt::uint ProductHelper::get_producer(EntitySystem& ents, tdt::uint id)
{
	auto comp = ents.get_component<ProductComponent>(id);
	if(comp)
		return comp->producer;
	else
		return Component::NO_ENTITY;
}