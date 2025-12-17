#include "MainApp.h"

#include "SDL3/SDL_vulkan.h"
#include <iostream>
#include <vector>


// App part
MainApp::MainApp() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "SDL_Init error: " << SDL_GetError() << '\n';
        throw std::runtime_error(SDL_GetError());
    }  
}

MainApp::~MainApp() {
    if (surface != VK_NULL_HANDLE) vkDestroySurfaceKHR(instance, surface, nullptr);
    if (instance != VK_NULL_HANDLE) vkDestroyInstance(instance, nullptr);
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();
}


// SDL part
void MainApp::CreateWindow() {
    window = SDL_CreateWindow(
        "Cubez",
        800,
        600,
        SDL_WINDOW_VULKAN
    );
}


// Vulkan part
void MainApp::CreateVulkanInstance() {
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

void MainApp::CreatePhysicalDevice() { 
    // It is like to find gpu with vulkan support
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

    if (deviceCount == 0) {
        throw std::runtime_error("No GPUs with vulkan support");
    }

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

    pDevice = devices.front();
}

void MainApp::CreateLogicalDevice() {
    
}

// Surface part
void MainApp::CreateSurface() {
    if (!SDL_Vulkan_CreateSurface(window, instance, nullptr, &surface)) {
        throw std::runtime_error("Failed to create vulkan surface");
    }
}
