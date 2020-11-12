#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <bits/stdc++.h>

using namespace std;

GLuint tex;
GLUquadric* sphere;

// Making the texture (in this case, the white and black checks) that
// needs to be mapped on the ball.
void make_texture()
{
	unsigned char data[256][256][3];

    for (int x = 0; x < 255; x++) 
    {
		for (int y = 0; y < 255; y++) 
		{
	    	unsigned char *colors = data[x][y];
	    	colors[0] = (x ^ y) & 16 ? 255 : 0;
	    	colors[1] = (x ^ y) & 16 ? 255 : 0;
	    	colors[2] = (x ^ y) & 16 ? 255 : 0;
		}
    }

    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, (const GLvoid *) data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

// Creating the room.
void createRoom()
{
 	glPolygonMode(GL_FRONT, GL_FILL);
	glBegin(GL_QUADS);
	
	// bottom wall
	glNormal3f(0,1,0);
	glColor3f(.658824, 0.658824, 0.658824);
    glVertex3f(-7,-5,0);
	glVertex3f(7,-5,0);
	glVertex3f(7,-5,-3);
	glVertex3f(-7,-5,-3);

	// left wall
	glNormal3f(1,0,0);
	glColor3f(0.858824, 0.439216, 0.858824);
	glVertex3f(-7,-5,0);
	glVertex3f(-7,-5,-3);
	glVertex3f(-7,5,-3);
	glVertex3f(-7,5,0);

	// right wall
	glNormal3f(-1,0,0);
	glColor3f(0.309804, 0.184314, 0.309804);
	glVertex3f(7,-5,-3);
	glVertex3f(7,-5,0);
	glVertex3f(7,5,0);
	glVertex3f(7,5,-3);

	// center wall
	glNormal3f(0,0,1);
	glColor3f(0.752941, 0.752941, 0.752941);
	glVertex3f(-7,-5,-3);
	glVertex3f(7,-5,-3);
	glVertex3f(7,5,-3);
	glVertex3f(-7,5,-3);

	// top wall
	glNormal3f(0,-1,0);
	glColor3f(0.658824, 0.658824, 0.658824);
	glVertex3f(-7,5,-3);
	glVertex3f(7,5,-3);
	glVertex3f(7,5,0);
	glVertex3f(-7,5,0);
	glEnd();
}

void init()
{
	// Adding smooth shading.
	glShadeModel(GL_SMOOTH);

	// Specifying the ambient, diffused and specular 
	// light for the sphere.
	GLfloat diffused_light[] = {1.0, 1.0, 1.0, 0.8};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffused_light);

	GLfloat specular_light[] = {1.0, 1.0, 1.0, 0.2};
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);

	GLfloat ambient_light[] = {0.5, 0.5, 0.5, 1.0};
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
}

// The ball in the left
void createPlasticBall()
{
	glTranslatef(-1.5, -3, -1.5);
	glColor3f(0.8, 0.2, 0.8);
	glutSolidSphere(1.0, 20, 16);
	glTranslatef(1.5, 3, 1.5);
}

// The ball in the right
void createTextureBall()
{
	// Calling the function to create the texture for the sphere.
	make_texture();
	sphere = gluNewQuadric();

	glEnable(GL_TEXTURE_2D);

	glTranslatef(0, -0.2, -1.5);
	
	// Mapping the texture to the ball.
	gluQuadricDrawStyle(sphere, GLU_FILL);
    glBindTexture(GL_TEXTURE_2D, tex);
    gluQuadricTexture(sphere, GL_TRUE);
    gluQuadricNormals(sphere, GLU_SMOOTH);
    glScalef(0.9,1.1,1);
    gluSphere(sphere, 1.0, 20, 16);
	glTranslatef(0, 0.2, 1.5);
}

// The ball in the right
void createGlossyBall()
{
	// Adding extra specular light and reflectiveness in case of 
	// the glossy ball
	GLfloat specular_glossy[] = { 1.0, 1.0, 1.0, 1.0};
	GLfloat shininess_glossy[] = { 50.0 };

	glMaterialfv(GL_FRONT, GL_SPECULAR, specular_glossy);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess_glossy);

	glTranslatef(2, -4, -1.7);
	glColor3f(0.8, 0.8, 0.8);
	glScalef(0.8,1.1,0.1);
	glutSolidSphere(1.0, 20, 16);
	glTranslatef(-2, 4, 1.7);
}

// Draws the 3D sphere in the viewing window.
void displayObject()
{
	// Clearing the buffer before displaying the sphere.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Specifying the location of camera and the positive y-axis.
	gluLookAt(0, 0, 1, 0, 0, 0, 0, 1, 0);

	// Calling the function to create the walls of the room.
	createRoom();

	// Calling the function to set initial lighting in the room.
	init();

	// Positioning the light sources at (0, 0, 0).
	GLfloat light_position[] = {0.0, 15.0, -0.5, 0.5};
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	// Calling the function to construct the glossy ball.
	createGlossyBall();

	// Calling the function to construct the texture ball.
	createTextureBall();

	// Calling the function to construct the plastic ball.
	createPlasticBall();

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
        gluOrtho2D(-10, 10, -10 * (GLfloat) h / (GLfloat) w,
            10 * (GLfloat) h / (GLfloat) w);
    else
        gluOrtho2D(-10 * (GLfloat) w / (GLfloat) h,
            10 * (GLfloat) w / (GLfloat) h, -10, 10);
    
    gluPerspective(30, (GLfloat) h / (GLfloat) w, 0, 20);
    glMatrixMode(GL_MODELVIEW); 
}


int main(int argc, char **argv)
{
	// Initialising the Glut toolkit and the display window.
	glutInit(&argc, argv);  

   	glutInitDisplayMode(GLUT_SINGLE| GLUT_RGB | GLUT_DEPTH); 

   	glutInitWindowSize(700, 500);  
   	glutInitWindowPosition(100, 100);
   	glutCreateWindow(argv[0]);

   	// Calling the displayObject function to draw the 3D object.
   	glutDisplayFunc(displayObject);

   	// Calling the reshape function to handle the resizing of the viewing window.
   	glutReshapeFunc(reshape);
   	
   	// Keeping the window open indefinitly.
   	glutMainLoop();
   	return 0; 

}