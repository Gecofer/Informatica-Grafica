//**************************************************************************
// Práctica 1
//
// Domingo Martin Perandres 2013-2016
//
// GPL
//**************************************************************************

#include "stdlib.h"
#include "stdio.h"
#include "file_ply_stl.h"
#include "vertex.h"
#include "grua.h"
#include <GL/glut.h>
#include <ctype.h>

// tamaño de los ejes
//const int AXIS_SIZE=5000;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Window_width,Window_height,Front_plane,Back_plane;

int modo=3; // almacenamos el modo de visualización
int modelo = 0;

bool bpala =true;
bool bplataforma  =true;

_piramide pim(3,3);
_cubo cubo(3);

_ply_triangles model_ply_beethoven("beethoven.ply");
_ply_triangles model_ply_peon("peon.ply");

_rotacion peon(model_ply_peon.vertices,30);

Grua Grua;

float girox=0;
float giroy=0;
float giroz=0;

// variables que determninan la posicion y tamaño de la ventana X
int UI_window_pos_x=60,UI_window_pos_y=60,UI_window_width=900,UI_window_height=900;

//**************************************************************************
//
//***************************************************************************

void clear_window()
{

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{

glMatrixMode(GL_PROJECTION);
glLoadIdentity();

// formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
//  Front_plane>0  Back_plane>PlanoDelantero)
glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{

// posicion del observador
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(0,0,-Observer_distance);
glRotatef(Observer_angle_x,1,0,0);
glRotatef(Observer_angle_y,0,1,0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{
glBegin(GL_LINES);
// eje X, color rojo
glColor3f(1,0,0);
glVertex3f(-AXIS_SIZE,0,0);
glVertex3f(AXIS_SIZE,0,0);
// eje Y, color verde
glColor3f(0,1,0);
glVertex3f(0,-AXIS_SIZE,0);
glVertex3f(0,AXIS_SIZE,0);
// eje Z, color azul
glColor3f(0,0,1);
glVertex3f(0,0,-AXIS_SIZE);
glVertex3f(0,0,AXIS_SIZE);
glEnd();
}


//**************************************************************************
// Funcion que dibuja los objetos
//***************************************************************************

void draw_objects(){

	switch(modelo){

		case 1:
		switch (modo){
				case 1: //Puntos
					cubo.draw_puntos(1,0,1,3);
					break;
				case 2: //Aristas
					cubo.draw_aristas(1,0,1,2);
					break;
				case 3: //Solido
					cubo.draw_solido(1,0,1);
					break;
				case 4: //Ajedrez
					cubo.draw_solido_ajedrez(1,0,1,0,0,1);
					break;
			}
		break;

		case 2:
		switch (modo){
				case 1: //Puntos
					pim.draw_puntos(1,0,1,3);
					break;
				case 2: //Aristas
					pim.draw_aristas(1,0,1,2);
					break;
				case 3: //Solido
					pim.draw_solido(1,0,1);
					break;
				case 4: //Ajedrez
					pim.draw_solido_ajedrez(1,0,1,0,0,1);
					break;
			}
		break;

		case 3:
		switch (modo){
				case 1: //Puntos
					model_ply_beethoven.draw_puntos(1,0,1,3);
					break;
				case 2: //Aristas
					model_ply_beethoven.draw_aristas(1,0,1,2);
					break;
				case 3: //Solido
					model_ply_beethoven.draw_solido(1,0,1);
					break;
				case 4: //Ajedrez
					model_ply_beethoven.draw_solido_ajedrez(1,0,1,0,0,1);
					break;
			}
		break;

		case 4:
		switch (modo){
				case 1: //Puntos
					peon.draw_puntos(1,0,1,3);
					break;
				case 2: //Aristas
					peon.draw_aristas(1,0,1,2);
					break;
				case 3: //Solido
					peon.draw_solido(1,0,1);
					break;
				case 4: //Ajedrez
					peon.draw_solido_ajedrez(1,0,1,0,0,1);
					break;
			}
		break;

		case 5:
			switch (modo){
				case 1: //Puntos
					Grua.draw_grua(1, 1, 0, 0, 0, 0, 0, 3);
					break;
				case 2: //Aristas
					Grua.draw_grua(2, 1, 0, 0, 0, 0, 0, 2);
					break;
				case 3: //Solido
					Grua.draw_grua(3, 1, 0, 0, 0, 0, 0, 0);
					break;
				case 4: //Ajedrez
					Grua.draw_grua(4, 1, 0, 0, 0, 0, 1, 0);
					break;
			}
		break;

	}
}


//**************************************************************************
//
//***************************************************************************

void draw_scene(void)
{

clear_window();
change_observer();
draw_axis();
draw_objects();
glutSwapBuffers();
}



//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1,int Alto1)
{
change_projection();
glViewport(0,0,Ancho1,Alto1);
glutPostRedisplay();
}


//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_keys(unsigned char Tecla1,int x,int y)
{

	switch (toupper(Tecla1)) {
				case 'Q': exit(0); break;
				case 'P': modo=1; break; // Puntos
				case 'L': modo=2; break; // Lineas/Aristas
				case 'S': modo=3; break; // Solido
				case 'A': modo=4; break; // Ajedrez
				case '4': modelo=2; break; // piramide
				case '5': modelo=1; break; // cubo
				case '1': modelo=3; break; // beethoven (ply 1)
				case '2': modelo=4; break; // peon (objeto por revolucion 2)
				case '3': modelo=5; break; // grua (objeto jerarquico 3)

				//case 'Z': if(giroz<30 && bpala)giroz++;else{ giroz--;bpala=false;if(giroz==0)bpala=true;} break;
				//case 'X': if(girox<10 && bplataforma)girox++;else{ girox--;bplataforma=false;if(girox==0)bplataforma=true;} break;
				//case 'C': giroy++; break;

				case 'C': Grua.giro_cilindro++;
					if(Grua.giro_cilindro > 180) Grua.giro_cilindro = 180; break;

				case 'Z': Grua.movimiento_basecable++;
					if(Grua.movimiento_basecable > 10) Grua.movimiento_basecable = 10; break;
				case 'N': Grua.movimiento_basecable --;
					if(Grua.movimiento_basecable < 2) Grua.movimiento_basecable = 2; break;

				case 'X': Grua.scalate_cable += 0.2;
					if(Grua.scalate_cable > 2) Grua.scalate_cable = 2; break;
				case 'B': Grua.scalate_cable -= 0.2;
					if(Grua.scalate_cable < 1) Grua.scalate_cable = 1; break;
	}

	glutPostRedisplay();
}

//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_keys(int Tecla1,int x,int y)
{

switch (Tecla1){
	case GLUT_KEY_LEFT:Observer_angle_y--;break;
	case GLUT_KEY_RIGHT:Observer_angle_y++;break;
	case GLUT_KEY_UP:Observer_angle_x--;break;
	case GLUT_KEY_DOWN:Observer_angle_x++;break;
	case GLUT_KEY_F6:Observer_distance*=1.2;break;
	case GLUT_KEY_F5:Observer_distance/=1.2;break;
	}
glutPostRedisplay();
}



//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{
// se inicalizan la ventana y los planos de corte
Window_width=5;
Window_height=5;
Front_plane=10;
Back_plane=1000;

// se inicia la posicion del observador, en el eje z
Observer_distance=2*Front_plane;
Observer_angle_x=0;
Observer_angle_y=0;

// se indica cual sera el color para limpiar la ventana	(r,v,a,al)
// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
glClearColor(1,1,1,1);

// se habilita el z-bufer
glEnable(GL_DEPTH_TEST);
//
change_projection();
//
glViewport(0,0,UI_window_width,UI_window_height);


}


//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************

int main(int argc, char **argv)
{

// se llama a la inicialización de glut
glutInit(&argc, argv);

/*
MAIN
ply.parametrox(argv[1]);
*/

// se indica las caracteristicas que se desean para la visualización con OpenGL
// Las posibilidades son:
// GLUT_SIMPLE -> memoria de imagen simple
// GLUT_DOUBLE -> memoria de imagen doble
// GLUT_INDEX -> memoria de imagen con color indizado
// GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
// GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
// GLUT_DEPTH -> memoria de profundidad o z-bufer
// GLUT_STENCIL -> memoria de estarcido
glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

// posicion de la esquina inferior izquierdad de la ventana
glutInitWindowPosition(UI_window_pos_x,UI_window_pos_y);

// tamaño de la ventana (ancho y alto)
glutInitWindowSize(UI_window_width,UI_window_height);

// llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
// al bucle de eventos)
glutCreateWindow("Practica 3 - Gema Correa Fernandez");

// asignación de la funcion llamada "dibujar" al evento de dibujo
glutDisplayFunc(draw_scene);
// asignación de la funcion llamada "cambiar_tamanio_ventana" al evento correspondiente
glutReshapeFunc(change_window_size);
// asignación de la funcion llamada "tecla_normal" al evento correspondiente
glutKeyboardFunc(normal_keys);
// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
glutSpecialFunc(special_keys);

// funcion de inicialización
initialize();

// inicio del bucle de eventos
glutMainLoop();
return 0;
}
