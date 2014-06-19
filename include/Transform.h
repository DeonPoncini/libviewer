#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>

namespace viewer
{
class Transform
{
public:
    explicit Transform(glm::vec3 position = glm::vec3(0.0f),
            glm::vec3 rotation = glm::vec3(0.0f),
            glm::vec3 scale = glm::vec3(1.0f));
    Transform(const Transform&) = delete;
    Transform(Transform&&) = delete;

    inline glm::mat4 model() const { return mModel; }

    void translate(const glm::vec3& v);
    void rotate(const glm::vec3& v);
    void scale(const glm::vec3& v);

private:
    glm::vec3 mPosition;
    glm::vec3 mRotation;
    glm::vec3 mScale;
    glm::mat4 mModel;

};
}

#endif
