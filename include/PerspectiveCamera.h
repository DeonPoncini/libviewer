#ifndef PERSPECTIVECAMERA_H
#define PERSPECTIVECAMERA_H

#include "Camera.h"

namespace viewer
{
class PerspectiveCamera : public Camera
{
public:
    explicit PerspectiveCamera(
            glm::vec3 eye = glm::vec3(0.0f,0.0f,20.0f),
            glm::vec3 center = glm::vec3(0.0f,0.0f,0.0f),
            glm::vec3 up = glm::vec3(0.0f,1.0f,0.0f),
            float fov = 45.0f,
            float aspect = 4.0f/3.0f,
            float zNear = 0.1f,
            float zFar = 100.0f);

};
}

#endif
