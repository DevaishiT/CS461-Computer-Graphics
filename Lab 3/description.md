# Sphere with different textures

In this lab assignment we have created a room contained 3 differently textures spheres, namely **Plastic, Textured** and **Glossy Ball**. 

We have placed the light source at (0, 15, -0.5). Since the light source can only be a point source, we have placed it a litle above the ciling of the room to replicate general tubelighs/light bulbs.

Note: Code for complete scene as well as individual balls is added in this submission

## Installation

Install freeglut toolkit to deal with intricacies of operating system while building OpenGL applications.

```bash
sudo apt-get install freeglut3 freeglut3-dev libglew-dev
sudo apt-get install mesa-utils
```

## Usage

User can either see the entire scene or replace the filename in below given command by **glossy_ball.cpp, plastic_ball.cpp** or **textured_ball.cpp**

The following command can be used in case of Linux OS.

```bash
elv@TheFirefly:~/Sem7/Graphics-Lab/lab3$  g++ final_scene.cpp -lGL -lGLU -lglut -o scene

elv@TheFirefly:~/Sem7/Graphics-Lab/lab3$ ./scene
```

## Working
Refer to code for understanding the internal functionalities involved. The code is well-commented, making the code easy to understand and use.

## Created by
Devaishi Tiwari (Roll no. **170101021**)