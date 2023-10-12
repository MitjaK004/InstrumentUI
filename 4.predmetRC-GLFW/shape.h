#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <functional>
#include "timeline.h"
#include "shader.h"
#include "tekstura.h"
#include "verteksi.h"
#include "vecf.h"

namespace UI {
	class SHAPE;
}
#include "window.h"

#define GL_QUADS 5
#define INIT true

namespace UI {
	extern int r;

	struct SquareRCT {
		float r1;
		float r2;
		float x1;
		float x2;
		int ID = 1;
		float stranicaA();
		float stranicaB();
		float kot();
		int orientacija();
	};

	typedef std::vector<SquareRCT> SquaresRCT;

	SquaresRCT operator+ (SquaresRCT a, SquaresRCT b);
	SquareRCT operator+ (SquareRCT a, SquareRCT b);
	SquareRCT operator- (SquareRCT a, SquareRCT b);
	SquareRCT operator/ (SquareRCT a, float b);
	SquaresRCT operator* (SquaresRCT a, SquaresRCT b);
	void operator++ (SquaresRCT& a);
	void operator+= (SquaresRCT& a, SquaresRCT& b);

	class SHAPE {
	private:
		bool _Tekstura = true;
		bool _3D = false;
		int kiraOblika = 0;
		char* potTeksture = nullptr;
		BARVA barva = { 1, 1, 1, 1 };
		float _Kot = 60.0f;
		GLfloat vert[32] =
		{ //     COORDINATES     /        COLORS      /   TexCoord  //
			-0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,	0.0f, 0.0f, // Lower left corner
			-0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,	0.0f, 1.0f, // Upper left corner
			 0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,	1.0f, 1.0f, // Upper right corner
			 0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,	1.0f, 0.0f  // Lower right corner
		};

		GLuint indices[6] =
		{
			0, 2, 1, // Upper triangle
			0, 3, 2 // Lower triangle
		};
		GLfloat predPoravnavoVert[32] =
		{ //     COORDINATES     /        COLORS      /   TexCoord  //
			-0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,	0.0f, 0.0f, // Lower left corner
			-0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,	0.0f, 1.0f, // Upper left corner
			 0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,	1.0f, 1.0f, // Upper right corner
			 0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,	1.0f, 0.0f  // Lower right corner
		};
		void poravnajVert();
		SHADER shader;
		TEKSTURA tekstura;
		bool update = true;
	public:
		float resolution = 300.0f;
		float mapSize = 64.0f;
		std::function<void()> Naredi = [&] {
			//create();
		};
		void create();
		void init();
		void texture(const char* pot);
		void newCoordinates(GLfloat ver[32]);
		void newShape(const char* pot, GLfloat ver[32]);
		void squareRC(float razdalja, float x, bool zastavica);
		void squareRCT(SquareRCT kv, float texvert[8]);
		void squareRCT(SquareRCT kv, vec8f texvert);
		void squareRCT(SquareRCT kv);
		void kvadratX(float x, float sirina);
		void kvadratY(float y, float sirina);
		void crta(float x1, float y1, float x2, float y2, float debelina);
		void kvadrat(float x1, float x2, float y1, float y2);
		void squareXY(float x, float y, float XYdolzina);
		void tocka(float x, float y, float sirina);
		void Barva(BARVA br);
		void Kot(float __KOT);
		void Zamik(float a[12]);
		void operator << (BARVA br);
		void operator << (const char* pot);
		void operator << (GLfloat ver[32]);
		void n3D();
		void vertecijiSlike(float a[8]);
		void vertecijiSlike(vec8f a);
		void setUpdateStaus();
		bool getUpdateStatus();
		SHAPE(BARVA br, bool INI_T = false);
		SHAPE(BARVA br, GLfloat ver[32], bool INI_T = false);
		SHAPE(const char* pot, bool INI_T = false);
		SHAPE(const char* pot, GLfloat ver[32], bool INI_T = false);
		SHAPE(bool INI_T = false);
		~SHAPE();
	};

	typedef std::vector<SHAPE> SHAPES;
	typedef std::vector<SHAPE*> SHAPES_ptr;

	void unici_OBLIKE(SHAPES_ptr& a);
}