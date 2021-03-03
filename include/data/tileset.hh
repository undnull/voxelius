/*
 * tileset.hh
 * Created: 2021-03-03, 20:35:56.
 * Copyright (C) 2021, Kirill GPRB.
 */
#pragma once
#include <data/tile.hh>
#include <gfx/texture.hh>

namespace data
{
class TileSet final {
public:
    TileSet();

    bool load(const char *path);

    const tile &getTile(size_t id) const;
    const gfx::Texture &getTexture() const;

private:
    gfx::Texture texture;
    std::vector<tile> tiles;
    tile default_tile;
};

inline const tile &TileSet::getTile(size_t id) const
{
    if(id < tiles.size())
        return tiles[id];
    return default_tile;
}

inline const gfx::Texture &TileSet::getTexture() const
{
    return texture;
}
} // namespace data
