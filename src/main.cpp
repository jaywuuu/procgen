#include "dungeongen.h"
#include "tileset.h"
#include "types.h"
#include "noisefunc.h"

#include <chrono>
#include <iostream>

using namespace std::chrono;

void printASCIIDungeon(Dungeon2DMap &d, ASCIIDungeonTileset &tileSet);

void run_dungeon_gen_with_params() {
    const unsigned width = 80;
    const unsigned height = 40;

    ASCIIDungeonTileset tileSet;

    system_clock::time_point now = system_clock::now();
    unsigned seed = static_cast<unsigned>(system_clock::to_time_t(now));

    DungeonGenerator dGen(seed);
    Dungeon2DMap dungeon(width, height);
    DungeonGenerator::Params params = {};
    params.room.roomWidth = 5;
    params.room.roomMaxWidth = 10;
    params.room.roomHeight = 3;
    params.room.roomMaxHeight = 8;
    params.room.numRooms = 4;
    params.room.numMaxRooms = 8;
    params.room.maxRetries = 10;
    params.room.randomRoomSize = true;
    params.room.randomNumRooms = true;
    params.room.discardInvalidRoom = true;
    params.room.skipRoomIfInvalid = false;

    dGen.generate(params, dungeon, tileSet);

    printASCIIDungeon(dungeon, tileSet);
}

int main(int argc, void *argv[]) {
    const unsigned width = 80;
    const unsigned height = 40;

    ASCIIDungeonTileset tileSet;

    system_clock::time_point now = system_clock::now();
    unsigned seed = static_cast<unsigned>(system_clock::to_time_t(now));

    DungeonGenerator dGen(seed);
    Dungeon2DMap dungeon(width, height);

    NoiseFunction nf(seed);
    dGen.generate(nf, dungeon, tileSet);

    printASCIIDungeon(dungeon, tileSet);

    return 0;
}

void printASCIIDungeon(Dungeon2DMap &d, ASCIIDungeonTileset &tileSet) {
    for (unsigned y = 0; y < d.getSizeY(); ++y) {
        for (unsigned x = 0; x < d.getSizeX(); ++x) {
            TileType t = d[y][x];
            std::cout << tileSet.get(t);
        }
        std::cout << std::endl;
    }
}