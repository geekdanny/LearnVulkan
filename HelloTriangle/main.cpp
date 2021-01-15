#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>
const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

//Create a class HelloTriangleApplication Class
class HelloTriangleApplication {
public:
    void run() {
        initWindow();
        initVulkan();
        mainloop();
        cleanup();
    }

private:
    GLFWwindow *window;
    VkInstance instance;

    void initWindow() {
        //initializes the GLFW library
        glfwInit();
        //Tell glfw to not create an OpenGL context
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        //Disable Window Resize
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
    }

    void initVulkan() {
        //Step 1. create Vulkan Instance
        createInstance();
    }

    void mainloop() {
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
        }
    }

    void cleanup() {
        vkDestroyInstance(instance, nullptr);
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    /*
     * To create an instance we'll first have to fill in a struct
     * with some information about our application. This data is
     * technically optional, but it may provide some useful information
     * to the driver in order to optimize our specific application
     * (e.g. because it uses a well-known graphics engine with certain special behavior).
     */
    void createInstance() {
        //1. Create appInfo
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Hello Triangle";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;
        //2. Create Instance createInfo
        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;
        //3. Query Extensions and set extensions
        uint32_t glfwExtensionCount = 0;
        const char **glfwExtensions;

        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
        createInfo.enabledExtensionCount = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtensions;

        //display the supported extensions
        displaySupportedExtensions();
        //For now, we set the extension enabled layers to be 0
        createInfo.enabledLayerCount = 0;


        if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
            throw std::runtime_error("failed to create instance");
        } else {
            std::cout << "The vkInstance has been successfully created!" << std::endl;
        }
    }

    void displaySupportedExtensions(){
        //checking for extensions support
        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
        //now allocate an array to hold the extension details
        std::vector<VkExtensionProperties> extensions(extensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr,&extensionCount,extensions.data());

        //list all the extension properites
        std::cout << "list all the extension properties" << std::endl;
        for(const auto& extension: extensions) {
            std::cout << '\t' << extension.extensionName << std::endl;
        }
    }

};


int main() {
    HelloTriangleApplication app;

    try {
        app.run();
    } catch (const std::exception &exception) {
        std::cerr << exception.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
