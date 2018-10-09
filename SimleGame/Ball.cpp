#include "pch.h"
#include "Ball.h"

Ball::Ball(float X, float Y)
{
	m_shape.setPosition(X, Y);
	m_shape.setRadius(m_radius);
	m_shape.setFillColor(Color::Green);
	m_shape.setOrigin(m_radius, m_radius);
}

void Ball::draw(RenderTarget& target, RenderStates state) const
{
	target.draw(m_shape, state);
}

void Ball::Update()
{
	m_shape.move(m_velocity);
}

void Ball::CheckCollisions(const sf::FloatRect& boundBox)
{
	Vector2f point = m_shape.getPosition();
	//point.x--->
	//y
	// |
	//\/

	if (point.y + m_radius >= boundBox.top && point.y - m_radius < boundBox.top + boundBox.height && (point.x >= boundBox.left && point.x <= boundBox.left + boundBox.width))
	{
		m_velocity.y = -m_speed;
	}
	else if (point.y - m_radius <= boundBox.top + boundBox.height && point.y + m_radius > boundBox.top && (point.x >= boundBox.left && point.x <= boundBox.left + boundBox.width))
	{
		m_velocity.y = m_speed;
	}
	else if (point.y + m_radius >= boundBox.left && point.y - m_radius < boundBox.left + boundBox.width && (point.y >= boundBox.top + boundBox.height && point.y <= boundBox.top))
	{
		m_velocity.x = -m_speed;
	}
	else if (point.x - m_radius <= boundBox.left + boundBox.width && point.x + m_radius > boundBox.left && (point.y >= boundBox.top + boundBox.height && point.y <= boundBox.top))
	{
		m_velocity.x = m_speed;
	}
}

void Ball::CheckCollisions(Vector2u windowSize)
{
	Vector2f point = m_shape.getPosition();
	if (point.x + m_radius >= windowSize.x)
	{
		m_velocity.x = -m_speed;
	}
	if (point.x - m_radius <= 0)
	{
		m_velocity.x = m_speed;
	}
	if (point.y + m_radius >= windowSize.y)
	{
		m_velocity.y = -m_speed;
	}
	if (point.y - m_radius <= 0)
	{
		m_velocity.y = m_speed;
	}
}