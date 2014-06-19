#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "VertexBuffer.h"

namespace viewer
{
class Mesh
{
public:
    explicit Mesh(VertexBuffer* buffer,
            const std::vector<GLfloat>& vertices,
            const std::vector<GLushort>& indices);
    Mesh(const Mesh&) = delete;
    Mesh(Mesh&&) = delete;

    void translate(const glm::vec3& v);

    void render() const;

private:
    unsigned mStartIndex;
    unsigned mIndexCount;
};
}

#endif
