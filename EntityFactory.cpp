#include "EntityFactory.hpp"

EntityFactory::EntityFactory(std::vector<std::unique_ptr<Entity>>& ents, Ogre::SceneManager* mgr)
    : entities_{ents}, scene_mgr_{*mgr}
{ /* DUMMY BODY */ }
