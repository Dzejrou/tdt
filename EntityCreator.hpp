#pragma once

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>

#include <set>
#include <string>

#include "EntityPlacer.hpp"
#include "EntitySystem.hpp"

class EntityCreator
{
	public:
		EntityCreator(EntityPlacer&, EntitySystem&);
		~EntityCreator() {}

		void init();
		void place(const CEGUI::EventArgs&);
		void change_to_place(const CEGUI::EventArgs&);
		void change_to_create(const CEGUI::EventArgs&);
		void actualize_list(const CEGUI::EventArgs&);

		void set_visible(bool);
		bool is_visible() const;
	private:
		EntityPlacer& placer_;
		EntitySystem& entities_;
		std::set<std::string>& registered_entities_;
		CEGUI::Window* window_;
		CEGUI::Listbox* list_box_;
};