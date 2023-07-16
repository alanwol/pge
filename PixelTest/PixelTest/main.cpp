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
		sAppName = "Test";
	}

	bool OnUserCreate() override
	{
		// Called once at the start, so create things here

		std::cout << "Width: " << ScreenWidth() << "Height: " << ScreenHeight() << std::endl;

		_sprite = std::make_unique<olc::Sprite>(20, 20);

		// Clear the screen to activate graphics code
		Clear(olc::VERY_DARK_BLUE);

		return true;
	}


	// TODO the 30 is now hard coded, could also be 45, 60, 75, 90, 120, 144 
	float GetMonitorMultiple(float elapsedTime) const
	{
		return std::max(1.0f, std::round(elapsedTime * 30.0f));
	}

	float GetDeltaTime(float elapsedTime) const
	{
		switch (_deltaTimeMode)
		{
		case DeltaTimeMode::DeltaTime:
			return elapsedTime;
		case DeltaTimeMode::MonitorDeltaTime:
			return GetMonitorMultiple(elapsedTime)/30.0f;
		}

		return 0.0;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		/*
		// Called once per frame, draws random colored pixels
		for (int x = 0; x < ScreenWidth(); x++)
			for (int y = 0; y < ScreenHeight(); y++)
				Draw(x, y, olc::Pixel(rand() % 256, rand() % 256, rand() % 256));
				*/

		//DrawString(20, 20, std::to_string(fElapsedTime));

		const float dt = GetDeltaTime(fElapsedTime);


		//std::cout << dt << std::endl;


		_cxw += _vx * dt;

		if ((_cxw > static_cast<float>(ScreenWidth() - 20) && _vx > 0.0f) || (_cxw < 20.0f && _vx < 0.0f))
			_vx = -_vx;

		//int32_t cx = static_cast<int32_t>(_cxw);
		int32_t cx = static_cast<int32_t>(std::round(_cxw));
		int32_t cy = static_cast<int32_t>(_cyw);

		// Render area

		Clear(olc::VERY_DARK_BLUE);

		DrawCircle( cx, cy, 20, olc::GREEN);

		FillRectDecal({ _cxw, _cyw + 50 }, { 20,20 }, olc::GREEN);

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
	if (demo.Construct(256, 192, 1, 1, false, true))
		demo.Start();
	return 0;
}