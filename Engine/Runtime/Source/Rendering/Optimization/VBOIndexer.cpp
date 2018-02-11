/// Copyright (C) 2018-2019, Cardinal Engine
/// Vincent STEHLY--CALISTO, vincentstehly@hotmail.fr
///
/// This program is free software; you can redistribute it and/or modify
/// it under the terms of the GNU General Public License as published by
/// the Free Software Foundation; either version 2 of the License, or
/// (at your option) any later version.
///
/// This program is distributed in the hope that it will be useful,
/// but WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
/// GNU General Public License for more details.
///
/// You should have received a copy of the GNU General Public License along
/// with this program; if not, write to the Free Software Foundation, Inc.,
/// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

/// \file       Indexer.cpp
/// \date       11/02/2018
/// \project    Cardinal Engine
/// \package    Rendering/Optimization
/// \author     Vincent STEHLY--CALISTO

#include "Rendering/Optimization/VBOIndexer.hpp"

/// \namespace cardinal
namespace cardinal
{

/// \brief Indexes vertices who shares same properties
/// \param inVertices  The input vertices vector
/// \param inColors    The input colors vector
/// \param outIndexes  The output indexes vector
/// \param outVertices The output vertices vector
/// \param outColors   The output colors vector
/* static */ void VBOIndexer::Index(
        const std::vector<glm::vec3> &inVertices,
        const std::vector<glm::vec3> &inColors,

        std::vector<unsigned short> &outIndexes,
        std::vector<glm::vec3> &outVertices,
        std::vector<glm::vec3> &outColors)
{
    std::map<sPackedVertex, unsigned short> output;

    // For each input vertex
    size_t inVerticesSize = inVertices.size();
    for (size_t nVertex = 0; nVertex < inVerticesSize; ++nVertex)
    {
        unsigned short index;
        sPackedVertex pack = {inVertices[nVertex], inColors[nVertex]};

        bool bIsFound = GetSimilarVertexIndex(pack, output, index);

        if (bIsFound)
        {
            outIndexes.push_back(index);
        }
        else
        {
            outVertices.push_back(inVertices[nVertex]);
            outColors.push_back  (inColors[nVertex]);

            size_t newIndex = outVertices.size() - 1;
            outIndexes.push_back(static_cast<unsigned short>(newIndex));
            output[pack] = static_cast<unsigned short>(newIndex);
        }

    }
}

} // !namespace