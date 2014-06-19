#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Mesh.h"
#include "OrthographicCamera.h"
#include "PerspectiveCamera.h"
#include "ShaderProgram.h"
#include "VertexBuffer.h"
#include "Scene.h"
#include "Texture.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <functional>
#include <memory>
#include <vector>

const auto WINDOW_WIDTH = 1024;
const auto WINDOW_HEIGHT = 768;
const auto TILE_WIDTH = 10;
const auto TILE_HEIGHT = 10;

class TileWindow
{
public:
    explicit TileWindow(viewer::Scene& scene) :
        mScene(scene),
        mPerspective(false)
    {
    }

    void setup()
    {
        mPlayer = mScene.gameObject("player");
        mMap = mScene.gameObject("map");

        // link up the keypresses
        auto& input = viewer::Input::instance();
        input.addKeyPress(std::bind(&TileWindow::switchCamera,this),GLFW_KEY_O);
        input.addKeyPress(std::bind(&TileWindow::up,this), GLFW_KEY_UP);
        input.addKeyPress(std::bind(&TileWindow::up,this), GLFW_KEY_W);
        input.addKeyPress(std::bind(&TileWindow::down,this), GLFW_KEY_DOWN);
        input.addKeyPress(std::bind(&TileWindow::down,this), GLFW_KEY_S);
        input.addKeyPress(std::bind(&TileWindow::right,this), GLFW_KEY_RIGHT);
        input.addKeyPress(std::bind(&TileWindow::right,this), GLFW_KEY_D);
        input.addKeyPress(std::bind(&TileWindow::left,this), GLFW_KEY_LEFT);
        input.addKeyPress(std::bind(&TileWindow::left,this), GLFW_KEY_A);
        input.addKeyPress(std::bind(&TileWindow::zoomOut,this), GLFW_KEY_Q);
        input.addKeyPress(std::bind(&TileWindow::zoomIn,this), GLFW_KEY_E);

        setCamera();
    }

private:
    void setCamera()
    {
        if (mPerspective)
        {
            mScene.selectCamera("perspective");
        }
        else
        {
            mScene.selectCamera("orthographic");
        }
    }

    // input handling
    void switchCamera()
    {
        mPerspective = !mPerspective;
        setCamera();
    }

    void up()
    {
        mMap->transform->translate(glm::vec3(0.0f, -1.0f,0.0f));
    }

    void down()
    {
        mMap->transform->translate(glm::vec3(0.0f, 1.0f, 0.0f));
    }

    void right()
    {
        mMap->transform->translate(glm::vec3(-1.0f,0.0f,0.0f));
    }

    void left()
    {
        mMap->transform->translate(glm::vec3(1.0f,0.0f,0.0f));
    }

    void zoomOut()
    {
        mMap->transform->translate(glm::vec3(0.0f,0.0f,1.0f));
        mPlayer->transform->translate(glm::vec3(0.0f,0.0f,1.0f));
    }

    void zoomIn()
    {
        mMap->transform->translate(glm::vec3(0.0f,0.0f,-1.0f));
        mPlayer->transform->translate(glm::vec3(0.0f,0.0f,-1.0f));
    }

    viewer::Scene& mScene;
    bool mPerspective;
    viewer::GameObject* mMap;
    viewer::GameObject* mPlayer;
};

std::vector<GLfloat> mapVertices(int x, int y)
{
    std::vector<GLfloat> ret;
    for (auto i = 0; i < y; i++)
    {
        for (auto j = 0; j < x; j++)
        {
            if ((i + j) % 2 == 0)
            {
                const GLfloat verts[] = {
                // x      y         z     u v
                j + 0.0f, i + 0.0f, 0.0f, 1.0f/3.0f, 2.0f/3.0f,
                j + 0.0f, i + 1.0f, 0.0f, 1.0f/3.0f, 1.0f,
                j + 1.0f, i + 1.0f, 0.0f, 2.0f/3.0f, 1.0f,
                j + 1.0f, i + 0.0f, 0.0f, 2.0f/3.0f, 2.0f/3.0f,
                };
                ret.insert(std::end(ret),
                        std::begin(verts),std::end(verts));
            }
            else
            {
                const GLfloat verts[] = {
                // x      y         z     u v
                j + 0.0f, i + 0.0f, 0.0f, 2.0f/3.0f, 2.0f/3.0f,
                j + 0.0f, i + 1.0f, 0.0f, 2.0f/3.0f, 1.0f,
                j + 1.0f, i + 1.0f, 0.0f, 1.0f, 1.0f,
                j + 1.0f, i + 0.0f, 0.0f, 1.0f, 2.0f/3.0f,
                };
                ret.insert(std::end(ret),
                        std::begin(verts),std::end(verts));
            }

        }
    }
    return ret;
}

std::vector<GLushort> mapIndices(int x, int y)
{
    std::vector<GLushort> ret;
    for (auto i = 0; i < x; i++)
    {
        for (auto j = 0; j < y; j++)
        {
            auto offset = (i*x + j)*4;
            const GLushort inds[] = {
                static_cast<GLushort>(offset + 0),
                static_cast<GLushort>(offset + 1),
                static_cast<GLushort>(offset + 2),
                static_cast<GLushort>(offset + 2),
                static_cast<GLushort>(offset + 3),
                static_cast<GLushort>(offset + 0),
            };
            ret.insert(std::end(ret), std::begin(inds),std::end(inds));
        }
    }
    return ret;
}

std::vector<GLfloat> playerVertices()
{
    return {
        // x y z u v
        0.0f, 0.0f, 0.0f,  0.0f, 2.0f/3.0f,
        0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
        1.0f, 1.0f, 0.0f,  1.0f/3.0f, 1.0f,
        1.0f, 0.0f, 0.0f,  1.0f/3.0f, 2.0f/3.0f,
    };
}

std::vector<GLushort> playerIndices()
{
    return { 0, 1, 2, 2, 3, 0 };
}

int main()
{
    viewer::Scene scene(WINDOW_WIDTH,WINDOW_HEIGHT,"Tile Map");

    // vertex buffers
    auto vertexBuffer =
        scene.addVertexBuffer("vb",std::vector<viewer::Vertex>{{0,3},{1,2}});

    // game objects
    auto player = scene.addGameObject("player");
    auto map = scene.addGameObject("map");
    auto texture = scene.addTexture("texture","textures/tile.dds");

    // add transforms
    map->transform = scene.addTransform("map",
            glm::vec3(-TILE_WIDTH/2, -TILE_HEIGHT/2,0.0f));
    player->transform = scene.addTransform("player");

    // add textures
    player->texture = texture;
    map->texture = texture;

    // add cameras
    scene.addCamera<viewer::PerspectiveCamera>("perspective");
    scene.addCamera<viewer::OrthographicCamera>("orthographic");

    // add meshes
    map->mesh = scene.addMesh("map",vertexBuffer,
            mapVertices(TILE_WIDTH,TILE_HEIGHT),
            mapIndices(TILE_WIDTH,TILE_HEIGHT));
    player->mesh = scene.addMesh("player",vertexBuffer,
            playerVertices(),playerIndices());

    // add shaders programs
    auto program = scene.addShaderProgram("shader");
    map->shaderProgram = program;
    player->shaderProgram = program;

    // setup shader program
    scene.addShader("vertex",program,viewer::Shader::VERTEX, "shaders/vertex.glsl");
    scene.addShader("fragment",program,viewer::Shader::FRAGMENT,
            "shaders/fragment.glsl");

    TileWindow tileWindow(scene);
    tileWindow.setup();
    scene.start();

    return 0;
}

