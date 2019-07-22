#include <vulkan/vulkan.h>

#include <vector>
#include <iostream>
#include <string>
#include <cstring>

#include "vulkandebug.hpp"

void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &info);

const char *validationLayers[] {
#ifdef DEBUG
    "VK_LAYER_KHRONOS_validation"
#endif
};

const char *instanceExtensions[] {
#ifdef DEBUG
    VK_EXT_DEBUG_UTILS_EXTENSION_NAME
#endif
};


int selectedDeviceIndex = -1;

VkInstance instance;

VkDebugUtilsMessengerEXT debugMessenger;

VkPhysicalDevice physicalDevice;

void processArguments(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        if (strncmp(argv[i], "-gpu", 4) == 0) {
            selectedDeviceIndex = atoi(&(argv[i][4]));
            if (selectedDeviceIndex < 0) {
                std::cerr << "Wrong gpu index\n";
            }
        }
    }
}

void createInstance() {
    uint32_t instanceVersion;
    vkEnumerateInstanceVersion(&instanceVersion);
#ifdef DEBUG
    std::cout << "Instance Version: " << versionName(instanceVersion) << '\n';
#endif
    if (VK_VERSION_MAJOR(instanceVersion) != 1 || VK_VERSION_MINOR(instanceVersion) < 1) {
        THROW_ERROR("Incompatible instance version.");
    }

    VkInstanceCreateInfo instanceInfo = { };
    instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;

#ifdef DEBUG
    VkDebugUtilsMessengerCreateInfoEXT messengerInfo;
    populateDebugMessengerCreateInfo(messengerInfo);
    instanceInfo.pNext = &messengerInfo;
#else
    instanceInfo.pNext = NULL;
#endif

    instanceInfo.flags = 0; // Reserved
    
    VkApplicationInfo appInfo = { };
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pNext = NULL;
    appInfo.pApplicationName = "Compute test";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = NULL;
    appInfo.engineVersion = 0;
    appInfo.apiVersion = instanceVersion;

    instanceInfo.pApplicationInfo = &appInfo;
    
    uint32_t layerCount = 0;
    vkEnumerateInstanceLayerProperties(&layerCount, NULL);
    std::vector<VkLayerProperties> layerProperties(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, layerProperties.data());

#ifdef DEBUG
    std::cout << "Available layers:\n";
    for (const VkLayerProperties & properties : layerProperties) {
        std::cout << '\t' << properties.layerName << '\n';
    }
#endif

    for (const char *layer : validationLayers) {
        bool available = false;
        for (const VkLayerProperties &properties : layerProperties) {
            if (strcmp(layer, properties.layerName) == 0) {
                available = true;
                break;
            }
        }
        if (!available) {
            std::cerr << "Layer '" << layer << "' not available!\n";
        }
    }

    instanceInfo.enabledLayerCount = sizeof(validationLayers) / sizeof(const char*);
    instanceInfo.ppEnabledLayerNames = validationLayers;

    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(NULL, &extensionCount, NULL);
    std::vector<VkExtensionProperties> extensionProperties(extensionCount);
    vkEnumerateInstanceExtensionProperties(NULL, &extensionCount, extensionProperties.data());
    
#ifdef DEBUG
    std::cout << "Available instance extensions:\n";
    for (const VkExtensionProperties & properties : extensionProperties) {
        std::cout << '\t' << properties.extensionName << '\n';
    }
#endif

    for (const char *extension : instanceExtensions) {
        bool available = false;
        for (const VkExtensionProperties &properties : extensionProperties) {
            if (strcmp(extension, properties.extensionName) == 0) {
                available = true;
                break;
            }
        }
        if (!available) {
            std::cerr << "Extension '" << extension << "' not available!\n";
        }
    }

    instanceInfo.enabledExtensionCount = sizeof(instanceExtensions) / sizeof(const char*);
    instanceInfo.ppEnabledExtensionNames = instanceExtensions;

    VK_CALL(vkCreateInstance(&instanceInfo, NULL, &instance))
}

VkBool32 debugMessengerCallback (
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
    void *pUserData
) {
    if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
        std::cerr << "VL: " << pCallbackData->pMessage << '\n';
    }
    return VK_FALSE;
}

void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &info) {
    info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    info.pNext = NULL;
    info.flags = 0; // Reserved
    info.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT
                         | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT
                         | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    info.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT
                     | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT
                     | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    info.pfnUserCallback = debugMessengerCallback;
    info.pUserData = NULL;
}

void createDebugMessenger() {
    VkDebugUtilsMessengerCreateInfoEXT createInfo;
    populateDebugMessengerCreateInfo(createInfo);

    auto createFunction = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(
        instance,
        "vkCreateDebugUtilsMessengerEXT"
    );
    if (createFunction == NULL) {
        THROW_ERROR("Failed to retrieve vkCreateDebugUtilsMessengerEXT function.");
    } else {
        VK_CALL(createFunction(instance, &createInfo, NULL, &debugMessenger))
    }
}

void createPhysicalDevice() {
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

    if (deviceCount == 0) {
        THROW_ERROR("No physical devices available.");
    }

#ifdef DEBUG
    std::cout << "Available devices " << deviceCount << ":\n";
    int deviceIndex = 0;
#endif

    bool chooseDevice = selectedDeviceIndex < 0;
    uint32_t bestPick = 0;
    if (chooseDevice) {
        int highestScore = 0;
        for (const VkPhysicalDevice &device : devices) {
            VkPhysicalDeviceProperties properties;
            vkGetPhysicalDeviceProperties(device, &properties);
    
            VkPhysicalDeviceFeatures features;
            vkGetPhysicalDeviceFeatures(device, &features);
    
#ifdef DEBUG
            std::cout << '\t' << deviceIndex << ' ' << properties.deviceName << '\n'
                    << "\t\tAPI version: " << versionName(properties.apiVersion) << '\n'
                    << "\t\tType: " << physicalDeviceTypeName(properties.deviceType) << '\n';
    //         printPhysicalDeviceFeatures(features);
            deviceIndex++;
#endif
        }
    }

    if (chooseDevice) {
        selectedDeviceIndex = bestPick;
    } else if (selectedDeviceIndex > deviceCount) {
        std::cerr << "Device number " << selectedDeviceIndex << " is unavailable!\n";
        exit(-1);
    }

    physicalDevice = devices[selectedDeviceIndex];
#ifdef DEBUG
    std::cout << "selected device: " << selectedDeviceIndex << '\n';
#endif


    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);
    std::vector<VkQueueFamilyProperties> queueFamilyProperties(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilyProperties.data());

#ifdef DEBUG
    std::cout << "Queue families: \n";
    int familyIndex = 0;
#endif

    for (const VkQueueFamilyProperties &properties : queueFamilyProperties) {
        
#ifdef DEBUG
        std::cout << "\tQueue #" << familyIndex << " " << properties.queueCount << ":\n";
        std::vector<std::string> flagNames = queueFlagBitsNames(properties.queueFlags);
        for (const std::string &name : flagNames) {
            std::cout << "\t\t" << name << '\n';
        }
        familyIndex++;
#endif
    }
}



void cleanUp() {
#ifdef DEBUG
    auto destroyMessenger = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(
        instance,
        "vkDestroyDebugUtilsMessengerEXT"
    );
    if (destroyMessenger == NULL) {
        THROW_ERROR("Failed to retrieve vkDestroyDebugUtilsMessengerEXT function.");
    } else {
        destroyMessenger(instance, debugMessenger, nullptr);
    }
#endif
    vkDestroyInstance(instance, NULL);
}

int main(int argc, char *argv[]) {
    processArguments(argc, argv);
    createInstance();
#ifdef DEBUG
    createDebugMessenger();
#endif
    createPhysicalDevice();

    cleanUp();
    return 0;
}

