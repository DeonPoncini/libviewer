#include "Mesh.h"

#include <glm/gtc/matrix_transform.hpp>

namespace viewer
{
Mesh::Mesh(VertexBuffer* buffer, const std::vector<GLfloat>& vertices,
        const std::vector<GLushort>& indices) :
    mStartIndex(buffer->size()),
    mIndexCount(indices.size())
{
    buffer->add(vertices,indices);
}

void Mesh::render() const
{
    glDrawElementsBaseVertex(GL_TRIANGLES, mIndexCount,
            GL_UNSIGNED_SHORT, 0, mStartIndex);
}
}
