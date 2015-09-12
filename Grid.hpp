#pragma once

#include <Ogre.h>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include "EntitySystem.hpp"

class Grid
{
	public:
		bool in_board(std::size_t) const;
		const std::vector<std::size_t>& get_freed() const;
		const std::vector<std::size_t>& get_unfreed() const;
		void clear_freed();
		void clear_unfreed();

		void add_node(std::size_t);
		void add_freed(std::size_t);
		void add_unfreed(std::size_t);
		void remove_node(std::size_t);

		void create_graph(EntitySystem&, std::size_t, std::size_t, Ogre::Real);

		static Grid& instance();
	private:
		Grid() = default;
		~Grid() {}
		Grid(const Grid&) = delete;
		Grid& operator=(const Grid&) = delete;
		Grid(Grid&&) = delete;
		Grid& operator=(Grid&&) = delete;

		std::vector<std::size_t> nodes_, freed_, unfreed_;
		std::size_t width_, height_;
};