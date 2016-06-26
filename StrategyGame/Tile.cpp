//
//  Tile.cpp
//  Game
//
//  Created by Jake Sanders on 6/22/16.
//  Copyright © 2016 Jake Sanders. All rights reserved.
//

#include "Tile.hpp"

//Constructors
Tile::Tile(Terrain terrain, unsigned int x, unsigned int y) : tileX(x), tileY(y) {
    this->tileTerrain = terrain;
}

//Destructor

/** Deletes this tile.
 */
Tile::~Tile() {
    delete this->tileCreature;
}

//Public member functions
/** Sets a creature as the creature located in this tile. Deletes the old creature to avoid memory leaks, and adjusts whether the tile is occupied.
 *
 * @param creature A pointer to the new creature. If nullptr, then the spot becomes empty.
 */
void Tile::setCreature(Creature *creature) {
    if (this->tileCreature != nullptr)
        delete this->tileCreature; //Prevent memory leaks
    
    this->tileCreature = creature; //Set the creature at this tile as the inputted creature
}