add_subdirectory(modifiable_scene)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

SET(MOC_HDRS
    Pose3dEditor.hpp
    Pose3dEditorPlugin.hpp
)

SET(HDRS
    Pose3dEditor.hpp
)

FILE(GLOB SRCS
    *.cpp
)

FILE(GLOB UI_FILES
    *.ui
)

SET(QtApp_RCCS resources.qrc)

rock_vizkit_widget(Pose3dEditor
    SOURCES ${SRCS} ${QtApp_RCC_SRCS}
    HEADERS ${HDRS}
    MOC ${MOC_HDRS}
    DEPS_PKGCONFIG QtCore QtGui QtOpenGL
    UI ${UI_FILES}
    DEPS modifiable_scene
)

QT4_ADD_RESOURCES(QtApp_RCC_SRCS ${QtApp_RCCS})

