#include "GameObject.h"

namespace viewer
{
GameObject::GameObject() :
    transform(nullptr),
    mesh(nullptr),
    shaderProgram(nullptr),
    texture(nullptr)
{
}
}
