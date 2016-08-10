#pragma once

#include <string>
#include <Typedefs.hpp>
#include <Enums.hpp>
class EntitySystem;
struct AnimationComponent;

/**
 *
 */
namespace AnimationHelper
{
	/**
	 *
	 */
	const std::string& get_animation_name(ANIMATION_TYPE::VAL);

	/**
	 *
	 */
	void play(EntitySystem&, tdt::uint, ANIMATION_TYPE::VAL, bool = false, bool = true);

	/**
	 *
	 */
	void stop(EntitySystem&, tdt::uint);

	/**
	 *
	 */
	void add_possible(EntitySystem&, tdt::uint, ANIMATION_TYPE::VAL);

	/**
	 *
	 */
	void delete_possible(EntitySystem&, tdt::uint, ANIMATION_TYPE::VAL);

	/**
	 *
	 */
	bool is_possible(EntitySystem&, tdt::uint, ANIMATION_TYPE::VAL);

	/**
	 *
	 */
	void set_stop_current_animation(EntitySystem&, tdt::uint, bool);

	/**
	 *
	 */
	bool get_stop_current_animation(EntitySystem&, tdt::uint);
}