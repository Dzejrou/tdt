#pragma once

#include <Ogre.h>
#include <OIS.h>

#include "System.hpp"
#include "EntitySystem.hpp"
#include "Components.hpp"

class InputSystem : public System
{
	public:
		InputSystem(EntitySystem&, OIS::Keyboard&);
		~InputSystem() {}

		void update(Ogre::Real);
		bool is_valid(std::size_t) const;
		bool is_first_person() const;
		void set_first_person(bool, std::size_t = 0);
		void rebind(int, int);
		void set_input_handler(std::size_t, const std::string&);
	private:
		EntitySystem& entities_;
		bool first_person_;
		std::size_t first_person_id_;
		OIS::Keyboard& keyboard_;
		int KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT; // Allow for rebinding.
};