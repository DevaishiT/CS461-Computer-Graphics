# Object-Viewer

**Viewer.cpp** is an extension of the previous assignment(Object-Loader). It loads **.obj files** for 3D shapes. It works for any shape that can be made up from an **3D mesh** of triangles.

The object can be rotated along the **x-axis** and **y-axis** by **pressing the left mouse button and dragging**, which helps us to visualise the object from different angles. We can also **scroll** to **zoom in** and out of the 3D object.

## Installation

Install freeglut toolkit to deal with intricacies of operating system while building OpenGL applications.

```bash
sudo apt-get install freeglut3 freeglut3-dev libglew-dev
sudo apt-get install mesa-utils
```

## Usage

viewer.cpp file can be run from terminal/command prompt similar to other .cpp files.

The following command can be used in case of Linux OS.

```bash
g++ viewer.cpp -lGL -lGLU -lglut -o viewer
./objLoader
```

You will then be asked to enter the name of .obj file (along with its extention). You can choose any of the existing .obj files in the submission folder, or can add another .obj file in the same.

```bash
elv@TheFirefly:~/Sem7/Graphics-Lab/lab2$ ./viewer
Enter the file name: (along with .obj extention) lowpolybunny.obj
```

Deals with the dragging of the mouse, which is used for rotating
// the object witn respect to x and y coordinates.

## Working
The code consists of **two** additional functions namely,

* **MouseCallBack function** - This function handles the mouse clicks and scrolls. In this function, we zoom-in and zoom-out the object by scrolling up and down.

* **MotionCallBack function** - This function handles the mouse dragging, i.e. moving the cursor while the left-click or right-click button is pressed. In this function, we change the angle with which we need to rotate the object along x and y axes.

The code is well-commented, making the code easy to understand and use.

## Created by
Devaishi Tiwari (Roll no. **170101021**)