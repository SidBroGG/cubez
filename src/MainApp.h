#pragma once

#include <SDL3/SDL.h>
#include <vulkan/vulkan.hpp>

class MainApp {
public:
    MainApp();
    ~MainApp();
    
    void Init();
    void MainLoop();
private:
    SDL_Window* window = nullptr;
    VkInstance instance = VK_NULL_HANDLE;
    VkSurfaceKHR surface = VK_NULL_HANDLE;
    VkPhysicalDevice pDevice = VK_NULL_HANDLE;

    void CreateWindow();
    
    void CreateVulkanInstance();
    void CreatePhysicalDevice();
    void CreateLogicalDevice();
    void CreateSwapchain();

    void CreateSurface();

};