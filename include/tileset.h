#ifndef _tileset_h_
#define _tileset_h_

#include "types.h"

class Tileset {
public:
    virtual unsigned getNumTypes() const = 0;
    virtual unsigned getNumSubTypes(TileType type) const = 0;
};

class DungeonTileset : public Tileset {
public:
    enum TileTypes {
        Empty = 0,
        Floor,
        Wall,
        Door,
        MaxTypes
    };

    virtual unsigned getNumTypes() const;
};

class ASCIIDungeonTileset : public DungeonTileset {
public:
    ASCIIDungeonTileset();

    virtual unsigned getNumSubTypes(TileType type) const;
    char get(TileType type, unsigned subType = 0) const;

private:
    const char *TileChars = " .#"; 
};

#endif // _tileset_h_