#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

enum class DeltaTimeMode { DeltaTime, MonitorDeltaTime };

// Override base class with your custom functionality
class Example : public olc::PixelGameEngine
{
public:
	Example()
	{
		// Name your application
		sAppName = "Example";
	}

	bool OnUserCreate() override
	{
		printf("Width: %d Height: %d", ScreenWidth(), ScreenHeight());

		_sprite = std::make_unique<olc::Sprite>(20, 20);

		// Called once at the start, so create things here
		return true;
	}

	float GetDeltaTime(float elapsedTime)
	{
		switch (_deltaTimeMode)
		{
		case DeltaTimeMode::DeltaTime:
			return elapsedTime;
		case DeltaTimeMode::MonitorDeltaTime:
			return 1.0 / 60.0;
		}

		return 0.0;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		Clear(olc::VERY_DARK_BLUE);

		/*
		// Called once per frame, draws random colored pixels
		for (int x = 0; x < ScreenWidth(); x++)
			for (int y = 0; y < ScreenHeight(); y++)
				Draw(x, y, olc::Pixel(rand() % 256, rand() % 256, rand() % 256));
				*/

		//DrawString(20, 20, std::to_string(fElapsedTime));

		float dt = GetDeltaTime(fElapsedTime);

		_cxw += _vx * dt;

		if ((_cxw > static_cast<float>(ScreenWidth() - 20) && _vx > 0) || (_cxw < 20.0f && _vx < 0))
			_vx = -_vx;

		int32_t cx = static_cast<int32_t>(_cxw);
		//int32_t cx = static_cast<int32_t>(std::round(_cxw));
		int32_t cy = static_cast<int32_t>(_cyw);

		DrawCircle( cx, cy, 20, olc::GREEN);

		DrawRectDecal({ _cxw, _cyw + 50 }, { 20,20 }, olc::GREEN);

		//if (fElapsedTime < 0.001f)
		//std::this_thread::sleep_for(std::chrono::milliseconds(8));

		return true;
	}

private:
	float _vx = 100;
	float _cxw = 20;
	float _cyw = 86;
	std::unique_ptr<olc::Sprite> _sprite;
	DeltaTimeMode _deltaTimeMode = DeltaTimeMode::MonitorDeltaTime;
};

int main()
{
	Example demo;
	if (demo.Construct(256, 192, 4, 4, false, true))
		demo.Start();
	return 0;
}