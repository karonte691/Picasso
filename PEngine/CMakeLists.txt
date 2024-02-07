
include_directories(vendor)

if(UNIX AND NOT APPLE)
        set(PICASSO_ENGINE_SRC        
                Core/Clock.cpp
                Core/PTime.cpp
                
                Math/Vector2.cpp
                Math/Vector3.cpp
                Math/Vector4.cpp
                Math/Matrix.cpp
                Math/Quaternion.cpp
                Math/PMath.cpp

                File/FileManager.cpp
                File/PFLoader.cpp

                EventSystem/EventFactory.cpp
                EventSystem/Dispatcher.cpp

                Input/Translator/KeyCodeTranslator.cpp
                Input/Translator/MouseCodeTranslator.cpp
                Input/Listener/KeyboardListener.cpp
                Input/Listener/MouseListener.cpp
                Input/PInput.cpp
        )

                if(${DRIVER} STREQUAL "OpenGl")
                        set(PICASSO_ENGINE_SRC ${PICASSO_ENGINE_SRC}  

                                Render/RCore/Drivers/OpenGL/Shaders/OpenGLShader.cpp
                                Render/RCore/Drivers/OpenGL/Shaders/OpenGLShaderFactory.cpp
                                Render/RCore/Drivers/OpenGL/OpenGLContext.cpp
                                Render/RCore/Drivers/OpenGL/OpenGLWindow.cpp
                                Render/RCore/Drivers/OpenGL/OpenGLDriver.cpp
                                Render/RCore/Drivers/OpenGL/OpenGLTexture.cpp
                                Render/RCore/Drivers/OpenGL/OpenGLGraphicsPipeline.cpp
                        )
                endif()

                if(${DRIVER} STREQUAL "Vulkan")
                        set(PICASSO_ENGINE_SRC ${PICASSO_ENGINE_SRC}  

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
                        )

                endif()
                
        set(PICASSO_ENGINE_SRC ${PICASSO_ENGINE_SRC}   

                Render/RCore/DriverManager.cpp
                Render/RCore/GraphicsPipelineFactory.cpp
                Render/RCore/RAPICore.cpp
                Render/PRender.cpp

                Platform/Linux/PlatformInputManager.cpp
                Platform/Linux/Platform.cpp
                
                Application.cpp
                PicassoEngine.cpp
        )

        add_library(PEngine SHARED ${PICASSO_ENGINE_SRC})

        target_include_directories(PEngine PUBLIC ${CMAKE_SOURCE_DIR})

        target_link_libraries(PEngine /usr/lib/x86_64-linux-gnu/libX11.so.6.4.0)
        target_link_libraries(PEngine /usr/lib/x86_64-linux-gnu/libX11-xcb.so.1.0.0)
        target_link_libraries(PEngine /usr/lib/x86_64-linux-gnu/libxcb.so.1.1.0)
        target_link_libraries(PEngine /usr/lib/x86_64-linux-gnu/libvulkan.so)
        target_link_libraries(PEngine /usr/lib/x86_64-linux-gnu/libGL.so)
        target_link_libraries(PEngine /usr/lib/x86_64-linux-gnu/libglfw.so)
        target_link_libraries(PEngine /usr/lib/x86_64-linux-gnu/libGLEW.so)
        target_link_libraries(PEngine /home/luca/pp/Picasso/build/Lib/Linux/libSOIL.so)
endif()

