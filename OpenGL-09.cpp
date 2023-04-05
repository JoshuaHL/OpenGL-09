//
//  OpenGL-09.cpp
//  OpenGL-09
//
//  Created by Dr. John Charlery on 03/16/2022.
//  Copyright (c) 2023 University of the West Indies. All rights reserved.
//
// ========================================================================
//  PROGRAM:
//          Two Animated, Textured Spheres
//
//=========================================================================

/*=========================================================================
Install the following in Package Manager :

Install-Package glew_dynamic
Install-Package glfw
Install-Package GLMathematics
Install-Package freeimage -version 3.16.0
Install-Package nupengl.core
Install-Package Soil
Install-Package Assimp -version 3.0.0

============================================================================*/

//  Shifting the focus here a bit:
//      1.  Using a modified class-based shaders system (shader.h)
//      2.  Using a model.h header to import objects from programs such
//          as Blender
//      3.  Using a mesh.h file to handle the object(s)
//      4.  Using a camera.h file to handle the camers's movements (pitch,
//          yaw, speed, zoom, etc)
//      4.  Using ASSIMP library to handle the textures to objects
//      5.  Using libSOIL library to handle the textures of diffrent
//          formats (PNG, BMP, etc)
// ========================================================================


// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GL includes
#include "shader.h"
#include "camera.h"
#include "model.h"

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Active window
GLFWwindow* window;

// Window Properties
GLuint sWidth = 800, sHeight = 800;



// Camera
Camera camera(glm::vec3(0.0f, 0.0f, 200.0f));


GLfloat angle = 0.0f;
GLfloat angleInc = 0.001f;


void init_Resources()
{
    // Initialize the resources - set window, etc.
    if (!glfwInit())
        {
            cout << "\nFailed to Initialize GLFW...";
            exit(EXIT_FAILURE);
        }
  
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    
    // Create the display window
    window = glfwCreateWindow(sWidth, sHeight, "COMP3420 - Textured Spheres", 0, 0); // Windowed

    
    //If window fails creation, then shut down the whole thing
    if (!window)
        {
            cout << "\nFailed to open display window...";
            glfwTerminate();
            exit(EXIT_FAILURE);
        }
    
    
    //If window succeeded then make it active on the display device
    glfwMakeContextCurrent(window);
    
    
    // ******  ABSOLUTELY required otherwise glGenVertexArrays will FAIL! *************
    glewExperimental = GL_TRUE;
    
    
    // Initialize GLEW
    if (glewInit() != GLEW_OK)
        {
            cout << "\nFailed to initialize GLEW...";
            exit(EXIT_FAILURE);
        }
    
    //Set the window's background colour (to GREY)
    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
    

    // Setup OpenGL options
    glEnable(GL_DEPTH_TEST);

}




// The MAIN function, from here we start our application and run our Game loop
int main()
{
     init_Resources();
    
    GLfloat earthX = 80.0;
    GLfloat earthY = 0.0;
    GLfloat earthXinc = 0.02;
    GLfloat earthYinc = 0.02;

    GLfloat marsX = -80.0;
    GLfloat marsY = 0.0;
    GLfloat marsXinc = -0.1;
    GLfloat marsYinc = -0.1;

    GLdouble xdif, ydif, temp;

    
    // ==============================================
    // ====== Set up the stuff for our sphere =======
    // ==============================================
    
    // 1. Setup and compile our shaders (new approach)
    Shader earthShader("earthVertex.glsl", "earthFragment.glsl");
    Shader marsShader("marsVertex.glsl", "marsFragment.glsl");

    
    // 2. Load the earth object
    Model earth((GLchar*)"earth.obj");
    Model mars((GLchar*)"mars.obj");

    
 
    // 3. Set the projection matrix
    glm::mat4 projection = glm::perspective(45.0f, (GLfloat)sWidth/(GLfloat)sHeight,
                                            1.0f, 10000.0f);
    
    
    
    // 4. Activate the earthShader object with the projection matrix
    earthShader.Use();
    glUniformMatrix4fv(glGetUniformLocation(earthShader.Program, "projection"),
                       1, GL_FALSE, glm::value_ptr(projection));
    
    marsShader.Use();
    glUniformMatrix4fv(glGetUniformLocation(marsShader.Program, "projection"),
                       1, GL_FALSE, glm::value_ptr(projection));

    
    
    
    
    // =============================++++++++++++++++++++=================
    // ====== Set up the changes we want while the window is open =======
    // =======================++++++++++++++++++++=======================

     while(!glfwWindowShouldClose(window))
    {
        
        // Clear buffers
        glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        
        // Add transformation matrices ... by repeatedly modifying the model matrix
        
        // 1. The View matrix first...
        earthShader.Use();
        glUniformMatrix4fv(glGetUniformLocation(earthShader.Program, "view"), 1,
                           GL_FALSE, glm::value_ptr(camera.GetViewMatrix()));
        
        marsShader.Use();
        glUniformMatrix4fv(glGetUniformLocation(marsShader.Program, "view"), 1,
                           GL_FALSE, glm::value_ptr(camera.GetViewMatrix()));

        
        


        
        // 2. Create the earth model and set it's properties
        earthShader.Use();
        glm::mat4 earthModel = glm::mat4(1);
        
        marsShader.Use();
        glm::mat4 marsModel = glm::mat4(1);

        
        
        
        // Test for edge detection

        earthX += earthXinc;
        if (earthX > 85 || earthX < -85)
            earthXinc *= -1;

    
        // ...Test for earth touching the sides...
    
        // ...Test for Mars touching the sides...
        
        
        // ...Test for earth touching Mars...
        
       
        
        
        
        
        
        
        
        
        // 3. Apply the translation matrix to the model matrix

        earthModel = glm::translate(earthModel, glm::vec3(earthX, earthY, 0.0f));
        marsModel  = glm::translate(marsModel, glm::vec3(marsX, marsY, 0.0f));

        
        // 4. Apply the scaling matrix to the model matrix
        earthModel = glm::scale(earthModel, glm::vec3(10.0f, 10.0f, 10.0f));
        marsModel  = glm::scale(marsModel, glm::vec3(10.0f, 10.0f, 10.0f));

        
        // 5. Apply the rotation matrix to the model matrix
  //      earthModel = glm::rotate(earthModel, -45.0f, glm::vec3(1.0f, 0.0f, 0.0f));
        earthModel = glm::rotate(earthModel, 0.0f, glm::vec3(1.0f, 0.0f, 0.0f));
        marsModel  = glm::rotate(marsModel, -45.0f, glm::vec3(1.0f, 0.0f, 0.0f));

        // make it rotate around the y-axis
        angle += angleInc;
        earthModel = glm::rotate(earthModel, angle, glm::vec3(0.0f, 1.0f, 0.0f));
        marsModel  = glm::rotate(marsModel, angle, glm::vec3(0.0f, 0.0f, 1.0f));
        if (angle >= 360) angle = 0.0;
    
        // 6. Send the earth model's matrix to the vertex shader as "model"
        glUniformMatrix4fv(glGetUniformLocation(earthShader.Program, "model"), 1,
                           GL_FALSE, glm::value_ptr(earthModel));
        
        // Display the Earth
        earth.Draw(earthShader);

        

        // 7. Send the mars model's matrix to the vertex shader as "model"

        glUniformMatrix4fv(glGetUniformLocation(marsShader.Program, "model"), 1,
                           GL_FALSE, glm::value_ptr(marsModel));
        
        // Display the Mars
        mars.Draw(marsShader);

        
        // Swap the frame buffers
        glfwSwapBuffers(window);
        
        glfwPollEvents();
        
     

    }
    
    glfwTerminate();
    return 0;
}



