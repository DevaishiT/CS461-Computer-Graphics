#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <bits/stdc++.h>

using namespace std;

void init()
{
	// Setting the background as grey to visualize the sphere
	glClearColor(0.1, 0.1, 0.1, 0.0);

	// Creating a light source at (1, 1, 1).
	GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	// Specifying the ambient, diffused and specular 
	// light for the sphere.
	GLfloat diffused_light[] = {1.0, 1.0, 1.0, 1.0};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffused_light);

	GLfloat specular_light[] = {1.0, 1.0, 1.0, 1.0};
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);

	GLfloat ambient_light[] = {0.1, 0.1, 0.1, 1.0};
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
}

// Draws the 3D sphere in the viewing window.
void displayObject()
{
	// Clearing the buffer before displaying the sphere.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glutSolidSphere(1.0, 20, 16);
	glFlush();
}

// Ensures that the entire object is visible irrespective to the shape
// of the viewing window.
void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    if (w <= h)
        gluOrtho2D(-3.2, 3.2, -3.2 * (GLfloat) h / (GLfloat) w,
            3.2 * (GLfloat) h / (GLfloat) w);
    else
        gluOrtho2D(-3.2 * (GLfloat) w / (GLfloat) h,
            3.2 * (GLfloat) w / (GLfloat) h, -3.2, 3.2);
    
    glMatrixMode(GL_MODELVIEW); 
}


int main(int argc, char **argv)
{
	// Initialising the Glut toolkit and the display window.
	glutInit(&argc, argv);  

   	glutInitDisplayMode(GLUT_SINGLE| GLUT_RGB | GLUT_DEPTH); 

   	glutInitWindowSize(500, 500);  
   	glutInitWindowPosition(100, 100);
   	glutCreateWindow(argv[0]);

   	// Calling the init function to initialise the 3D object.
   	init();

   	// Calling the displayObject function to draw the 3D object.
   	glutDisplayFunc(displayObject);

   	// Calling the reshape function to handle the resizing of the viewing window.
   	glutReshapeFunc(reshape);
   	
   	// Keeping the window open indefinitly.
   	glutMainLoop();
   	return 0; 

}