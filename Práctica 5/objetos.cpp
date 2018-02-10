#include <vector>
#include <GL/gl.h>
#include "objetos.h"
#include "vertex.h"
#include <stdlib.h>
#include <cmath>

/*************************************************************************
 								Clase Punto
*************************************************************************/

_puntos3D::_puntos3D(){}

// Función para dibujar los puntos de un polígono
void _puntos3D::draw_puntos(float r, float g, float b, int grosor){
	glPointSize(grosor);
	glColor3f(r,g,b);
	glBegin(GL_POINTS);
		for (int i = 0; i < vertices.size(); i++){
			glVertex3fv((GLfloat*)&vertices[i]);
		}
	glEnd();
}


/*************************************************************************
 								Clase Triángulo
*************************************************************************/

_triangulos3D::_triangulos3D(){}

// Función para dibujar las líneas de un polígono
void _triangulos3D::draw_aristas(float r, float g, float b, int grosor){
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(grosor);
	glColor3f(r,g,b);
	glBegin(GL_TRIANGLES);
		for(int i = 0; i < caras.size(); i++){
			glVertex3fv((GLfloat*)&vertices[caras[i]._0]);
			glVertex3fv((GLfloat*)&vertices[caras[i]._1]);
			glVertex3fv((GLfloat*)&vertices[caras[i]._2]);
		}
	glEnd();
}

// Función para dibujar un polígono con color uniforme
void _triangulos3D::draw_solido(float r, float g, float b){
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor3f(r,g,b);
	glBegin(GL_TRIANGLES);
		for(int i = 0; i < caras.size(); i++){
			glVertex3fv((GLfloat*)&vertices[caras[i]._0]);
			glVertex3fv((GLfloat*)&vertices[caras[i]._1]);
			glVertex3fv((GLfloat*)&vertices[caras[i]._2]);
		}
	glEnd();
}

// Función para dibujar un polígono con color tipo ajedrez
void _triangulos3D::draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2){
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLES);
		for(int i = 0; i < caras.size(); i++){
			if(i%2 == 0){
				glColor3f(r1,g1,b1);
			}else{
				glColor3f(r2,g2,b2);
			}
			glVertex3fv((GLfloat*)&vertices[caras[i]._0]);
			glVertex3fv((GLfloat*)&vertices[caras[i]._1]);
			glVertex3fv((GLfloat*)&vertices[caras[i]._2]);
		}
	glEnd();
}

/*************************************************************************
 								Clase Cubo
*************************************************************************/

_cubo::_cubo() {

	float tam = 3;

	float half = tam/2;
	float mhalf = -half;
	vertices.resize(8);
	vertices[0].x = mhalf; 	vertices[0].y = mhalf; 	vertices[0].z = half;
	vertices[1].x = half; 	vertices[1].y = mhalf;	vertices[1].z = half;
	vertices[2].x = mhalf; 	vertices[2].y = half; 	vertices[2].z = half;
	vertices[3].x = half; 	vertices[3].y = half; 	vertices[3].z = half;
	vertices[4].x = half; 	vertices[4].y = half; 	vertices[4].z = mhalf;
	vertices[5].x = mhalf; 	vertices[5].y = half; 	vertices[5].z = mhalf;
	vertices[6].x = half; 	vertices[6].y = mhalf; 	vertices[6].z = mhalf;
	vertices[7].x = mhalf; 	vertices[7].y = mhalf; 	vertices[7].z = mhalf;

	caras.resize(12);
	caras[0]._0= 0; caras[0]._1= 1; caras[0]._2= 2;
	caras[1]._0= 1; caras[1]._1= 3; caras[1]._2= 2;

	caras[2]._0= 1; caras[2]._1= 4; caras[2]._2= 3;
	caras[3]._0= 1; caras[3]._1= 6; caras[3]._2= 4;

	caras[4]._0= 4; caras[4]._1= 6; caras[4]._2= 5;
	caras[5]._0= 6; caras[5]._1= 7; caras[5]._2= 5;

	caras[6]._0= 7; caras[6]._1= 0; caras[6]._2= 5;
	caras[7]._0= 0; caras[7]._1= 2; caras[7]._2= 5;

	caras[8]._0= 2; caras[8]._1= 3; caras[8]._2= 5;
	caras[9]._0= 3; caras[9]._1= 4; caras[9]._2= 5;

	caras[10]._0= 7; caras[10]._1= 6; caras[10]._2= 1;
	caras[11]._0= 7; caras[11]._1= 1; caras[11]._2= 0;

}

_cubo::_cubo(float tam){
	float half = tam/2;
	float mhalf = -half;
	vertices.resize(8);
	vertices[0].x = mhalf; 	vertices[0].y = mhalf; 	vertices[0].z = half;
	vertices[1].x = half; 	vertices[1].y = mhalf;	vertices[1].z = half;
	vertices[2].x = mhalf; 	vertices[2].y = half; 	vertices[2].z = half;
	vertices[3].x = half; 	vertices[3].y = half; 	vertices[3].z = half;
	vertices[4].x = half; 	vertices[4].y = half; 	vertices[4].z = mhalf;
	vertices[5].x = mhalf; 	vertices[5].y = half; 	vertices[5].z = mhalf;
	vertices[6].x = half; 	vertices[6].y = mhalf; 	vertices[6].z = mhalf;
	vertices[7].x = mhalf; 	vertices[7].y = mhalf; 	vertices[7].z = mhalf;

	caras.resize(12);
	caras[0]._0= 0; caras[0]._1= 1; caras[0]._2= 2;
	caras[1]._0= 1; caras[1]._1= 3; caras[1]._2= 2;

	caras[2]._0= 1; caras[2]._1= 4; caras[2]._2= 3;
	caras[3]._0= 1; caras[3]._1= 6; caras[3]._2= 4;

	caras[4]._0= 4; caras[4]._1= 6; caras[4]._2= 5;
	caras[5]._0= 6; caras[5]._1= 7; caras[5]._2= 5;

	caras[6]._0= 7; caras[6]._1= 0; caras[6]._2= 5;
	caras[7]._0= 0; caras[7]._1= 2; caras[7]._2= 5;

	caras[8]._0= 2; caras[8]._1= 3; caras[8]._2= 5;
	caras[9]._0= 3; caras[9]._1= 4; caras[9]._2= 5;

	caras[10]._0= 7; caras[10]._1= 6; caras[10]._2= 1;
	caras[11]._0= 7; caras[11]._1= 1; caras[11]._2= 0;
}


/*************************************************************************
 								Clase Piramide
*************************************************************************/

_piramide::_piramide(float tam, float al){
	vertices.resize(5);
	vertices[0].x = -tam; 	vertices[0].y = 0; 	vertices[0].z = tam;
	vertices[1].x = tam; 	vertices[1].y = 0; 	vertices[1].z = tam;
	vertices[2].x = tam; 	vertices[2].y = 0; 	vertices[2].z = -tam;
	vertices[3].x = -tam; 	vertices[3].y = 0; 	vertices[3].z = -tam;
	vertices[4].x = 0; 		vertices[4].y = al; vertices[4].z = 0;

	caras.resize(6);
	caras[0]._0= 0; caras[0]._1= 1; caras[0]._2= 4;
	caras[1]._0= 1; caras[1]._1= 2; caras[1]._2= 4;
	caras[2]._0= 2; caras[2]._1= 3; caras[2]._2= 4;
	caras[3]._0= 3; caras[3]._1= 0; caras[3]._2= 4;
	caras[4]._0= 0; caras[4]._1= 3; caras[4]._2= 2;
	caras[5]._0= 0; caras[5]._1= 2; caras[5]._2= 1;
}


/*************************************************************************
 				Funcion para importar y modelar un .ply
*************************************************************************/

_ply_triangles::_ply_triangles () {}

_ply_triangles::_ply_triangles (char *file) {

	vector<float> v;
	vector<int> c;

	// Para leer el fichero
	_file_ply fichero;
	fichero.open(file);

	// Obtenemos los vértices del fichero .ply
	fichero.read(v,c);

	_vertex3f vert;
	for (int i=0; i<v.size(); i+=3){
		vert.x = v[i];
        vert.y = v[i+1];
        vert.z = v[i+2];

       	vertices.push_back(vert);
	}

	_vertex3i car;
	for (int i=0; i<c.size(); i+=3){
		car.x = c[i];
        car.y = c[i+1];
        car.z = c[i+2];

        caras.push_back(car);
	}
}


/*************************************************************************
 				Funcion para rotacion
*************************************************************************/

_rotacion::_rotacion(){}

_rotacion::_rotacion(vector<_vertex3f> perfil, int num) { 
  	int i, j; 
  	_vertex3f vertice_aux; 
  	_vertex3i caras_aux; 
  	int num_aux; 
 
  	num_aux = perfil.size(); 
  	vertices.resize(num_aux * num); 
  	for (j = 0; j < num; j++) { 
    	for (i = 0; i < num_aux; i++) { 
      		vertice_aux.x = perfil[i].x * cos(2.0 * M_PI * j / (1.0 * num)) + 
                      		perfil[i].z * sin(2.0 * M_PI * j / (1.0 * num)); 
      		vertice_aux.y = perfil[i].y; 
      		vertice_aux.z = perfil[i].z * cos(2.0 * M_PI * j / (1.0 * num)) - 
                      		perfil[i].x * sin(2.0 * M_PI * j / (1.0 * num)); 
      		vertices[i + j * num_aux] = vertice_aux; 
    	} 
 	 } 
 
  	// caras 
  	for (j = 0; j < num; j++) { 
    	for (i = 0; i < num_aux - 1; i++) { 
      		caras_aux._0 = i + ((j + 1) % num) * num_aux; 
      		caras_aux._1 = i + 1 + ((j + 1) % num) * num_aux; 
      		caras_aux._2 = i + 1 + j * num_aux; 
      		caras.push_back(caras_aux); 
 
      		caras_aux._0 = i + 1 + j * num_aux; 
      		caras_aux._1 = i + j * num_aux; 
      		caras_aux._2 = i + ((j + 1) % num) * num_aux; 
      		caras.push_back(caras_aux); 
    	} 
  	} 
 
  	// tapa inferior 
  	if (fabs(perfil[num_aux - 1].x) > 0.0) { 
    	vertice_aux.y = perfil[num_aux - 1].y; 
    	vertice_aux.x = 0.0; 
    	vertice_aux.z = 0.0; 
    	vertices.push_back(vertice_aux); 
 
    	caras_aux._0 = num_aux * num; 
 
    	for (int i = 0; i < num; i++) { 
      	caras_aux._1 = (i + 1) * num_aux - 1; 
      	caras_aux._2 = ((i + 1) % num) * num_aux + num_aux - 1; 
      	caras.push_back(caras_aux); 
    	}
  	}
    
    // tapa superior
    if (fabs(perfil[0].x) > 0.0) {
        vertice_aux.y = perfil[0].y;
        vertice_aux.x = 0.0;
        vertice_aux.z = 0.0;
        vertices.push_back(vertice_aux);
        
        caras_aux._0 = num_aux * num + 1;
        
        for (int i = 0; i < num; i++) {
            caras_aux._1 = ((i + 1) % num) * num_aux;
            caras_aux._2 = i * num_aux;
            caras.push_back(caras_aux);
        }
    }
}