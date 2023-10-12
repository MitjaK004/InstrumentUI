#pragma once
#include <chrono>
#include <iostream>
#include <vector>
#include <functional>

namespace UI {
	extern std::vector<int> c_id;

	typedef std::function<void()> CALL;

	void nothing();

	class STOPWATCH {
	private:
		std::chrono::system_clock::time_point zacetek = std::chrono::system_clock::now();
		float ret = 0;
		int id = 0;
		bool vrniPovprecje = false;
		std::vector<float> retVr;
	public:
		STOPWATCH(bool VP = false);
		~STOPWATCH();
		void begin();
		float end();
		float reset();
		float time();
		float previousTime();
		std::vector<float> previousTimes();
		float average();
		void countdown(int cas, CALL k);
	};

	void sleep(float ms);
}