cmake_minimum_required(VERSION 3.2)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE AND DEFINED ENV{CMAKE_TOOLCHAIN_FILE})
   set(CMAKE_TOOLCHAIN_FILE $ENV{CMAKE_TOOLCHAIN_FILE})
endif()

# Build and .exe name
project(ray-marching-build)
set(TargetName ray-marching)

# Use C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# Run moc automatically (Qt projects ONLY)
set(CMAKE_AUTOMOC ON)

# Find packages
find_package(Qt5Widgets)
find_package(fmt CONFIG REQUIRED)
find_package(OpenImageIO CONFIG REQUIRED)
find_package(freetype CONFIG REQUIRED)

# Set the name of the executable we want to build
add_executable(${TargetName})

# Add NGL include path
include_directories(include $ENV{HOME}/NGL/include)
target_sources(${TargetName} PRIVATE
	# .cpp
	${PROJECT_SOURCE_DIR}/src/main.cpp
	${PROJECT_SOURCE_DIR}/src/NGLScene.cpp
	${PROJECT_SOURCE_DIR}/src/ScreenQuad.cpp
    ${PROJECT_SOURCE_DIR}/src/NGLSceneMouseControls.cpp
	${PROJECT_SOURCE_DIR}/src/Window.cpp
	${PROJECT_SOURCE_DIR}/src/ContainerWidget.cpp
	${PROJECT_SOURCE_DIR}/src/ShaderCodeWidget.cpp
	${PROJECT_SOURCE_DIR}/src/CodeEditorWidget.cpp
	${PROJECT_SOURCE_DIR}/src/SyntaxHighlighter.cpp
	# .h
	${PROJECT_SOURCE_DIR}/include/NGLScene.h
	${PROJECT_SOURCE_DIR}/include/ScreenQuad.h
	${PROJECT_SOURCE_DIR}/include/Window.h
	${PROJECT_SOURCE_DIR}/include/WindowParams.h
	${PROJECT_SOURCE_DIR}/include/Window.h
	${PROJECT_SOURCE_DIR}/include/ContainerWidget.h
	${PROJECT_SOURCE_DIR}/include/ShaderCodeWidget.h
	${PROJECT_SOURCE_DIR}/include/CodeEditorWidget.h
	${PROJECT_SOURCE_DIR}/include/SyntaxHighlighter.h
	#.glsl
	${PROJECT_SOURCE_DIR}/shaders/RayMarchFragment.glsl
	${PROJECT_SOURCE_DIR}/shaders/RayMarchVertex.glsl
)

# Platform specific definitions
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	message("Mac build")
  	find_library(MACGL OpenGL)
  	find_package(IlmBase CONFIG REQUIRED)
	find_package(OpenEXR CONFIG REQUIRED)
	set(EXTRALIBS ${MACGL})
	target_link_libraries(${TargetName} PRIVATE IlmBase::Iex IlmBase::Half IlmBase::Imath IlmBase::IexMath)
	target_link_libraries(${TargetName} PRIVATE OpenEXR::IlmImf OpenEXR::IlmImfUtil OpenEXR::IlmImfConfig)
	add_definitions(-DGL_SCILENCE_DEPRICATION)
	set(PROJECT_LINK_LIBS ${MACGL} NGL)

elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	set(PROJECT_LINK_LIBS -lGL NGL)

elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	include_directories(include $ENV{HOMEDRIVE}/$ENV{HOMEPATH}/NGL/include)
	link_directories($ENV{HOMEDRIVE}/$ENV{HOMEPATH}/NGL/lib)	
	target_link_libraries(${TargetName} PRIVATE $ENV{HOMEDRIVE}/$ENV{HOMEPATH}/NGL/lib/NGL.lib)
	add_compile_definitions(_USE_MATH_DEFINES)
	add_compile_definitions(NOMINMAX)
	target_compile_definitions(${TargetName} PRIVATE /wd4251)
	# Need to define this when building shared library or suffer dllimport errors
	add_compile_definitions(BUILDING_DLL)
endif()

# Link NGL
target_link_directories(${TargetName} PRIVATE $ENV{HOME}/NGL/lib)

# Link packages
target_link_libraries(${TargetName} PRIVATE OpenImageIO::OpenImageIO OpenImageIO::OpenImageIO_Util)
target_link_libraries(${TargetName} PRIVATE ${PROJECT_LINK_LIBS} Qt5::Widgets fmt::fmt-header-only freetype)

# Copy shaders to .exe directory
add_custom_target(${TargetName}CopyShaders ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/shaders
    $<TARGET_FILE_DIR:${TargetName}>/shaders
)
