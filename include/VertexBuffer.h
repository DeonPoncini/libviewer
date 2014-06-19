#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include <GL/glew.h>

#include <vector>

namespace viewer
{
struct Vertex
{
    GLuint index;
    GLsizei size;
    GLboolean normalized;

    Vertex(GLuint i, GLsizei s, GLboolean n = GL_FALSE) :
        index(i), size(s), normalized(n)
    {
    }
};

class VertexBuffer
{
public:
    explicit VertexBuffer(std::vector<Vertex> descriptions);
    ~VertexBuffer();

    void add(const std::vector<GLfloat>& vertices,
            const std::vector<GLushort>& indices);
    void fill();
    void bind();

    inline unsigned size() const { return mVertices.size()/mStride; }

private:
    GLuint mArrayID;
    GLuint mBufferID;
    GLuint mIndexID;
    GLsizei mStride;

    std::vector<Vertex> mVertexDescriptions;
    std::vector<GLfloat> mVertices;
    std::vector<GLushort> mIndices;
};
}

#endif
