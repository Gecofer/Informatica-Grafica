//****************************************************************************
// grua.h 
//****************************************************************************

#ifndef __GRUA_
#define __GRUA_

#include "objetos.h"

class Grua: public _triangulos3D {

public:
	Grua();
	void draw_grua(int modo, int r1,int g1, int b1, int r2, int g2, int b2, int grosor);
	float giro_base;
	float giro_palo;
	float giro_cilindro;
	float scalate_cable;
	float movimiento_basecable;

protected:
	_cubo base;
	_rotacion palo;
	_cubo cabina;
	_piramide encima_cabina;
	_rotacion cilindro_cabina;
	_rotacion cable;
	_cubo basecable;
};

#endif