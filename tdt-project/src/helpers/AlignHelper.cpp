#include <Components.hpp>
#include <Cache.hpp>
#include <systems/EntitySystem.hpp>
#include "AlignHelper.hpp"

static tdt::cache::AlignCache cache{Component::NO_ENTITY, nullptr};

void AlignHelper::set_material(EntitySystem& ents, tdt::uint id, tdt::uint state, const std::string& val)
{
	AlignComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, AlignComponent);
	if(comp && state < AlignComponent::state_count)
		comp->states[state].material = val;
}

const std::string& AlignHelper::get_material(EntitySystem& ents, tdt::uint id, tdt::uint state)
{
	static const std::string NO_MAT{"colour/pink"};

	AlignComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, AlignComponent);
	if(comp && state < AlignComponent::state_count)
		return comp->states[state].material;
	else
		return NO_MAT;
}

void AlignHelper::set_mesh(EntitySystem& ents, tdt::uint id, tdt::uint state, const std::string& val)
{
	AlignComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, AlignComponent);
	if(comp && state < AlignComponent::state_count)
		comp->states[state].mesh = val;
}

const std::string& AlignHelper::get_mesh(EntitySystem& ents, tdt::uint id, tdt::uint state)
{
	static const std::string NO_MESH{"cube.mesh"};

	AlignComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, AlignComponent);
	if(comp && state < AlignComponent::state_count)
		return comp->states[state].mesh;
	else
		return NO_MESH;
}

void AlignHelper::set_position_offset(EntitySystem& ents, tdt::uint id, tdt::uint state, const Ogre::Vector3& val)
{
	AlignComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, AlignComponent);
	if(comp && state < AlignComponent::state_count)
		comp->states[state].position_offset = val;
}

const Ogre::Vector3 & AlignHelper::get_position_offset(EntitySystem& ents, tdt::uint id, tdt::uint state)
{
	static const Ogre::Vector3 NO_OFFSET{0.f, 0.f, 0.f};

	AlignComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, AlignComponent);
	if(comp && state < AlignComponent::state_count)
		return comp->states[state].position_offset;
	else
		return NO_OFFSET;
}

void AlignHelper::set_scale(EntitySystem& ents, tdt::uint id, tdt::uint state, const Ogre::Vector3& val)
{
	AlignComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, AlignComponent);
	if(comp && state < AlignComponent::state_count)
		comp->states[state].scale = val;
}

const Ogre::Vector3 & AlignHelper::get_scale(EntitySystem& ents, tdt::uint id, tdt::uint state)
{
	static const Ogre::Vector3 NO_SCALE{1.f, 1.f, 1.f};

	AlignComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, AlignComponent);
	if(comp && state < AlignComponent::state_count)
		return comp->states[state].scale;
	else
		return NO_SCALE;
}
