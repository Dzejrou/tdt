#include "SelectionBox.hpp"

SelectionBox::SelectionBox(const Ogre::String& name, EntitySystem& ents,
						   Ogre::PlaneBoundedVolumeListSceneQuery& query)
	: Ogre::ManualObject(name), entities_{ents}, volume_query_{query}
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

void SelectionBox::select_object(Ogre::MovableObject& obj)
{
	auto node = obj.getParentSceneNode();
	node->showBoundingBox(true);

	// Since it was found by Ogre, it has GraphicsComponent.
	for(auto& ent : entities_.get_component_container<GraphicsComponent>())
	{
		if(ent.second.node == node)
			selected_entities_.emplace_back(ent.first);
	}
}

void SelectionBox::clear_selected_entities()
{
	for(auto& ent : selected_entities_)
		entities_.get_component<GraphicsComponent>(ent).node->showBoundingBox(false);

	selected_entities_.clear();
}

void SelectionBox::execute_selection(const Ogre::Vector2& end, Ogre::Camera& cam)
{
	float left = start_.x;
	float top = start_.y;
	float right = end.x;
	float bott = end.y;

	// Adjust coordinates in case of selection in a different direction.
	if(left > right)
		std::swap(left, right);
	if(top > bott)
		std::swap(top, bott);

	auto top_left_ray = cam.getCameraToViewportRay(left, left);
	auto top_right_ray = cam.getCameraToViewportRay(top, right);
	auto bott_left_ray = cam.getCameraToViewportRay(bott, left);
	auto bott_right_ray = cam.getCameraToViewportRay(bott, right);

	Ogre::PlaneBoundedVolume volume{};
	// Front plane.
	volume.planes.emplace_back(top_left_ray.getOrigin(),
							   top_right_ray.getOrigin(),
							   bott_right_ray.getOrigin());
	// Top plane.
	volume.planes.emplace_back(top_left_ray.getOrigin(),
		                       top_left_ray.getPoint(10.f),
		                       top_right_ray.getPoint(10.f));
	// Left plane.
	volume.planes.emplace_back(top_left_ray.getOrigin(),
		                       bott_left_ray.getPoint(10.f),
		                       top_left_ray.getPoint(10.f));
	// Bottom plane.
	volume.planes.emplace_back(bott_left_ray.getOrigin(),
							   bott_right_ray.getPoint(10.f),
							   bott_left_ray.getPoint(10.f));
	// Right plane.
	volume.planes.emplace_back(top_right_ray.getOrigin(),
							   top_right_ray.getPoint(10.f),
							   bott_right_ray.getPoint(10.f));

	Ogre::PlaneBoundedVolumeList volume_list{volume};
	volume_query_.setVolumes(volume_list);
	Ogre::SceneQueryResult result{volume_query_.execute()};
	clear_selected_entities(); // Previous selection.

	for(const auto& movable : result.movables)
	{
		select_object(*movable);
	}
}

void SelectionBox::set_starting_point(const Ogre::Vector2& start)
{
	start_ = start;
}
