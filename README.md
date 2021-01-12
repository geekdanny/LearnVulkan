# LearnVulkan

# 前言

学习图形学编程的时候，其实在MacOS的编程环境默认都是用Xcode，Windows又经常用Visual Studio。但是因为我经常要在Windows 和 MacOS上切换编程，偶尔还得跑到Ubuntu上去，也不想反复的切换不同的IDE，所以我选择了Clion。Clion 好的好处就是跨平台的使用。

今天花了几个小时在MacOS上配置了Clion+Vulkan的开发环境，对于后期学习Vulkan做铺垫。 了解Clion的人都知道，Clion的C/C++编程采用的是cmake 做工程构建，这样子又可以逼迫我使用一个跨平台的构架方案，对于底层的工程构建可以了如指掌，也可促使我更进一步的了解和学习cmake。

# 我的工作环境

### MacOS: Big Sur

![ACE1oA](https://raw.githubusercontent.com/geekdanny/images/master/blog/ACE1oA-20210112150444971.png)

### gcc verson

```bash
~/C/V/shaders ❯❯❯ gcc --version
Configured with: --prefix=/Applications/Xcode.app/Contents/Developer/usr --with-gxx-include-dir=/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/c++/4.2.1
Apple clang version 12.0.0 (clang-1200.0.32.27)
Target: x86_64-apple-darwin20.2.0
Thread model: posix
InstalledDir: /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin
```



# 配置Vulkan所需要的Lib

Vulkan的MacOS的配置主要参考Vulkan Tutorial的[Development Environment](https://vulkan-tutorial.com/Development_environment)。但是很对MacOS的文章只提供了XCode的配置，但是其实对于文件包的依赖都是一样的。主要是需要三样东西: Vulkan SDK, GLFW，GLM.

我们分别看一下如何安装这三样东西。

## 安装Vulkan SDK

Vulkan SDK可以直接从https://vulkan.lunarg.com/sdk/home下载。其具体的安装过程可参考[Getting Started with the macOS Vulkan SDK](https://vulkan.lunarg.com/doc/sdk/latest/mac/getting_started.html)。在具体安装的环节，我采用了**Install the SDK - Alternate method using system paths**这一步。即通过运行sdk自带的python安装脚本来进行安装：

```bash
sudo ./install_vulkan.py
```

脚本的运行结果如下，主要是把vulkan sdk 的庫和头文件分别安装到了系统目录 /usr/local下。

*/usr/local/lib is one of the directories that linker searches for required libraries. 用户安装的lib一般都会放在/usr/local 这个folder内。 Clion搜索庫的依据主要来自于cmake 所定义的include_directories所指定的路径。*

```
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/bin/spirv-opt to /usr/local/bin
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/bin/vkvia to /usr/local/bin
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/lib/cmake/SPVRemapperTargets-release.cmake to /usr/local/lib/cmake/vulkan
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/lib/cmake/SPIRV-Tools to /usr/local/lib/cmake/vulkan/SPIRV-Tools
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/bin/spirv-link to /usr/local/bin
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/bin/spirv-cfg to /usr/local/bin
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/lib/libspirv-cross-c-shared.0.44.0.dylib to /usr/local/lib
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/bin/spirv-val to /usr/local/bin
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/include/vulkan to /usr/local/include/vulkan
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/lib/cmake/SPIRVTargets.cmake to /usr/local/lib/cmake/vulkan
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/lib/libSPIRV.a to /usr/local/lib
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/bin/MoltenVKShaderConverter to /usr/local/bin
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/lib/cmake/glslangTargets-release.cmake to /usr/local/lib/cmake/vulkan
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/share/vulkan to /usr/local/share/vulkan
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/lib/libshaderc_util.a to /usr/local/lib
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/lib/libSPIRV-Tools.a to /usr/local/lib
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/bin/vulkaninfo to /usr/local/bin
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/bin/spirv-as to /usr/local/bin
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/lib/libSPIRV-Tools-opt.a to /usr/local/lib
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/lib/cmake/SPIRVTargets-release.cmake to /usr/local/lib/cmake/vulkan
Copying /Volumes/vulkansdk-macos-1.2.162.0/Applications/vkconfig.app to /Applications/vkconfig.app
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/lib/cmake/glslangValidatorTargets.cmake to /usr/local/lib/cmake/vulkan
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/lib/cmake/OGLCompilerTargets.cmake to /usr/local/lib/cmake/vulkan
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/lib/libspirv-cross-c-shared.dylib to /usr/local/lib
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/lib/libspirv-cross-cpp.a to /usr/local/lib
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/bin/glslc to /usr/local/bin
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/lib/cmake/HLSLTargets.cmake to /usr/local/lib/cmake/vulkan
Copying /Volumes/vulkansdk-macos-1.2.162.0/Applications/vkcubepp.app to /Applications/vkcubepp.app
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/lib/libGenericCodeGen.a to /usr/local/lib
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/lib/libspirv-cross-c-shared.0.dylib to /usr/local/lib
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/lib/libspirv-cross-glsl.a to /usr/local/lib
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/lib/libspirv-cross-msl.a to /usr/local/lib
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/bin/spirv-remap to /usr/local/bin
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/bin/spirv-dis to /usr/local/bin
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/include/spirv_cross to /usr/local/include/spirv_cross
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/lib/cmake/SPIRV-Tools-link to /usr/local/lib/cmake/vulkan/SPIRV-Tools-link
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/lib/cmake/SPVRemapperTargets.cmake to /usr/local/lib/cmake/vulkan
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/bin/dxc-3.7 to /usr/local/bin
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/lib/cmake/SPIRV-Tools-opt to /usr/local/lib/cmake/vulkan/SPIRV-Tools-opt
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/lib/cmake/OGLCompilerTargets-release.cmake to /usr/local/lib/cmake/vulkan
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/bin/glslangValidator to /usr/local/bin
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/bin/spirv-lesspipe.sh to /usr/local/bin
Copying /Volumes/vulkansdk-macos-1.2.162.0/Applications/vkcube.app to /Applications/vkcube.app
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/lib/cmake/HLSLTargets-release.cmake to /usr/local/lib/cmake/vulkan
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/lib/cmake/spirv-remapTargets.cmake to /usr/local/lib/cmake/vulkan
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/lib/cmake/glslangValidatorTargets-release.cmake to /usr/local/lib/cmake/vulkan
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/lib/libSPIRV-Tools-link.a to /usr/local/lib
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/lib/libspirv-cross-c.a to /usr/local/lib
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/bin/spirv-reflect to /usr/local/bin
Copying /Volumes/vulkansdk-macos-1.2.162.0/Applications/vulkaninfo.app to /Applications/vulkaninfo.app
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/lib/libspirv-cross-hlsl.a to /usr/local/lib
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/include/shaderc to /usr/local/include/shaderc
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/lib/libSPIRV-Tools-reduce.a to /usr/local/lib
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/lib/libshaderc_combined.a to /usr/local/lib
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/lib/libspirv-cross-util.a to /usr/local/lib
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/lib/libvulkan.1.2.162.dylib to /usr/local/lib
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/lib/libOGLCompiler.a to /usr/local/lib
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/lib/libshaderc_shared.1.dylib to /usr/local/lib
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/lib/libSPIRV-Tools-shared.dylib to /usr/local/lib
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/lib/libvulkan.dylib to /usr/local/lib
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/lib/libOSDependent.a to /usr/local/lib
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/lib/libshaderc.a to /usr/local/lib
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/include/spirv-tools to /usr/local/include/spirv-tools
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/lib/cmake/SPIRV-Tools-reduce to /usr/local/lib/cmake/vulkan/SPIRV-Tools-reduce
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/lib/libglslang.a to /usr/local/lib
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/lib/libdxcompiler.3.7.dylib to /usr/local/lib
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/lib/libMoltenVK.dylib to /usr/local/lib
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/lib/libspirv-cross-reflect.a to /usr/local/lib
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/lib/libHLSL.a to /usr/local/lib
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/lib/libdxcompiler.dylib to /usr/local/lib
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/bin/spirv-cross to /usr/local/bin
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/lib/libVkLayer_khronos_validation.dylib to /usr/local/lib
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/include/glslang to /usr/local/include/glslang
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/bin/spirv-reduce to /usr/local/bin
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/lib/cmake/OSDependentTargets.cmake to /usr/local/lib/cmake/vulkan
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/bin/dxc to /usr/local/bin
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/lib/libspirv-cross-core.a to /usr/local/lib
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/lib/libSPVRemapper.a to /usr/local/lib
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/lib/libVkLayer_api_dump.dylib to /usr/local/lib
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/lib/cmake/spirv-remapTargets-release.cmake to /usr/local/lib/cmake/vulkan
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/lib/cmake/OSDependentTargets-release.cmake to /usr/local/lib/cmake/vulkan
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/lib/libvulkan.1.dylib to /usr/local/lib
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/lib/cmake/glslangTargets.cmake to /usr/local/lib/cmake/vulkan
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/lib/libshaderc_shared.dylib to /usr/local/lib
Copying /Volumes/vulkansdk-macos-1.2.162.0/macOS/lib/libMachineIndependent.a to /usr/local/lib
```

## 安装GLFW

GLFW是用来创建window的，它支持不同的操作系统的。无论是OpenGL还是Vulkan，它们的只负责图形渲染到内存中用于显示到屏幕的桌面上，至于最后每个操作系统的桌面的创建，GL跟Vulkan都不负责。这就是GLFW的工作了。在苹果上，glfw可以通过brew来安装。我的mac已经安装好了brew，所以就直接通过brew来安装glfw就好了。

```bash
brew install glfw
```

## 安装GLM

Vulkan也不包含线性代数的数学庫。所以我们之后做图形变化的时候，需要用到GLM。他也可以通过brew 来安装。

```
brew install glm
```

安装以上所有需要的libs之后，我们可以设定一个shell 的profile 里设定自己的环境变量。这些设定的环境变量将用来为我后之后在clion IDE里使用cmake配置文件时指明需要搜索的庫的路径。因为我用的是zsh，所以，我在~/.zprofile 里添加了glfw和glm的lib的路径。

```
export GLFW_HOME="/usr/local/Cellar/glfw/3.3.2"
export GLM_HOME="/usr/local/include/glm"
```

备注：brew 会把所有的安装都在一个叫Cellar的目录下，然后在/usr/local 下创建soft link连接到这些在Cellar下的目录。

然后我们重新source一下我.zprofile.

当一些都配置好了后，可以调用vksdk的命令`vkvia`来查询vulkan是否成功安装了。

也可以run一下vulkan sdk的 cube app来看一下。

![FtU9D7](https://raw.githubusercontent.com/geekdanny/images/master/blog/FtU9D7.png)

# 创建Clion 项目

让我们的创建一个VulkanDemo 项目。项目创建后非常简单，只有一个main.cpp 的helloworld代码。

这里我们来画一个三角形，所有，让我们配置cmake file 保证所需要的头文件和庫都被正确的加载了。

```cmake
cmake_minimum_required(VERSION 3.17)
project(VulkanDemo)

set(CMAKE_CXX_STANDARD 17)

# 检查环境变量
if (NOT DEFINED ENV{GLFW_HOME})
    message(FATAL_ERROR "found no env named GLFW_HOME")
endif()
if (NOT DEFINED ENV{GLM_HOME})
    message(FATAL_ERROR "found no env named GLM_HOME")
endif()

# 暂存环境变量
set(GLFW_HOME $ENV{GLFW_HOME})
set(GLM_HOME $ENV{GLM_HOME})

add_executable(VulkanDemo main.cpp)

# 添加 GLFW3 预编译库
add_library(glfw SHARED IMPORTED)
SET_TARGET_PROPERTIES(glfw PROPERTIES IMPORTED_LOCATION "${GLFW_HOME}/lib/libglfw.3.dylib")

# GLM
include_directories(${GLM_INCLUDE_DIRS})

# Vulkan
find_package(Vulkan REQUIRED FATAL_ERROR)
target_link_libraries(${PROJECT_NAME} glfw Vulkan::Vulkan)
#include_directories(${Vulkan_INCLUDE_DIRS})
#target_include_directories(${PROJECT_NAME} PUBLIC ${Vulkan_INCLUDE_DIRS})

# copy the shader files to the cmake-build-debug folder
file(COPY shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

```

cmake 配置好后我们开始画我么你的三角形。这篇文章直接用了Vulkan Tutorial的代码。把[代码](https://vulkan-tutorial.com/code/16_swap_chain_recreation.cpp) 复制到`main.cpp` 里。因为画三角形我们这里要用到两个shaders。shader的代码来自[这一章节](https://vulkan-tutorial.com/Drawing_a_triangle/Graphics_pipeline_basics/Shader_modules)。所以我们需要添加两个shader文件，和一个compile 脚本帮我们生成SPIR-V文件。

大家可能留意到，cmake 的配置文件最后一行我用到了`file(COPY shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})`，主要因为在main的代码里调用了openfile 需要打开我们的shader文件。但是Clion run 项目的二进制文件的时候，它假设资源文件是放在`cmake-build-debug`这个文件夹里。所以我们必须把shader文件夹复制到`cmake-build-debug`里。

来看一下我么你的项目的整体的样子：

![lk33hI](https://raw.githubusercontent.com/geekdanny/images/master/blog/lk33hI.png)

好了，最后，我们在clion里运行我们的VulkanDemo程序吧。一个三角形孕育而生！

![dUqc07](https://raw.githubusercontent.com/geekdanny/images/master/blog/dUqc07.png)

