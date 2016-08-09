#include <Components.hpp>
#include <Cache.hpp>
#include <systems/EntitySystem.hpp>
#include "PriceHelper.hpp"

static tdt::cache::PriceCache cache{Component::NO_ENTITY, nullptr};

void PriceHelper::set_price(EntitySystem& ents, tdt::uint id, tdt::uint val)
{
	PriceComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, PriceComponent);
	if(comp)
		comp->price = val;
}

tdt::uint PriceHelper::get_price(EntitySystem& ents, tdt::uint id)
{
	PriceComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, PriceComponent);
	if(comp)
		return comp->price;
	else
		return tdt::uint{};
}
