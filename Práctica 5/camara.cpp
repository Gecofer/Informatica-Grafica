#include <camara.h>

Camara::Camara(){
	Observer_distance=4;
	Observer_angle_x=0;
	Observer_angle_y=0;
	cenital=false;
}

void Camara::girar(){}
	
void Camara::setObservador(){
	
	if(cenital){
		glRotatef(90,1,0,0);
		glTranslatef(0,-Observer_distance/2,0);
		glTranslatef(-Observer_angle_y*0.005,0,0);
		glTranslatef(0,0,-Observer_angle_x*0.005);
	}
	else{
		glTranslatef(0,0,-Observer_distance);
		glRotatef(Observer_angle_x,1,0,0);
		glRotatef(Observer_angle_y,0,1,0);
	}

}
