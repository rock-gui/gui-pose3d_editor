rock_library(pose3d_editor
    SOURCES Dummy.cpp
    HEADERS Dummy.hpp)

rock_executable(pose3d_editor_bin Main.cpp
    DEPS pose3d_editor)

