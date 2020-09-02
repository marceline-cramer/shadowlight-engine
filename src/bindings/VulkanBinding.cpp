#include "bindings/VulkanBinding.hpp"

VulkanBinding::VulkanBinding()
{
    // Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw std::runtime_error("Failure to initialize SDL");
    }

    // Create SDL window
    window = SDL_CreateWindow("SDL Tutorial",
                              SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              800, 600,
                              SDL_WINDOW_SHOWN | SDL_WINDOW_VULKAN);
    if(!window) {
        throw std::runtime_error("Failed to create SDL window");
    }

    // Setup Vulkan
    createInstance();
    setupDebugMessenger();
    pickPhysicalDevice();
    createLogicalDevice();
}

void VulkanBinding::createInstance()
{
    uint32_t extensionCount;
    SDL_Vulkan_GetInstanceExtensions(window, &extensionCount, nullptr);
    std::vector<const char *> extensionNames(extensionCount);
    SDL_Vulkan_GetInstanceExtensions(window, &extensionCount, extensionNames.data());

    // TODO Settings class for info like this
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Hello Triangle";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "Shadowlight Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    std::vector<const char *> layerNames {};
    // uncomment below if you want to use validation layers
    // layerNames.push_back("VK_LAYER_LUNARG_standard_validation");

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
    createInfo.enabledLayerCount = layerNames.size();
    createInfo.ppEnabledLayerNames = layerNames.data();
    createInfo.enabledExtensionCount = extensionNames.size();
    createInfo.ppEnabledExtensionNames = extensionNames.data();

    // TODO Better error checking
    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create Vulkan instance");
    }
}

void VulkanBinding::setupDebugMessenger()
{
    // TODO Validation layers
}

void VulkanBinding::pickPhysicalDevice()
{
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

    if(deviceCount == 0) {
        throw std::runtime_error("No Vulkan physical devices found");
    }

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

    // TODO Rank physical device support?
    for(const auto& device : devices) {
        if(isDeviceSuitable(device)) {
            physicalDevice = device;
            break;
        }
    }

    if(physicalDevice == VK_NULL_HANDLE) {
        throw std::runtime_error("Failed to find suitable Vulkan physical device");
    }
}

QueueFamilyIndices VulkanBinding::findQueueFamilies(VkPhysicalDevice device)
{
    QueueFamilyIndices indices;

    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

    int i = 0;
    for (const auto& queueFamily : queueFamilies) {
        if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            indices.graphicsFamily = i;
            indices.hasGraphicsFamily = true;
        }

        if(indices.isComplete()) break;

        i++;
    }

    return indices;
}

bool VulkanBinding::isDeviceSuitable(VkPhysicalDevice device)
{
    // TODO Add support for preferred physical device
    QueueFamilyIndices indices = findQueueFamilies(device);

    return indices.hasGraphicsFamily;
}

void VulkanBinding::createLogicalDevice()
{
    QueueFamilyIndices indices = findQueueFamilies(physicalDevice);
    float queuePriority = 1.0f;

    VkDeviceQueueCreateInfo queueCreateInfo{
        .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
        .queueFamilyIndex = indices.graphicsFamily,
        .queueCount = 1,
        .pQueuePriorities = &queuePriority
    };

    VkPhysicalDeviceFeatures deviceFeatures{};

    VkDeviceCreateInfo createInfo{
        .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
        .queueCreateInfoCount = 1,
        .pQueueCreateInfos = &queueCreateInfo,
        // TODO Validation layers
        .enabledLayerCount = 0,
        .enabledExtensionCount = 0,
        .pEnabledFeatures = &deviceFeatures
    };

    if(vkCreateDevice(physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create Vulkan logical device");
    }

    vkGetDeviceQueue(device, indices.graphicsFamily, 0, &graphicsQueue);
}

VulkanBinding::~VulkanBinding()
{
    vkDestroyDevice(device, nullptr);
    vkDestroyInstance(instance, nullptr);

    SDL_DestroyWindow(window);
    SDL_Quit();
}

void VulkanBinding::update()
{

}
