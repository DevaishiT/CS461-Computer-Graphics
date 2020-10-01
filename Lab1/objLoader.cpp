#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>

using namespace std;

// Data structure used to store coordinates of a vertex.
struct coordinates{
	double x, y, z;
};

// Data structure used to store vertices of a face.
struct face{
	int vertex[3];
};

// Vector to store all the vertices used in the 3D object.
vector<coordinates> vertices;

// Vector used to store the vertices that make up a particular
// face in the 3D object.
// (index of the corresponding vertex in vertices stored)
vector<face> faces;

void reshape(int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
}

// Reads the object file and populates the faces and vertices
// global vectors.
int loadObject(const char* filename)
{
	ifstream fp(filename, ios::in);
	
	// Checking if the file was correctly opened.
	if (!fp)
	{
	    cout << "Cannot open " << filename << endl;
	    return -1;
	}

	// Reading the data in object file line by line.
	string line;
	while(getline(fp, line))
	{
	    // Checking if the corresponding line refers
	    // to a vertex of a face.
	    if (line.substr(0,2) == "v ")
	    {
	        istringstream s(line.substr(2));
	        coordinates v;
	        s >> v.x; s >> v.y; s >> v.z;
	        vertices.push_back(v);
	    }
	    else if (line.substr(0,2) == "f ")
	    {
	        istringstream s(line.substr(2));
	        face f;
	        s >> f.vertex[0];
	        s >> f.vertex[1];
	        s >> f.vertex[2];
	        
	        faces.push_back(f);
	    }
	}

	fp.close();
	return true;
}

// Angles by which the X and Y axes are to be rotated respectively.
double angleX = 0;
double angleY = 0;
bool res = 0;

// Draws the 3D object by iteratively displaying all the faces 
// defined in the object file.
void displayObject ()
{
	// Setting up the background window
    glClearColor(0.8, 0.8, 0.8, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);

    // Rotating axes to support the keyboard rotation function
    glRotatef(angleX, 1.0, 0.0, 0.0);
 	glRotatef(angleY, 0.0, 1.0, 0.0);

 	glMatrixMode(GL_PROJECTION);
 	glLoadIdentity();
 	gluOrtho2D(-3, 3, -3, 3);
 	glMatrixMode(GL_MODELVIEW);

    for(int i=0; i<faces.size(); i++)
	{
		// Getting the coordinates of vertices of the face.
		coordinates v1 = vertices[faces[i].vertex[0] - 1];
		coordinates v2 = vertices[faces[i].vertex[1] - 1];
		coordinates v3 = vertices[faces[i].vertex[2] - 1];

		// Creating and outlining the triangle faces
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
		glBegin(GL_TRIANGLES);
 
		glColor3f(1.0, 1.0, 1.0);
		glVertex3f(v1.x, v1.y, v1.z);
        glVertex3f(v2.x, v2.y, v2.z);
        glVertex3f(v3.x, v3.y, v3.z);

        glEnd();
	}

    glFlush();

    // Dual buffers are maintained to allow faster reloads
    // of the window.
    glutSwapBuffers();
}

// Allows the user to use the up, down, left and right arrow
// keys to rotate the axes.
void keyboard(int key, int x, int y)
{
    if (key == GLUT_KEY_RIGHT) angleY += 15;
    else if (key == GLUT_KEY_LEFT) angleY -= 15;
    else if (key == GLUT_KEY_DOWN) angleX -= 15;
    else if (key == GLUT_KEY_UP) angleX += 15;
    
    // Reloading the display window to view the changes.
    glutPostRedisplay();
}

int main (int argc, char** argv)
{
    cout << "Use up, down, left and right keys to rotate the object.";
    cout << endl << endl;

    cout << "Enter the file name: (along with .obj extention) ";

    // Getting the object file name from the user through command line.
    char filename[20];
    cin >> filename;

    // Initialising the Glut toolkit and the display window.
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(1000,700);
    glutInitWindowPosition(10, 10);
    glutCreateWindow(filename);

    glEnable(GL_DEPTH_TEST);
    glutReshapeFunc(reshape);

    // Calling the loadObject function with filename as an argument.
    res = loadObject(filename);

    // Calling the displayObject function to draw the 3D object.
    glutDisplayFunc(displayObject);

    // Calling the keyboard function everytime a key is pressed on the
    // keyboard to enable rotating the object.
	glutSpecialFunc(keyboard);
	
	// Keeping the window open indefinitly.
    glutMainLoop();
}