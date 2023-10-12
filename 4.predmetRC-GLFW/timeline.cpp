#include "timeline.h"
#include <chrono>
#include <iostream>
#include <vector>
#include <functional>
#include <thread>
#include <Windows.h>

namespace UI {
	std::vector<int> c_id;

	void nothing() {
		return;
	}

	STOPWATCH::STOPWATCH(bool VP) {
		if (VP == true) {
			vrniPovprecje = true;
			c_id.push_back(0);
			id = c_id.size();
		}
	}
	STOPWATCH::~STOPWATCH() {
		if (vrniPovprecje == true) {
			std::cout << "\n------------------\nID:  " << id << "\n"
				<< average() << "\n------------------\n";
		}
	}
	void STOPWATCH::begin() {
		zacetek = std::chrono::system_clock::now();
	}
	float STOPWATCH::end() {
		std::chrono::system_clock::time_point konec = std::chrono::system_clock::now();
		std::chrono::duration<float> prC = konec - zacetek;
		ret = prC.count() * 1000.0f;
		retVr.push_back(prC.count() * 1000.0f);
		return ret;
	}
	float STOPWATCH::reset() {
		std::chrono::system_clock::time_point konec = std::chrono::system_clock::now();
		std::chrono::duration<float> prC = konec - zacetek;
		ret = prC.count() * 1000.0f;
		retVr.push_back(prC.count() * 1000.0f);
		zacetek = std::chrono::system_clock::now();
		return ret;
	}
	float STOPWATCH::time() {
		std::chrono::system_clock::time_point konec = std::chrono::system_clock::now();
		std::chrono::duration<float> prC = konec - zacetek;
		float rret = prC.count() * 1000.0f;
		return rret;
	}
	float STOPWATCH::previousTime() {
		return ret;
	}
	std::vector<float> STOPWATCH::previousTimes() {
		return retVr;
	}
	float STOPWATCH::average() {
		float povprecje = 0.0f;
		for (int c = 0; c < retVr.size(); c++) {
			povprecje += retVr.at(c);
		}
		povprecje /= retVr.size();
		return povprecje;
	}
	void STOPWATCH::countdown(int cas_v_ms, CALL k) {
		CALL cakaj = [&] {
			Sleep(cas_v_ms);
			k();
		};
		std::thread{ cakaj }.detach();
	}

	void sleep(float ms) {
		/*STOPWATCH st1;
		st1.begin();
		while (st1.time() < ms) {
			nothing();
		}*/
		Sleep(ms);
		return;
	}
}