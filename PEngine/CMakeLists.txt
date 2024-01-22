
include_directories(vendor)

if(UNIX AND NOT APPLE)
        add_library(PEngine SHARED          
                
                Core/Clock.cpp
                Core/PTime.cpp
                
                EventSystem/EventFactory.cpp
                EventSystem/Dispatcher.cpp

                Input/Translator/KeyCodeTranslator.cpp
                Input/Translator/MouseCodeTranslator.cpp
                Input/Listener/KeyboardListener.cpp
                Input/Listener/MouseListener.cpp
                Input/PInput.cpp

                Render/RCore/Drivers/OpenGL/OpenGLDriver.cpp

                Render/RCore/Drivers/Vulkan/Linux/VulkanPlatform.cpp
                Render/RCore/Drivers/Vulkan/VulkanDevice.cpp
                Render/RCore/Drivers/Vulkan/VulkanImageManager.cpp
                Render/RCore/Drivers/Vulkan/VulkanFenceManager.cpp
                Render/RCore/Drivers/Vulkan/VulkanSwapChainManager.cpp
                Render/RCore/Drivers/Vulkan/VulkanGraphicsPipeline.cpp
                Render/RCore/Drivers/Vulkan/VulkanCommandBuffer.cpp
                Render/RCore/Drivers/Vulkan/VulkanFrameBuffer.cpp
                Render/RCore/Drivers/Vulkan/VulkanRender.cpp
                Render/RCore/Drivers/Vulkan/VulkanDebug.cpp
                Render/RCore/Drivers/Vulkan/VulkanDriver.cpp


                Render/RCore/DriverManager.cpp
                Render/RCore/RAPICore.cpp
                Render/PRender.cpp

                Platform/Linux/PlatformInputManager.cpp
                Platform/Linux/Platform.cpp
                
                Application.cpp
                PicassoEngine.cpp
        )

        target_include_directories(PEngine PUBLIC ${CMAKE_SOURCE_DIR})

        target_link_libraries(PEngine /usr/lib/x86_64-linux-gnu/libX11.so.6.4.0)
        target_link_libraries(PEngine /usr/lib/x86_64-linux-gnu/libX11-xcb.so.1.0.0)
        target_link_libraries(PEngine /usr/lib/x86_64-linux-gnu/libxcb.so.1.1.0)
        target_link_libraries(PEngine /usr/lib/x86_64-linux-gnu/libvulkan.so)
        target_link_libraries(PEngine /usr/lib/x86_64-linux-gnu/libglfw.so)
endif()

