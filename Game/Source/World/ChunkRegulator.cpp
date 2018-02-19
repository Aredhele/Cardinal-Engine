//
// Created by kelle on 19/02/2018.
//

#include "World/ChunkRegulator.hpp"

ChunkRegulator::ChunkRegulator(World *world) : mp_world(world)
{
    m_playerCubeText  = cardinal::RenderingEngine::AllocateTextRenderer();
    m_playerChunkText = cardinal::RenderingEngine::AllocateTextRenderer();
    m_playerCubeText->Initialize();
    m_playerChunkText->Initialize();
    m_playerChunkText->SetText("Cube : 0 0 0",  680, 530, 12, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    m_playerCubeText->SetText ("Chunk : 0 0 0", 680, 515, 12, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
}
