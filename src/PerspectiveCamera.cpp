#include "PerspectiveCamera.h"

#include <glm/gtc/matrix_transform.hpp>

#include <utility>

namespace viewer
{
PerspectiveCamera::PerspectiveCamera(
            glm::vec3 eye,
            glm::vec3 center,
            glm::vec3 up,
            float fov,
            float aspect,
            float zNear,
            float zFar) :
    Camera(std::move(glm::perspective(fov,aspect,zNear,zFar)),
    std::move(glm::lookAt(std::move(eye),std::move(center),std::move(up))))
{
}
}
