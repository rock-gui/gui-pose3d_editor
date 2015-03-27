include_directories(../src)

add_definitions(-DEIGEN_DONT_ALIGN)
rock_find_cmake(Boost REQUIRED COMPONENTS thread system)
rock_vizkit_plugin(pose3d_editor-viz
    Pose3dEditorVizkit.cpp
    DEPS_PKGCONFIG base-types eigen3
    DEPS pose3d_editor modifiable_scene
    MOC Pose3dEditorVizkit.hpp
    HEADERS Pose3dEditorVizkit.hpp
    LIBS ${Boost_THREAD_LIBRARY} ${Boost_SYSTEM_LIBRARY})

