//****************************************************************************
// grua.cpp
//****************************************************************************

#include "grua.h"

using namespace std;

// Constructor
Grua::Grua(){

	// Inicializamos del valor del giro
	giro_base = 0;
	giro_palo = 0;
	giro_cilindro = 0;
	scalate_cable = 1;
	movimiento_basecable = 3;

  	/**
  	 * Creación de los Objetos
  	 */

  	vector<_vertex3f> vertices_base, vertices_palo, vertices_cilindro_cabina, vertices_cable;
  	_vertex3f vertice;

  	// BASE
  	// La base nos la creamos en el draw, al ser una fugura que no está creada

	// PALO
	vertice.x = 0.65;
	vertice.y = 8;
	vertice.z = 0;

	vertices_palo.push_back(vertice);

  	vertice.x = 0.65;
  	vertice.y = 0;
  	vertice.z = 0;

  	vertices_palo.push_back(vertice);
  	palo = _rotacion(vertices_palo,10);

  	// CABINA
  	encima_cabina = _piramide(1,2);

  	// PALO DE LA GRUA
  	vertice.x = 0.5;
  	vertice.y = 12;
  	vertice.z = 0;

  	vertices_cilindro_cabina.push_back(vertice);
  	
  	vertice.x = 0.5;
  	vertice.y = 0;
  	vertice.z = 0;

  	vertices_cilindro_cabina.push_back(vertice);
  	cilindro_cabina = _rotacion(vertices_cilindro_cabina,10);
  
  	// CABLE
  	vertice.x = 0.1;
  	vertice.y = 4.5;
  	vertice.z = 0;

  	vertices_cable.push_back(vertice);

  	vertice.x = 0.1;
  	vertice.y = 0;
  	vertice.z = 0;

  	vertices_cable.push_back(vertice);
  	cable = _rotacion(vertices_cable,10);
  
  	//BASE DEL CABLE
  	basecable = _cubo(1);
}

void Grua::draw_grua(int modo,int r1,int g1, int b1, int r2, int g2, int b2, int grosor) {
	// Dibujamos los objetos

	glRotatef(giro_base,0,1,0);
    
    // BASE
    glPushMatrix(); // push base
    glTranslatef(0,0,0);
    glScalef(3,0.1,3);

    switch(modo){
    	case 1: // Pintar Puntos
			base.draw_puntos(1,0,0,2);
			break;
		case 2: // Pintar Aristas
			base.draw_aristas(1,0,0,2);
			break;
		case 3: // Pintar Solido
			base.draw_solido(1,0,0);
			break;
		case 4: // Pintar Ajedrez
			base.draw_solido_ajedrez(0.6,0.6,0.6,0,0,1);
			break;
	}

	glPopMatrix(); // pop base
    
    // PALO
    glRotatef(giro_palo,1,0,0); // push palo
    glPushMatrix();
	glTranslatef(0,0,0);
	
	switch(modo){
    	case 1: // Pintar Puntos
			palo.draw_puntos(0.75,0.75,0.75,3);
			break;
		case 2: // Pintar Aristas
			palo.draw_aristas(0.75,0.75,0.75,2);
			break;
		case 3: // Pintar Solido
			palo.draw_solido(0.75,0.75,0.75);
			break;
		case 4: // Pintar Ajedrez
			palo.draw_solido_ajedrez(0.75,0.75,0.75,0,0,1);
			break;
	}
           
    glPopMatrix(); // pop palo
    glRotatef(giro_cilindro,0,1,0);
                 
    // CABINA
    glPushMatrix(); // push cabina
    glTranslatef(0,8,0);

   	switch(modo){
    	case 1: // Pintar Puntos
			encima_cabina.draw_puntos(0.1,0.65,0.75,3);
			break;
		case 2: // Pintar Aristas
			encima_cabina.draw_aristas(0.1,0.65,0.75,2);
			break;
		case 3: // Pintar Solido
			encima_cabina.draw_solido(0.1,0.65,0.75);
			break;
		case 4: // Pintar Ajedrez
			encima_cabina.draw_solido_ajedrez(0.1,0.65,0.75,0,0,1);
			break;
	}
                   
    glPopMatrix(); // pop palo
    
    // PALO DE LA GRUA
    glPushMatrix(); // push palo grua
    glTranslatef(-2,6.43,0);
    glRotatef(90,0,0,-1);

    switch(modo){
    	case 1: // Pintar Puntos
			cilindro_cabina.draw_puntos(0.75,0.75,0.75,3);
			break;
		case 2: // Pintar Aristas
			cilindro_cabina.draw_aristas(0.75,0.75,0.75,2);
			break;
		case 3: // Pintar Solido
			cilindro_cabina.draw_solido(0.75,0.75,0.75);
			break;
		case 4: // Pintar Ajedrez
			cilindro_cabina.draw_solido_ajedrez(0.75,0.75,0.75,0,0,1);
			break;
	}
               
    glPopMatrix(); // push palo grua

   	// BASE DEL CABLE
    glTranslatef(movimiento_basecable,5.43,0);
    glPushMatrix(); // push base del cable

    switch(modo){
    	case 1: // Pintar Puntos
			basecable.draw_puntos(0,0,0.3,3);
			break;
		case 2: // Pintar Aristas
			basecable.draw_aristas(0,0,0.3,2);
			break;
		case 3: // Pintar Solido
			basecable.draw_solido(0,0,0.3);
			break;
		case 4: // Pintar Ajedrez
			basecable.draw_solido_ajedrez(0,0,0.3,0,0,1);
			break;
	}
                   
    glPopMatrix(); // pop cable
    
    // CABLE
    glPushMatrix(); // push cable

    glTranslatef(0,0.55,0);
    glScalef(1,-scalate_cable,1);
    
    switch(modo){
    	case 1: // Pintar Puntos
			cable.draw_puntos(0,0,0,3);
			break;
		case 2: // Pintar Aristas
			cable.draw_aristas(0,0,0,2);
			break;
		case 3: // Pintar Solido
			cable.draw_solido(0,0,0);
			break;
		case 4: // Pintar Ajedrez
			cable.draw_solido_ajedrez(0,0,0,0,0,1);
			break;
	}
           
    glPopMatrix(); // pop cable
}
