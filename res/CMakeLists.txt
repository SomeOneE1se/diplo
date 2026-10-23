file(GLOB_RECURSE   RESOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/resources/shaders/*.glsl
    ${CMAKE_CURRENT_SOURCE_DIR}/resources/shaders/*.glslv
    ${CMAKE_CURRENT_SOURCE_DIR}/resources/shaders/*.glslf

    ${CMAKE_CURRENT_SOURCE_DIR}/resources/textures/*.png
    ${CMAKE_CURRENT_SOURCE_DIR}/resources/textures/*.jpg
    ${CMAKE_CURRENT_SOURCE_DIR}/resources/textures/*.jpeg

    ${CMAKE_CURRENT_SOURCE_DIR}/resources/fonts/*.ttf

    ${CMAKE_CURRENT_SOURCE_DIR}/resources/*.ig
)

add_custom_target(resources SOURCES
    ${RESOURCE_FILES}
)
