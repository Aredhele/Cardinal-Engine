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

/// \file       VBOIndexer.inl
/// \date       11/02/2018
/// \project    Cardinal Engine
/// \package    Rendering/Optimization/Impl
/// \author     Vincent STEHLY--CALISTO

/// \namespace cardinal
namespace cardinal
{

/// \brief  Tells if there already is a similar vertex
/// \param  pack The current pack to check
/// \param  output The output map
/// \param  result The result
/// \return True or false
/* static */ inline bool VBOIndexer::GetSimilarVertexIndex(
        const VBOIndexer::sPackedVertex &pack,
        const std::map<VBOIndexer::sPackedVertex, unsigned short> &output,
        unsigned short &result)
{
    std::map<sPackedVertex, unsigned short>::const_iterator it = output.find(pack);

    if (it != output.end())
    {
        result = it->second;
        return true;
    }

    return false;
}

/// \brief  Tells if there already is a similar vertex
/// \param  pack The current pack to check
/// \param  output The output map
/// \param  result The result
/// \return True or false
/* static */ inline bool VBOIndexer::GetSimilarVertexIndex(
        const VBOIndexer::sPackedVertexBeta &pack,
        const std::map<VBOIndexer::sPackedVertexBeta, unsigned short> &output,
        unsigned short &result)
{
    std::map<sPackedVertexBeta, unsigned short>::const_iterator it = output.find(pack);

    if (it != output.end())
    {
        result = it->second;
        return true;
    }

    return false;
}

} // !namespace