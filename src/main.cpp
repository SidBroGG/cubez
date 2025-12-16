#include <SDL3/SDL.h>
#include <SDL3/SDL_vulkan.h>
#include <vulkan/vulkan.h>
#include <vector>
#include <iostream>

class App {
public:
    App() {
        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            throw std::runtime_error(SDL_GetError());
        }
    }

    ~App() {

    }

    void Init() {

    }

    void Run() {

    }

private:
    SDL_Window* window = nullptr;
    VkInstance instance = VK_NULL_HANDLE;
    VkSurfaceKHR surface = VK_NULL_HANDLE;

    void CreateWindow() {
        window = SDL_CreateWindow(
            "Cubez",
            800,
            600,
            SDL_WINDOW_VULKAN
        );

        if (!window) {
            throw std::runtime_error(SDL_GetError());
        }
    }

    void CreateVulkanInstance() {
        uint32_t extCount = 0;
        if (!SDL_Vulkan_GetInstanceExtensions(&extCount)) {
            throw std::runtime_error("Failed to get vulkan extensions");
        }
        
    }
};

int main() {
    App app{};
    app.Init();
    app.Run();

    return 0;
}