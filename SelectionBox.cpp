#include "SelectionBox.hpp"

SelectionBox::SelectionBox(const Ogre::String& name, EntitySystem& ents)
	: Ogre::ManualObject(name), entities_{ents}
{
	setRenderQueueGroup(Ogre::RENDER_QUEUE_OVERLAY); // So that the box renders over everything else.
	setUseIdentityProjection(true);
	setUseIdentityView(true);
	setQueryFlags(0); // So that it isn't part of any query.
}

void SelectionBox::set_corners(float left, float top, float right, float bottom)
{
	/**
	 * Neccessary translation, mouse positions are normalized to belong to the (0,1)
	 * range, but the Ogre::ManualObject creation requires them to belong to the (-1, 1).
	 */
	left = 2 * left - 1;
	right = 2 * right - 1;
	top = 1 - 2 * top;
	bottom = 1 - 2 * bottom;

	clear();
	
	// Constructs the selection box.
	begin("color/green", Ogre::RenderOperation::OT_LINE_STRIP);
	position(left, top, -1); // Since it's a 2D object, z is set to -1 (no real reason, won't be used).
	position(right, top, -1);
	position(right, bottom, -1);
	position(left, bottom, -1);
	position(left, top, -1);
	end();

	setBoundingBox(Ogre::AxisAlignedBox::BOX_INFINITE);
}

void SelectionBox::set_corners(const Ogre::Vector2& top_left, const Ogre::Vector2& bottom_right)
{
	set_corners(top_left.x, top_left.y, bottom_right.x, bottom_right.y);
}

std::vector<std::size_t>& SelectionBox::get_selected_entities()
{
	return selected_entities_;
}

void SelectionBox::select_object(Ogre::MovableObject* obj)
{
	auto* node = obj->getParentSceneNode();

	// Since it was found by Ogre, it has GraphicsComponent.
	for(auto& ent : entities_.get_component_container<GraphicsComponent>())
	{
		if(ent.second.node)
			selected_entities_.emplace_back(ent.first);
	}
}
