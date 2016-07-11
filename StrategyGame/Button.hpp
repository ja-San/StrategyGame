//
//  Button.hpp
//  Strategy Game
//
//  Created by Jake Sanders on 7/10/16.
//  Copyright © 2016 Jake Sanders. All rights reserved.
//

#ifndef Button_hpp
#define Button_hpp

//GLEW: Locates memory location of OpenGL functions
#define GLEW_STATIC
#include <GL/glew.h>

//GLFW: Window functionality
#include <GLFW/glfw3.h>

//GLM: OpenGL mathematics for vectors here
#include <GLM/glm.hpp>

//Local includes
#include "Shader.hpp"

class Button {
public:
    //Constructors
    Button(Shader* shader, GLFWwindow* window, GLfloat x, GLfloat y, GLfloat width, GLfloat height, GLuint interfaceX, GLuint interfaceY, GLfloat interfaceWidth, GLfloat interfaceHeight);
    
    //Public member functions
    void render();
    
    void updateMouse();
    
private:
    //OpenGL and GLFW properties
    GLFWwindow* buttonWindow;
    Shader* buttonShader; //Pointer to a compiled shader
    GLuint VAO; //VAO (Vertex Array Object) stores objects that can be drawn, including VBO data with the linked shader
    //VBO (Vertex Buffer Object) stores vertex data in the GPU graphics card. Will be stored in VAO
    GLuint buttonVBO;
    GLuint colorVBO;
    
    //Viewport information
    const GLfloat lowerLeftX;
    const GLfloat lowerLeftY;
    const GLfloat buttonWidth;
    const GLfloat buttonHeight;
    
    const GLfloat interfaceBoxlowerLeftX;
    const GLfloat interfaceBoxlowerLeftY;
    const GLfloat interfaceBoxWidth;
    const GLfloat interfaceBoxHeight;
    
    //Private member functions
    void setBuffers();
    
};

#endif /* Button_hpp */
