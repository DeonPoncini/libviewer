#ifndef ORTHOGRAPHICCAMERA_H
#define ORTHOGRAPHICCAMERA_H

#include "Camera.h"

namespace viewer
{
class OrthographicCamera : public Camera
{
public:
    explicit OrthographicCamera(
            glm::vec3 eye = glm::vec3(0.0f,0.0f,1.0f),
            float xrot = 35.0f,
            float yrot = 0.0f,
            float zrot = -45.0f,
            float zoom = 10.0f);

};
}

#endif
