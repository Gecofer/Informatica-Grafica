//**************************************************************************
// Práctica 4 usando objetos
//**************************************************************************

#include <vector>
#include <string>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>
#include "jpg_imagen.hpp"
#include "file_ply_stl.h"

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

		// Funciones para dibujar
		void draw_aristas(float r, float g, float b, int grosor);
		void draw_solido(float r, float g, float b);
		void draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2);

		// Funciones para iluminación
		void calcular_normales_caras();
		void calcular_normales_vertices();
		void draw_iluminacion_plana();
		void draw_iluminacion_suave();

		//Funciones para textura
		void draw_textura(GLuint ident_textura, jpg::Imagen*& imagen);
		void draw_textura_ilum_plana(GLuint ident_textura, jpg::Imagen*& imagen);
		void draw_textura_ilum_suave(GLuint ident_textura, jpg::Imagen*& imagen);

    	// Atributos para iluminación
    	vector <_vertex3f> normales_caras;
    	vector<_vertex3f> normales_vertices;
    	bool b_textura_coord;
    	bool b_normales_caras;
    	bool b_normales_vertices;
    
    	// Atributos para texturas
	    GLfloat coefs_s[4], coefs_t[4]; 
	    vector<_vertex2f> textura_coord; 
	    bool mode_text;

	    // Atributos para textura e iluminación
	    _vertex4f ambiente_difusa; // coeficientes ambiente y difuso
	    _vertex4f especular; // coeficiente especular
	    float brillo; // exponente del brillo
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


//*************************************************************************
// 				Clase Rotacion Textura
//*************************************************************************

class _rotacion_text: public _triangulos3D{
	public:
		_rotacion_text();
		_rotacion_text(vector<_vertex3f> ver, int num_caras);
};


//*************************************************************************
// 				Clase Textura
//*************************************************************************

class textura: public _triangulos3D{
	public:

		GLuint ident_textura; // Entero que asigna OpenGL a la textura
		jpg::Imagen * imagen; // imagen a leer
	
		textura();
  	
  		// Método para leer una imágen y poder usarla con OpenGL 
  		textura(const char * archivoJPG);
};



