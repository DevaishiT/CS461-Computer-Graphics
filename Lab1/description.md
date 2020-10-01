# Object-Loader

ObjLoader.cpp loads **.obj files** for simple 3D shapes. It works for any shape that can be made up from an **3D mesh** of triangles.

ObjLoader.cpp, when run, displays the 3D object. You can use the **left, right, top** and **down arrow keys**, to rotate the axes and hence visualise the object from different angles.

## Installation

Install freeglut toolkit to deal with intricacies of operating system while building OpenGL applications.

```bash
sudo apt-get install freeglut3 freeglut3-dev libglew-dev
sudo apt-get install mesa-utils
```

## Usage

ObjLoader.cpp file can be run from terminal/command prompt similar to other .cpp files.

The following command can be used in case of Linux OS.
```bash
g++ objLoader.cpp -lGL -lGLU -lglut -o objLoader
./objLoader
```
You will then be asked to enter the name of .obj file (along with its extention). You can choose any of the existing .obj files in the submission folder, or can add another .obj file in the same.
```bash
elv@TheFirefly:~/Sem7/Graphics-Lab/lab1$ ./objLoader 
Use up, down, left and right keys to rotate the object.

Enter the file name: (along with .obj extention) gourd.obj
```

## Working
The code consists of three main functions namely, displayObject, loadObject and keyboard functions.

* The **loadObject** function reads the object file and populates the **faces** and **vertices** vectors maintained in the code.

* The **displayObject** function draws the **3D object** by iteratively displaying all the faces defined in the object file. 

* The **keyboard function** is called everytime a key is pressed on the keyboard. It allows the user to use the up, down, left and right arrow keys to **rotate the axes**.

The code is well-commented, making the code easy to undestand and use.
 

## Created by
Devaishi Tiwari (Roll no. **170101021**)