# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/mengjiao/Desktop/project/DifferentialVolumeRendering

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mengjiao/Desktop/project/DifferentialVolumeRendering/build

# Include any dependencies generated for this target.
include CMakeFiles/libs.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/libs.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/libs.dir/flags.make

CMakeFiles/libs.dir/loadVTK.cpp.o: CMakeFiles/libs.dir/flags.make
CMakeFiles/libs.dir/loadVTK.cpp.o: ../loadVTK.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mengjiao/Desktop/project/DifferentialVolumeRendering/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/libs.dir/loadVTK.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/libs.dir/loadVTK.cpp.o -c /home/mengjiao/Desktop/project/DifferentialVolumeRendering/loadVTK.cpp

CMakeFiles/libs.dir/loadVTK.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libs.dir/loadVTK.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mengjiao/Desktop/project/DifferentialVolumeRendering/loadVTK.cpp > CMakeFiles/libs.dir/loadVTK.cpp.i

CMakeFiles/libs.dir/loadVTK.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libs.dir/loadVTK.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mengjiao/Desktop/project/DifferentialVolumeRendering/loadVTK.cpp -o CMakeFiles/libs.dir/loadVTK.cpp.s

CMakeFiles/libs.dir/parseArgs.cpp.o: CMakeFiles/libs.dir/flags.make
CMakeFiles/libs.dir/parseArgs.cpp.o: ../parseArgs.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mengjiao/Desktop/project/DifferentialVolumeRendering/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/libs.dir/parseArgs.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/libs.dir/parseArgs.cpp.o -c /home/mengjiao/Desktop/project/DifferentialVolumeRendering/parseArgs.cpp

CMakeFiles/libs.dir/parseArgs.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libs.dir/parseArgs.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mengjiao/Desktop/project/DifferentialVolumeRendering/parseArgs.cpp > CMakeFiles/libs.dir/parseArgs.cpp.i

CMakeFiles/libs.dir/parseArgs.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libs.dir/parseArgs.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mengjiao/Desktop/project/DifferentialVolumeRendering/parseArgs.cpp -o CMakeFiles/libs.dir/parseArgs.cpp.s

# Object files for target libs
libs_OBJECTS = \
"CMakeFiles/libs.dir/loadVTK.cpp.o" \
"CMakeFiles/libs.dir/parseArgs.cpp.o"

# External object files for target libs
libs_EXTERNAL_OBJECTS =

liblibs.so: CMakeFiles/libs.dir/loadVTK.cpp.o
liblibs.so: CMakeFiles/libs.dir/parseArgs.cpp.o
liblibs.so: CMakeFiles/libs.dir/build.make
liblibs.so: /home/mengjiao/Desktop/project/ospcommon/install/lib/libospcommon.so
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkDomainsChemistryOpenGL2-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkFiltersFlowPaths-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkFiltersGeneric-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkFiltersHyperTree-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkFiltersParallelImaging-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkFiltersPoints-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkFiltersProgrammable-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkFiltersSMP-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkFiltersSelection-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkFiltersTexture-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkFiltersTopology-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkFiltersVerdict-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkGeovisCore-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkIOAMR-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkIOAsynchronous-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkIOCityGML-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkIOEnSight-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkIOExodus-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkIOExportOpenGL2-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkIOExportPDF-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkIOImport-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkIOInfovis-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkIOLSDyna-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkIOMINC-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkIOMovie-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkIOPLY-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkIOParallel-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkIOParallelXML-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkIOSQL-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkIOSegY-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkIOTecplotTable-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkIOVeraOut-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkIOVideo-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkImagingMorphological-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkImagingStatistics-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkImagingStencil-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkInteractionImage-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkRenderingContextOpenGL2-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkRenderingImage-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkRenderingLOD-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkRenderingVolumeOpenGL2-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkViewsContext2D-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkViewsInfovis-8.2.so.1
liblibs.so: /usr/lib/x86_64-linux-gnu/libtbb.so
liblibs.so: /usr/lib/x86_64-linux-gnu/libtbbmalloc.so
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkDomainsChemistry-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkverdict-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkproj-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkFiltersAMR-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkpugixml-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkIOExport-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkRenderingGL2PSOpenGL2-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkgl2ps-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtklibharu-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtklibxml2-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtktheora-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkogg-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkFiltersParallel-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkexodusII-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkIOGeometry-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkIONetCDF-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkNetCDF-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkjsoncpp-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkParallelCore-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkIOLegacy-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtksqlite-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkhdf5-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkhdf5_hl-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkRenderingOpenGL2-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkglew-8.2.so.1
liblibs.so: /usr/lib/x86_64-linux-gnu/libSM.so
liblibs.so: /usr/lib/x86_64-linux-gnu/libICE.so
liblibs.so: /usr/lib/x86_64-linux-gnu/libX11.so
liblibs.so: /usr/lib/x86_64-linux-gnu/libXext.so
liblibs.so: /usr/lib/x86_64-linux-gnu/libXt.so
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkImagingMath-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkChartsCore-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkRenderingContext2D-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkFiltersImaging-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkInfovisLayout-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkInfovisCore-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkViewsCore-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkInteractionWidgets-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkFiltersHybrid-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkImagingGeneral-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkImagingSources-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkFiltersModeling-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkImagingHybrid-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkIOImage-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkDICOMParser-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkmetaio-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkjpeg-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkpng-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtktiff-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkInteractionStyle-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkFiltersExtraction-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkFiltersStatistics-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkImagingFourier-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkRenderingAnnotation-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkImagingColor-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkRenderingVolume-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkImagingCore-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkIOXML-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkIOXMLParser-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkIOCore-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkdoubleconversion-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtklz4-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtklzma-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkexpat-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkRenderingLabel-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkRenderingFreeType-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkRenderingCore-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkCommonColor-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkFiltersGeometry-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkFiltersSources-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkFiltersGeneral-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkCommonComputationalGeometry-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkFiltersCore-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkCommonExecutionModel-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkCommonDataModel-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkCommonMisc-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkCommonSystem-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtksys-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkCommonTransforms-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkCommonMath-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkCommonCore-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkfreetype-8.2.so.1
liblibs.so: /home/mengjiao/external/VTK-8.2.0/install/lib/libvtkzlib-8.2.so.1
liblibs.so: CMakeFiles/libs.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mengjiao/Desktop/project/DifferentialVolumeRendering/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX shared library liblibs.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/libs.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/libs.dir/build: liblibs.so

.PHONY : CMakeFiles/libs.dir/build

CMakeFiles/libs.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/libs.dir/cmake_clean.cmake
.PHONY : CMakeFiles/libs.dir/clean

CMakeFiles/libs.dir/depend:
	cd /home/mengjiao/Desktop/project/DifferentialVolumeRendering/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mengjiao/Desktop/project/DifferentialVolumeRendering /home/mengjiao/Desktop/project/DifferentialVolumeRendering /home/mengjiao/Desktop/project/DifferentialVolumeRendering/build /home/mengjiao/Desktop/project/DifferentialVolumeRendering/build /home/mengjiao/Desktop/project/DifferentialVolumeRendering/build/CMakeFiles/libs.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/libs.dir/depend
