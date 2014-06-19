#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

namespace viewer
{
class Camera
{
public:
    Camera(glm::mat4 projection, glm::mat4 view);
    Camera(const Camera&) = delete;
    Camera(Camera&&) = delete;

    inline glm::mat4 projection() const { return mProjection; }
    inline glm::mat4 view() const { return mView; }

private:
    glm::mat4 mProjection;
    glm::mat4 mView;
};
}

#endif
