cmake_minimum_required(VERSION 3.2)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE AND DEFINED ENV{CMAKE_TOOLCHAIN_FILE})
   set(CMAKE_TOOLCHAIN_FILE $ENV{CMAKE_TOOLCHAIN_FILE})
endif()

# Build and .exe name
project(ray-marching-build)
set(TargetName ray-marching)

# Find Qt packages on Mac (change Qt version depending on your system)
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	set(CMAKE_PREFIX_PATH "~/Qt/5.12.11/clang_64/")
	find_package(Qt5 COMPONENTS Widgets OpenGL Core Gui REQUIRED)
endif()

# Use C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# Run moc automatically (Qt projects ONLY)
set(CMAKE_AUTOMOC ON)

# Find vcpkg packages
find_package(Qt5Widgets)
find_package(fmt CONFIG REQUIRED)
find_package(OpenImageIO CONFIG REQUIRED)
find_package(freetype CONFIG REQUIRED)

# Set the name of the executable we want to build
add_executable(${TargetName})

target_sources(${TargetName} PRIVATE
	# .cpp
	${PROJECT_SOURCE_DIR}/src/main.cpp
	${PROJECT_SOURCE_DIR}/src/NGLScene.cpp
	${PROJECT_SOURCE_DIR}/src/ScreenQuad.cpp
	${PROJECT_SOURCE_DIR}/src/Window.cpp
	${PROJECT_SOURCE_DIR}/src/ShaderCodeContainer.cpp
	${PROJECT_SOURCE_DIR}/src/ShaderCodeWidget.cpp
	${PROJECT_SOURCE_DIR}/src/CodeEditor.cpp
	${PROJECT_SOURCE_DIR}/src/SyntaxHighlighter.cpp
	${PROJECT_SOURCE_DIR}/src/NodeEditorContainer.cpp
	${PROJECT_SOURCE_DIR}/src/NodeEditorWidget.cpp
	${PROJECT_SOURCE_DIR}/src/TestNode.cpp
	${PROJECT_SOURCE_DIR}/src/SphereNode.cpp
	${PROJECT_SOURCE_DIR}/src/RayMarchNode.cpp
	# .h
	${PROJECT_SOURCE_DIR}/include/NGLScene.h
	${PROJECT_SOURCE_DIR}/include/ScreenQuad.h
	${PROJECT_SOURCE_DIR}/include/Window.h
	${PROJECT_SOURCE_DIR}/include/WindowParams.h
	${PROJECT_SOURCE_DIR}/include/Window.h
	${PROJECT_SOURCE_DIR}/include/ShaderCodeContainer.h
	${PROJECT_SOURCE_DIR}/include/ShaderCodeWidget.h
	${PROJECT_SOURCE_DIR}/include/CodeEditor.h
	${PROJECT_SOURCE_DIR}/include/SyntaxHighlighter.h
	${PROJECT_SOURCE_DIR}/include/NodeEditorContainer.h
	${PROJECT_SOURCE_DIR}/include/NodeEditorWidget.h
	${PROJECT_SOURCE_DIR}/include/TestNode.h
	${PROJECT_SOURCE_DIR}/include/SphereNode.h
	${PROJECT_SOURCE_DIR}/include/RayMarchNode.h
	${PROJECT_SOURCE_DIR}/include/ShaderCodeData.h
	#.glsl
	${PROJECT_SOURCE_DIR}/shaders/DefaultFragment.glsl
	${PROJECT_SOURCE_DIR}/shaders/DefaultVertex.glsl
	${PROJECT_SOURCE_DIR}/shaders/SDFs/Capsule.glsl
	${PROJECT_SOURCE_DIR}/shaders/SDFs/Plane.glsl
	${PROJECT_SOURCE_DIR}/shaders/SDFs/Sphere.glsl
)

# Add NGL and nodeeditor include paths
include_directories(include $ENV{HOMEDRIVE}/$ENV{HOMEPATH}/$ENV{HOME}/NGL/include)
include_directories(include $ENV{HOMEDRIVE}/$ENV{HOMEPATH}/$ENV{HOME}/nodeeditor/include)

# Mac specific setup
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  	find_library(MACGL OpenGL)
  	find_package(IlmBase CONFIG REQUIRED)
	find_package(OpenEXR CONFIG REQUIRED)
	set(EXTRALIBS ${MACGL})
	target_link_libraries(${TargetName} PRIVATE IlmBase::Iex IlmBase::Half IlmBase::Imath IlmBase::IexMath)
	target_link_libraries(${TargetName} PRIVATE OpenEXR::IlmImf OpenEXR::IlmImfUtil OpenEXR::IlmImfConfig)
	add_definitions(-DGL_SCILENCE_DEPRICATION)
	set(PROJECT_LINK_LIBS ${MACGL} NGL nodes)
	target_compile_definitions(${TargetName} PRIVATE NODE_EDITOR_SHARED)
	target_link_directories(${TargetName} PRIVATE $ENV{HOME}/nodeeditor/build/lib)

# Windows specific setup
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	link_directories($ENV{HOMEDRIVE}/$ENV{HOMEPATH}/NGL/lib)
	link_directories($ENV{HOMEDRIVE}/$ENV{HOMEPATH}/nodeeditor/lib)
	target_link_libraries(${TargetName} PRIVATE $ENV{HOMEDRIVE}/$ENV{HOMEPATH}/NGL/lib/NGL.lib)
	target_link_libraries(${TargetName} PRIVATE $ENV{HOMEDRIVE}/$ENV{HOMEPATH}/nodeeditor/lib/nodes.lib)
	add_compile_definitions(_USE_MATH_DEFINES)
	add_compile_definitions(NOMINMAX)
	# NODE_EDITOR_SHARED/STATIC
	target_compile_definitions(${TargetName} PRIVATE /wd4251 NODE_EDITOR_SHARED)
	# Need to define this when building shared library or suffer dllimport errors
	add_compile_definitions(BUILDING_DLL)
	target_link_directories(${TargetName} PRIVATE $ENV{HOMEDRIVE}/$ENV{HOMEPATH}/nodeeditor/lib)
endif()

# Link NGL and nodeeditor
target_link_directories(${TargetName} PRIVATE $ENV{HOMEDRIVE}/$ENV{HOMEPATH}/$ENV{HOME}/NGL/lib)

# Link packages
target_link_libraries(${TargetName} PRIVATE OpenImageIO::OpenImageIO OpenImageIO::OpenImageIO_Util)
target_link_libraries(${TargetName} PRIVATE ${PROJECT_LINK_LIBS} Qt5::Widgets fmt::fmt-header-only freetype)

# Copy shaders to .exe directory
add_custom_target(${TargetName}CopyShaders ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/shaders
    $<TARGET_FILE_DIR:${TargetName}>/shaders
)
