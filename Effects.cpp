#include "Effects.hpp"
#include "EntitySystem.hpp"
#include "Helpers.hpp"
#include "Util.hpp"
#include "GUI.hpp"

util::effect::DAMAGE_EFFECT::DAMAGE_EFFECT(EntitySystem& ents, tdt::uint min, tdt::uint max)
	: min_{min}, max_{max}, entities_{ents}
{ /* DUMMY BODY */ }

void util::effect::DAMAGE_EFFECT::operator()(tdt::uint id)
{
	HealthHelper::sub_health(entities_, id, util::get_random(min_, max_));
}

util::effect::HEAL_EFFECT::HEAL_EFFECT(EntitySystem& ents)
	: entities_{ents}
{ /* DUMMY BODY */ }

void util::effect::HEAL_EFFECT::operator()(tdt::uint id)
{
	HealthHelper::heal(entities_, id);
}

util::effect::LOWER_SPEED_EFFECT::LOWER_SPEED_EFFECT(EntitySystem& ents, tdt::real time)
	: entities_{ents}, time_{time}
{ /* DUMMY BODY */ }

void util::effect::LOWER_SPEED_EFFECT::operator()(tdt::uint id)
{
	auto mov_comp = entities_.get_component<MovementComponent>(id);

	// Restoring event.
	auto evt_id = entities_.create_entity("");
	entities_.add_component<EventComponent>(evt_id);
	entities_.add_component<TimeComponent>(evt_id);
	auto evt_comp = entities_.get_component<EventComponent>(evt_id);
	auto time_comp = entities_.get_component<TimeComponent>(evt_id);

	if(mov_comp && evt_comp && time_comp)
	{
		mov_comp->speed_modifier /= 2.f;

		evt_comp->handler = id;
		evt_comp->active = false;
		evt_comp->event_type = EVENT_TYPE::RESTORE_SPEED;
		evt_comp->target = id;

		time_comp->time_limit = time_;
		time_comp->event_type = TIME_EVENT::START_EVENT;
		time_comp->target = evt_id;
	}

	return;
}

util::effect::FREEZE_EFFECT::FREEZE_EFFECT(EntitySystem& ents, tdt::real time)
	: entities_{ents}, time_{time}
{ /* DUMMY BODY */ }

void util::effect::FREEZE_EFFECT::operator()(tdt::uint id)
{
	auto mov_comp = entities_.get_component<MovementComponent>(id);

	// Restoring event.
	auto evt_id = entities_.create_entity("");
	entities_.add_component<EventComponent>(evt_id);
	entities_.add_component<TimeComponent>(evt_id);
	auto evt_comp = entities_.get_component<EventComponent>(evt_id);
	auto time_comp = entities_.get_component<TimeComponent>(evt_id);

	if(mov_comp && evt_comp && time_comp)
	{
		mov_comp->speed_modifier = tdt::real{};

		evt_comp->handler = id;
		evt_comp->active = false;
		evt_comp->event_type = EVENT_TYPE::RESTORE_SPEED;
		evt_comp->target = id;

		time_comp->time_limit = time_;
		time_comp->event_type = TIME_EVENT::START_EVENT;
		time_comp->target = evt_id;
	}

	return;
}
