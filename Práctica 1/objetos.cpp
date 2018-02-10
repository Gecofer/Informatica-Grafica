#include "objetos.h"


//*************************************************************************
// clase punto
//*************************************************************************

_puntos3D::_puntos3D(){}

void _puntos3D::draw_puntos(float r, float g, float b, int grosor){
	glPointSize(grosor);
	glColor3f(r,g,b);
	glBegin(GL_POINTS);
		for (int i = 0; i < vertices.size(); i++){
			glVertex3fv((GLfloat*)&vertices[i]);
		}
	glEnd();
}


//*************************************************************************
// clase triángulo
//*************************************************************************
_triangulos3D::_triangulos3D(){}
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
//*************************************************************************
// clase cubo
//*************************************************************************

_cubo::_cubo(float tam){
	float half = tam/2;
	float mhalf = -half;
	vertices.resize(8);
	vertices[0].x = mhalf; vertices[0].y = mhalf; vertices[0].z = half;
	vertices[1].x = half; vertices[1].y = mhalf; vertices[1].z = half;
	vertices[2].x = mhalf; vertices[2].y = half; vertices[2].z = half;
	vertices[3].x = half; vertices[3].y = half; vertices[3].z = half;
	vertices[4].x = half; vertices[4].y = half; vertices[4].z = mhalf;
	vertices[5].x = mhalf; vertices[5].y = half; vertices[5].z = mhalf;
	vertices[6].x = half; vertices[6].y = mhalf; vertices[6].z = mhalf;
	vertices[7].x = mhalf; vertices[7].y = mhalf; vertices[7].z = mhalf;

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


//*************************************************************************
// clase piramide
//*************************************************************************
_piramide::_piramide(float tam, float al){
	vertices.resize(5);
	vertices[0].x = -tam; vertices[0].y = 0; vertices[0].z = tam;
	vertices[1].x = tam; vertices[1].y = 0; vertices[1].z = tam;
	vertices[2].x = tam; vertices[2].y = 0; vertices[2].z = -tam;
	vertices[3].x = -tam; vertices[3].y = 0; vertices[3].z = -tam;
	vertices[4].x = 0; vertices[4].y = al; vertices[4].z = 0;

	caras.resize(6);
	caras[0]._0= 0; caras[0]._1= 1; caras[0]._2= 4;
	caras[1]._0= 1; caras[1]._1= 2; caras[1]._2= 4;
	caras[2]._0= 2; caras[2]._1= 3; caras[2]._2= 4;
	caras[3]._0= 3; caras[3]._1= 0; caras[3]._2= 4;
	caras[4]._0= 0; caras[4]._1= 3; caras[4]._2= 2;
	caras[5]._0= 0; caras[5]._1= 2; caras[5]._2= 1;
}
