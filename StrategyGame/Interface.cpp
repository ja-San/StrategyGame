//
//  Interface.cpp
//  Strategy Game
//
//  Created by Jake Sanders on 7/9/16.
//  Copyright © 2016 Jake Sanders. All rights reserved.
//

#include "Interface.hpp"

//Only so that Visualizer.hpp can have properly initialized interfaces. No other purpose.
Interface::Interface() {}

Interface::Interface(Shader* shader, Shader* shaderForButtons, Shader* shaderForDisplayBars, Window* window, GLuint x, GLuint y, GLuint width, GLuint height, interfaceType type = interface_other) {
    this->window = window;
    this->interfaceShader = shader;
    this->buttonShader = shaderForButtons;
    this->displayBarShader = shaderForDisplayBars;
    
    //Set viewport specifics
    this->lowerLeftX = x;
    this->lowerLeftY = y;
    this->boxWidth = width;
    this->boxHeight = height;
    
    GLfloat data[] = {
        -1.0, -1.0,
        -1.0,  1.0,
         1.0, -1.0,
        
        -1.0,  1.0,
         1.0, -1.0,
         1.0,  1.0,
    };
    
    switch (type) {
        case default_left: {
            this->buttons.push_back(Button(*this->buttonShader, this->window, 0.25, this->nextPropertyHeight, 0.5, 0.067, this->lowerLeftX, this->lowerLeftY, this->boxWidth, this->boxHeight, "settings", "Settings"));
            
            this->nextPropertyHeight -= 0.1;
            
            //Reminder: x, y, Race, maxHealth, maxEnergy, attack, attackStyle, vision, range, cost, startDirection, controller
            this->buttons.push_back(Button(*this->buttonShader, this->window, 0.25, this->nextPropertyHeight, 0.5, 0.067, this->lowerLeftX, this->lowerLeftY, this->boxWidth, this->boxHeight, "make_creature,Human,100,4,30,1,1,1,NORTH", "New Melee"));
            
            this->nextPropertyHeight -= 0.1;
            
            this->buttons.push_back(Button(*this->buttonShader, this->window, 0.25, this->nextPropertyHeight, 0.5, 0.067, this->lowerLeftX, this->lowerLeftY, this->boxWidth, this->boxHeight, "make_creature,Human,70,3,30,1,3,1,NORTH", "New 3-Ranged"));
            
            this->nextPropertyHeight -= 0.1;
            
            break;
            
        } case default_bottom: {
            
            this->buttons.push_back(Button(*this->buttonShader, this->window, 0.0, 0.0, 0.25, 1.0, this->lowerLeftX, this->lowerLeftY, this->boxWidth, this->boxHeight, "make_building,300,1", "New Building"));
            
            break;
        
        } case creature: {
            
            //Create the displayBar for health that will be added to the map
            DisplayBar healthBar(this->displayBarShader, this->window, 0.125, this->nextPropertyHeight, 0.75, 0.05, this->lowerLeftX, this->lowerLeftY, this->boxWidth, this->boxHeight, 0, "Health: ", HealthBar, glm::vec3(0.2, 0.4, 0.2), glm::vec3(0.67, 0.0, 0.0), glm::vec3(0.5, 0.5, 0.5));
            
            //Inserts a display bar into the map with the key health
            this->displayBars.insert(std::pair<DisplayBarType, DisplayBar>(HealthBar, healthBar));
            
            this->nextPropertyHeight -= 0.1;
            
            //Create the displayBar for energy that will be added to the map
            DisplayBar energyBar(this->displayBarShader, this->window, 0.125, this->nextPropertyHeight, 0.75, 0.05, this->lowerLeftX, this->lowerLeftY, this->boxWidth, this->boxHeight, 0, "Energy: ", EnergyBar, glm::vec3(0.2, 0.2, 0.4), glm::vec3(0.67, 0.0, 0.0), glm::vec3(0.5, 0.5, 0.5));
            
            //Insert the display bar into the map with the key energy
            this->displayBars.insert(std::pair<DisplayBarType, DisplayBar>(EnergyBar, energyBar));
            
            this->nextPropertyHeight -= 0.1;
            
            //Create the box for attack info that will be added to the map
            Box attackBox(*this->buttonShader, this->window, 0.05, this->nextPropertyHeight, 0.425, 0.067, this->lowerLeftX, this->lowerLeftY, this->boxWidth, this->boxHeight, "Attack: ", creature_attack);
            
            //Insert the box into with the key creature_
            this->boxMap.insert(std::pair<DisplayBoxType, Box>(creature_attack, attackBox));
            
            //Create the box for range info that will be added to the map
            Box rangeBox(*this->buttonShader, this->window, 0.525, this->nextPropertyHeight, 0.425, 0.067, this->lowerLeftX, this->lowerLeftY, this->boxWidth, this->boxHeight, "Range: ", creature_range);
            
            //Insert the box into with the key creature_range
            this->boxMap.insert(std::pair<DisplayBoxType, Box>(creature_range, rangeBox));
            
            this->nextPropertyHeight -= 0.1;
            
            //Create the box for vision info that will be added to the map
            Box visionBox(*this->buttonShader, this->window, 0.05, this->nextPropertyHeight, 0.425, 0.067, this->lowerLeftX, this->lowerLeftY, this->boxWidth, this->boxHeight, "Vision: ", creature_vision);
            
            //Insert the box into with the key creature_vision
            this->boxMap.insert(std::pair<DisplayBoxType, Box>(creature_vision, visionBox));
            
            //Create the box for race info that will be added to the map
            Box raceBox(*this->buttonShader, this->window, 0.525, this->nextPropertyHeight, 0.425, 0.067, this->lowerLeftX, this->lowerLeftY, this->boxWidth, this->boxHeight, "Race: ", creature_race);
            
            //Insert the box into with the key creature_race
            this->boxMap.insert(std::pair<DisplayBoxType, Box>(creature_race, raceBox));
            
            this->nextPropertyHeight -= 0.1;
            
            break;
            
        } case building: {
            
            //Create the displayBar for health that will be added to the map
            DisplayBar healthBar(this->displayBarShader, this->window, 0.125, this->nextPropertyHeight, 0.75, 0.05, this->lowerLeftX, this->lowerLeftY, this->boxWidth, this->boxHeight, 0, "Health: ", HealthBar, glm::vec3(0.2, 0.4, 0.2), glm::vec3(0.67, 0.0, 0.0), glm::vec3(0.5, 0.5, 0.5));
            
            //Inserts a display bar into the map with the key health
            this->displayBars.insert(std::pair<DisplayBarType, DisplayBar>(HealthBar, healthBar));
            
            this->nextPropertyHeight -= 0.1;
            
            break;
            
        } default: //For now includes the default_right and settings interfaces
            
            break;
    }
    
    this->initialPropertyHeight = this->nextPropertyHeight;
    
    //Draw with OpenGL
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    
    //First we bind the VAO
    glBindVertexArray(this->VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
    
    //Next we tell OpenGL how to interpret the array
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Interface::render(bool mouseDown, bool mouseUp, bool buttonInteraction) {
    if (active) {
        //Get updated information about the viewport
//        this->updateViewport();
        
        this->window->setViewport(this->lowerLeftX, this->lowerLeftY, this->boxWidth, this->boxHeight);
        
        //Set the box where OpenGL can draw
//        glScissor(this->lowerLeftX, this->lowerLeftY, this->boxWidth, this->boxHeight);
        
        //Bind the VAO and draw shapes
        this->interfaceShader->use();
        
        glBindVertexArray(this->VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
        
        
        
        for (auto box = this->boxes.begin(); box != this->boxes.end(); box++) {
            box->render();
        }
        
        for (auto box = this->boxMap.begin(); box != this->boxMap.end(); box++) {
            box->second.render();
        }
        
        for (auto button = this->buttons.begin(); button != this->buttons.end(); button++) {
            button->render(mouseDown, mouseUp, buttonInteraction);
        }
        
        for (auto displayBar = this->displayBars.begin(); displayBar != this->displayBars.end(); displayBar++) {
            displayBar->second.render();
        }
        
        glm::ivec2 framebufferSize = this->window->framebufferSize();
        
        //Reset window information for game rendering
//        this->window->setViewport(0.0, 0.0, framebufferSize.x, framebufferSize.y);
//        this->window->setViewport(framebufferSize.x / 6.0, framebufferSize.y / 4.0, framebufferSize.x * 2.0 / 3.0, framebufferSize.x * 3.0 / 4.0); //So that there is a 6th of the screen on both sides, and the bottom quarter of the screen left for interfaces
    }
}

void Interface::addButton(std::string action, std::string text, Texture texture) {
    this->buttons.push_back(Button(*this->buttonShader, this->window, 0.25, this->nextPropertyHeight, 0.5, 0.067, this->lowerLeftX, this->lowerLeftY, this->boxWidth, this->boxHeight, action, text, texture));
    
    this->nextPropertyHeight -= 0.1;
}

void Interface::addBox(std::string text, Texture texture) {
    this->boxes.push_back(Box(*this->buttonShader, this->window, 0.25, this->nextPropertyHeight, 0.5, 0.067, this->lowerLeftX, this->lowerLeftY, this->boxWidth, this->boxHeight, text, other, texture));
    
    this->nextPropertyHeight -= 0.1;
}

bool Interface::removePropertyLayer() {
    if (this->nextPropertyHeight + 0.1 < this->initialPropertyHeight) {
        this->buttons.pop_back();
        this->nextPropertyHeight += 0.1;
        return true;
    } else {
        return false;
    }
}

//void Interface::updateViewport() {
//    GLuint oldViewportWidth = this->viewportWidth;
//    GLuint oldViewportHeight = this->viewportHeight;
//    
//    glfwGetFramebufferSize(this->window, &this->viewportWidth, &this->viewportHeight);
//    
//    //If the viewport size has changed, update the interface viewports by multiplying them by the ratio
//    
//    //Update the width
//    if (oldViewportWidth != this->viewportWidth) {
//        this->lowerLeftX *= (this->viewportWidth / oldViewportWidth);
//        this->boxWidth *= (this->viewportWidth / oldViewportWidth);
//    }
//    
//    //Update the height
//    if (oldViewportHeight != this->viewportHeight) {
//        this->lowerLeftY *= (this->viewportHeight / oldViewportHeight);
//        this->boxHeight *= (this->viewportHeight / oldViewportHeight);
//    }
//}
