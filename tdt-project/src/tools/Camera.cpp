#include "Camera.hpp"
#include "Grid.hpp"

void Camera::init(Ogre::Camera* cam)
{
	camera_ = cam;
	reset();
}

void Camera::set_position(const Ogre::Vector2& val)
{
	if(camera_)
		camera_->setPosition(Ogre::Vector3{val.x, height_, val.y});
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

const Ogre::Vector3 Camera::get_direction() const
{
	return camera_->getDirection();
}

void Camera::look_at(const Ogre::Vector2& val)
{
	if(camera_)
		camera_->lookAt(Ogre::Vector3{val.x, 0.f, val.y});
}

void Camera::reset()
{
	camera_->setPosition(std::get<0>(start_));
	camera_->setOrientation(Ogre::Quaternion{});
	camera_->lookAt(std::get<1>(start_));
	speed_ = 500.f;
}

void Camera::set_start(const Ogre::Vector2& position, const Ogre::Vector2& center, tdt::real height)
{
	height_ = height;
	start_ = std::make_tuple(Ogre::Vector3{position.x, height_, position.y},
							 Ogre::Vector3{center.x, 0.f, center.y});
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
	if(free_mode_)
		camera_->moveRelative(movement_direction_ * speed_ * delta);
	else
	{ // Additional movement by keys, this ignores elevation.
		if(movement_direction_.z < 0)
			move(DIRECTION::DOWN, delta);
		else if(movement_direction_.z > 0)
			move(DIRECTION::UP, delta);
		else if(movement_direction_.x < 0)
			move(DIRECTION::LEFT, delta);
		else if(movement_direction_.x > 0)
			move(DIRECTION::RIGHT, delta);
	}
}

void Camera::key_pressed(CEGUI::Key::Scan key)
{
	switch(key)
	{
		case CEGUI::Key::Scan::A:
			movement_direction_.x -= 1;
			break;
		case CEGUI::Key::Scan::D:
			movement_direction_.x += 1;
			break;
		case CEGUI::Key::Scan::W:
			movement_direction_.z -= 1;
			break;
		case CEGUI::Key::Scan::S:
			movement_direction_.z += 1;
			break;
		case CEGUI::Key::Scan::Space:
			movement_direction_.y += 1;
			break;
		case CEGUI::Key::Scan::LeftControl:
			movement_direction_.y -= 1;
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
	switch(dir)
	{
		case DIRECTION::UP:
			camera_->move(Ogre::Vector3{-1.f, 0.f, -1.f} * speed_ * delta);
			break;
		case DIRECTION::DOWN:
			camera_->move(Ogre::Vector3{1.f, 0.f, 1.f} * speed_ * delta);
			break;
		case DIRECTION::LEFT:
			camera_->move(Ogre::Vector3{1.f, 0.f, -1.f} * speed_ * delta);
			break;
		case DIRECTION::RIGHT:
			camera_->move(Ogre::Vector3{-1.f, 0.f, 1.f} * speed_ * delta);
			break;
		default:
			// Ignore atm.
			break;
	}
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
