#include "OrthographicCamera.h"
#include <glm/gtc/matrix_transform.hpp>

#include <utility>

namespace viewer
{
OrthographicCamera::OrthographicCamera(
            glm::vec3 eye,
            float xrot,
            float yrot,
            float zrot,
            float zoom) :
    Camera(std::move(glm::ortho(-zoom,zoom,-zoom,zoom,-zoom,zoom)),
            glm::translate(
                glm::rotate(
                    glm::rotate(
                        glm::rotate(
                            glm::mat4(1.0f),xrot,glm::vec3(1.0f,0.0f,0.0f)),
                    yrot,glm::vec3(0.0f,1.0f,0.0f)),
                zrot,glm::vec3(0.0f,0.0f,1.0f)),
            std::move(eye)))
{
}
}
