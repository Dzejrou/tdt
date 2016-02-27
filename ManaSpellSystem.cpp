#include "ManaSpellSystem.hpp"
#include "Player.hpp"

ManaSpellSystem::ManaSpellSystem(EntitySystem& ents)
	: entities_{ents}, regen_timer_{}, regen_period_{5.f}
{ /* DUMMY BODY */ }

void ManaSpellSystem::update(Ogre::Real delta)
{
	if(regen_timer_ < regen_period_)
		regen_timer_ += delta;
	else
	{
		regen_timer_ = 0.f;

		Player::instance().add_mana(Player::instance().get_mana_regen());

		// TODO: Mana to entities.
	}

	// TODO: Spell casting of entities.
}

void ManaSpellSystem::set_regen_period(Ogre::Real val)
{
	regen_period_ = val;
}

Ogre::Real ManaSpellSystem::get_regen_period() const
{
	return regen_period_;
}
