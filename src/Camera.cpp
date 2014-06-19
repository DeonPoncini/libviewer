#include "Camera.h"

#include <utility>

namespace viewer
{
Camera::Camera(glm::mat4 projection, glm::mat4 view) :
    mProjection(std::move(projection)),
    mView(std::move(view))
{
}
}
