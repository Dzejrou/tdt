#pragma once

#include <vector>
#include "Typedefs.hpp"
class EntitySystem;
class WaveSystem;

/**
 * Namespace that contains different level generators that can be used in the game
 * as well as the typedef for the DEFAULT_LEVEL_GENERATOR.
 */
namespace level_generators
{

/**
 * Abstract parent class of all level generators,
 * allows for different level generators used to create
 * levels with minimal effort.
 */
class LevelGenerator
{
	public:
		/**
		 * Constructor.
		 * Param: Entity system that contains the level's entities.
		 * Param: Number of iterations done while generating.
		 */
		LevelGenerator(EntitySystem&, tdt::uint);

		/**
		 * Destructor.
		 */
		virtual ~LevelGenerator() = default;

		/**
		 * Brief: Generates a level with the given dimensions.
		 * Param: Width of the level.
		 * Param: Height of the level.
		 * Param: Wave system that will have it's spawn nodes set.
		 */
		virtual void generate(tdt::uint, tdt::uint, WaveSystem&) = 0;

	protected:
		/**
		 * Entity system that contains the level's entities.
		 */
		EntitySystem& entities_;

		/**
		 * Number of cycles done while generating the world.
		 */
		tdt::uint cycles_;
};

/**
 * Level generator that uses simple RNG approach (counts the number
 * of gold neighbours and increases the chance to spawn a gold deposit
 * if needed).
 */
class RandomLevelGenerator : public LevelGenerator
{
	public:
		/**
		 * Constructor.
		 * Param: Entity system that contains the level's entities.
		 * Param: Number of iterations done while generating.
		 */
		RandomLevelGenerator(EntitySystem&, tdt::uint);

		/**
		 * Brief: Generates a level with the given dimensions
		 *        using an RNG approach.
		 * Param: Width of the level.
		 * Param: Height of the level.
		 * Param: Wave system that will have it's spawn nodes set.
		 */
		void generate(tdt::uint, tdt::uint, WaveSystem&) override;
};

/**
 * Typedef used as the default level generator when the game starts.
 */
using DEFAULT_LEVEL_GENERATOR = RandomLevelGenerator;

}