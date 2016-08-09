#include <Components.hpp>
#include <Cache.hpp>
#include <systems/EntitySystem.hpp>
#include "ProductHelper.hpp"

static tdt::cache::ProductCache cache{Component::NO_ENTITY, nullptr};

void ProductHelper::set_producer(EntitySystem& ents, tdt::uint id, tdt::uint producer)
{
	ProductComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, ProductComponent);
	if(comp)
		comp->producer = producer;
}

tdt::uint ProductHelper::get_producer(EntitySystem& ents, tdt::uint id)
{
	ProductComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, ProductComponent);
	if(comp)
		return comp->producer;
	else
		return Component::NO_ENTITY;
}