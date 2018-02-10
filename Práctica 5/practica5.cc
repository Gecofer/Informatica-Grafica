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
#include <values.h>
#include "camara.h"

// tamaño de los ejes
//const int AXIS_SIZE=5000;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Window_width,Window_height,Front_plane,Back_plane;

int modo = 3; // almacenamos el modo de visualización
int modelo = 0;

bool bpala = true;
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

// VARIABLES NUEVAS PARA LA PRÁCTICA 5
_ply_triangles arrayPractica[4];

_cubo cubo1(15);

int yboton = 0;
int xboton = 0; 
int CamActual = 0;
Camara camaras[3];

int valor = 4;
int gl = -1;
int ObjetoSel = -1; 
int mx = 0;
int zoom = 5;

bool pulsado_derecho = false;
bool pulsado_izquierda = false; 
bool primera = true; 
bool pinta = true;
bool pulsado[4];

// variables que determninan la posicion y tamaño de la ventana X
int UI_window_pos_x=60,UI_window_pos_y=60,UI_window_width=900,UI_window_height=900;


#define MAXNAMES 256

typedef struct {
  int nnms;             // Número de identificadores del objeto
  int nms[MAXNAMES];    // Vector con las identificadores
  float zmin;
  float zmax;
} OBJ;


//**************************************************************************
// 
//***************************************************************************

void clear_window() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************
void projection(){
	if(camaras[CamActual].cenital){
		float zoomp=camaras[CamActual].Observer_distance*0.1;
		glOrtho(zoomp * -Window_width * glutGet(GLUT_WINDOW_WIDTH) / (float) UI_window_width , 
			zoomp * Window_width * glutGet(GLUT_WINDOW_WIDTH) / (float) UI_window_width, 
			zoomp * -Window_height * glutGet(GLUT_WINDOW_HEIGHT) / (float) UI_window_height, 
			zoomp * Window_height * glutGet(GLUT_WINDOW_HEIGHT) / (float) UI_window_height,Front_plane,Back_plane);
	} else {
		glFrustum(-Window_width * glutGet(GLUT_WINDOW_WIDTH) / (float) UI_window_width , 
			Window_width * glutGet(GLUT_WINDOW_WIDTH) / (float) UI_window_width, 
			-Window_height * glutGet(GLUT_WINDOW_HEIGHT) / (float) UI_window_height, 
			Window_height * glutGet(GLUT_WINDOW_HEIGHT) / (float) UI_window_height,Front_plane,Back_plane);
	}
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
	// Front_plane>0  Back_plane>PlanoDelantero)
	// glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);
	projection();
	cout << "Change projection" << endl;
}


//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void change_observer() {
	// posicion del observador
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// glTranslatef(0,0,-Observer_distance);
	// glRotatef(Observer_angle_x,1,0,0);
	// glRotatef(Observer_angle_y,0,1,0);
	camaras[CamActual].setObservador();
	cout << "Observador" << endl;
}


//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis() {
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
			case 1: cubo.draw_puntos(1,0,1,3); break;
			case 2: cubo.draw_aristas(1,0,1,2); break;
			case 3: cubo.draw_solido(1,0,1); break;
			case 4: cubo.draw_solido_ajedrez(1,0,1,0,0,1); break;
		} 
		break;

		case 2:
		switch (modo){
				case 1: pim.draw_puntos(1,0,1,3);break;
				case 2: pim.draw_aristas(1,0,1,2); break;
				case 3: pim.draw_solido(1,0,1); break;
				case 4: pim.draw_solido_ajedrez(1,0,1,0,0,1); break;
		}
		break;

		case 3:
		switch (modo){
			case 1: model_ply_beethoven.draw_puntos(1,0,1,3); break;
			case 2: model_ply_beethoven.draw_aristas(1,0,1,2); break;
			case 3: model_ply_beethoven.draw_solido(1,0,1); break;
			case 4: model_ply_beethoven.draw_solido_ajedrez(1,0,1,0,0,1); break;
		}
		break;

		case 4:
		switch (modo){
				case 1: peon.draw_puntos(1,0,1,3); break;
				case 2: peon.draw_aristas(1,0,1,2); break;
				case 3: peon.draw_solido(1,0,1); break;
				case 4: peon.draw_solido_ajedrez(1,0,1,0,0,1); break;
		}
		break;

		case 5:
		switch (modo){
			case 1: Grua.draw_grua(1, 1, 0, 0, 0, 0, 0, 3); break;
			case 2: Grua.draw_grua(2, 1, 0, 0, 0, 0, 0, 2); break;
			case 3: Grua.draw_grua(3, 1, 0, 0, 0, 0, 0, 0); break;
			case 4: Grua.draw_grua(4, 1, 0, 0, 0, 0, 1, 0); break;
		}
		break;

		case 6:
			cout << "Pintando Beethoven" << endl;
			if(mx == 0){	
				glScalef(0.3,0.3,0.3);
				
				for (int m=0; m<4; m++) {
					glTranslatef(0,15,0);	
					glLoadName(m);
					
					if(ObjetoSel == m){
						arrayPractica[m].draw_solido(1,0,1);
					} else {
						arrayPractica[m].draw_solido(0,0,0);
					}
				}		
			}
		break;

		case 7:
			cout << "Pintando Cuadrado" << endl;
			if(mx == 0){	
				glScalef(0.3,0.3,0.3);
				for(int m=0; m<1; m++) {
					glTranslatef(0,0,0);	
					glLoadName(m);
					if(ObjetoSel == m){
						if (m == 0) {
							//cubo1.draw_solido_ajedrez(1,0,1,0,0,1);
							switch (modo){
								case 1: cubo1.draw_puntos(0.5,0.5,0.5,3); break;
								case 2: cubo1.draw_aristas(0.5,0.5,0.5,2); break;
								case 3: cubo1.draw_solido(0.5,0.5,0.5); break;
								case 4: cubo1.draw_solido_ajedrez(0,0,0,1,0,1); break;
							} 
							glTranslatef(0,0,0);	
						}
					} else {
						if (m == 0){
							//cubo1.draw_solido_ajedrez(1,0,1,0,0,0);
							switch (modo){
								case 1: cubo1.draw_puntos(0,0,0,3); break;
								case 2: cubo1.draw_aristas(0,0,0,2); break;
								case 3: cubo1.draw_solido(0,0,0); break;
								case 4: cubo1.draw_solido_ajedrez(0,0,0,0.5,0.5,0.5); break;
							} 
							glTranslatef(0,0,0);
						}
					}
				}		
			}
		break;

	}
}


//**************************************************************************
//
//***************************************************************************

void draw_scene(void) {
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

void change_window_size(int Ancho1,int Alto1) {
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

void normal_keys(unsigned char Tecla1,int x,int y) {

	switch (toupper(Tecla1)) {
		case 'Q': exit(0); break;

		// Diversos modos de pintar
		case 'P': modo=1; break; // Puntos
		case 'L': modo=2; break; // Lineas/Aristas
		case 'O': modo=3; break; // Solido
		case 'J': modo=4; break; // Ajedrez

		// Dibujar los objetos
		case '1': modelo=3; break; // beethoven (ply 1)
		case '2': modelo=4; break; // peon (objeto por revolucion 2)
		case '3': modelo=5; break; // grua (objeto jerarquico 3)
		case '4': modelo=2; break; // piramide
		case '5': modelo=1; break; // cubo
		case '6': modelo=6; break; // dibujar beethoven para pick
		case '7': modelo=7; break; // dibujar grua para pick
				
		// Para mover la Grua
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

		// Para la cámara
		case 'U': CamActual = (CamActual+1)%2; break;

		// Mover la cámara activa por la escena
		case 'A':camaras[CamActual].Observer_angle_y--; break;
		case 'D':camaras[CamActual].Observer_angle_y++; break;
		case 'W':camaras[CamActual].Observer_angle_x--; break;
		case 'S':camaras[CamActual].Observer_angle_x++; break;	

		case '8':
			camaras[CamActual].Observer_distance=zoom*Front_plane+ Front_plane*2;
			camaras[CamActual].Observer_angle_x=0;
			camaras[CamActual].Observer_angle_y=0;
		break;
		case '9':
			camaras[CamActual].Observer_distance=zoom*Front_plane - Front_plane*2;
			camaras[CamActual].Observer_angle_x=0;
			camaras[CamActual].Observer_angle_y=0;
		break;
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

void special_keys(int Tecla1,int x,int y){
	switch (Tecla1){
		// case GLUT_KEY_LEFT:Observer_angle_y--; break;
		// case GLUT_KEY_RIGHT:Observer_angle_y++; break;
		// case GLUT_KEY_UP:Observer_angle_x--; break;
		// case GLUT_KEY_DOWN:Observer_angle_x++; break;
		// case GLUT_KEY_F6:Observer_distance*=1.2; break;
		// case GLUT_KEY_F5:Observer_distance/=1.2; break;

		case GLUT_KEY_LEFT: camaras[CamActual].Observer_angle_y--; break;
		case GLUT_KEY_RIGHT: camaras[CamActual].Observer_angle_y++; break;
		case GLUT_KEY_UP: camaras[CamActual].Observer_angle_x--; break;
		case GLUT_KEY_DOWN: camaras[CamActual].Observer_angle_x++; break;
		case GLUT_KEY_F6:camaras[CamActual].Observer_distance*=1.2; break;
		case GLUT_KEY_F5: camaras[CamActual].Observer_distance/=1.2; break;
	}

	gl = -1;
	change_projection();

	glutPostRedisplay();
}


//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void) {
	// se inicalizan la ventana y los planos de corte
	Window_width=5;
	Window_height=5;
	Front_plane=10;
	Back_plane=1000;

	// se inicia la posicion del observador, en el eje z
	// Observer_distance=2*Front_plane;
	// Observer_angle_x=0;
	// Observer_angle_y=0;

	// se inicia la posicion del observador, en el eje z
	camaras[CamActual].Observer_distance=zoom*Front_plane;
	camaras[CamActual].Observer_angle_x=0;
	camaras[CamActual].Observer_angle_y=0;

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


//**************************************************************************
// Función de selección
//***************************************************************************
 
int pick (int x, int y) {
	
	int vp[4], nobj;
	GLuint buff[512];

	// Indicamos el buffer de los objetos seleccionados
	glSelectBuffer(512, buff);   

	// Obtener los parámetros del viewport 
	glGetIntegerv(GL_VIEWPORT, vp);
	
	// Realizamos la visualización en modo selección
	glRenderMode(GL_SELECT); 

	// Inicializamos la pila de nombres 
	glInitNames();
	glPushName(-1);
	 
	// Fijar la transformación de proyección para la seleccion
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPickMatrix(x,vp[3]-y,5,5,vp);
	// glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);
	projection();
	glMatrixMode(GL_MODELVIEW);

	// Dibujar la escena
	draw_scene();

	// Restablecer la transformación de proyección (sin gluPickMatrix)
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);
	projection();
	 
	// Ejecutar el movimiento correspondiente a la figura seleccionada
	nobj = glRenderMode(GL_RENDER);
	 
	OBJ obj;
	int i, k, omin;
	float zmin = MAXFLOAT;
	int ins;

	omin = -1;
	k = i = 0;

	while (k < nobj) {
		ins = 0;
		obj.nnms = buff[i++];
		obj.zmin = (float)buff[i++]/0xFFFFFFFF;
		obj.zmax = (float)buff[i++]/0xFFFFFFFF;

		if(obj.zmin < zmin) {
			ins = 1;
			for(int j=0; j<obj.nnms; j++) {	
				obj.nms[j] = buff[i++];
				if(ins && obj.nms[j] >= 0) {
					omin = obj.nms[j];
				}
			}
		}

		k++;
	}

	if(omin == ObjetoSel){
		omin = -1;
	}

	cout << "PICK " << omin << endl; 

	primera = false;	

	return omin;
}


//**************************************************************************
// Gestionar los eventos de movimiento del raton.
//***************************************************************************

void ratonMovido (int x, int y) {
	if(pulsado_derecho){
		camaras[CamActual].Observer_angle_y = x+xboton;
		camaras[CamActual].Observer_angle_x = y+yboton;
		yboton= y;
		xboton=x;
	}

	mx = 0;
	glutPostRedisplay();
}


//**************************************************************************
// Gestionar los eventos de pulsacion de los botones del raton.
//***************************************************************************

void clickRaton (int boton, int state, int x, int y) {
	if (boton == GLUT_MIDDLE_BUTTON) {
        if (state == GLUT_DOWN) {
        	camaras[CamActual].Observer_distance*=1.0115;
        }

        if (boton == GLUT_MIDDLE_BUTTON) {
        	if (state == GLUT_UP) {
        		camaras[CamActual].Observer_distance*=1.0115;
        	}
        }
    }

	if(boton == GLUT_RIGHT_BUTTON) {
		if(state == GLUT_DOWN){
			// ObjetoSel = pick(x,y);
			pulsado_derecho = true;
		}
	} else {
		if(boton == GLUT_LEFT_BUTTON){
			if(state == GLUT_DOWN){
				pulsado_derecho=false;
				ObjetoSel =pick(x,y);
			}
		} else {
			if (boton == 3)
				camaras[CamActual].Observer_distance/=1.2;
			else if(boton==4)
				camaras[CamActual].Observer_distance*=1.2;

			pulsado_derecho=false;
		}
	}

	glutPostRedisplay();
}


//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************

int main(int argc, char **argv) {

	camaras[1].cenital=true;
	_ply_triangles bet1("beethoven.ply");
	_ply_triangles bet2("beethoven.ply");
	_ply_triangles bet3("beethoven.ply");
	_ply_triangles bet4("beethoven.ply");
	arrayPractica[0] = bet1;
	arrayPractica[1] = bet2;
	arrayPractica[2] = bet3;
	arrayPractica[3] = bet4;
	for(int i=0;i<4;i++){
		pulsado[i]=false;
	}

	camaras[1].cenital=true;
	_cubo cubo1(5);
	for(int i=0;i<1;i++){
		pulsado[i]=false;
	}

	// se llama a la inicialización de glut
	glutInit(&argc, argv);

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
	glutCreateWindow("Practica 5 - Gema Correa Fernandez");

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

	// funciones que procesan los callback de ratón
	glutMouseFunc(clickRaton);
	glutMotionFunc(ratonMovido);

	// inicio del bucle de eventos
	glutMainLoop();
	return 0;
}
