#pragma once

class Time
{
	private:
	static float last_time;
	static float delta;

	public:
	static void update();
	static float get_delta();
};
