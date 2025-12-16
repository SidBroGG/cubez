#include <SDL3/SDL.h>
#include <SDL3/SDL_vulkan.h>
#include <vulkan/vulkan.h>
#include <vector>
#include <iostream>

class App {
public:
    App() {
        if (!SDL_Init(SDL_INIT_VIDEO)) {
            std::cerr << "SDL_Init error: " << SDL_GetError() << '\n';
            throw std::runtime_error(SDL_GetError());
        }  
    }

    ~App() {
        if (surface != VK_NULL_HANDLE) vkDestroySurfaceKHR(instance, surface, nullptr);
        if (instance != VK_NULL_HANDLE) vkDestroyInstance(instance, nullptr);
        if (window) SDL_DestroyWindow(window);
        SDL_Quit();
    }

    void Init() {
        CreateWindow();
        CreateVulkanInstance();
        CreateSurface();
    }

    void Run() {
        bool running = true;

        while (running) {
            std::cout << "running\n";
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_EVENT_QUIT) running = false;
            }

            SDL_Delay(16);
        }
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
        // extensions
        uint32_t extCount = 0;
        const char* const* extensions = SDL_Vulkan_GetInstanceExtensions(&extCount);

        if (!extensions) {
            throw std::runtime_error("Failed to write vulkan extensions");
        }

        // app info
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Cubez";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_4;
        
        // vk instance
        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;
        createInfo.enabledExtensionCount = extCount;
        createInfo.ppEnabledExtensionNames = extensions;

        if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create vulkan instance");
        }
    }

    void CreateSurface() {
        if (!SDL_Vulkan_CreateSurface(window, instance, nullptr, &surface)) {
            throw std::runtime_error("Failed to create vulkan surface");
        }
    }
};

int main() {
    try {
        App app{};
        app.Init();
        app.Run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}