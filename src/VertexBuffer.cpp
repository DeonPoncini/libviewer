#include "VertexBuffer.h"

#include <iostream>

namespace viewer
{
VertexBuffer::VertexBuffer(std::vector<Vertex> descriptions) :
    mArrayID(0),
    mBufferID(0),
    mIndexID(0),
    mStride(0),
    mVertexDescriptions(descriptions)
{
    glGenVertexArrays(1, &mArrayID);
    glBindVertexArray(mArrayID);

    // find out the total stride
    for (auto&& d : mVertexDescriptions)
    {
        mStride += d.size;
    }
}

VertexBuffer::~VertexBuffer()
{
    for (auto&& d : mVertexDescriptions)
    {
        glDisableVertexAttribArray(d.index);
    }
    glDeleteBuffers(1, &mBufferID);
    glDeleteVertexArrays(1, &mArrayID);
}

void VertexBuffer::add(const std::vector<GLfloat>& vertices,
        const std::vector<GLushort>& indices)
{
    mVertices.insert(std::end(mVertices),
                    std::begin(vertices),std::end(vertices));
    mIndices.insert(std::end(mIndices),
                    std::begin(indices),std::end(indices));
}

void VertexBuffer::fill()
{
    // bind the vertex data
    glGenBuffers(1, &mBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, mBufferID);
    glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(GLfloat),
            mVertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, mBufferID);

    auto offset = 0;
    for (auto&& d : mVertexDescriptions)
    {
        glEnableVertexAttribArray(d.index);
        glVertexAttribPointer(
            d.index,
            d.size,
            GL_FLOAT,
            d.normalized,
            mStride*sizeof(GLfloat),
            static_cast<char*>(0) + offset * sizeof(GLfloat)
        );
        offset += d.size;
    }

    // bind the index data
    glGenBuffers(1, &mIndexID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(GLushort),
            mIndices.data(), GL_STATIC_DRAW);
}

void VertexBuffer::bind()
{
    glBindVertexArray(mArrayID);
}
}
