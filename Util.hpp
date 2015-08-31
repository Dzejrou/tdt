#pragma once

#include <cstdlib>
#include "Helpers.hpp"
#include "Enums.hpp"
class EntitySystem;

namespace util
{
	/**
	 * Functors.
	 */
	struct IS_ENEMY
	{
		IS_ENEMY(EntitySystem&, std::size_t);

		bool operator()(std::size_t);

		private:
			FACTION enemy_faction_;
			EntitySystem& entities_;
	};

	struct IS_FRIENDLY
	{
		IS_FRIENDLY(EntitySystem&, std::size_t);

		bool operator()(std::size_t);

		private:
			FACTION faction_;
			EntitySystem& entities_;
	};

	struct IS_FRIENDLY_OR_NEUTRAL
	{
		IS_FRIENDLY_OR_NEUTRAL(EntitySystem&, std::size_t);

		bool operator()(std::size_t);

		private:
			FACTION faction_;
			EntitySystem& entities_;
	};

	struct IS_GOLD_DEPOSIT
	{
		IS_GOLD_DEPOSIT(EntitySystem&);

		bool operator()(std::size_t);

		private:
			EntitySystem& entities_;
	};

	class EntityDestroyer
	{
		friend void DestructorHelper::destroy(EntitySystem&, std::size_t, bool, std::size_t);
		static void destroy(EntitySystem&, std::size_t);
	};
}