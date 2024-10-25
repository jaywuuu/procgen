#include "dungeongen.h"
#include "noisefunc.h"
#include "random.h"
#include "tileset.h"

void DungeonGenerator::generate(Params &params, Dungeon2DMap &dungeon,
                                DungeonTileset &tileSet) {
    NoiseFunctionRNG rng(m_seed);

    RoomHints &roomParams = params.room;
    unsigned roomCount = 0;
    unsigned numRooms = roomParams.numRooms;

    unsigned retryCount = 0;

    if (roomParams.randomNumRooms)
        numRooms = rng.getRandUIntInRange(numRooms, roomParams.numMaxRooms);

    while (roomCount < numRooms) {
        if (retryCount >= roomParams.maxRetries)
            break;

        unsigned roomWidth = roomParams.roomWidth;
        unsigned roomHeight = roomParams.roomHeight;

        if (roomParams.randomRoomSize) {
            roomWidth =
                rng.getRandUIntInRange(roomWidth, roomParams.roomMaxWidth);
            roomHeight =
                rng.getRandUIntInRange(roomHeight, roomParams.roomMaxHeight);
        }

        unsigned x = rng.getRandUIntInRange(0, dungeon.getSizeX() - 1);
        unsigned y = rng.getRandUIntInRange(0, dungeon.getSizeY() - 1);
        Room candidate{x, y, x + roomWidth, y + roomHeight};

        bool isRoomValid = isRoomValidInDungeon(candidate, dungeon);

        if (roomParams.discardInvalidRoom && !isRoomValid) {
            if (roomParams.skipRoomIfInvalid)
                ++roomCount;

            ++retryCount;
            continue;
        }

        paintRoom(candidate, dungeon, roomParams.mergeRooms, isRoomValid);

        retryCount = 0;
        ++roomCount;
    }
}

void DungeonGenerator::generate(NoiseFunction &nf, Dungeon2DMap &dungeon,
                                DungeonTileset &tileSet) {
    Grid2D nfVals(dungeon.getSizeX(), dungeon.getSizeY());
    for (unsigned y = 0; y < dungeon.getSizeY(); ++y) {
        for (unsigned x = 0; x < dungeon.getSizeX(); ++x) {
            nfVals[y][x] = nf.noise2D(x, y);
            dungeon[y][x] = DungeonTileset::TileTypes::Floor;
        }
    }

    // scan through values from noise function and draw in walls at local maxima
    for (unsigned y = 0; y < dungeon.getSizeY(); ++y) {
        for (unsigned x = 0; x < dungeon.getSizeX(); ++x) {
            if (x > 0 && x < dungeon.getSizeX() - 1 &&
                nfVals[y][x] > nfVals[y][x - 1] &&
                nfVals[y][x] < nfVals[y][x + 1]) {
                dungeon[y][x] = DungeonTileset::TileTypes::Wall;
            }

            if (y > 0 && y < dungeon.getSizeY() - 1 &&
                nfVals[y][x] > nfVals[y - 1][x] &&
                nfVals[y][x] < nfVals[y + 1][x]) {
                dungeon[y][x] = DungeonTileset::TileTypes::Wall;
            }
        }
    }
}

bool DungeonGenerator::isRoomValidInDungeon(Room &room,
                                            Dungeon2DMap &dungeon) const {
    // TODO: do actual collision detection, I guess.
    if (room.x1 < 0 || room.x2 >= dungeon.getSizeX() || room.y1 < 0 ||
        room.y2 >= dungeon.getSizeY())
        return false;

#if 0
    for (unsigned y = room.y1; y <= room.y2; ++y) {
        for (unsigned x = room.x1; x <= room.x2; ++x) {
            if (dungeon[y][x] != DungeonTileset::TileTypes::Empty)
                return false;
        }
    }
#endif

    return true;
}

void DungeonGenerator::paintRoom(Room &room, Dungeon2DMap &dungeon,
                                 bool mergeRooms, bool isValid) {
    for (unsigned y = room.y1; y <= room.y2; ++y) {
        for (unsigned x = room.x1; x <= room.x2; ++x) {
            if (x == room.x1 || x == room.x2 || y == room.y1 || y == room.y2)
                dungeon[y][x] = DungeonTileset::TileTypes::Wall;
            else
                dungeon[y][x] = DungeonTileset::TileTypes::Floor;
        }
    }
}