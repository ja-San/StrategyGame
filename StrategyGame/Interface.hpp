//
//  Interface.hpp
//  Strategy Game
//
//  Created by Jake Sanders on 7/9/16.
//  Copyright © 2016 Jake Sanders. All rights reserved.
//

#ifndef Interface_hpp
#define Interface_hpp

#include "Macros.h"

//Standard library includes
#include <vector>

//GLEW: Locates memory location of OpenGL functions
#define GLEW_STATIC
#include <GL/glew.h>

//GLFW: Window functionality
#include <GLFW/glfw3.h>

//Local includes
#include "Shader.hpp"
#include "Font.hpp"
#include "Button.hpp"

class Interface {
public:
    //Constructors
    
    /*!
     * A class representing an interface box.
     *
     * @param shader A pointer to a compiled shader for the interface box to use for rendering.
     * @param shaderForButtons A pointer to another compiled shader that will be used for rendering the buttons on this interface.
     * @param window A pointer to the current window object.
     * @param x The lower left corner's x coordinate, for setting the interface box. Should be in terms of GLFW screen coordinates, where (0,0) is the lower left corner of the screen.
     * @param y The lower left corner's y coordinate, for setting the interface box. Similar settings and configurations as with x.
     * @param width The width of the interface box, in GLFW screen coordinates.
     * @param height The height of the interface box, in GLFW screen coordinates.
     * @param withButtons Whether buttons should be drawn on the interface.
     */
    Interface(Shader* shader, Shader* shaderForButtons, GLFWwindow* window, GLuint x, GLuint y, GLuint width, GLuint height, bool withButtons);
    
    //Public properties
    std::vector<Button> buttons; //So that the buttons can be accessed by the game
    
    //Public member functions
    
    /*!
     * A function to render the interface. Should be called within the game loop's render function. This also renders the buttons on this interface.
     *
     * @param mouseDown A boolean representing if the mouse is down, for the buttons to figure out whether to become pressed.
     * @param mouseUp A boolean representing if the mouse has just been released. This is used for when the button resets its 'down' state.
     */
    void render(bool mouseDown, bool mouseUp);
    
private:
    //OpenGL and GLFW properties
    GLFWwindow* interfaceWindow;
    Shader *interfaceShader; //Compiled shader
    Shader *buttonShader; //Shader for the buttons
    GLuint VAO; //VAO (Vertex Array Object) stores objects that can be drawn, including VBO data with the linked shader
    //VBO (Vertex Buffer Object) stores vertex data in the GPU graphics card. Will be stored in VAO
    GLuint VBO;
    
    //Viewport information
    GLuint lowerLeftX;
    GLuint lowerLeftY;
    GLuint boxWidth;
    GLuint boxHeight;
    
    int viewportWidth;
    int viewportHeight;
    
    //Private member functions
    
    /*!
     * Update the viewport information of this object. This functino would be relevant with resizing, but for now do not use this function! The function works, but there is no substitute with the buttons!
     */
    void updateViewport();
    
};

#endif /* Interface_hpp */
