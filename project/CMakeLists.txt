cmake_minimum_required(VERSION 3.31)
set(NAME core)

################################################################################

add_executable(${NAME}
	main/main.c
	main/project.h
	main/settings.h

	window/window.h
	window/window.c

	window/events.h
	window/events.c

	window/camera.h
	window/camera.c

	window/input.h
	window/input.c
	window/keys.h

	graphics/renderer.h
	graphics/renderer.c

	graphics/shader.h
	graphics/shader.c

	graphics/texture.h
	graphics/texture.c

	support/deltaTimer.h
	support/deltaTimer.c
	support/glSupport.c
	support/glSupport.h
	support/stb_image.h
	support/stb_truetype.h

	thread/lib/threads.h
	thread/lib/threads.c
	thread/dispetcher.h
	thread/dispetcher.c
	thread/workers.h
	thread/worker100.c
	thread/worker50.c
	thread/worker25.c
	thread/worker10.c
	thread/worker01.c


	apple/objects/objects.h
	apple/objects/objects.c
	apple/apple.h
	apple/apple.c
	apple/logic.h
	apple/logic.c

	network/lib/network.h
	network/lib/network.c
	network/net.h
	network/net.c
	manager/manager.h manager/manager.c
)

################################################################################
target_include_directories(${NAME}	PUBLIC	${CMAKE_CURRENT_SOURCE_DIR}/main)
target_include_directories(${NAME}	PUBLIC	${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${NAME}	PRIVATE	lib)
target_link_libraries(${NAME}	PRIVATE	glad)
target_link_libraries(${NAME}	PRIVATE	glfw)
target_link_libraries(${NAME}	PRIVATE	cglm)

if(WIN32)
target_link_libraries(${NAME}	PRIVATE	winmm)
endif()

################################################################################
set_target_properties(${NAME}
	PROPERTIES RUNTIME_OUTPUT_DIRECTORY
	${CMAKE_BINARY_DIR}/bin)

add_custom_command(TARGET ${NAME} PRE_BUILD
	COMMAND ${CMAKE_COMMAND} -E remove_directory
	"${CMAKE_BINARY_DIR}/bin")

add_custom_command(TARGET ${NAME} PRE_BUILD
	COMMAND ${CMAKE_COMMAND} -E make_directory
	"${CMAKE_BINARY_DIR}/bin")

add_custom_command(TARGET ${NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${CMAKE_SOURCE_DIR}/res/resources $<TARGET_FILE_DIR:${NAME}>)
