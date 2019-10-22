#pragma once

#include <iostream>
#include <cmath>

#include "ospcommon/math/vec.h"

ospcommon::math::vec3i indexToPosition(int index, ospcommon::math::vec3i dims)
{
    int z = index / (dims.x * dims.y);
    int left = std::remainder(index, dims.x * dims.y);

    int y = left / dims.x;
    int x = std::remainder(left, dims.x);

    return ospcommon::math::vec3i(x, y, z);
}

ospcommon::math::vec2i pixelToTileID(ospcommon::math::vec2f pixel, ospcommon::math::vec2i tileSize)
{
    // std::cout << "pixel (" << pixel.x << ", " << pixel.y << ") " << std::endl;
    ospcommon::math::vec2i tileId = ospcommon::math::vec2i(std::ceil(pixel.x / tileSize.x), std::ceil(pixel.y / tileSize.y));

    // std::cout << 
    return tileId;
}

void remove(std::vector<ospcommon::math::vec2i> &v)
{
	auto end = v.end();
	for (auto it = v.begin(); it != end; ++it) {
		end = std::remove(it + 1, end, *it);
	}

	v.erase(end, v.end());
}