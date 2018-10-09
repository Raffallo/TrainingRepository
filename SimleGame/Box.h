#pragma once
#include "SFML/Graphics.hpp"
using namespace sf;

class Box : public Drawable
{
public:
	Box(float X, float Y, float width, float height);
	Box() = delete;
	~Box() = default;
	void Update();
	void Change(float X, float Y, float width, float height);
	const sf::FloatRect GetBoundBox();
private:
	RectangleShape m_shape;
	Vector2f m_size{ 0.0f, 0.0f };
	float m_speed{ 0.0f };
	Vector2f m_velocity{ m_speed ,m_speed };
	void draw(RenderTarget& target, RenderStates state) const override;
};

