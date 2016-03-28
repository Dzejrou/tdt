#include "LevelGenerators.hpp"
#include "EntitySystem.hpp"
#include "lppscript/LppScript.hpp"
#include "Grid.hpp"
#include "WaveSystem.hpp"

namespace level_generators
{

LevelGenerator::LevelGenerator(EntitySystem& ents, tdt::uint c)
	: entities_{ents}, cycles_{c}
{ /* DUMMY BODY */ }

RandomLevelGenerator::RandomLevelGenerator(EntitySystem& ents, tdt::uint c)
	: LevelGenerator{ents, c}
{ /* DUMMY BODY */ }

void RandomLevelGenerator::generate(tdt::uint width, tdt::uint height, WaveSystem& wsystem)
{
	/**
	 * 0 == free space
	 * 1 == wall
	 * 2 == gold deposit
	 * 3 == border
	 * 4 == walkway
	 * 5 == light source
	 * 6 == throne
	 */
	std::vector<std::vector<tdt::uint>> level{};
	level.resize(width);
	for(tdt::uint i = 0; i < width; ++i)
	{ // Initialize the level to be only made of walls.
		for(tdt::uint j = 0; j < height; ++j)
			level[i].push_back(1);
	}

	// Generate gold deposits.
	for(tdt::uint not_used = 0; not_used < cycles_; ++not_used) // Repeats the process for better results.
	for(tdt::uint i = 0; i < width; ++i)
	{
		for(tdt::uint j = 0; j < height; ++j)
		{
			// Check the neighbours for gold veins.
			int gold_neighbours{0};
			for(int k = -1; k <= 1; ++k)
			{
				for(int l = -1; l <= 1; ++l)
				{
					tdt::uint new_i = i + k;
					tdt::uint new_j = j + l;
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
	tdt::uint mid_w = width / 2;
	tdt::uint mid_h = height / 2;
	tdt::uint rad_w = (width / 4 > 3) ? 3 : width / 4;
	tdt::uint rad_h = (height / 4 > 3) ? 3 : height / 4;

	for(tdt::uint i = mid_w - rad_w; i < mid_w + rad_w; ++i)
	{
		for(tdt::uint j = mid_h - rad_h; j < mid_h + rad_h; ++j)
			level[i][j] = 0;
	}

	// Light sources in the corners.
	level[mid_w + rad_w - 1][mid_h + rad_h - 1] = 5;
	level[mid_w - rad_w][mid_h - rad_h] = 5;
	level[mid_w + rad_w - 1][mid_h - rad_h] = 5;
	level[mid_w - rad_w][mid_h + rad_h - 1] = 5;

	// Left/Right borders.
	for(tdt::uint i = 0; i < height; ++i)
	{
		level[0][i] = 3;
		level[width - 1][i] = 3;
	}

	// Top/Bottom borders.
	for(tdt::uint i = 0; i < width; ++i)
	{
		level[i][0] = 3;
		level[i][height - 1] = 3;
	}

	// Enemy spawn points and walkway.
	tdt::uint side = util::get_random(0, 2);
	tdt::uint walkway_w = (mid_w - rad_w) / 2;
	tdt::uint walkway_h = (mid_h - rad_h) / 2;
	auto& grid = Grid::instance();
	switch(side)
	{
		case 0:
			level[1][mid_h] = 4; // Makes sure there are atleast 2.
			level[1][mid_h - 1] = 4;
			
			for(tdt::uint i = 2; i < walkway_h; ++i)
			{
				level[i][mid_h] = 4;
				level[i][mid_h - 1] = 4;
			}
			wsystem.add_spawn_node(grid.get_node(1, mid_h));
			wsystem.add_spawn_node(grid.get_node(1, mid_h - 1));
			break;
		case 1:
			level[mid_w][1] = 4;
			level[mid_w - 1][1] = 4;

			for(tdt::uint i = 2; i < walkway_w; ++i)
			{
				level[mid_w][i] = 4;
				level[mid_w - 1][i] = 4;
			}
			wsystem.add_spawn_node(grid.get_node(mid_w, 1));
			wsystem.add_spawn_node(grid.get_node(mid_w - 1, 1));
			break;
	}

	// The dungeon throne.
	level[mid_w][mid_h] = 6;

	// Actual structure placing.
	auto& script = lpp::Script::get_singleton();
	std::string wall_table{script.get<std::string>("game.config.default_wall_table")};
	std::string gold_table{script.get<std::string>("game.config.default_gold_table")};
	std::string border_table{script.get<std::string>("game.config.default_border_table")};
	std::string walkway_table{script.get<std::string>("game.config.default_walkway_table")};
	std::string light_table{script.get<std::string>("game.config.default_light_table")};
	std::string throne_table{script.get<std::string>("game.config.default_throne_table")};
	for(tdt::uint i = 0; i < width; ++i)
	{
		for(tdt::uint j = 0; j < height; ++j)
		{
			tdt::uint id{Component::NO_ENTITY};
			if(level[i][j] == 1)
				id = entities_.create_entity(wall_table);
			else if(level[i][j] == 2)
				id = entities_.create_entity(gold_table);
			else if(level[i][j] == 3)
				id = entities_.create_entity(border_table);
			else if(level[i][j] == 4)
				id = entities_.create_entity(walkway_table);
			else if(level[i][j] == 5)
				id = entities_.create_entity(light_table);
			else if(level[i][j] == 6)
				id = entities_.create_entity(throne_table);

			if(level[i][j] == 1 || level[i][j] == 2 ||
			   level[i][j] == 3 || level[i][j] == 4 ||
			   level[i][j] == 5 || level[i][j] == 6)
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