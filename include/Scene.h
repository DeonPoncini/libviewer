#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <unordered_map>

#include "Mesh.h"
#include "Camera.h"
#include "GameObject.h"
#include "ShaderProgram.h"
#include "Shader.h"
#include "Texture.h"
#include "Transform.h"
#include "VertexBuffer.h"
#include "Input.h"

namespace viewer
{
class Scene
{
public:
    Scene(int width, int height, const char* title);
    Scene(const Scene&) = delete;
    Scene(Scene&&) = delete;
    ~Scene();

    void start();
    void selectCamera(const char* name);
    void render(GameObject* object);

    // maker methods
    template <typename... Args>
    Mesh* addMesh(const char* name, Args&&... args);
    Mesh* mesh(const char* name);

    template <typename T, typename... Args>
    Camera* addCamera(const char* name, Args&&... args);
    Camera* camera(const char* name);

    template <typename... Args>
    GameObject* addGameObject(const char* name, Args&&... args);
    GameObject* gameObject(const char* name);

    template <typename... Args>
    ShaderProgram* addShaderProgram(const char* name, Args&&... args);
    ShaderProgram* shaderProgram(const char* name);

    template <typename... Args>
    Shader* addShader(const char* name, Args&&... args);
    Shader* shader(const char* name);

    template <typename... Args>
    Texture* addTexture(const char* name, Args&&... args);
    Texture* texture(const char* name);

    template <typename... Args>
    Transform* addTransform(const char* name, Args&&... args);
    Transform* transform(const char* name);

    template <typename... Args>
    VertexBuffer* addVertexBuffer(const char* name, Args&&... args);
    VertexBuffer* vertexBuffer(const char* name);

private:
    GLFWwindow* mWindow;
    Camera* mCurrentCamera;

    std::unordered_map<const char*,std::unique_ptr<Mesh>> mMeshes;
    std::unordered_map<const char*,std::unique_ptr<Camera>> mCameras;
    std::unordered_map<const char*,std::unique_ptr<GameObject>> mGameObjects;
    std::unordered_map<const char*,std::unique_ptr<ShaderProgram>> mShaderPrograms;
    std::unordered_map<const char*,std::unique_ptr<Shader>> mShaders;
    std::unordered_map<const char*,std::unique_ptr<Texture>> mTextures;
    std::unordered_map<const char*,std::unique_ptr<Transform>> mTransforms;
    std::unordered_map<const char*,std::unique_ptr<VertexBuffer>> mVertexBuffers;
};

template <typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

template <typename... Args>
Mesh* Scene::addMesh(const char* name, Args&&... args)
{
    mMeshes.emplace(name,make_unique<Mesh>(std::forward<Args>(args)...));
    return mesh(name);
}

template <typename T, typename... Args>
Camera* Scene::addCamera(const char* name, Args&&... args)
{
    mCameras.emplace(name,make_unique<T>(std::forward<Args>(args)...));
    return camera(name);
}

template <typename... Args>
GameObject* Scene::addGameObject(const char* name, Args&&... args)
{
    mGameObjects.emplace(name,
            make_unique<GameObject>(std::forward<Args>(args)...));
    return gameObject(name);
}

template <typename... Args>
Shader* Scene::addShader(const char* name, Args&&... args)
{
    mShaders.emplace(name,make_unique<Shader>(std::forward<Args>(args)...));
    return shader(name);
}

template <typename... Args>
ShaderProgram* Scene::addShaderProgram(const char* name, Args&&... args)
{
    mShaderPrograms.emplace(name,
            make_unique<ShaderProgram>(std::forward<Args>(args)...));
    return shaderProgram(name);
}

template <typename... Args>
Texture* Scene::addTexture(const char* name, Args&&... args)
{
    mTextures.emplace(name,make_unique<Texture>(std::forward<Args>(args)...));
    return texture(name);
}

template <typename... Args>
Transform* Scene::addTransform(const char* name, Args&&... args)
{
    mTransforms.emplace(name,make_unique<Transform>(std::forward<Args>(args)...));
    return transform(name);
}

template <typename... Args>
VertexBuffer* Scene::addVertexBuffer(const char* name, Args&&... args)
{
    mVertexBuffers.emplace(name,
            make_unique<VertexBuffer>(std::forward<Args>(args)...));
    return vertexBuffer(name);
}
}

#endif
