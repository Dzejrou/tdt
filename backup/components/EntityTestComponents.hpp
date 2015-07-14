#pragma once

#include <Ogre.h>
#include <string>

#include "BaseComponent.hpp"
#include "../lppscript/LppScript.hpp"

class EntityTestInputComponent : public InputComponent
{
	public:
		EntityTestInputComponent(std::string);
		void update(Entity&, Ogre::Real) override;
	private:
		std::string name_;
		lpp::Script& script_;
};

class EntityTestPhysicsComponent : public PhysicsComponent
{
	public:
		EntityTestPhysicsComponent(std::string);
		void update(Entity&, Ogre::Real) override;
	private:
		std::string name_;
		lpp::Script& script_;
};

class EntityTestGraphicsComponent : public GraphicsComponent
{
	public:
		EntityTestGraphicsComponent(Ogre::SceneManager&);
		~EntityTestGraphicsComponent() {}
		void update(Entity&, Ogre::Real) override;
};