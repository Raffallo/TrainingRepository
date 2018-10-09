#include "pch.h"
#include "Box.h"


Box::Box(float X, float Y, float width, float height)
{
	Change(X, Y, width, height);
}

void Box::Change(float X, float Y, float width, float height)
{
	m_shape.setPosition(X, Y);
	Vector2f v2f(width, height);
	m_shape.setSize(v2f);
	m_shape.setFillColor(Color::Red);
	m_shape.setOrigin(width / 2, height / 2);
}

const sf::FloatRect Box::GetBoundBox()
{
	return m_shape.getGlobalBounds();
}

void Box::draw(RenderTarget& target, RenderStates state) const
{
	target.draw(m_shape, state);
}

void Box::Update()
{
	m_shape.move(m_velocity);
}
