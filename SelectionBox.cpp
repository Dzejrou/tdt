#include "SelectionBox.hpp"
#include "GUI.hpp"
#include "EntitySystem.hpp"

SelectionBox::SelectionBox(const Ogre::String& name, EntitySystem& ents,
						   Ogre::PlaneBoundedVolumeListSceneQuery& vol_query,
						   Ogre::RaySceneQuery& ray_query, Ogre::SceneManager& mgr)
	: Ogre::ManualObject(name), entities_{ents}, volume_query_{vol_query},
	  ray_query_{ray_query}, scene_mgr_{mgr}, start_{}
{
	setRenderQueueGroup(Ogre::RENDER_QUEUE_OVERLAY); // So that the box renders over everything else.
	setUseIdentityProjection(true);
	setUseIdentityView(true);
	setQueryFlags(0); // So that it isn't part of any query.
	scene_mgr_.getRootSceneNode()->createChildSceneNode()->attachObject(this);
	ray_query_.setSortByDistance(true);
}

SelectionBox::~SelectionBox()
{
	scene_mgr_.destroyQuery(&volume_query_);
	scene_mgr_.destroyQuery(&ray_query_);
}

void SelectionBox::set_corners(float left, float top, float right, float bott)
{
	/**
	 * Neccessary translation, mouse positions are normalized to belong to the (0,1)
	 * range, but the Ogre::ManualObject creation requires them to belong to the (-1, 1).
	 */
	left = 2 * left - 1;
	right = 2 * right - 1;
	top = 1 - 2 * top;
	bott = 1 - 2 * bott;

	clear();
	
	// Constructs the selection box.
	begin("colour/green", Ogre::RenderOperation::OT_LINE_STRIP);
	position(left, top, -1); // Since it's a 2D object, z is set to -1 (no real reason, won't be used).
	position(right, top, -1);
	position(right, bott, -1);
	position(left, bott, -1);
	position(left, top, -1);
	end();

	setBoundingBox(Ogre::AxisAlignedBox::BOX_INFINITE);
}

void SelectionBox::set_corners(const Ogre::Vector2& t_l, const Ogre::Vector2& b_r)
{
	auto top_left = t_l;
	auto bottom_right = b_r;
	set_corners(top_left.x, top_left.y, bottom_right.x, bottom_right.y);
}

std::vector<tdt::uint>& SelectionBox::get_selected_entities()
{
	return selected_entities_;
}

void SelectionBox::select_object(Ogre::MovableObject& obj)
{
	// Since it was found by Ogre, it has GraphicsComponent.
	for(auto& ent : entities_.get_component_container<GraphicsComponent>())
	{
		if(ent.second.entity == &obj)
		{
			selected_entities_.emplace_back(ent.first);
			ent.second.node->showBoundingBox(true);
			break;
		}
	}
}

void SelectionBox::clear_selected_entities()
{
	for(auto& ent : selected_entities_)
	{
		auto comp = entities_.get_component<GraphicsComponent>(ent);
		if(comp)
			comp->node->showBoundingBox(false);
	}

	selected_entities_.clear();
}

void SelectionBox::execute_selection(const Ogre::Vector2& end, Ogre::Camera& cam, bool append)
{
	float left = start_.x;
	float top = start_.y;
	float right = end.x;
	float bott = end.y;
	
	if(!append)
		clear_selected_entities(); // Previous selection.
	GUI::instance().get_tracker().clear();

	// Adjust coordinates in case of selection in a different direction.
	if(left > right)
		std::swap(left, right);
	if(top > bott)
		std::swap(top, bott);

	if((right - left) * (bott - top) < 0.0001)
	{
		execute_single_selection(cam);
		return;
	}

	Ogre::PlaneBoundedVolumeList volume_list{cam.getCameraToViewportBoxVolume(
												left, top, right, bott
											)};
	volume_query_.setVolumes(volume_list);
	Ogre::SceneQueryResult result{volume_query_.execute()};

	for(const auto& movable : result.movables)
	{
		select_object(*movable);
	}
}

void SelectionBox::set_starting_point(const Ogre::Vector2& start)
{
	start_ = start;
}

void SelectionBox::set_selecting(bool sel)
{
	selection_in_progress_ = sel;
	setVisible(sel);
}

bool SelectionBox::is_selecting() const
{
	return selection_in_progress_;
}

void SelectionBox::extend_to(const Ogre::Vector2& end)
{
	set_corners(start_, end);
}

void SelectionBox::execute_single_selection(Ogre::Camera& cam)
{
	auto mouse_ray = cam.getCameraToViewportRay(start_.x, start_.y);
	ray_query_.setRay(mouse_ray);

	auto& res = ray_query_.execute();

	for(auto& obj : res)
	{
		if(obj.movable && obj.movable->getName() != cam.getName())
		{ // Select closest movable object that isn't the camera itself.
			select_object(*obj.movable);
			break;
		}
	}
}
