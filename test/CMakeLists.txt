FIND_PACKAGE(Qt4 REQUIRED)
INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})

add_executable(plugintest plugintest.cpp)
target_link_libraries(plugintest Pose3dEditor)
