#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include <string>
#include <iostream>
using namespace std;

class BreakOut : public olc::PixelGameEngine
{
public:
	BreakOut()
	{
		sAppName = "First";
	}

private:
	float fBatPos = 20.0f;
	float fBatWidth = 50.0f;
	float fBatSpeed = 250.0f;
	float fBallRadius = 5.0f;
	olc::vf2d vBall = { 200.0f, 200.0f };
	olc::vf2d vBallVel = { 200.0f, -100.0f };

	// string
	float StrinX = 30.0f;
	float StrinY = 30.0f;
	
public:
	bool OnUserCreate() override
	{
		srand(100);
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{

		
		// user input
		if (GetKey(olc::Key::RIGHT).bHeld) fBatPos += fBatSpeed * fElapsedTime;
		if (GetKey(olc::Key::LEFT).bHeld) fBatPos -= fBatSpeed * fElapsedTime;

		if (fBatPos < 11.0f) fBatPos = 11.0f;
		if (fBatPos + fBatWidth > float(ScreenWidth()) - 10.0f) fBatPos = float(ScreenWidth()) - 10.0f - fBatWidth;
		
		vBall += vBallVel * fElapsedTime;

		// Really crude arena detection - this approach sucks
		if (vBall.y <= 10.0f) vBallVel.y *= -1.0f;
		if (vBall.x <= 10.0f) vBallVel.x *= -1.0f;
		if (vBall.x >= float(ScreenWidth()) - 10.0f) vBallVel.x *= -1.0f;

		// Check Bat
		if (vBall.y >= (float(ScreenHeight()) - 20.0f) && (vBall.x > fBatPos) && (vBall.x < fBatPos + fBatWidth))
			vBallVel.y *= -1.0f;

		// Check if ball has gone off screen
		if (vBall.y > ScreenHeight())
		{
			// Reset ball location
			vBall = { 200.0f, 200.0f };
			// Choose Random direction
			float fAngle = (float(rand()) / float(RAND_MAX)) * 2.0f * 3.14159f;
			vBallVel = { 300.0f * cos(fAngle), 300.0f * sin(fAngle) };
		}
		// mouse scroll wheel
		/* if (GetMouseWheel() > 0) fBallRadius += 1.0f;
		if (GetMouseWheel() < 0) fBallRadius -= 1.0f;
		if (fBallRadius < 5.0f) fBallRadius = 5.0f; */
		Clear(olc::DARK_CYAN);
		
		DrawLine(10, 10, ScreenWidth() - 10, 10, olc::RED);
		DrawLine(10, 10, 10, ScreenHeight() - 10, olc::RED);
		DrawLine(ScreenWidth() - 10, 10, ScreenWidth() - 10, ScreenHeight() - 10, olc::RED);
		
		// draw bat
		FillRect(int(fBatPos), ScreenHeight() - 30, int(fBatWidth), 20, olc::YELLOW);
		FillCircle(vBall, 5, olc::BLACK);
		DrawString(StrinX, StrinY, "Built by KJ", olc::WHITE);
		
		
		return true;
		
	}
};

int main()
{
	BreakOut demo;
	if (demo.Construct(500, 400, 2, 2))
		demo.Start();
	return 0;
}
