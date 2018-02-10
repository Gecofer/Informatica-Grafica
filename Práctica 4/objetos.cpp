#include <vector>
#include <GL/gl.h>
#include "objetos.h"
#include "vertex.h"
#include <stdlib.h>
#include <cmath>
#include "jpg_imagen.hpp"

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

_triangulos3D::_triangulos3D(){
    b_normales_caras = false;
    b_normales_vertices = false;
    b_textura_coord = false;

    /*
    ambiente_difusa = _vertex4f(0.3,0.8,0.8,1.0);
    brillo = 40;
    especular = _vertex4f(0.7,0.7,0.7,1.0);
    */

    ambiente_difusa = _vertex4f(1,1,1,1);
    brillo = 40;
    especular = _vertex4f(1,1,1,1);

    mode_text = true;

    for(int i=0; i<4;i++) {
        coefs_s[i]=0.0;
        coefs_t[i]=0.0;
    }
    
    coefs_t[1] = 1.0;
    coefs_s[0] = 1.0;
}

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

  float max_x, min_x, max_y, min_y;
  max_x = min_x = vertices[0].x;
  max_y = max_y = vertices[0].y;

  for (int i=0; i<v.size(); i++){
    if (vertices[i].x > max_x)
        max_x=vertices[i].x;
    if (vertices[i].x < min_x)
        min_x=vertices[i].x;
    if (vertices[i].y > max_y)
        max_y=vertices[i].y;
    if (vertices[i].y < min_y)
        min_y=vertices[i].y;
  }

  coefs_s[0] /= (max_x-min_x);
  coefs_t[1] /= (max_y-min_y);
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


/*************************************************************************
 				Métodos _trtiangulos3D
*************************************************************************/

// Calcular las normales de la cara
void _triangulos3D::calcular_normales_caras() {
	normales_caras.resize(caras.size());

	for(unsigned long i=0;i<caras.size();i++){
		// obtener dos vectores en el triángulo y calcular el producto vectorial
    	_vertex3f
        	a1 = vertices[caras[i]._1]-vertices[caras[i]._0],
        	a2 = vertices[caras[i]._2]-vertices[caras[i]._0],
        	n = a1.cross_product(a2);

    	// modulo
    	float m = sqrt(n.x*n.x+n.y*n.y+n.z*n.z);

    	// normalización
    	normales_caras[i] = _vertex3f(n.x/m,n.y/m,n.z/m);
  	}
  
  	// ponemos a true que hemos calculado las normales de las caras
  	b_normales_caras = true; 
}


// Calcular las normales de los vertices
void _triangulos3D::calcular_normales_vertices(){
 	if(b_normales_vertices == false) {
 		// Si no hemos calculado las normales de las caras hay que hacerlo
    	if(b_normales_caras == false) 
    		calcular_normales_caras(); 

     	normales_vertices.resize(vertices.size());
     
     	for(int i=0; i<vertices.size(); i++){
       	normales_vertices[i].x = 0.0;
       	normales_vertices[i].y = 0.0;
    		normales_vertices[i].z = 0.0;
     	}
     
     	for(int i=0; i<caras.size(); ++i){
       	// se suma la normal de la cara a las normales de los tres vértices de la cara.
       	normales_vertices[caras[i]._0]+=normales_caras[i];
       	normales_vertices[caras[i]._1]+=normales_caras[i];
       	normales_vertices[caras[i]._2]+=normales_caras[i];
     	}
     
     	// Normalización
     	for(int i=0; i<vertices.size(); i++){
       	normales_vertices[i].normalize(); 
     	}
     
     	// ponemos a true que hemos calculado las normales de los vértices
     	b_normales_vertices = true; 
   }	
}


// Hacer la iluminacion plana
void _triangulos3D::draw_iluminacion_plana(){
  	GLfloat ambient_component[4] = {1,1,1,1};

  	if(b_normales_caras == false) 
  		calcular_normales_caras();

  	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);

  	glShadeModel(GL_FLAT);
  	glEnable(GL_LIGHTING);
  
  	// Hay que añadir más luces
  	glEnable(GL_LIGHT0);
  	glEnable(GL_LIGHT1);
  	glEnable(GL_NORMALIZE);

  	// Atributos de la luz
  	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,(GLfloat *)&ambiente_difusa);
  	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,(GLfloat *)&especular);
  	glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,(GLfloat *)&brillo);

  	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
  	glBegin(GL_TRIANGLES);

  	// Vamos dibujando
  	for(int i=0; i<caras.size(); ++i){
    	glNormal3fv((GLfloat *) &normales_caras[i]);
    	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
    	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
    	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
  	}

  	glEnd();

  	//deshabilitamos las luces
  	glDisable(GL_LIGHTING); 
}


// Hacer la iluminacion suave
void _triangulos3D::draw_iluminacion_suave(){
	GLfloat ambient_component[4] = {1,1,1,1};

  	if(b_normales_vertices == false) 
  		calcular_normales_vertices();

  	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
  	glShadeModel(GL_SMOOTH);
  	glEnable(GL_LIGHTING);
  	//glEnable(GL_LIGHT0);
  	//glEnable(GL_LIGHT1);
  	glEnable(GL_NORMALIZE);

  	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,(GLfloat *)&ambiente_difusa);
  	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,(GLfloat *)&especular);
  	glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,(GLfloat *)&brillo);

  	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
  	glBegin(GL_TRIANGLES);

  	for(int i=0; i<caras.size(); ++i){
    	glNormal3fv((GLfloat *) &normales_vertices[caras[i]._0]);
    	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
    	glNormal3fv((GLfloat *) &normales_vertices[caras[i]._1]);
    	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
    	glNormal3fv((GLfloat *) &normales_vertices[caras[i]._2]);
    	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
  	}

  	glEnd();

  	// deshabilitamos las luces
  	glDisable(GL_LIGHTING); 
}


// Hacer la textura 
void _triangulos3D::draw_textura(GLuint ident_textura, jpg::Imagen*& imagen){
  
  // Carga la imagen
  glTexImage2D(GL_TEXTURE_2D, 0, 3, imagen->tamX(), imagen->tamY(), 0, GL_RGB, GL_UNSIGNED_BYTE, imagen->leerPixels());
  
  // Activación de la textura
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,ident_textura); //vínculo con la tectura
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);

  // Vamos a realizar la generación automática de texturas
  if(mode_text) {
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_EYE_LINEAR);
    glTexGenfv(GL_S,GL_EYE_PLANE,coefs_s);
    glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_EYE_LINEAR);
    glTexGenfv(GL_T,GL_EYE_PLANE,coefs_t);
  }

  glColor3f(1.0,1.0,1.0); // máscara blanca

  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
  glBegin(GL_TRIANGLES);

  // Vamos dibujando
  for(int i=0; i<caras.size(); ++i) {
    if (b_textura_coord) {
      glTexCoord2f(textura_coord[caras[i]._0].s,textura_coord[caras[i]._0].t);
    }

    glVertex3fv((GLfloat *) &vertices[caras[i]._0]);

    if (b_textura_coord) {
      glTexCoord2f(textura_coord[caras[i]._1].s,textura_coord[caras[i]._1].t);
    }

    glVertex3fv((GLfloat *) &vertices[caras[i]._1]);

    if (b_textura_coord) {
      glTexCoord2f(textura_coord[caras[i]._2].s,textura_coord[caras[i]._2].t);
    }

    glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
  }

  glEnd();

  glDisable(GL_TEXTURE_2D);
  glDisable(GL_TEXTURE_GEN_S);
  glDisable(GL_TEXTURE_GEN_T);
}


// Hacer la textura con iluminación suave
void _triangulos3D::draw_textura_ilum_suave(GLuint ident_textura, jpg::Imagen*& imagen) {

  //Carga la imagen
  glTexImage2D(GL_TEXTURE_2D, 0, 3, imagen->tamX(), imagen->tamY(), 0, GL_RGB, GL_UNSIGNED_BYTE, imagen->leerPixels());
  
  GLfloat material_blanco[4] = {1,1,1,1}; // para que no se quede negra del todo

  if(b_normales_vertices == false) 
    calcular_normales_vertices();

  //glLightModeli(GL_SEPARATED_ESPECULAR_COLOR,GL_TRUE);
  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
  glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);
  //glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  glEnable(GL_NORMALIZE);

  // para que no quede del todo negra, si no que queda con sombra
  glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,material_blanco); 
  //glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,(GLfloat *)&ambiente_difusa);
  glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,(GLfloat *)&especular);
  glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,(GLfloat *)&brillo);

  // activamos la textura
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,ident_textura); // vínculo con la tectura
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  
  if(mode_text) {
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_EYE_LINEAR);
    glTexGenfv(GL_S,GL_EYE_PLANE,coefs_s);
    glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_EYE_LINEAR);
    glTexGenfv(GL_T,GL_EYE_PLANE,coefs_t);
  }

  glColor3f(1.0,1.0,1.0);

  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
  glBegin(GL_TRIANGLES);

  for(int i =0; i<caras.size();++i) {
    if (b_textura_coord) { 
      //solo se utiliza para la revolución, que es cuando asignamos manualmente las coordenadas
      glTexCoord2f(textura_coord[caras[i]._0].s,textura_coord[caras[i]._0].t);
    }

    glVertex3fv((GLfloat *) &vertices[caras[i]._0]);

    if (b_textura_coord) {
      glTexCoord2f(textura_coord[caras[i]._1].s,textura_coord[caras[i]._1].t);
    }

    glVertex3fv((GLfloat *) &vertices[caras[i]._1]);

    if (b_textura_coord) {
      glTexCoord2f(textura_coord[caras[i]._2].s,textura_coord[caras[i]._2].t);
    }

    glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
  }

  glEnd();

  glDisable(GL_TEXTURE_2D);
  glDisable(GL_TEXTURE_GEN_S);
  glDisable(GL_TEXTURE_GEN_T);
  glDisable(GL_LIGHTING);
}


// Hacer la textura con iluminación plana
void _triangulos3D::draw_textura_ilum_plana(GLuint ident_textura, jpg::Imagen*& imagen) {

  // Carga la imagen
  glTexImage2D(GL_TEXTURE_2D, 0, 3, imagen->tamX(), imagen->tamY(), 0, GL_RGB, GL_UNSIGNED_BYTE, imagen->leerPixels());
  GLfloat material_blanco[4] = {1,1,1,1}; //Para que no se quede negra del todo

  if(b_normales_caras == false) 
    calcular_normales_caras();

  // activamos la iluminación
  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);

  glShadeModel(GL_FLAT);
  glEnable(GL_LIGHTING);
  // Hay que añadir más luces
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  glEnable(GL_NORMALIZE);

  //para que no quede del todo negra
  glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,material_blanco); 
  //glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,(GLfloat *)&ambiente_difusa);
  glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,(GLfloat *)&especular);
  glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,(GLfloat *)&brillo);

  //activamos la textura
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,ident_textura); // vínculo con la textura
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  
  if(mode_text) {
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_EYE_LINEAR);
    glTexGenfv(GL_S,GL_EYE_PLANE,coefs_s);
    glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_EYE_LINEAR);
    glTexGenfv(GL_T,GL_EYE_PLANE,coefs_t);
  }

  glColor3f(1.0,1.0,1.0);

  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
  glBegin(GL_TRIANGLES);

  for(int i =0; i<caras.size();++i) {
    if (b_textura_coord) {
      glTexCoord2f(textura_coord[caras[i]._0].s,textura_coord[caras[i]._0].t);
    }

    glVertex3fv((GLfloat *) &vertices[caras[i]._0]);

    if (b_textura_coord) {
      glTexCoord2f(textura_coord[caras[i]._1].s,textura_coord[caras[i]._1].t);
    }

    glVertex3fv((GLfloat *) &vertices[caras[i]._1]);

    if (b_textura_coord) {
      glTexCoord2f(textura_coord[caras[i]._2].s,textura_coord[caras[i]._2].t);
    }

    glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
  }

  glEnd();

  glDisable(GL_TEXTURE_2D);
  glDisable(GL_TEXTURE_GEN_S);
  glDisable(GL_TEXTURE_GEN_T);
  glDisable(GL_LIGHTING);
}


//*************************************************************************
//        Clase Rotacion Textura
//*************************************************************************

_rotacion_text::_rotacion_text(){}

_rotacion_text::_rotacion_text(vector<_vertex3f> ver, int num_caras) {
  _vertex3f vertices_aux;
  _vertex3i caras_aux;
  _vertex2f tex_aux;

  int num_aux;
  b_textura_coord = true;

  vector <float> distancias;

  float alfa = 2*3.1416/num_caras;
  float alfa_aux = 2*3.1416/num_caras;
  float distancia_total = 0.0;

  // Calculo las distancias para las coordenadas de la textura
  num_aux = ver.size();

  for(int i=0; i<num_aux-1; ++i) {
    distancias.push_back(distancia_total);
    distancia_total += sqrt((ver[i].x-ver[i+1].x)*(ver[i].x-ver[i+1].x)+
                            (ver[i].y-ver[i+1].y)*(ver[i].y-ver[i+1].y)+
                            (ver[i].z-ver[i+1].z)*(ver[i].z-ver[i+1].z));
  }

  // Normalizamos las distancias
  for(int i=0;i<num_aux-1;++i) {
    distancias[i] = 1.0-distancias[i]/distancia_total;

  }

  distancias[0] = 1.0; //primera instancia
  distancias.push_back(0.0); //última instancia

  // Tratamiento de los vértices
  for(int j=0; j<num_caras+1; ++j) {
    tex_aux.s=j/(1.0*num_caras);

    for(int i=0; i<num_aux; i++) {
      vertices_aux.x =  ver[i].x * cos(alfa);
      vertices_aux.z = -ver[i].x * sin(alfa);
      vertices_aux.y  = ver[i].y;
      vertices.push_back(vertices_aux);

      tex_aux.t=distancias[i];
      textura_coord.push_back(tex_aux);
    }

    alfa += alfa_aux;
  }

  // Asignación manual de coordenadas de textura
  mode_text = false;
  b_textura_coord = true;

  // Tratamiento de las caras
  for(int j=0; j<num_caras; j++) {
    for(int i=0; i<num_aux-1; i++) {
      caras_aux._0=i+(j+1)*num_aux;
      caras_aux._1=i+1+(j+1)*num_aux;
      caras_aux._2=i+1+j*num_aux;

      caras.push_back(caras_aux);

      caras_aux._0=i+1+j*num_aux;
      caras_aux._1=i+j*num_aux;
      caras_aux._2=i+(j+1)*num_aux;

      caras.push_back(caras_aux);
    }
  }
}


//*************************************************************************
//        Clase Textura
//*************************************************************************

textura::textura(){}

textura::textura(const char *archivoJPG) {
  this->imagen = new jpg::Imagen(archivoJPG);
}


