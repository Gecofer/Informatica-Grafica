#ifndef _CAMARA_
#define _CAMARA_

#include <GL/gl.h>
#include <vector>
#include <iostream>

using namespace std;
class Camara
{
	private:
	
	public:
	// variables que definen la posicion de la camara en coordenadas polares
	GLfloat Observer_distance;
	GLfloat Observer_angle_x;
	GLfloat Observer_angle_y;
	bool cenital;
	// variables que controlan la ventana y la transformacion de perspectiva
	GLfloat Window_width,Window_height,Front_plane,Back_plane;
	
	Camara();
	void girar();
	
	void setObservador();
};

#endif
