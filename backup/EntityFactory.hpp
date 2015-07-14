#pragma once

#include "components/Components.hpp"
#include "Entity.hpp"

class EntityFactory
{
	public:
		EntityFactory(std::vector<std::unique_ptr<Entity>>&, Ogre::SceneManager*);

		template<typename T>
		Entity* create_entity(Ogre::Real x = 0, Ogre::Real y = 0, Ogre::Real z = 0)
		{ // TODO: change default spawn point when possible.
			Entity* tmp = new Entity{
				std::to_string(id_counter_), entities_, x, y, z,
				new T::InputComponent{std::to_string(id_counter_)},
				new T::PhysicsComponent{std::to_string(id_counter_)},
				new T::GraphicsComponent{scene_mgr_}
			};
			++id_counter_;
			return tmp;
		}
	private:
		std::vector<std::unique_ptr<Entity>>& entities_;
		Ogre::SceneManager& scene_mgr_;
		int id_counter_;
};