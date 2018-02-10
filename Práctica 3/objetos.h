//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>

using namespace std;

const float AXIS_SIZE=5000;

//*************************************************************************
// 				Clase Punto
//*************************************************************************

class _puntos3D{
	public:
		vector<_vertex3f> vertices;

		_puntos3D();
		void draw_puntos(float r, float g, float b, int grosor);
};

//*************************************************************************
// 				Clase Triángulo
//*************************************************************************

class _triangulos3D: public _puntos3D{
	public:
		vector<_vertex3i> caras;

		_triangulos3D();
		void draw_aristas(float r, float g, float b, int grosor);
		void draw_solido(float r, float g, float b);
		void draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2);
};


//*************************************************************************
// 				Clase Cubo
//*************************************************************************

class _cubo: public _triangulos3D{
	public:
		_cubo(float tam=1);
};


//*************************************************************************
// 				Clase Piramide
//*************************************************************************

class _piramide: public _triangulos3D{
	public:
		_piramide(float tam=1, float a=1);
};


//*************************************************************************
// 				Clase PLY
//*************************************************************************

class _ply_triangles: public _triangulos3D{
	public:
		_ply_triangles(char *file);
};


//*************************************************************************
// 				Clase Rotacion
//*************************************************************************

class _rotacion: public _triangulos3D{
	public:
		_rotacion();
		_rotacion(vector<_vertex3f> perfil, int num);
};


