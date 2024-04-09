#include <iostream>
#include <fstream>
#include <string>
#include "logic.h"

using std::cout, std::endl, std::ifstream, std::string, std::ifstream;

int const INT32_MAX_CUSTOM = 2147483647;
int const INT32_MIN_CUSTOM = -2147483648;

bool multiplicationExceedsInt32Max(int a, int b) {
    if (a > 0 && b > 0) {
        return a > INT32_MAX_CUSTOM / b;
    } else if (a < 0 && b < 0) {
        return a < INT32_MAX_CUSTOM / b;
    } else if (a < 0 && b > 0) {
        return b > INT32_MIN_CUSTOM / a;
    } else if (a > 0 && b < 0) {
        return a > INT32_MIN_CUSTOM / b;
    }
    return false;
}

/**
 * TODO: Student implement this function
 * Load representation of the dungeon level from file into the 2D map.
 * Calls createMap to allocate the 2D array.
 * @param   fileName    File name of dungeon level.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object by reference to set starting position.
 * @return  pointer to 2D dynamic array representation of dungeon map with player's location., or nullptr if loading fails for any reason
 * @updates  maxRow, maxCol, player
 */
char** loadLevel(const string& fileName, int& maxRow, int& maxCol, Player& player) {
    ifstream file(fileName);
    if (!file.is_open()){
        file.close();
        return nullptr;
    }

    file >> maxRow >> maxCol >> player.row >> player.col;

    if (file.fail()) {
        file.close();
        return nullptr;
    }

    if (maxRow <= 0 || maxCol <= 0 || maxRow > 999999 || maxCol > 999999 || player.row < 0 || player.col < 0 || player.row >= maxRow || player.col >= maxCol){
        file.close();
        return nullptr;
    }

    if (multiplicationExceedsInt32Max(maxRow, maxCol)){
        file.close();
        return nullptr;
    }

    char** map = createMap(maxRow, maxCol);
    if (map == nullptr){
        file.close();
        deleteMap(map, maxRow);
        return nullptr;
    }

    bool containsDoorOrExit = false;
    for (int i = 0; i < maxRow; ++i) {
        for (int j = 0; j < maxCol; ++j) {
            if(file >> map[i][j]){
                if (map[i][j] != TILE_OPEN && map[i][j] != TILE_TREASURE && map[i][j] != TILE_AMULET && map[i][j] != TILE_PILLAR && map[i][j] != TILE_MONSTER && map[i][j] != TILE_DOOR && map[i][j] != TILE_EXIT){
                    file.close();
                    deleteMap(map, maxRow);
                    return nullptr;
                }

                if (map[i][j] == TILE_DOOR || map[i][j] == TILE_EXIT){
                    containsDoorOrExit = true;
                }
            }else{
                file.close();
                deleteMap(map, maxRow);
                return nullptr;
            
            }
        }
    }

    char c;
    if(file >> c)
    {
        file.close();
        deleteMap(map, maxRow);
        return nullptr;
    }
    

    if (!containsDoorOrExit){
        file.close();
        deleteMap(map, maxRow);
        return nullptr;
    }

    if (file.fail()) {
        file.close();
        deleteMap(map, maxRow);
        return nullptr;
    }

    if (map[player.row][player.col] != TILE_OPEN){
        file.close();
        deleteMap(map, maxRow);
        return nullptr;
    }

    map[player.row][player.col] = TILE_PLAYER;

    file.close();
    return map;
}

/**
 * TODO: Student implement this function
 * Translate the character direction input by the user into row or column change.
 * That is, updates the nextRow or nextCol according to the player's movement direction.
 * @param   input       Character input by the user which translates to a direction.
 * @param   nextRow     Player's next row on the dungeon map (up/down).
 * @param   nextCol     Player's next column on dungeon map (left/right).
 * @updates  nextRow, nextCol
 */
void getDirection(char input, int& nextRow, int& nextCol) {
    switch (input)
    {
    case 'w':
        nextRow--;
        break;
    case 's':
        nextRow++;
        break;
    case 'a':
        nextCol--;
        break;
    case 'd':
        nextCol++;
        break;
    default:
        break;
    }
}

/**
 * TODO: [suggested] Student implement this function
 * Allocate the 2D map array.
 * Initialize each cell to TILE_OPEN.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @return  2D map array for the dungeon level, holds char type.
 */
char** createMap(int maxRow, int maxCol) {
    if (maxRow <= 0 || maxCol <= 0)
        return nullptr;

    char** map = new char*[maxRow];
    for (int i = 0; i < maxRow; ++i) {
        map[i] = new char[maxCol];
        for (int j = 0; j < maxCol; ++j) {
            map[i][j] = TILE_OPEN;
        }
    }

    return map;
}

/**
 * Deallocates the 2D map array.
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @return None
 * @update map, maxRow
 */
void deleteMap(char**& map, int& maxRow) {
    if (map == nullptr) {
        maxRow = 0;
        return;
    }

    for (int i = 0; i < maxRow; ++i) {
        delete[] map[i];
    }
    delete[] map;
    map = nullptr;
    maxRow = 0;
}

/**
 * TODO: Student implement this function
 * Resize the 2D map by doubling both dimensions.
 * Copy the current map contents to the right, diagonal down, and below.
 * Do not duplicate the player, and remember to avoid memory leaks!
 * You can use the STATUS constants defined in logic.h to help!
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height), to be doubled.
 * @param   maxCol      Number of columns in the dungeon table (aka width), to be doubled.
 * @return  pointer to a dynamically-allocated 2D array (map) that has twice as many columns and rows in size.
 * @update maxRow, maxCol
 */
char** resizeMap(char** map, int& maxRow, int& maxCol) {
    if (map == nullptr || maxRow <= 0 || maxCol <= 0)
        return nullptr;

    int newRow = maxRow * 2;
    int newCol = maxCol * 2;

    if (multiplicationExceedsInt32Max(newRow, newCol))
        return nullptr;

    char** resizedMap = createMap(maxRow * 2, maxCol * 2);
    if (resizedMap == nullptr) {
        deleteMap(resizedMap, newRow);
        return nullptr;
    }

    for (int i = 0; i < maxRow; ++i) {
        for (int j = 0; j < maxCol; ++j) {
            if (map[i][j] == TILE_PLAYER)
            {
                resizedMap[i][j] = map[i][j];
                resizedMap[i + maxRow][j] = TILE_OPEN;
                resizedMap[i][j + maxCol] = TILE_OPEN;
                resizedMap[i + maxRow][j + maxCol] = TILE_OPEN;
            }else{
                resizedMap[i][j] = map[i][j];
                resizedMap[i + maxRow][j] = map[i][j];
                resizedMap[i][j + maxCol] = map[i][j];
                resizedMap[i + maxRow][j + maxCol] = map[i][j];
            }
        }
    }

    deleteMap(map, maxRow);
    maxRow = newRow;
    maxCol = newCol;

    return resizedMap;
}

/**
 * TODO: Student implement this function
 * Checks if the player can move in the specified direction and performs the move if so.
 * Cannot move out of bounds or onto TILE_PILLAR or TILE_MONSTER.
 * Cannot move onto TILE_EXIT without at least one treasure. 
 * If TILE_TREASURE, increment treasure by 1.
 * Remember to update the map tile that the player moves onto and return the appropriate status.
 * You can use the STATUS constants defined in logic.h to help!
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object to by reference to see current location.
 * @param   nextRow     Player's next row on the dungeon map (up/down).
 * @param   nextCol     Player's next column on dungeon map (left/right).
 * @return  Player's movement status after updating player's position.
 * @update map contents, player
 */
int doPlayerMove(char** map, int maxRow, int maxCol, Player& player, int nextRow, int nextCol) {
    if (nextRow < 0 || nextRow >= maxRow || nextCol < 0 || nextCol >= maxCol || map[nextRow][nextCol] == TILE_PILLAR || map[nextRow][nextCol] == TILE_MONSTER || (map[nextRow][nextCol] == TILE_EXIT && player.treasure == 0))
        return STATUS_STAY;
    else if (map[nextRow][nextCol] == TILE_TREASURE){
        player.treasure++;
        map[player.row][player.col] = TILE_OPEN;
        player.row = nextRow;
        player.col = nextCol;
        map[player.row][player.col] = TILE_PLAYER;
        return STATUS_TREASURE;
    } else if (map[nextRow][nextCol] == TILE_AMULET){
        map[player.row][player.col] = TILE_OPEN;
        player.row = nextRow;
        player.col = nextCol;
        map[player.row][player.col] = TILE_PLAYER;
        return STATUS_AMULET;
    } else if (map[nextRow][nextCol] == TILE_DOOR){
        map[player.row][player.col] = TILE_OPEN;
        player.row = nextRow;
        player.col = nextCol;
        map[player.row][player.col] = TILE_PLAYER;
        return STATUS_LEAVE;
    } else if (map[nextRow][nextCol] == TILE_EXIT && player.treasure > 0){
        map[player.row][player.col] = TILE_OPEN;
        player.row = nextRow;
        player.col = nextCol;
        map[player.row][player.col] = TILE_PLAYER;
        return STATUS_ESCAPE;
    } else{
        map[player.row][player.col] = TILE_OPEN;
        player.row = nextRow;
        player.col = nextCol;
        map[player.row][player.col] = TILE_PLAYER;
        return STATUS_MOVE;
    }
}

/**
 * TODO: Student implement this function
 * Update monster locations:
 * We check up, down, left, right from the current player position.
 * If we see an obstacle, there is no line of sight in that direction, and the monster does not move.
 * If we see a monster before an obstacle, the monster moves one tile toward the player.
 * We should update the map as the monster moves.
 * At the end, we check if a monster has moved onto the player's tile.
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object by reference for current location.
 * @return  Boolean value indicating player status: true if monster reaches the player, false if not.
 * @update map contents
 */
bool doMonsterAttack(char** map, int maxRow, int maxCol, const Player& player) {
    bool playerCaught = false;

    for(int a = player.row; a > -1; a--)
    {
        if(map[a][player.col] != TILE_OPEN && map[a][player.col] != TILE_MONSTER && map[a][player.col] != TILE_PLAYER && map[a][player.col] != TILE_DOOR){
            break;
        }
        
        if(map[a][player.col] == TILE_MONSTER && a+1 < maxRow)
        {
            map[a+1][player.col] = TILE_MONSTER;
            map[a][player.col] = TILE_OPEN;
            if(map[a+1][player.col] == map[player.row][player.col])
                playerCaught = true;
        }
    }

    for(int b = player.row; b < maxRow; b++)
    { 
        if(map[b][player.col] != TILE_OPEN && map[b][player.col] != TILE_MONSTER && map[b][player.col] != TILE_PLAYER)
        {
            break;
            
        }
        if(map[b][player.col] == TILE_MONSTER && b-1 > -1)
        {
            map[b-1][player.col] = TILE_MONSTER;
            map[b][player.col] = TILE_OPEN;
            if(map[b-1][player.col] == map[player.row][player.col])
                playerCaught = true;
        }
    }

    for(int c = player.col; c > -1; c--)
    {
        if(map[player.row][c] != TILE_OPEN && map[player.row][c] != TILE_MONSTER && map[player.row][c] != TILE_PLAYER){ 
            break;
        }
        if(map[player.row][c] == TILE_MONSTER && c+1 < maxCol)
        {
            map[player.row][c+1] = TILE_MONSTER;
            map[player.row][c] = TILE_OPEN;
            if(map[player.row][c+1] == map[player.row][player.col])
                playerCaught = true;
        }
    }
    
    for(int d = player.col; d < maxCol; d++)
    {
        if(map[player.row][d] != TILE_OPEN && map[player.row][d] != TILE_MONSTER && map[player.row][d] != TILE_PLAYER)
        {
            break;
        }
        if(map[player.row][d] == TILE_MONSTER && d-1 > -1)
        {
            map[player.row][d-1] = TILE_MONSTER;
            map[player.row][d] = TILE_OPEN;
            if(map[player.row][d-1] == map[player.row][player.col])
                playerCaught = true;
        }
    }

    return playerCaught;
}
