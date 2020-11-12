#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <bits/stdc++.h>

using namespace std;

GLuint tex;
GLUquadric* sphere;

void make_texture()
{
	unsigned char data[256][256][3];

    for (int x = 0; x < 255; x++) 
    {
		for (int y = 0; y < 255; y++) 
		{
	    	unsigned char *colors = data[x][y];
	    	colors[0] = (x ^ y) & 4 ? 255 : 0;
	    	colors[1] = (x ^ y) & 4 ? 255 : 0;
	    	colors[2] = (x ^ y) & 4 ? 255 : 0;
		}
    }

    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, (const GLvoid *) data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void init()
{
	// Setting the background as grey to visualize the sphere
	glClearColor(0.1, 0.1, 0.1, 0.0);

	// Calling the function to create the texture for the sphere.
	make_texture();
	sphere = gluNewQuadric();

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
	glEnable(GL_TEXTURE_2D);
}

// Draws the 3D sphere in the viewing window.
void displayObject()
{
	// Clearing the buffer before displaying the sphere.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glColor3f(0.0,1.0,0.0);
    gluQuadricDrawStyle(sphere, GLU_FILL);
    glBindTexture(GL_TEXTURE_2D, tex);
    gluQuadricTexture(sphere, GL_TRUE);
    gluQuadricNormals(sphere, GLU_SMOOTH);

	gluSphere(sphere, 1.0, 20, 16);
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