FIND_PACKAGE(Qt4 REQUIRED QtCore QtGui QtOpenGL)
INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})

add_executable(plugintest plugintest.cpp)
target_link_libraries(plugintest Pose3dEditor)

find_package(PkgConfig)
pkg_check_modules(EIGEN eigen3)
pkg_check_modules(vizkit3d vizkit3d)
find_package(Boost COMPONENTS system filesystem REQUIRED)
include_directories(${EIGEN_INCLUDE_DIRS} ${vizkit3d_INCLUDE_DIRS})

add_executable(vizkitest vizkittest.cpp)
target_link_libraries(vizkitest pose3d_editor-viz Pose3dEditor modifiable_scene ${vizkit3d_LIBRARIES} ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_SYSTEM_LIBRARY})
