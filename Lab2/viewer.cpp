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

int res = 0;

// Angles by which the X and Y axes are to be rotated respectively.
float angleX = 0.0, angleY = 0.0;

// Retaining the old locations of the cursor to obtain the distance
// between current and old cursor positions
int prevx, prevy;

// The scaling factor for zooming in and out by mouse scroll
float scaling = 1.0;

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
    glRotatef(angleX, 0.0, 1.0, 0.0);
 	glRotatef(angleY, 1.0, 0.0, 0.0);

 	glScalef(scaling, scaling, scaling);

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

// Deals with the dragging of the mouse, which is used for rotating
// the object witn respect to x and y coordinates.
void motionCallBack(int x, int y)
{
	int movx, movy;

	// computing the change in the x and y coordinates of the cursor
	// position
	movx = prevx - x;
	movy = prevy - y;

	// set angleX and angleY values for rotation using the change in
	// cursor position
	if ( abs(movx) < 10 ){angleX += (float)(movx) / 4;}
	if ( abs(movy) < 10 ){angleY += (float)(movy) / 4;}

	if (angleX > 360) angleX -= 360;
	else if (angleX < 0) angleX += 360;

	if (angleY > 360) angleY -= 360;
	else if (angleY < 0) angleY += 360;
	         
	// Updating the variable storing old cursor position   
	prevx = x;
	prevy = y;

	// Reload the display window
	glutPostRedisplay();
}

// Deals with the clicking and scrolling of the mouse, which is used for
// zooming in and out the object.
void mouseCallBack(int button, int state, int x, int y)
{
    if ( state == GLUT_DOWN )
    {
        // button value 3 represents scrolling up the mouse wheel
        // button value 4 represents scrolling down the mouse wheel
        if (button == 3 or button == 4)
        {
			// Increasing or decreasing the scaling factor accordingly
			if ( button == 3 ){scaling  += 0.05;}
			else scaling  -= 0.05; 

			// Ensure that the user can't zoom in or zoom out indefinitely
			if ( scaling < 00.1f) scaling = 0.1f;
			if ( scaling > 10.0f) scaling = 10.0f; 
			
			// Reload the display window
			glutPostRedisplay();
        }
    }
}

int main (int argc, char** argv)
{
    // cout << "Use up, down, left and right keys to rotate the object.";
    // cout << endl << endl;

    cout << "Enter the file name: (along with .obj extention) ";

    // Getting the object file name from the user through command line.
    char filename[20];
    cin >> filename;

    // Initialising the Glut toolkit and the display window.
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(700, 700);
    glutInitWindowPosition(200, 200);
    glutCreateWindow(filename);

    glEnable(GL_DEPTH_TEST);

    // Calling the reshape function to handle the resizing of the viewing window.
    glutReshapeFunc(reshape);

    // Calling the loadObject function with filename as an argument.
    res = loadObject(filename);

    // Calling the displayObject function to draw the 3D object.
    glutDisplayFunc(displayObject);

    // Calling the function to handle mouse clicks and scrolling interrupts
    glutMouseFunc(mouseCallBack);

    // Calling the function to handle mouse click and drag interrupt.
    glutMotionFunc(motionCallBack);
	
	// Keeping the window open indefinitly.
    glutMainLoop();
}