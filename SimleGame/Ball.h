#pragma once
#include "SFML/Graphics.hpp"
using namespace sf;
class Ball : public Drawable
{
public:
	Ball(float X, float Y);
	Ball() = delete;
	~Ball() = default;
	void Update();
	void CheckCollisions(Vector2u windowSize);
	void CheckCollisions(const sf::FloatRect& boundBox);
private:
	CircleShape m_shape;
	const float m_radius{ 10.0f };
	float m_speed{ 7.0f };
	Vector2f m_velocity{ m_speed ,m_speed };
	void draw(RenderTarget& target, RenderStates state) const override;
};

