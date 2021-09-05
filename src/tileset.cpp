#include "tileset.h"

unsigned DungeonTileset::getNumTypes() const {
    return DungeonTileset::TileTypes::MaxTypes;
}

ASCIIDungeonTileset::ASCIIDungeonTileset() {}

unsigned ASCIIDungeonTileset::getNumSubTypes(TileType type) const {
    return 1;
}

char ASCIIDungeonTileset::get(TileType type, unsigned subType) const {
    return TileChars[type];
}