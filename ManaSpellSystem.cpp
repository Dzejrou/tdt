#include "ManaSpellSystem.hpp"
#include "Player.hpp"
#include "Helpers.hpp"
#include "EntitySystem.hpp"

ManaSpellSystem::ManaSpellSystem(EntitySystem& ents)
	: entities_{ents}, regen_timer_{}, regen_period_{5.f}
{ /* DUMMY BODY */ }

void ManaSpellSystem::update(tdt::real delta)
{
	if(regen_timer_ < regen_period_)
		regen_timer_ += delta;
	else
	{
		regen_timer_ = REAL_ZERO;

		Player::instance().add_mana(Player::instance().get_mana_regen());

		for(auto& ent : entities_.get_component_container<ManaComponent>())
		{
			if(ent.second.curr_mana + ent.second.mana_regen < ent.second.max_mana)
				ent.second.curr_mana += ent.second.mana_regen;
			else
				ent.second.curr_mana = ent.second.max_mana;
		}
	}

	for(auto& ent : entities_.get_component_container<SpellComponent>())
	{
		ent.second.cd_time += delta;
		if(ent.second.cd_time >= ent.second.cooldown)
		{
			SpellHelper::cast(entities_, ent.first);
			ent.second.cd_time = REAL_ZERO;
		}
	}
}

void ManaSpellSystem::set_regen_period(tdt::real val)
{
	regen_period_ = val;
}

tdt::real ManaSpellSystem::get_regen_period() const
{
	return regen_period_;
}
