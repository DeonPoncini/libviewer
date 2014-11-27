#include "Scene.h"

#include <GL/glew.h>

#include <stdexcept>

namespace viewer
{
Scene::Scene(int width, int height, const char* title) :
    mCurrentCamera(nullptr)
{
    if (!glfwInit())
    {
        throw std::runtime_error("Failed to init GLFW");
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    mWindow = glfwCreateWindow(width,height, title, nullptr, nullptr);
    if (mWindow == nullptr)
    {
        throw std::runtime_error("Failed to open GLFW window");
    }
    glfwMakeContextCurrent(mWindow);

    glewExperimental = true;
    if (glewInit() != GLEW_OK)
    {
        throw std::runtime_error("Failed to init GLEW");
    }

    glfwSetInputMode(mWindow, GLFW_STICKY_KEYS, GL_TRUE);

    glClearColor(0.0f,0.0f,0.0f,0.0f);

    // setup the input manager
    Input::instance().window(mWindow);
}

Scene::~Scene()
{
    glfwTerminate();
}

void Scene::render(GameObject* object)
{
    if (object->transform != nullptr &&
            object->shaderProgram != nullptr &&
            object->mesh != nullptr)
    {
        auto mvp = mCurrentCamera->projection()
            * mCurrentCamera->view() * object->transform->model();
        object->texture->activate(0);
        object->shaderProgram->activate();
        object->shaderProgram->setUniform("MVP",mvp);
        object->shaderProgram->setUniform("textureSampler",0);
        object->mesh->render();
    }
}

void Scene::start()
{
    // setup
    // link the shader programs
    for (auto&& p : mShaderPrograms)
    {
        p.second->link();
    }

    // fill the vertex buffer data
    for (auto&& v : mVertexBuffers)
    {
        v.second->fill();
    }

    do
    {
        glClear(GL_COLOR_BUFFER_BIT);

        for (auto&& g : mGameObjects)
        {
            render(g.second.get());
        }

        glfwSwapBuffers(mWindow);
        glfwPollEvents();
    }
    while (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
            glfwWindowShouldClose(mWindow) == 0);
}

void Scene::selectCamera(const char* name)
{
    mCurrentCamera = camera(name);
}

Mesh* Scene::mesh(const char* name)
{
    return mMeshes.find(name)->second.get();
}

Camera* Scene::camera(const char* name)
{
    return mCameras.find(name)->second.get();
}

GameObject* Scene::gameObject(const char* name)
{
    return mGameObjects.find(name)->second.get();
}

ShaderProgram* Scene::shaderProgram(const char* name)
{
    return mShaderPrograms.find(name)->second.get();
}

Shader* Scene::shader(const char* name)
{
    return mShaders.find(name)->second.get();
}

Texture* Scene::texture(const char* name)
{
    return mTextures.find(name)->second.get();
}

Transform* Scene::transform(const char* name)
{
    return mTransforms.find(name)->second.get();
}

VertexBuffer* Scene::vertexBuffer(const char* name)
{
    return mVertexBuffers.find(name)->second.get();
}
}
