# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Pharadas\Documents\repos\VulkanEngine

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Pharadas\Documents\repos\VulkanEngine

# Include any dependencies generated for this target.
include CMakeFiles/GamingTime.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/GamingTime.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/GamingTime.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/GamingTime.dir/flags.make

CMakeFiles/GamingTime.dir/include/engine/buffer_helper.cpp.obj: CMakeFiles/GamingTime.dir/flags.make
CMakeFiles/GamingTime.dir/include/engine/buffer_helper.cpp.obj: CMakeFiles/GamingTime.dir/includes_CXX.rsp
CMakeFiles/GamingTime.dir/include/engine/buffer_helper.cpp.obj: include/engine/buffer_helper.cpp
CMakeFiles/GamingTime.dir/include/engine/buffer_helper.cpp.obj: CMakeFiles/GamingTime.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Pharadas\Documents\repos\VulkanEngine\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/GamingTime.dir/include/engine/buffer_helper.cpp.obj"
	C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/GamingTime.dir/include/engine/buffer_helper.cpp.obj -MF CMakeFiles\GamingTime.dir\include\engine\buffer_helper.cpp.obj.d -o CMakeFiles\GamingTime.dir\include\engine\buffer_helper.cpp.obj -c C:\Users\Pharadas\Documents\repos\VulkanEngine\include\engine\buffer_helper.cpp

CMakeFiles/GamingTime.dir/include/engine/buffer_helper.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GamingTime.dir/include/engine/buffer_helper.cpp.i"
	C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Pharadas\Documents\repos\VulkanEngine\include\engine\buffer_helper.cpp > CMakeFiles\GamingTime.dir\include\engine\buffer_helper.cpp.i

CMakeFiles/GamingTime.dir/include/engine/buffer_helper.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GamingTime.dir/include/engine/buffer_helper.cpp.s"
	C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Pharadas\Documents\repos\VulkanEngine\include\engine\buffer_helper.cpp -o CMakeFiles\GamingTime.dir\include\engine\buffer_helper.cpp.s

CMakeFiles/GamingTime.dir/include/engine/descriptors/descriptor.cpp.obj: CMakeFiles/GamingTime.dir/flags.make
CMakeFiles/GamingTime.dir/include/engine/descriptors/descriptor.cpp.obj: CMakeFiles/GamingTime.dir/includes_CXX.rsp
CMakeFiles/GamingTime.dir/include/engine/descriptors/descriptor.cpp.obj: include/engine/descriptors/descriptor.cpp
CMakeFiles/GamingTime.dir/include/engine/descriptors/descriptor.cpp.obj: CMakeFiles/GamingTime.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Pharadas\Documents\repos\VulkanEngine\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/GamingTime.dir/include/engine/descriptors/descriptor.cpp.obj"
	C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/GamingTime.dir/include/engine/descriptors/descriptor.cpp.obj -MF CMakeFiles\GamingTime.dir\include\engine\descriptors\descriptor.cpp.obj.d -o CMakeFiles\GamingTime.dir\include\engine\descriptors\descriptor.cpp.obj -c C:\Users\Pharadas\Documents\repos\VulkanEngine\include\engine\descriptors\descriptor.cpp

CMakeFiles/GamingTime.dir/include/engine/descriptors/descriptor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GamingTime.dir/include/engine/descriptors/descriptor.cpp.i"
	C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Pharadas\Documents\repos\VulkanEngine\include\engine\descriptors\descriptor.cpp > CMakeFiles\GamingTime.dir\include\engine\descriptors\descriptor.cpp.i

CMakeFiles/GamingTime.dir/include/engine/descriptors/descriptor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GamingTime.dir/include/engine/descriptors/descriptor.cpp.s"
	C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Pharadas\Documents\repos\VulkanEngine\include\engine\descriptors\descriptor.cpp -o CMakeFiles\GamingTime.dir\include\engine\descriptors\descriptor.cpp.s

CMakeFiles/GamingTime.dir/include/engine/device/device.cpp.obj: CMakeFiles/GamingTime.dir/flags.make
CMakeFiles/GamingTime.dir/include/engine/device/device.cpp.obj: CMakeFiles/GamingTime.dir/includes_CXX.rsp
CMakeFiles/GamingTime.dir/include/engine/device/device.cpp.obj: include/engine/device/device.cpp
CMakeFiles/GamingTime.dir/include/engine/device/device.cpp.obj: CMakeFiles/GamingTime.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Pharadas\Documents\repos\VulkanEngine\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/GamingTime.dir/include/engine/device/device.cpp.obj"
	C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/GamingTime.dir/include/engine/device/device.cpp.obj -MF CMakeFiles\GamingTime.dir\include\engine\device\device.cpp.obj.d -o CMakeFiles\GamingTime.dir\include\engine\device\device.cpp.obj -c C:\Users\Pharadas\Documents\repos\VulkanEngine\include\engine\device\device.cpp

CMakeFiles/GamingTime.dir/include/engine/device/device.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GamingTime.dir/include/engine/device/device.cpp.i"
	C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Pharadas\Documents\repos\VulkanEngine\include\engine\device\device.cpp > CMakeFiles\GamingTime.dir\include\engine\device\device.cpp.i

CMakeFiles/GamingTime.dir/include/engine/device/device.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GamingTime.dir/include/engine/device/device.cpp.s"
	C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Pharadas\Documents\repos\VulkanEngine\include\engine\device\device.cpp -o CMakeFiles\GamingTime.dir\include\engine\device\device.cpp.s

CMakeFiles/GamingTime.dir/include/engine/engine.cpp.obj: CMakeFiles/GamingTime.dir/flags.make
CMakeFiles/GamingTime.dir/include/engine/engine.cpp.obj: CMakeFiles/GamingTime.dir/includes_CXX.rsp
CMakeFiles/GamingTime.dir/include/engine/engine.cpp.obj: include/engine/engine.cpp
CMakeFiles/GamingTime.dir/include/engine/engine.cpp.obj: CMakeFiles/GamingTime.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Pharadas\Documents\repos\VulkanEngine\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/GamingTime.dir/include/engine/engine.cpp.obj"
	C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/GamingTime.dir/include/engine/engine.cpp.obj -MF CMakeFiles\GamingTime.dir\include\engine\engine.cpp.obj.d -o CMakeFiles\GamingTime.dir\include\engine\engine.cpp.obj -c C:\Users\Pharadas\Documents\repos\VulkanEngine\include\engine\engine.cpp

CMakeFiles/GamingTime.dir/include/engine/engine.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GamingTime.dir/include/engine/engine.cpp.i"
	C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Pharadas\Documents\repos\VulkanEngine\include\engine\engine.cpp > CMakeFiles\GamingTime.dir\include\engine\engine.cpp.i

CMakeFiles/GamingTime.dir/include/engine/engine.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GamingTime.dir/include/engine/engine.cpp.s"
	C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Pharadas\Documents\repos\VulkanEngine\include\engine\engine.cpp -o CMakeFiles\GamingTime.dir\include\engine\engine.cpp.s

CMakeFiles/GamingTime.dir/include/engine/helper_functions.cpp.obj: CMakeFiles/GamingTime.dir/flags.make
CMakeFiles/GamingTime.dir/include/engine/helper_functions.cpp.obj: CMakeFiles/GamingTime.dir/includes_CXX.rsp
CMakeFiles/GamingTime.dir/include/engine/helper_functions.cpp.obj: include/engine/helper_functions.cpp
CMakeFiles/GamingTime.dir/include/engine/helper_functions.cpp.obj: CMakeFiles/GamingTime.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Pharadas\Documents\repos\VulkanEngine\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/GamingTime.dir/include/engine/helper_functions.cpp.obj"
	C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/GamingTime.dir/include/engine/helper_functions.cpp.obj -MF CMakeFiles\GamingTime.dir\include\engine\helper_functions.cpp.obj.d -o CMakeFiles\GamingTime.dir\include\engine\helper_functions.cpp.obj -c C:\Users\Pharadas\Documents\repos\VulkanEngine\include\engine\helper_functions.cpp

CMakeFiles/GamingTime.dir/include/engine/helper_functions.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GamingTime.dir/include/engine/helper_functions.cpp.i"
	C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Pharadas\Documents\repos\VulkanEngine\include\engine\helper_functions.cpp > CMakeFiles\GamingTime.dir\include\engine\helper_functions.cpp.i

CMakeFiles/GamingTime.dir/include/engine/helper_functions.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GamingTime.dir/include/engine/helper_functions.cpp.s"
	C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Pharadas\Documents\repos\VulkanEngine\include\engine\helper_functions.cpp -o CMakeFiles\GamingTime.dir\include\engine\helper_functions.cpp.s

CMakeFiles/GamingTime.dir/include/engine/material/material.cpp.obj: CMakeFiles/GamingTime.dir/flags.make
CMakeFiles/GamingTime.dir/include/engine/material/material.cpp.obj: CMakeFiles/GamingTime.dir/includes_CXX.rsp
CMakeFiles/GamingTime.dir/include/engine/material/material.cpp.obj: include/engine/material/material.cpp
CMakeFiles/GamingTime.dir/include/engine/material/material.cpp.obj: CMakeFiles/GamingTime.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Pharadas\Documents\repos\VulkanEngine\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/GamingTime.dir/include/engine/material/material.cpp.obj"
	C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/GamingTime.dir/include/engine/material/material.cpp.obj -MF CMakeFiles\GamingTime.dir\include\engine\material\material.cpp.obj.d -o CMakeFiles\GamingTime.dir\include\engine\material\material.cpp.obj -c C:\Users\Pharadas\Documents\repos\VulkanEngine\include\engine\material\material.cpp

CMakeFiles/GamingTime.dir/include/engine/material/material.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GamingTime.dir/include/engine/material/material.cpp.i"
	C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Pharadas\Documents\repos\VulkanEngine\include\engine\material\material.cpp > CMakeFiles\GamingTime.dir\include\engine\material\material.cpp.i

CMakeFiles/GamingTime.dir/include/engine/material/material.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GamingTime.dir/include/engine/material/material.cpp.s"
	C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Pharadas\Documents\repos\VulkanEngine\include\engine\material\material.cpp -o CMakeFiles\GamingTime.dir\include\engine\material\material.cpp.s

CMakeFiles/GamingTime.dir/include/engine/mesh/mesh.cpp.obj: CMakeFiles/GamingTime.dir/flags.make
CMakeFiles/GamingTime.dir/include/engine/mesh/mesh.cpp.obj: CMakeFiles/GamingTime.dir/includes_CXX.rsp
CMakeFiles/GamingTime.dir/include/engine/mesh/mesh.cpp.obj: include/engine/mesh/mesh.cpp
CMakeFiles/GamingTime.dir/include/engine/mesh/mesh.cpp.obj: CMakeFiles/GamingTime.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Pharadas\Documents\repos\VulkanEngine\CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/GamingTime.dir/include/engine/mesh/mesh.cpp.obj"
	C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/GamingTime.dir/include/engine/mesh/mesh.cpp.obj -MF CMakeFiles\GamingTime.dir\include\engine\mesh\mesh.cpp.obj.d -o CMakeFiles\GamingTime.dir\include\engine\mesh\mesh.cpp.obj -c C:\Users\Pharadas\Documents\repos\VulkanEngine\include\engine\mesh\mesh.cpp

CMakeFiles/GamingTime.dir/include/engine/mesh/mesh.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GamingTime.dir/include/engine/mesh/mesh.cpp.i"
	C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Pharadas\Documents\repos\VulkanEngine\include\engine\mesh\mesh.cpp > CMakeFiles\GamingTime.dir\include\engine\mesh\mesh.cpp.i

CMakeFiles/GamingTime.dir/include/engine/mesh/mesh.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GamingTime.dir/include/engine/mesh/mesh.cpp.s"
	C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Pharadas\Documents\repos\VulkanEngine\include\engine\mesh\mesh.cpp -o CMakeFiles\GamingTime.dir\include\engine\mesh\mesh.cpp.s

CMakeFiles/GamingTime.dir/include/engine/pipeline/pipeline.cpp.obj: CMakeFiles/GamingTime.dir/flags.make
CMakeFiles/GamingTime.dir/include/engine/pipeline/pipeline.cpp.obj: CMakeFiles/GamingTime.dir/includes_CXX.rsp
CMakeFiles/GamingTime.dir/include/engine/pipeline/pipeline.cpp.obj: include/engine/pipeline/pipeline.cpp
CMakeFiles/GamingTime.dir/include/engine/pipeline/pipeline.cpp.obj: CMakeFiles/GamingTime.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Pharadas\Documents\repos\VulkanEngine\CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/GamingTime.dir/include/engine/pipeline/pipeline.cpp.obj"
	C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/GamingTime.dir/include/engine/pipeline/pipeline.cpp.obj -MF CMakeFiles\GamingTime.dir\include\engine\pipeline\pipeline.cpp.obj.d -o CMakeFiles\GamingTime.dir\include\engine\pipeline\pipeline.cpp.obj -c C:\Users\Pharadas\Documents\repos\VulkanEngine\include\engine\pipeline\pipeline.cpp

CMakeFiles/GamingTime.dir/include/engine/pipeline/pipeline.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GamingTime.dir/include/engine/pipeline/pipeline.cpp.i"
	C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Pharadas\Documents\repos\VulkanEngine\include\engine\pipeline\pipeline.cpp > CMakeFiles\GamingTime.dir\include\engine\pipeline\pipeline.cpp.i

CMakeFiles/GamingTime.dir/include/engine/pipeline/pipeline.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GamingTime.dir/include/engine/pipeline/pipeline.cpp.s"
	C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Pharadas\Documents\repos\VulkanEngine\include\engine\pipeline\pipeline.cpp -o CMakeFiles\GamingTime.dir\include\engine\pipeline\pipeline.cpp.s

CMakeFiles/GamingTime.dir/include/engine/texture/texture.cpp.obj: CMakeFiles/GamingTime.dir/flags.make
CMakeFiles/GamingTime.dir/include/engine/texture/texture.cpp.obj: CMakeFiles/GamingTime.dir/includes_CXX.rsp
CMakeFiles/GamingTime.dir/include/engine/texture/texture.cpp.obj: include/engine/texture/texture.cpp
CMakeFiles/GamingTime.dir/include/engine/texture/texture.cpp.obj: CMakeFiles/GamingTime.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Pharadas\Documents\repos\VulkanEngine\CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/GamingTime.dir/include/engine/texture/texture.cpp.obj"
	C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/GamingTime.dir/include/engine/texture/texture.cpp.obj -MF CMakeFiles\GamingTime.dir\include\engine\texture\texture.cpp.obj.d -o CMakeFiles\GamingTime.dir\include\engine\texture\texture.cpp.obj -c C:\Users\Pharadas\Documents\repos\VulkanEngine\include\engine\texture\texture.cpp

CMakeFiles/GamingTime.dir/include/engine/texture/texture.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GamingTime.dir/include/engine/texture/texture.cpp.i"
	C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Pharadas\Documents\repos\VulkanEngine\include\engine\texture\texture.cpp > CMakeFiles\GamingTime.dir\include\engine\texture\texture.cpp.i

CMakeFiles/GamingTime.dir/include/engine/texture/texture.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GamingTime.dir/include/engine/texture/texture.cpp.s"
	C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Pharadas\Documents\repos\VulkanEngine\include\engine\texture\texture.cpp -o CMakeFiles\GamingTime.dir\include\engine\texture\texture.cpp.s

CMakeFiles/GamingTime.dir/include/engine/window/window.cpp.obj: CMakeFiles/GamingTime.dir/flags.make
CMakeFiles/GamingTime.dir/include/engine/window/window.cpp.obj: CMakeFiles/GamingTime.dir/includes_CXX.rsp
CMakeFiles/GamingTime.dir/include/engine/window/window.cpp.obj: include/engine/window/window.cpp
CMakeFiles/GamingTime.dir/include/engine/window/window.cpp.obj: CMakeFiles/GamingTime.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Pharadas\Documents\repos\VulkanEngine\CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/GamingTime.dir/include/engine/window/window.cpp.obj"
	C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/GamingTime.dir/include/engine/window/window.cpp.obj -MF CMakeFiles\GamingTime.dir\include\engine\window\window.cpp.obj.d -o CMakeFiles\GamingTime.dir\include\engine\window\window.cpp.obj -c C:\Users\Pharadas\Documents\repos\VulkanEngine\include\engine\window\window.cpp

CMakeFiles/GamingTime.dir/include/engine/window/window.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GamingTime.dir/include/engine/window/window.cpp.i"
	C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Pharadas\Documents\repos\VulkanEngine\include\engine\window\window.cpp > CMakeFiles\GamingTime.dir\include\engine\window\window.cpp.i

CMakeFiles/GamingTime.dir/include/engine/window/window.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GamingTime.dir/include/engine/window/window.cpp.s"
	C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Pharadas\Documents\repos\VulkanEngine\include\engine\window\window.cpp -o CMakeFiles\GamingTime.dir\include\engine\window\window.cpp.s

CMakeFiles/GamingTime.dir/include/engine/world_object/world_object.cpp.obj: CMakeFiles/GamingTime.dir/flags.make
CMakeFiles/GamingTime.dir/include/engine/world_object/world_object.cpp.obj: CMakeFiles/GamingTime.dir/includes_CXX.rsp
CMakeFiles/GamingTime.dir/include/engine/world_object/world_object.cpp.obj: include/engine/world_object/world_object.cpp
CMakeFiles/GamingTime.dir/include/engine/world_object/world_object.cpp.obj: CMakeFiles/GamingTime.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Pharadas\Documents\repos\VulkanEngine\CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/GamingTime.dir/include/engine/world_object/world_object.cpp.obj"
	C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/GamingTime.dir/include/engine/world_object/world_object.cpp.obj -MF CMakeFiles\GamingTime.dir\include\engine\world_object\world_object.cpp.obj.d -o CMakeFiles\GamingTime.dir\include\engine\world_object\world_object.cpp.obj -c C:\Users\Pharadas\Documents\repos\VulkanEngine\include\engine\world_object\world_object.cpp

CMakeFiles/GamingTime.dir/include/engine/world_object/world_object.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GamingTime.dir/include/engine/world_object/world_object.cpp.i"
	C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Pharadas\Documents\repos\VulkanEngine\include\engine\world_object\world_object.cpp > CMakeFiles\GamingTime.dir\include\engine\world_object\world_object.cpp.i

CMakeFiles/GamingTime.dir/include/engine/world_object/world_object.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GamingTime.dir/include/engine/world_object/world_object.cpp.s"
	C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Pharadas\Documents\repos\VulkanEngine\include\engine\world_object\world_object.cpp -o CMakeFiles\GamingTime.dir\include\engine\world_object\world_object.cpp.s

CMakeFiles/GamingTime.dir/source/main.cpp.obj: CMakeFiles/GamingTime.dir/flags.make
CMakeFiles/GamingTime.dir/source/main.cpp.obj: CMakeFiles/GamingTime.dir/includes_CXX.rsp
CMakeFiles/GamingTime.dir/source/main.cpp.obj: source/main.cpp
CMakeFiles/GamingTime.dir/source/main.cpp.obj: CMakeFiles/GamingTime.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Pharadas\Documents\repos\VulkanEngine\CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/GamingTime.dir/source/main.cpp.obj"
	C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/GamingTime.dir/source/main.cpp.obj -MF CMakeFiles\GamingTime.dir\source\main.cpp.obj.d -o CMakeFiles\GamingTime.dir\source\main.cpp.obj -c C:\Users\Pharadas\Documents\repos\VulkanEngine\source\main.cpp

CMakeFiles/GamingTime.dir/source/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GamingTime.dir/source/main.cpp.i"
	C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Pharadas\Documents\repos\VulkanEngine\source\main.cpp > CMakeFiles\GamingTime.dir\source\main.cpp.i

CMakeFiles/GamingTime.dir/source/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GamingTime.dir/source/main.cpp.s"
	C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Pharadas\Documents\repos\VulkanEngine\source\main.cpp -o CMakeFiles\GamingTime.dir\source\main.cpp.s

# Object files for target GamingTime
GamingTime_OBJECTS = \
"CMakeFiles/GamingTime.dir/include/engine/buffer_helper.cpp.obj" \
"CMakeFiles/GamingTime.dir/include/engine/descriptors/descriptor.cpp.obj" \
"CMakeFiles/GamingTime.dir/include/engine/device/device.cpp.obj" \
"CMakeFiles/GamingTime.dir/include/engine/engine.cpp.obj" \
"CMakeFiles/GamingTime.dir/include/engine/helper_functions.cpp.obj" \
"CMakeFiles/GamingTime.dir/include/engine/material/material.cpp.obj" \
"CMakeFiles/GamingTime.dir/include/engine/mesh/mesh.cpp.obj" \
"CMakeFiles/GamingTime.dir/include/engine/pipeline/pipeline.cpp.obj" \
"CMakeFiles/GamingTime.dir/include/engine/texture/texture.cpp.obj" \
"CMakeFiles/GamingTime.dir/include/engine/window/window.cpp.obj" \
"CMakeFiles/GamingTime.dir/include/engine/world_object/world_object.cpp.obj" \
"CMakeFiles/GamingTime.dir/source/main.cpp.obj"

# External object files for target GamingTime
GamingTime_EXTERNAL_OBJECTS =

build/GamingTime.exe: CMakeFiles/GamingTime.dir/include/engine/buffer_helper.cpp.obj
build/GamingTime.exe: CMakeFiles/GamingTime.dir/include/engine/descriptors/descriptor.cpp.obj
build/GamingTime.exe: CMakeFiles/GamingTime.dir/include/engine/device/device.cpp.obj
build/GamingTime.exe: CMakeFiles/GamingTime.dir/include/engine/engine.cpp.obj
build/GamingTime.exe: CMakeFiles/GamingTime.dir/include/engine/helper_functions.cpp.obj
build/GamingTime.exe: CMakeFiles/GamingTime.dir/include/engine/material/material.cpp.obj
build/GamingTime.exe: CMakeFiles/GamingTime.dir/include/engine/mesh/mesh.cpp.obj
build/GamingTime.exe: CMakeFiles/GamingTime.dir/include/engine/pipeline/pipeline.cpp.obj
build/GamingTime.exe: CMakeFiles/GamingTime.dir/include/engine/texture/texture.cpp.obj
build/GamingTime.exe: CMakeFiles/GamingTime.dir/include/engine/window/window.cpp.obj
build/GamingTime.exe: CMakeFiles/GamingTime.dir/include/engine/world_object/world_object.cpp.obj
build/GamingTime.exe: CMakeFiles/GamingTime.dir/source/main.cpp.obj
build/GamingTime.exe: CMakeFiles/GamingTime.dir/build.make
build/GamingTime.exe: CMakeFiles/GamingTime.dir/linklibs.rsp
build/GamingTime.exe: CMakeFiles/GamingTime.dir/objects1.rsp
build/GamingTime.exe: CMakeFiles/GamingTime.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Pharadas\Documents\repos\VulkanEngine\CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Linking CXX executable build\GamingTime.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\GamingTime.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/GamingTime.dir/build: build/GamingTime.exe
.PHONY : CMakeFiles/GamingTime.dir/build

CMakeFiles/GamingTime.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\GamingTime.dir\cmake_clean.cmake
.PHONY : CMakeFiles/GamingTime.dir/clean

CMakeFiles/GamingTime.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Pharadas\Documents\repos\VulkanEngine C:\Users\Pharadas\Documents\repos\VulkanEngine C:\Users\Pharadas\Documents\repos\VulkanEngine C:\Users\Pharadas\Documents\repos\VulkanEngine C:\Users\Pharadas\Documents\repos\VulkanEngine\CMakeFiles\GamingTime.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/GamingTime.dir/depend

