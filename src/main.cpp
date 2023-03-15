#include "dungeongen.h"
#include "tileset.h"
#include "types.h"
#include "noisefunc.h"

#include <chrono>
#include <iostream>

using namespace std::chrono;

void printASCIIDungeon(Dungeon2DMap &d, ASCIIDungeonTileset &tileSet);

static void run_dungeon_gen_with_rooms() {
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

static void run_dungeon_gen_default(unsigned int width, unsigned int height) {
    ASCIIDungeonTileset tileSet;

    system_clock::time_point now = system_clock::now();
    unsigned seed = static_cast<unsigned>(system_clock::to_time_t(now));

    DungeonGenerator dGen(seed);
    Dungeon2DMap dungeon(width, height);

    NoiseFunction nf(seed);
    dGen.generate(nf, dungeon, tileSet);

    printASCIIDungeon(dungeon, tileSet);
}

enum class RunMode : int {
    Default = 0,
    Rooms,
    Count
};

struct RunParams {
    unsigned int width = 0;
    unsigned int height = 0;
    RunMode mode = RunMode::Default;
    bool parse_status = false;
};

static RunParams parse_command_line(int argc, char *argv[]) {
    RunParams p;
    
    if (argc <= 1) {
        p.parse_status = true;
        return p;
    }

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-w") {
            if (i == argc-1)
                return p;
            
            std::string v = argv[i+1];
            p.width = std::stoul(v);
        } else if (arg == "-h") {
            if (i == argc-1)
                return p;

            std::string v = argv[i+1];
            p.height = std::stoul(v);
        } else if (arg == "-m") {
            if (i == argc-1)
                return p;

            std::string v = argv[i+1];
            if (v == "rooms") 
                p.mode = RunMode::Rooms;
        }
    }

    p.parse_status = true;
    return p;
}

int main(int argc, char *argv[]) {
    const unsigned width = 80;
    const unsigned height = 40;

    RunParams p = parse_command_line(argc, argv);
    if (!p.parse_status) {
        std::cout << "Error: invalid command line parameters.\n";
        return -1;
    }

    if (p.width <= 0 || p.height <= 0) {
        p.width = width;
        p.height = height;
    }

    switch (p.mode) {
        case RunMode::Default: {
            run_dungeon_gen_default(p.width, p.height);
            break;
        }
        case RunMode::Rooms: {
            run_dungeon_gen_with_rooms();
            break;
        }
        default: {
            std::cout << "Error: invalid run mode.\n";
            return -1;
        }
    }

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
