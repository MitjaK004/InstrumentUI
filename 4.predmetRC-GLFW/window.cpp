#include "window.h"
#include <string>
#include <vector>
#include <functional>
#include "shape.h"
#include <memory>
#include <thread>
#include <future>

namespace UI {
	STOPWATCH stdStp = { true };

	void zacniStopat() {
		stdStp.begin();
	}

	float nehajStopat() {
		return stdStp.end();
	}

	float zracunajPovprecje() {
		return stdStp.average();
	}

	float(*hejajStopat)() = nehajStopat;

	WINDOW::WINDOW(std::string imeOkna)
	{
		i_okna = imeOkna;
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}

	WINDOW::~WINDOW()
	{

	}

	void WINDOW::operator << (CALL klic) {
		addCall(klic);
	}

	void WINDOW::operator << (SHAPE* oblika) {
		onInit([&] {oblika->init(); });
		addCall([&] {
			if (oblika->getUpdateStatus()) {
				addShape_ptr(oblika);
				oblika->setUpdateStaus();
			}
		});
	}

	void WINDOW::operator << (SHAPE& oblika) {
		onInit([&] {oblika.init(); });
		addCall([&] {
			if (oblika.getUpdateStatus()) {
				addShape(oblika);
				oblika.setUpdateStaus();
			}
		});
	}

	void WINDOW::createWindow() {
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		okno = glfwCreateWindow(resolucija.dolzina, resolucija.sirina, i_okna.c_str(), NULL, NULL);
		glfwSetWindowPos(okno, pozicija.x, pozicija.y);
		glfwShowWindow(okno);
		if (okno == NULL)
		{
			std::cout << "napaka pri nastanku okna" << std::endl;
			glfwTerminate();
			return;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_CONTEXT_ROBUSTNESS, GLFW_LOSE_CONTEXT_ON_RESET);
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
		glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API);
		glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_CONTEXT_RELEASE_BEHAVIOR, GLFW_RELEASE_BEHAVIOR_FLUSH);

		glfwMakeContextCurrent(okno);
		gladLoadGL();
		glViewport(0, 0, resolucija.dolzina, resolucija.sirina);

		glfwSwapInterval(0);

		init();

		while (!glfwWindowShouldClose(okno))
		{
			if (!skipCycle) {
				glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
				glClear(GL_COLOR_BUFFER_BIT);

				zacniStopat();
				narisiVseOblike();
				hejajStopat();
				narisiVseTekste();
				izvediVseKlice();

				glfwSwapBuffers(okno);
				glfwPollEvents();

				skipCycle = !skipCycle;
			}
			else {
				sleep(50);
				skipCycle = !skipCycle;
			}
			
		}

		glfwDestroyWindow(okno);
		glfwTerminate();
		return;
	}

	void WINDOW::addShape(SHAPE& oblika) {
		oblike.push_back(oblika);
	}

	void WINDOW::addCall(CALL klic) {
		klicNazaj.push_back(klic);
	}

	void WINDOW::izvediVseKlice() {
		for (int c = 0; c < klicNazaj.size(); c++) {
			klicNazaj.at(c)();
		}
	}

	void WINDOW::narisiVseOblike() {
		for (int c = 0; c < oblike.size(); c++) {
			oblike.at(c).create();
		}
		for (int c = 0; c < oblikePtr.size(); c++) {
			oblikePtr.at(c)->create();
		}
	}

	double WINDOW::X_coeficient() {
		double k = 200 / double(resolucija.sirina);
		k /= 100;
		return k;
	}

	double WINDOW::Y_coeficient() {
		double k = 200 / double(resolucija.dolzina);
		k /= 100;
		return k;
	}

	void WINDOW::setText(std::string text) {
		glfwSetWindowTitle(okno, text.c_str());
		//nic se
	}

	void WINDOW::addShape_ptr(SHAPE* oblika) {
		oblikePtr.push_back(oblika);
	}

	GLFWwindow* WINDOW::getGLFW_window() {
		return okno;
	}

	void WINDOW::operator<<(RESOLUTION rs) {
		resolucija = rs;
	}

	void WINDOW::operator<<(TEXT& t) {
		onInit([&] {t.init(); });
		addCall([&] {
			if (t.getUpdatestatus()) {
				addText(t);
				t.setUpdateStatus();
			}
			});
	}

	void WINDOW::addText(TEXT& text) {
		teksti.push_back(text);
	}

	void WINDOW::narisiVseTekste() {
		for (int c = 0; c < teksti.size(); c++) {
			teksti.at(c).create();
		}
	}

	void WINDOW::onInit(CALL lambda) {
		initLambde.push_back(lambda);
	}

	void WINDOW::init() {
		for (auto a : initLambde) {
			a();
		}
	}
}