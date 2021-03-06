#version 330 core

layout (location = 0) in vec2 position;
layout (location = 1) in int terrainInt;
layout (location = 2) in ivec3 creatureIn;
layout (location = 3) in vec3 tileColorIn;
layout (location = 4) in int damageInt;
layout (location = 5) in float offset;
layout (location = 6) in ivec2 buildingIn;

//Tile
out int terrain;
out vec4 tileColor;

//Creature
out int creature;
out int creatureDirection;
out int creatureController;
out int creatureDamage;
out float creatureOffset;

//Building
out int building;
out int buildingController;

void main() {
    gl_Position = vec4(position.x, position.y, 0.0f, 1.0f);
    
    terrain = terrainInt;
    tileColor = vec4(tileColorIn, 1.0f);
    
    creature = creatureIn.x;
    creatureDirection = creatureIn.y;
    creatureController = creatureIn.z;
    creatureDamage = damageInt;
    creatureOffset = offset;
    
    building = buildingIn.x;
    buildingController = buildingIn.y;
}