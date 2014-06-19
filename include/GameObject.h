#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Camera.h"
#include "Texture.h"
#include "Transform.h"
#include "Mesh.h"
#include "ShaderProgram.h"

namespace viewer
{
class GameObject
{
public:
    Transform* transform;
    Mesh* mesh;
    ShaderProgram* shaderProgram;
    Texture* texture;

    GameObject();
    GameObject(const GameObject&) = delete;
    GameObject(GameObject&&) = delete;
};
}

#endif
