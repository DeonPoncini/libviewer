#include "Transform.h"

#include <glm/gtc/matrix_transform.hpp>

namespace viewer
{
Transform::Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) :
    mPosition(position),
    mRotation(rotation),
    mScale(scale),
    mModel(glm::translate(
                glm::rotate(
                    glm::rotate(
                        glm::rotate(
                            glm::scale(glm::mat4(1.0f),mScale),
                        mRotation.x,glm::vec3(1.0f,0.0f,0.0f)),
                    mRotation.y,glm::vec3(0.0f,1.0f,0.0f)),
                mRotation.z,glm::vec3(0.0f,0.0f,1.0f)),
            mPosition))

{
}

void Transform::translate(const glm::vec3& v)
{
    mModel = glm::translate(mModel,v);
}

void Transform::rotate(const glm::vec3& v)
{
    mModel = glm::rotate(mModel,v.x,glm::vec3(1.0f,0.0f,0.0f));
    mModel = glm::rotate(mModel,v.y,glm::vec3(0.0f,1.0f,0.0f));
    mModel = glm::rotate(mModel,v.z,glm::vec3(0.0f,0.0f,1.0f));
}

void Transform::scale(const glm::vec3& v)
{
    mModel = glm::scale(mModel,v);
}
}
