#ifndef _dungeongen_h_
#define _dungeongen_h_

#include "types.h"

class DungeonTileset;
class NoiseFunction;

typedef Grid2D Dungeon2DMap;
typedef Rect Room;

class DungeonGenerator {
public:
    struct RoomHints {
        unsigned roomWidth;
        unsigned roomHeight;
        unsigned roomMaxWidth;
        unsigned roomMaxHeight;
        unsigned numRooms;
        unsigned numMaxRooms;
        unsigned maxRetries;
        bool randomRoomSize;
        bool randomNumRooms;
        bool discardInvalidRoom;
        bool skipRoomIfInvalid;
        bool mergeRooms;
        bool connectRooms;
    };

    struct Params {
       RoomHints room;
    };

    DungeonGenerator(unsigned seed = 0) : m_seed(seed) {};

    void generate(Params& params, Dungeon2DMap& dungeon, DungeonTileset& tileSet);
    void generate(NoiseFunction& nf, Dungeon2DMap& dungeon, DungeonTileset& tileSet);

private:
    unsigned m_seed;

    bool isRoomValidInDungeon(Room& room, Dungeon2DMap& dungeon) const;
    void paintRoom(Room& room, Dungeon2DMap& dungeon, bool mergeRooms, bool isValid);
};

#endif // _dungeongen_h_