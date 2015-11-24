#include "PriceHelper.hpp"
#include "EntitySystem.hpp"
#include "Components.hpp"

void PriceHelper::set_price(EntitySystem& ents, std::size_t id, std::size_t val)
{
	auto comp = ents.get_component<PriceComponent>(id);
	if(comp)
		comp->price = val;
}

std::size_t PriceHelper::get_price(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<PriceComponent>(id);
	if(comp)
		return comp->price;
	else
		return std::size_t{};
}
