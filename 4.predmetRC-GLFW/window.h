#pragma once
#include <string>
#include <vector>
#include <functional>
#include "shape.h"
#include "Tekst.h"
#include <memory>
#include <thread>
#include <future>

namespace UI {
	typedef std::vector<SHAPE> SHAPES;
	typedef std::vector<SHAPE*> SHAPES_ptr;

	typedef std::vector<std::function<void()>> KLICI;

	struct RESOLUTION {
		int dolzina;
		int sirina;
	};

	struct POSITION {
		int x;
		int y;
	};

	extern STOPWATCH stdStp;

	void zacniStopat();
	float nehajStopat();
	float zracunajPovprecje();

	extern float(*hejajStopat)();

	class WINDOW
	{
	public:
		WINDOW(std::string imeOkna);
		~WINDOW();
		std::string i_okna = "ime_okna";
		RESOLUTION resolucija = { 600, 400 };
		POSITION pozicija = { 100, 100 };
		void createWindow();
		void addShape(SHAPE& oblika);
		void addShape_ptr(SHAPE* oblika);
		void addText(TEXT& text);
		void addCall(CALL klic);
		void setText(std::string text);
		double Y_coeficient();
		double X_coeficient();
		void operator<<(CALL klic);
		void operator<<(SHAPE* oblika);
		void operator<<(SHAPE& oblika);
		void operator<<(RESOLUTION rs);
		void operator<<(TEXT &t);
		GLFWwindow* getGLFW_window();
		void onInit(CALL lambda);
	private:
		GLFWwindow* okno;
		SHAPES oblike;
		std::vector<TEXT> teksti;
		SHAPES_ptr oblikePtr;
		KLICI klicNazaj;
		SHAPE* chache = nullptr;
		std::vector<CALL> initLambde;
		bool skipCycle = false;
		void izvediVseKlice();
		void narisiVseOblike();
		void narisiVseTekste();
		void init();
	};
}