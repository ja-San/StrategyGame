# Strategy Game (name pending)

This game will be a turn-based strategy game, where each player will have to successfully conquer the opponent.

Currently, each player starts with a number of creatures and a tower unit. To win, the player must destroy the opponent's tower. This is just a preliminary and far overly simple version of the game.

This game is still being worked on.

## Units

### Creatures

* Health
* Attack (How much damage it deals)
* Energy (How far it can move)
Energy regenrates slowly over time. A creature can only move one tile (horizontal or vertical only) per energy. Additionally, attacking uses all remaining energy.
* Range (How far it can attack)
Melee units are defined as only being able to attack one tile away.
* Race
Races include Human, Elf, Dwarf, Orc, Goblin, Undead, and Vampire. At the moment, it has no effect.

Creatures can have special abilities. These abilities may either be called on death or may be added to the side menu displaying the creature to be clicked by the player.

### Buildings

Buildings are like creatures, but they cannot move nor attack. Buildings can have special abilities like creatures. Currently, the initial buildings have been set such that when killed, their controller dies.

## Menu

The game can either be run as a hosting client or just as a client. One player must host, and other clients can join if they are on the same local network. To connect the host's name must be entered. Currently it is displayed on the console of the hosting player. When ready, the host can begin.

The project has been written such that the host and client are completely separatable. For that reason, a server could run the host and connect over the internet to individual clients.

In the game, there are three main interface panels of the GUI, the left and right sides and the bottom. The bottom is used to give messages and game updates. The left will have general settings and buttons, but currently only has a "Leave Game" option that returns to the menu. The right menu is empty initially, but is updated to show information of the selected tile. If that is a creature or building, its health, energy, and stats will be displayed.

## Program information

This game is programmed directly in OpenGL in C++ (and GLSL), using C sockets. It uses the following libraries:
* C++ 11 Standard Library
* GLEW 1.13.0
Helps to define many of the OpenGL functions and make it more portable.
* GLFW 3.2
Window handling library.
* SOIL (Simple OpenGL Image Library)
Loads in images from files to use as OpenGL textures.
* FreeType 6
Used to turn fonts into renderable textures.
* GLM (GL Mathematics)
__Header Only__ Handles vectors and matrix math, especially for graphical calculations.

PLease check the documentation if interested; I tried to make most of the functions thoroughly documented so they are understandable.

## Known Bugs

* Max camera distance gets stuck after going too far, such that no more movement is possible
* Window resizing doesn't work visually
* Sometimes crashes when one client is closed
* May crash after clicking the back button from connecting as a host to connecting as a client

## Currently In Progress

* Adding abilities for creatures, which arer displayed in the interface as a button
* Max camera distance

## Upcoming Additions

* Vision 
* More polished menu
* Better/prettier textures
* More complex and interesting game mechanics

It's still very much in progress, but the engine and underlying code is here, even though the game itself is very basic.

## Authors

[Jake Sanders](https://github.com/ja-San)
* Inital planning
* Underlying game engine
* Host mechanics
* Client side code
* C Socket wrapper classes
* OpenGL
* GUI and window

[Michael Caosun](https://github.com/theonlycaosun)
* Initial planning
* Attack styles / combat details
* RTS functionality (energy regeneration)
* Bug fixes

Additionaly, consultations with [Ben Spector](https://github.com/Sydriax) were also very useful
