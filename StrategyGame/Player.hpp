//
//  Player.hpp
//  Strategy Game
//
//  Created by Jake Sanders on 6/25/16.
//  Copyright © 2016 Jake Sanders. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include "Macros.h"

//Standard library includes
#include <array>
#include <queue>
#include <string>

//GLFW: Window functionality
#include <GLFW/glfw3.h>

//GLM: OpenGL mathematics for rotations, translations, dilations
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

//Local includes
#include "Board.hpp"

//Preprocessor Directives
#define BOARD_WIDTH 12
#define NUMBER_OF_TILES BOARD_WIDTH * BOARD_WIDTH
#define INDICES_PER_TILES 2
#define NUMBER_OF_PLAYERS 2

#define NO_SELECTION glm::ivec2(-1, -1)
#define INTERFACE_BOX_SELECTION glm::ivec2(-2, -2)

#define TILE_STYLE 0
#define TILE_HOVER 1
#define TILE_VISION 2

#define WHITE glm::vec3(1.0f, 1.0f, 1.0f)
#define GREY glm::vec3(0.625f, 0.625f, 0.625f)
#define RED glm::vec3(1.0f, 0.625f, 0.625f)
#define YELLOW glm::vec3(1.0f, 1.0f, 0.5f)
#define GREEN glm::vec3(0.62f, 1.0f, 0.625f)
#define CYAN glm::vec3(0.625f, 1.0f, 1.0f)
#define BLUE glm::vec3(0.625f, 0.625f, 1.0f)
#define PURPLE glm::vec3(0.5f, 0.1f, 0.9f)

#define HOVER_EFFECT glm::vec3(0.75f, 0.75f, 0.75f)

//TILE_STYLE
#define REGULAR 0
#define SELECTED 1
#define ATTACKABLE 2
#define REACHABLE 3

//HOVER
#define NO_HOVERING 0
#define HOVERING 1

//VISION
#define UNEXPLORED 0
#define EXPLORED 1
#define VISIBLE 2

class Player {
public:
    //Constructor
    Player(Board* board, unsigned int num);
    
    //Public properties
    
    Board* board;
    
    //Public member functions
    
    /*!
     * Reset the style of all tiles.
     */
    void resetAllTiles();
    
    /*!
     * A function to set the selected tile. If the x or y is out of range and the input isn't NO_SELECTION or INTERFACE_BOX_SELECTION, then nothing will happen and false will be returned. To pass NO_SELECTION or other glm::ivec2 macros as arguments, do this: selectTile(NO_SELECTION.x, NO_SELECTION.y);
     *
     * @param x An unsigned int representing the x location of the tile on the board.
     * @param y An unsigned int representing the y location of the tile on the board.
     *
     * @return Whether the tile was successfully selected.
     */
    bool selectTile(unsigned int x, unsigned int y);
    
    /*!
     * A function to set the style tile. If the x or y is out of range, then nothing will happen and false will be returned.
     *
     * @param x An unsigned int representing the x location of the tile on the board.
     * @param y An unsigned int representing the y location of the tile on the board.
     * @param style An unsigned int representing the style to set for the given tile.
     *
     * @return Whether the tile was successfully given the new style.
     */
    bool setStyle(unsigned int x, unsigned int y, unsigned int style);
    
    /*!
     * A function that updates the offset of each creature to cause movement animation. This should be called once every frame.
     *
     * @param deltaTime The time since the last fram, to multiply by the velocity to get a constant distance. This keeps animation speed constant on different machines.
     */
    void updateCreatures(float deltaTime);
    
    /*!
     * A function to update the selected tile based on mouse clicks.
     *
     * @param mouseDown A boolean representing if the mouse is down. 
     * @param mousePos A glm::ivec2 representing the tile the mouse is currently at. This should be calculated on the client side and sent to the server.
     * @param currentTime An unsigned int representing the time of the current grame.
     */
//    void updateSelected(bool mouseDown, glm::ivec2 mousePos, unsigned int currentTime);
    
    //Public get functions
    
    /*!
     * @return The current selected tile, in the form of a glm::ivec2. The coordinates are in terms of board coordinates.
     */
    glm::ivec2 tileSelected();
    
    /*!
     * @return The color of the tile at the specified location.
     */
    glm::vec3 tileColor(unsigned int x, unsigned int y);
    
    std::vector<GLuint> getPath(GLuint x, GLuint y, GLuint destinationX, GLuint destinationY);
    
private:
    
    //Private properties
    
    //Player data
    unsigned int playerNum;
    
    //Board data
    glm::ivec2 selectedTile = glm::ivec2(-1, -1);
    
    std::vector<std::vector<std::array<int, 3> > > boardInfo; //Contains an array of ints (represented by macros) that give information:
    /*
     * [0]: Tile style (whether it is selected, attackable, reachable, etc...)
     * [1]: Whether the mouse is hovering, either as TRUE or FALSE
     */
    
    std::vector<std::vector<std::queue<std::string> > > tileActions; //For each tile, contains a queue of action strings, the first to be done when the tile is clicked if it is reachable
    
    //Private member functions
    
    /*!
     * Resolve the next tile action at the given location
     *
     * @param x The x coordinate of the tile to resolve.
     * @param y The y coordinate of the tile to resolve.
     */
    void resolveTileAction(unsigned int x, unsigned int y);
    
    bool moveAdjacent(unsigned int x, unsigned int y, int direction, float deltaTime);
    
    /*!
     * A function to select a creature and and make nearby tiles properly stylized (reachable ones and attackable, for instance). If an error occurs (see below) no error is thrown, instead false is returned and nothing happens.
     *
     * @param x An unsigned int representing the x location of the creature on the board.
     * @param y An unsigned int representing the y location of the creature on the board.
     *
     * @return Whether the creature was successfully selected or if an error prevented this. Errors include if x or y is out of range, or if there is no creature at the designated spot.
     */
    bool selectCreature(unsigned int x, unsigned int y);
};

#endif /* Player_hpp */
