#include <Components.hpp>
#include <systems/EntitySystem.hpp>
#include "PriceHelper.hpp"

void PriceHelper::set_price(EntitySystem& ents, tdt::uint id, tdt::uint val)
{
	auto comp = ents.get_component<PriceComponent>(id);
	if(comp)
		comp->price = val;
}

tdt::uint PriceHelper::get_price(EntitySystem& ents, tdt::uint id)
{
	auto comp = ents.get_component<PriceComponent>(id);
	if(comp)
		return comp->price;
	else
		return tdt::uint{};
}
