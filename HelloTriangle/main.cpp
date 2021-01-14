#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

//Create a class HelloTriangleApplication Class
class HelloTriangleApplication{
public:
    void run(){
        initWindow();
        initVulkan();
        mainloop();
        cleanup();
    }

private:
    GLFWwindow * window;

    void initWindow(){
        //initializes the GLFW library
        glfwInit();
        //Tell glfw to not create an OpenGL context
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        //Disable Window Resize
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        window = glfwCreateWindow(WIDTH,HEIGHT, "Vulkan", nullptr, nullptr);
    }
    void initVulkan(){

    }
    void mainloop(){
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
        }
    }
    void cleanup(){
        glfwDestroyWindow(window);
        glfwTerminate();
    }

};


int main() {
    HelloTriangleApplication app;

    try {
        app.run();
    } catch (const std::exception &exception) {
        std::cerr <<exception.what()<<std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
