include_directories(../src)
rock_vizkit_plugin(pose3d_editor-viz
    Pose3dEditorVizkit.cpp
    DEPS_PKGCONFIG base-types
    DEPS Pose3dEditor modifiable_scene
    MOC Pose3dEditorVizkit.hpp
    HEADERS Pose3dEditorVizkit.hpp)

