#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>

#include <functional>
#include <vector>
#include <unordered_map>

namespace viewer
{
class Input
{
public:
    typedef std::function<void(void)> KeyHandler;

    static Input& instance();

    void window(GLFWwindow* window);

    void addKeyPress(KeyHandler function, int key, int mods = 0);
    void addKeyRelease(KeyHandler function, int key, int mods = 0);
    void addKeyRepeat(KeyHandler function, int key, int mods = 0);

    void unbindKeyPress(int key, int mods = 0);
    void unbindKeyRelease(int key, int mods = 0);
    void unbindKeyRepeat(int key, int mods = 0);

private:
    typedef std::unordered_map<int, std::vector<KeyHandler>> ModMap;
    typedef std::unordered_map<int, ModMap> KeyMap;
    Input() = default;
    static void keyInput(GLFWwindow* window, int key,
            int scancode, int action, int mods);

    void keyInput(int key, int scancode, int action, int mods);

    void addKeyHandler(KeyMap& map, KeyHandler function, int key, int mods);
    void unbindKeyHandler(KeyMap& map, int key, int mods);
    void dispatchKey(const KeyMap& map, int key, int mods);

    GLFWwindow* mWindow;
    KeyMap mKeyPresses;
    KeyMap mKeyReleases;
    KeyMap mKeyRepeats;

};
}

#endif
