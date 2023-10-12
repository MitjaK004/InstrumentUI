#include "shape.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include "timeline.h"
#include <windows.h>
#include "shader.h"
#include "tekstura.h"
#include "verteksi.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GL_QUADS 5

namespace UI {
	int r = 0;

	SquaresRCT operator+ (SquaresRCT a, SquaresRCT b) {
		SquaresRCT ret;
		for (int c = 0; c < a.size(); c++) {
			ret.push_back(a.at(c));
		}
		for (int c = 0; c < b.size(); c++) {
			ret.push_back(b.at(c));
		}
		return ret;
	}

	SquareRCT operator+ (SquareRCT a, SquareRCT b) {
		SquareRCT ret;
		ret.r1 = a.r1;
		ret.x1 = a.x1;
		ret.r2 = b.r2;
		ret.x2 = b.x2;
		return ret;
	}

	SquareRCT operator- (SquareRCT a, SquareRCT b) {
		SquareRCT ret;
		ret.r1 = b.r1;
		ret.x1 = b.x1;
		ret.r2 = a.r2;
		ret.x2 = a.x2;
		return ret;
	}

	SquareRCT operator/ (SquareRCT a, float b) {
		SquareRCT ret;
		ret.r1 = a.r1;
		ret.x1 = a.x1;
		ret.r2 = a.r2 / b;
		ret.x2 = a.x2 / b;
		return ret;
	}

	SquaresRCT operator* (SquaresRCT a, SquaresRCT b) {
		SquaresRCT ret;
		bool prvi = true;
		for (int c = 0; c < a.size(); c++) {
			if (c < b.size()) {
				ret.push_back(a.at(c) + b.at(c));
			}
			else {
				ret.push_back(a.at(c));
			}
		}
		return ret;
	}

	void operator++ (SquaresRCT& a) {
		SquaresRCT mat;
		for (int c = 0; c < a.size(); c += 2) {
			SquareRCT kv;
			if (c + 1 < a.size()) {
				kv = a.at(c);
				kv.x2 = a.at(c + 1).x2;
				kv.r2 = a.at(c + 1).r2;
			}
			else {
				kv = a.at(c);
			}
			mat.push_back(kv);
		}
		a = mat;
	}

	void operator += (SquaresRCT& a, SquaresRCT& b) {
		for (int c = 0; c < b.size(); c++) {
			a.push_back(b.at(c));
		}
	}

	float SquareRCT::stranicaA() {
		return r2 - r1;
	}
	float SquareRCT::stranicaB() {
		return abs(x2 - x1);
	}
	float SquareRCT::kot() {
		return asinf(stranicaA() / sqrtf(powf(stranicaB(), 2) - powf(stranicaA(), 2)));
	}
	int SquareRCT::orientacija() {
		if (stranicaA() < 0.0f) {
			return -1;
		}
		else if (stranicaA() > 0.0f) {
			return 1;
		}
		else {
			return 0;
		}
	}


	SHAPE::SHAPE(const char* pot, bool INI_T) {
		potTeksture = (char*)pot;
		r++;
		if (INI_T == true) {
			init();
		}
	}

	SHAPE::SHAPE(const char* pot, GLfloat ver[32], bool INI_T) {
		potTeksture = (char*)pot;
		for (int c = 0; c < 32; c++) {
			vert[c] = ver[c];
		}
		r++;
		if (INI_T == true) {
			init();
		}
	}

	SHAPE::SHAPE(bool INI_T) {
		//defolt
		_Tekstura = false;
		r++;
		if (INI_T == true) {
			init();
		}
	}

	SHAPE::SHAPE(BARVA br, bool INI_T) {
		_Tekstura = false;
		barva = br;
		r++;
		if (INI_T == true) {
			init();
		}
	}

	SHAPE::SHAPE(BARVA br, GLfloat ver[32], bool INI_T) {
		_Tekstura = false;
		barva = br;
		for (int c = 0; c < 32; c++) {
			vert[c] = ver[c];
		}
		r++;
		if (INI_T == true) {
			init();
		}
	}

	SHAPE::~SHAPE() {
		r--;
	}

	void SHAPE::Kot(float __KOT) {
		_Kot = __KOT;
	}

	void SHAPE::poravnajVert() {
		for (int c = 0; c < 25; c += 8) {
			for (int i = 0; i < 3; i++) {
				if (vert[c + i] != predPoravnavoVert[c + i] * 0.666f) {
					predPoravnavoVert[c + i] = vert[c + i];
					vert[c + i] *= 0.666f;
				}
			}
		}
	}

	void SHAPE::setUpdateStaus() {
		update = !update;
	}

	bool SHAPE::getUpdateStatus() {
		return update;
	}

	void SHAPE::Barva(BARVA br) {
		barva = br;
	}

	void SHAPE::operator<<(BARVA br) {
		barva = br;
	}

	void SHAPE::operator<<(const char* pot) {
		potTeksture = (char*)pot;
	}

	void SHAPE::operator<<(GLfloat ver[32]) {
		for (int c = 0; c < 32; c++) {
			vert[c] = ver[c];
		}
	}

	void SHAPE::texture(const char* pot) {
		potTeksture = (char*)pot;
		_Tekstura = true;
	}

	void SHAPE::newCoordinates(GLfloat ver[32]) {
		for (int c = 0; c < 32; c++) {
			vert[c] = ver[c];
		}
	}

	void SHAPE::newShape(const char* pot, GLfloat ver[32]) {
		potTeksture = (char*)pot;
		for (int c = 0; c < 32; c++) {
			vert[c] = ver[c];
		}
	}

	void SHAPE::squareRC(float razdalja = 1.0f, float x = -1.0f, bool zastavica = false) {
		float razlika = 1.0f - (2.0f / razdalja);
		x -= 2.0 / resolution;
		vert[0] = x;
		vert[1] = -1.0 + razlika;
		vert[8] = x;
		vert[9] = 1.0 - razlika;
		vert[16] = x + (2.0f / resolution);
		vert[17] = 1.0 - razlika;
		vert[24] = x + (2.0f / resolution);
		vert[25] = -1.0 + razlika;
	}

	void SHAPE::squareRCT(SquareRCT kv, float texvert[8]) {
		float razlika1 = 1.0 - (2.0 / kv.r1);
		float razlika2 = 1.0 - (2.0 / kv.r2);
		vert[0] = kv.x1;
		vert[1] = 1.0 - razlika1;
		vert[8] = kv.x2;
		vert[9] = 1.0 - razlika2;
		vert[16] = kv.x2;
		vert[17] = -1.0 + razlika2;
		vert[24] = kv.x1;
		vert[25] = -1.0 + razlika1;

		vert[6] = texvert[0];
		vert[7] = texvert[1];
		vert[14] = texvert[2];
		vert[15] = texvert[3];
		vert[22] = texvert[4];
		vert[23] = texvert[5];
		vert[30] = texvert[6];
		vert[31] = texvert[7];
	}

	void SHAPE::squareRCT(SquareRCT kv, vec8f texvert) {
		float razlika1 = 1.0 - (2.0 / kv.r1);
		float razlika2 = 1.0 - (2.0 / kv.r2);
		vert[0] = kv.x1;
		vert[1] = 1.0 - razlika1;
		vert[8] = kv.x2;
		vert[9] = 1.0 - razlika2;
		vert[16] = kv.x2;
		vert[17] = -1.0 + razlika2;
		vert[24] = kv.x1;
		vert[25] = -1.0 + razlika1;

		vert[6] = texvert[0];
		vert[7] = texvert[1];
		vert[14] = texvert[2];
		vert[15] = texvert[3];
		vert[22] = texvert[4];
		vert[23] = texvert[5];
		vert[30] = texvert[6];
		vert[31] = texvert[7];
	}

	void SHAPE::squareRCT(SquareRCT kv) {
		float razlika1 = 1.0 - (2.0 / kv.r1);
		float razlika2 = 1.0 - (2.0 / kv.r2);
		vert[0] = kv.x1;
		vert[1] = 1.0 - razlika1;
		vert[8] = kv.x2;
		vert[9] = 1.0 - razlika2;
		vert[16] = kv.x2;
		vert[17] = -1.0 + razlika2;
		vert[24] = kv.x1;
		vert[25] = -1.0 + razlika1;

		vert[6] = 1.0f;
		vert[7] = 1.0f;
		vert[22] = 0.0f;
		vert[23] = 0.0f;
	}

	void SHAPE::kvadratX(float x = -0.9, float sirina = 0.01) {
		vert[0] = x + (sirina / 2);
		vert[1] = -1.0;
		vert[8] = x - (sirina / 2);
		vert[9] = -1.0;
		vert[16] = x - (sirina / 2);
		vert[17] = 1.0;
		vert[24] = x + (sirina / 2);
		vert[25] = 1.0;
	}

	void SHAPE::kvadratY(float y = -0.9, float sirina = 0.01) {
		vert[0] = -1.0;
		vert[1] = y - (sirina / 2);
		vert[8] = -1.0;
		vert[9] = y + (sirina / 2);
		vert[16] = 1.0;
		vert[17] = y + (sirina / 2);
		vert[24] = 1.0;
		vert[25] = y - (sirina / 2);
	}

	void SHAPE::crta(float x1 = -0.6, float y1 = 0.3, float x2 = 0.4, float y2 = 0.1, float debelina = 0.015) {
		float a = x1 - x2;
		float b = y1 - y2;
		float c = sqrtf((a * a) + (b * b));
		float ka = asinf(b / c);
		float kb = acosf(a / c);
		vert[0] = x1 - ((debelina / 2.0) * kb);
		vert[1] = y1 - ((debelina / 2.0) * ka);
		vert[8] = x1 + ((debelina / 2.0) * kb);
		vert[9] = y1 + ((debelina / 2.0) * ka);
		vert[16] = x2 + ((debelina / 2.0) * kb);
		vert[17] = y2 + ((debelina / 2.0) * ka);
		vert[24] = x2 - ((debelina / 2.0) * kb);
		vert[25] = y2 - ((debelina / 2.0) * ka);
	}

	void SHAPE::squareXY(float x = 0.9, float y = 0.9, float XYdolzina = 1.0) {
		vert[0] = x;
		vert[1] = y - XYdolzina;
		vert[8] = x;
		vert[9] = y;
		vert[16] = x + XYdolzina;
		vert[17] = y;
		vert[24] = x + XYdolzina;
		vert[25] = y - XYdolzina;
	}

	void SHAPE::kvadrat(float x1 = -0.9, float x2 = -0.8, float y1 = 0.9, float y2 = -0.9) {
		vert[0] = x1;
		vert[1] = y1;
		vert[8] = x1;
		vert[9] = y2;
		vert[16] = x2;
		vert[17] = y2;
		vert[24] = x2;
		vert[25] = y1;
	}

	void SHAPE::tocka(float x = -0.6, float y = -0.6, float sirina = 0.05) {
		vert[0] = x - (sirina / 2.0f);
		vert[1] = y - (sirina / 2.0f);
		vert[8] = x - (sirina / 2.0f);
		vert[9] = y + (sirina / 2.0f);
		vert[16] = x + (sirina / 2.0f);
		vert[17] = y + (sirina / 2.0f);
		vert[24] = x + (sirina / 2.0f);
		vert[25] = y - (sirina / 2.0f);
	}

	void SHAPE::n3D() {
		_3D = true;
	}

	void SHAPE::vertecijiSlike(float a[8]) {
		vert[6] = a[0];
		vert[7] = a[1];
		vert[14] = a[2];
		vert[15] = a[3];
		vert[22] = a[4];
		vert[23] = a[5];
		vert[30] = a[6];
		vert[31] = a[7];
	}

	void SHAPE::vertecijiSlike(vec8f a) {
		vert[6] = a[0];
		vert[7] = a[1];
		vert[14] = a[2];
		vert[15] = a[3];
		vert[22] = a[4];
		vert[23] = a[5];
		vert[30] = a[6];
		vert[31] = a[7];
	}

	void SHAPE::Zamik(float a[8]) {
		vert[0] += a[0];
		vert[1] += a[1];
		vert[8] += a[2];
		vert[9] += a[3];
		vert[16] += a[4];
		vert[17] += a[5];
		vert[24] += a[6];
		vert[25] += a[7];
	}

	void SHAPE::init() {
		if (_Tekstura == true) {
			shader = SHADER("default.vert", "default.frag");
		}
		else {
			shader = SHADER("default.vert", "barva.frag", barva);
		}
		if (_Tekstura == true) {
			tekstura.nalozi(potTeksture, GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
			tekstura.dodajShader(shader, "tex0", 0);
		}
	}

	void SHAPE::create() {
		poravnajVert();

		shader.Aktiviraj();

		VAO VAO1;
		VAO1.Aktiviraj();
;
		VBO VBO1(vert, sizeof(vert));
		EBO EBO1(indices, sizeof(indices));

		VAO1.poveziAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
		VAO1.poveziAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		VAO1.poveziAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		VAO1.Deaktiviraj();
		VBO1.Deaktiviraj();
		EBO1.Deaktiviraj();
		GLuint uniID = glGetUniformLocation(shader.ID, "scale");

		glUniform1f(uniID, 0.5f);

		if (_Tekstura) {
			tekstura.Aktiviraj();
		}
		VAO1.Aktiviraj();

		if (_Tekstura) {
			glEnable(GL_BLEND);
			glBlendEquation(GL_FUNC_ADD); // defolt
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_TEXTURE_2D);
		}

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		if (_Tekstura) {
			glDisable(GL_TEXTURE_2D);
		}

		VAO1.Zbrisi();
		VBO1.Zbrisi();
		EBO1.Zbrisi();
		return;
	}

	typedef std::vector<SHAPE> SHAPES;
	typedef std::vector<SHAPE*> SHAPES_ptr;

	void unici_OBLIKE(SHAPES_ptr& a) {
		for (auto b : a) {
			delete b;
		}
		a.clear();
	}
}