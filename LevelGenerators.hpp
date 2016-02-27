#pragma once

#include <vector>
class EntitySystem;

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
		LevelGenerator(EntitySystem&, std::size_t);

		/**
		 * Destructor.
		 */
		virtual ~LevelGenerator() = default;

		/**
		 * Brief: Generates a level with the given dimensions.
		 * Param: Width of the level.
		 * Param: Height of the level.
		 */
		virtual void generate(std::size_t, std::size_t) = 0;
	protected:
		/**
		 * Entity system that contains the level's entities.
		 */
		EntitySystem& entities_;

		/**
		 * Number of cycles done while generating the world.
		 */
		std::size_t cycles_;
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
		RandomLevelGenerator(EntitySystem&, std::size_t);

		/**
		 * Brief: Generates a level with the given dimensions
		 *        using an RNG approach.
		 * Param: Width of the level.
		 * Param: Height of the level.
		 */
		void generate(std::size_t, std::size_t) override;
};

/**
 * Typedef used as the default level generator when the game starts.
 */
using DEFAULT_LEVEL_GENERATOR = RandomLevelGenerator;

}