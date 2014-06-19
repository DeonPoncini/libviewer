#include "Input.h"

namespace viewer
{
Input& Input::instance()
{
    static Input instance;
    return instance;
}

void Input::window(GLFWwindow* window)
{
    mWindow = window;
    glfwSetKeyCallback(mWindow,Input::keyInput);
}

void Input::addKeyPress(KeyHandler function, int key, int mods)
{
    addKeyHandler(mKeyPresses,function,key,mods);
}

void Input::addKeyRelease(std::function<void(void)> function, int key, int mods)
{
    addKeyHandler(mKeyReleases,function,key,mods);
}

void Input::addKeyRepeat(std::function<void(void)> function, int key, int mods)
{
    addKeyHandler(mKeyRepeats,function,key,mods);
}

void Input::addKeyHandler(KeyMap& map, KeyHandler function, int key, int mods)
{
    auto it = map.find(key);
    if (it != map.end())
    {
        auto mit = it->second.find(mods);
        if (mit != it->second.end())
        {
            mit->second.push_back(function);
        }
        else
        {
            it->second.insert({mods,{function}});
        }
    }
    else
    {
        ModMap inner;
        inner.insert({mods,{function}});
        map.insert({key,inner});
    }
}

void Input::unbindKeyPress(int key, int mods)
{
    unbindKeyHandler(mKeyPresses,key,mods);
}

void Input::unbindKeyRelease(int key, int mods)
{
    unbindKeyHandler(mKeyReleases,key,mods);
}

void Input::unbindKeyRepeat(int key, int mods)
{
    unbindKeyHandler(mKeyRepeats,key,mods);
}

void Input::unbindKeyHandler(KeyMap& map, int key, int mods)
{
    auto it = map.find(key);
    if (it != map.end())
    {
        auto mit = it->second.find(mods);
        if (mit != it->second.end())
        {
            mit->second.clear();
        }
    }
}

void Input::keyInput(GLFWwindow* window, int key, int scancode,
        int action, int mods)
{
    instance().keyInput(key,scancode,action,mods);
}

void Input::keyInput(int key, int scancode, int action, int mods)
{
    switch (action)
    {
        case GLFW_PRESS:
            dispatchKey(mKeyPresses,key,mods);
            break;
        case GLFW_RELEASE:
            dispatchKey(mKeyReleases,key,mods);
            break;
        case GLFW_REPEAT:
            dispatchKey(mKeyRepeats,key,mods);
            break;
    }
}

void Input::dispatchKey(const KeyMap& map, int key, int mods)
{
    // look up the key
    auto it = map.find(key);
    if (it != map.end())
    {
        // look up the mods
        auto mit = it->second.find(mods);
        if (mit != it->second.end())
        {
            // call every function
            for (auto&& f : mit->second)
            {
                f();
            }
        }
    }
}
}

