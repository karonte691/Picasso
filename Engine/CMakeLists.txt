if(UNIX AND NOT APPLE)
        add_library(Engine SHARED          
                                
                EventSystem/EventFactory.cpp
                EventSystem/Dispatcher.cpp

                Input/Translator/KeyCodeTranslator.cpp
                Input/Translator/MouseCodeTranslator.cpp
                Input/Listener/KeyboardListener.cpp
                Input/Listener/MouseListener.cpp
                Input/PInput.cpp

                Platform/Linux/PlatformInputManager.cpp
                Platform/Linux/Platform.cpp
                
                Application.cpp
                PicassoEngine.cpp
        )

        target_include_directories(Engine PUBLIC ${CMAKE_SOURCE_DIR})

        target_link_libraries(Engine /usr/lib/x86_64-linux-gnu/libX11.so.6.4.0)
        target_link_libraries(Engine /usr/lib/x86_64-linux-gnu/libX11-xcb.so.1.0.0)
        target_link_libraries(Engine /usr/lib/x86_64-linux-gnu/libxcb.so.1.1.0)
endif()

