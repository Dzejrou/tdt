#include "Camera.hpp"

Camera::Camera()
	: camera_{}, start_{}, free_mode_{false}, movement_direction_{0.f, 0.f, 0.f},
	  speed_{}, height_{}, zoom_{}, zoom_min_{-15}, zoom_max_{25},
	  parent_node_{}, child_node_{}, last_delta_{}, zoom_modifier_{15.f},
	  target_{}
{ /* DUMMY BODY */ }

void Camera::init(Ogre::Camera* cam, const Ogre::Vector3& target)
{
	camera_ = cam;
	target_ = target;
	reset();

	parent_node_ = camera_->getParentSceneNode();
	child_node_ = parent_node_->createChildSceneNode("camera_child");
	parent_node_->detachObject(camera_);
	//child_node_->attachObject(camera_);
}

void Camera::set_position(const Ogre::Vector2& val)
{
	if(camera_)
	{
		auto new_pos = Ogre::Vector3{val.x, height_, val.y};
		auto diff = new_pos - camera_->getPosition();
		camera_->setPosition(new_pos);
		target_ += diff;
		camera_->lookAt(diff);
	}
}

const Ogre::Vector3& Camera::get_position() const
{
	return camera_->getPosition();
}

void Camera::set_direction(const Ogre::Vector3& val)
{
	if(camera_)
		camera_->setDirection(val);
}

Ogre::Vector3 Camera::get_direction() const
{
	if(camera_)
		return camera_->getDirection();
	else
		return Ogre::Vector3{};
}

void Camera::look_at(const Ogre::Vector2& val)
{
	if(camera_)
	{
		target_ = Ogre::Vector3{val.x, 0.f, val.y};
		camera_->lookAt(target_);
	}
}

void Camera::reset()
{
	camera_->setPosition(std::get<0>(start_));
	camera_->setOrientation(Ogre::Quaternion{});
	camera_->lookAt(std::get<1>(start_));
	movement_direction_ = Ogre::Vector3{0.f, 0.f, 0.f};
	speed_ = 500.f;
}

void Camera::set_start(const Ogre::Vector2& position, const Ogre::Vector2& center, tdt::real height)
{
	target_ = Ogre::Vector3{center.x, 0.f, center.y};
	height_ = height;
	start_ = std::make_tuple(Ogre::Vector3{position.x, height_, position.y},
							 target_);
}

void Camera::set_free_mode(bool val)
{
	if(!val)
		reset();
	free_mode_ = val;
}

bool Camera::get_free_mode() const
{
	return free_mode_;
}

void Camera::update(tdt::real delta)
{
	last_delta_ = delta;
	if(free_mode_)
		camera_->moveRelative(movement_direction_ * speed_ * delta * -1.f);
	else
	{ // Additional movement by keys, this ignores elevation.
		if(movement_direction_.z > 0)
			move(DIRECTION::DOWN, delta);
		else if(movement_direction_.z < 0)
			move(DIRECTION::UP, delta);

		if(movement_direction_.x > 0)
			move(DIRECTION::LEFT, delta);
		else if(movement_direction_.x < 0)
			move(DIRECTION::RIGHT, delta);
	}
}

void Camera::key_pressed(CEGUI::Key::Scan key)
{
	switch(key)
	{
		case CEGUI::Key::Scan::A:
			movement_direction_.x += 1;
			break;
		case CEGUI::Key::Scan::D:
			movement_direction_.x -= 1;
			break;
		case CEGUI::Key::Scan::W:
			movement_direction_.z += 1;
			break;
		case CEGUI::Key::Scan::S:
			movement_direction_.z -= 1;
			break;
		case CEGUI::Key::Scan::Space:
			movement_direction_.y -= 1;
			break;
		case CEGUI::Key::Scan::LeftControl:
			movement_direction_.y += 1;
			break;
	}
}

void Camera::key_released(CEGUI::Key::Scan key)
{
	switch(key)
	{
		case CEGUI::Key::Scan::A:
			movement_direction_.x = 0;
			break;
		case CEGUI::Key::Scan::D:
			movement_direction_.x = 0;
			break;
		case CEGUI::Key::Scan::W:
			movement_direction_.z = 0;
			break;
		case CEGUI::Key::Scan::S:
			movement_direction_.z = 0;
			break;
		case CEGUI::Key::Scan::Space:
			movement_direction_.y = 0;
			break;
		case CEGUI::Key::Scan::LeftControl:
			movement_direction_.y = 0;
			break;
	}
}

void Camera::move(DIRECTION::VAL dir, tdt::real delta)
{
	Ogre::Vector3 diff{camera_->getDirection().normalisedCopy()};
	diff.y = 0;
	switch(dir)
	{
		case DIRECTION::UP:
			diff = Ogre::Quaternion{Ogre::Degree{180.f}, Ogre::Vector3::UNIT_Y} * diff;
			break;
		case DIRECTION::DOWN:
			// No rotation needed.
			break;
		case DIRECTION::LEFT:
			diff = Ogre::Quaternion{Ogre::Degree{90.f}, Ogre::Vector3::UNIT_Y} * diff;
			break;
		case DIRECTION::RIGHT:
			diff = Ogre::Quaternion{Ogre::Degree{-90.f}, Ogre::Vector3::UNIT_Y} * diff;
			break;
		default:
			// Ignore atm.
			break;
	}
	diff *= speed_ * delta;
	camera_->move(diff);

	target_ += diff;
}

void Camera::set_height(tdt::real val)
{
	height_ = val;

	auto pos = camera_->getPosition();
	pos.y = height_;
	camera_->setPosition(pos);
}

tdt::real Camera::get_height() const
{
	return height_;
}

void Camera::pitch(const Ogre::Degree& val)
{
	camera_->pitch(val);
}

void Camera::yaw(const Ogre::Degree& val)
{
	camera_->yaw(val);
}

void Camera::rotate(int val)
{
	if(free_mode_)
		return;

	auto angle = ((val > 0) ? 0.1f : -0.1f);
	auto cos_angle = Ogre::Math::Cos(angle);
	auto sin_angle = Ogre::Math::Sin(angle);

	auto pos = camera_->getPosition();
	auto diff_x = pos.x - target_.x;
	auto diff_z = pos.z - target_.z;
	Ogre::Vector3 new_position{
		target_.x + diff_x * cos_angle - diff_z * sin_angle,
		height_,
		target_.z + diff_x * sin_angle + diff_z * cos_angle
	};

	camera_->setPosition(new_position);
	camera_->lookAt(target_);
}

void Camera::zoom(int val)
{
	if(free_mode_)
		return;

	if(val > 0 && zoom_ > zoom_min_)
	{
		camera_->move(camera_->getDirection() * speed_ * last_delta_ * zoom_modifier_);
		--zoom_;
	}
	else if(val < 0 && zoom_ < zoom_max_)
	{
		camera_->move(camera_->getDirection() * speed_ * last_delta_ * -1.f * zoom_modifier_);
		++zoom_;
	}

	// Need to update it to avoid resetting of the height on movement.
	height_ = camera_->getPosition().y;
}
