#include "GameSerializer.hpp"

GameSerializer::GameSerializer(EntitySystem& ents)
	: entities_{ents}, script_{lpp::Script::get_singleton()}
{ /* DUMMY BODY */ }

void GameSerializer::save_game(const std::string &)
{
}

void GameSerializer::load_game(const std::string &)
{
}
