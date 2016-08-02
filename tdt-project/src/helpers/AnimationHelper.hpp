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
}