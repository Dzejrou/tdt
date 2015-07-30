#pragma once

#include <set>

#include "System.hpp"
#include "EntitySystem.hpp"
#include "GridSystem.hpp"

class TaskSystem : public System
{
	public:
		TaskSystem(EntitySystem&, GridSystem&);
		~TaskSystem() {}

		void update(Ogre::Real);
		void add_task(std::size_t, std::size_t);
		void cancel_task(std::size_t);
		std::size_t create_task(std::size_t, TASK_TYPE);
	private:
		void next_task_(TaskHandlerComponent&);
		void handle_task_(std::size_t, TaskComponent&);
		EntitySystem& entities_;
		GridSystem& grid_;
};