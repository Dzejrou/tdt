#include "LevelGenerators.hpp"
#include "EntitySystem.hpp"
#include "lppscript/LppScript.hpp"
#include "Grid.hpp"

namespace level_generators
{

LevelGenerator::LevelGenerator(EntitySystem& ents, std::size_t c)
	: entities_{ents}, cycles_{c}
{ /* DUMMY BODY */ }

RandomLevelGenerator::RandomLevelGenerator(EntitySystem& ents, std::size_t c)
	: LevelGenerator{ents, c}
{ /* DUMMY BODY */ }

void RandomLevelGenerator::generate(std::size_t width, std::size_t height)
{
	/**
	 * 0 == free space
	 * 1 == wall
	 * 2 == gold deposit
	 * 3 == border
	 * 4 == walkway
	 */
	std::vector<std::vector<std::size_t>> level{};
	level.resize(width);
	for(std::size_t i = 0; i < width; ++i)
	{ // Initialize the level to be only made of walls.
		for(std::size_t j = 0; j < height; ++j)
			level[i].push_back(1);
	}

	// Generate gold deposits.
	for(std::size_t not_used = 0; not_used < cycles_; ++not_used) // Repeats the process for better results.
	for(std::size_t i = 0; i < width; ++i)
	{
		for(std::size_t j = 0; j < height; ++j)
		{
			// Check the neighbours for gold veins.
			int gold_neighbours{0};
			for(int k = -1; k <= 1; ++k)
			{
				for(int l = -1; l <= 1; ++l)
				{
					std::size_t new_i = i + k;
					std::size_t new_j = j + l;
					if(new_i >= 0 && new_i < width &&
					   new_j >= 0 && new_j < height)
					{
						if(level[new_i][new_j] == 2)
							++gold_neighbours;
					}
				}
			}
			auto rand = util::get_random(0, 6 + gold_neighbours / 4);
			if(rand > 4)
				level[i][j] = 2;
			else if(rand <= 4 && rand > 0)
				level[i][j] = 1;
		}
	}

	// Empty space for player starting position.
	std::size_t mid_w = width / 2;
	std::size_t mid_h = height / 2;
	std::size_t rad_w = (width / 4 > 3) ? 3 : width / 4;
	std::size_t rad_h = (height / 4 > 3) ? 3 : height / 4;

	for(std::size_t i = mid_w - rad_w; i < mid_w + rad_w; ++i)
	{
		for(std::size_t j = mid_w - rad_w; j < mid_w + rad_w; ++j)
			level[i][j] = 0;
	}

	// Left/Right borders.
	for(std::size_t i = 0; i < height; ++i)
	{
		level[0][i] = 3;
		level[width - 1][i] = 3;
	}

	// Top/Bottom borders.
	for(std::size_t i = 0; i < width; ++i)
	{
		level[i][0] = 3;
		level[i][height - 1] = 3;
	}

	// Actual structure placing.
	auto& script = lpp::Script::get_singleton();
	auto& grid = Grid::instance();
	std::string wall_table{script.get<std::string>("game.config.default_wall_table")};
	std::string gold_table{script.get<std::string>("game.config.default_gold_table")};
	std::string border_table{script.get<std::string>("game.config.default_border_table")};
	std::string walkway_table{script.get<std::string>("game.config.default_walkway_table")};
	for(std::size_t i = 0; i < width; ++i)
	{
		for(std::size_t j = 0; j < height; ++j)
		{
			std::size_t id{Component::NO_ENTITY};
			if(level[i][j] == 1)
			{
				id = entities_.create_entity(wall_table);
			}
			else if(level[i][j] == 2)
				id = entities_.create_entity(gold_table);
			else if(level[i][j] == 3)
				id = entities_.create_entity(border_table);

			if(level[i][j] == 1 || level[i][j] == 2 ||
			   level[i][j] == 3 || level[i][j] == 4)
			{
				auto node = grid.get_node(i,j);
				PhysicsHelper::set_2d_position(entities_, id,
											   PhysicsHelper::get_2d_position(entities_, node));
				GridNodeHelper::set_free(entities_, node, false);
				GridNodeHelper::set_resident(entities_, node, id);
				StructureHelper::add_residence(entities_, id, node);
			}
		}
	}
}

}