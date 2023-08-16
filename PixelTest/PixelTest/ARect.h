#pragma once

extern float _screenWidth;

class ARect
{
public:
	void Update(float dt)
	{
		_x += _vx * dt;

		if ((_x >= _screenWidth - 20.0f && _vx > 0.0f) || (_x <= 0.0f && _vx < 0.0f))
			_vx = -_vx;
	}
public:
	float _x;
	float _y;
	float _vx;
};
