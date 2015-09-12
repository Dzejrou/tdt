#include "Grid.hpp"

bool Grid::in_board(std::size_t id) const
{
	return std::find(nodes_.begin(), nodes_.end(), id) != nodes_.end();
}

const std::vector<std::size_t>& Grid::get_freed() const
{
	return freed_;
}

const std::vector<std::size_t>& Grid::get_unfreed() const
{
	return unfreed_;
}

void Grid::clear_freed()
{
	freed_.clear();
}

void Grid::clear_unfreed()
{
	unfreed_.clear();
}

void Grid::add_node(std::size_t id)
{
	nodes_.push_back(id);
}

void Grid::add_freed(std::size_t id)
{
	freed_.push_back(id);
}

void Grid::add_unfreed(std::size_t id)
{
	unfreed_.push_back(id);
}

void Grid::remove_node(std::size_t id)
{
	std::remove(nodes_.begin(), nodes_.end(), id);
}

Grid& Grid::instance()
{
	static Grid inst{};

	return inst;
}
