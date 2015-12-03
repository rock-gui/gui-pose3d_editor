CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
set(CMAKE_BUILD_TYPE Debug)

FIND_PACKAGE(OpenSceneGraph REQUIRED osgManipulator osgViewer osgDB osgUtil osgGA osgText)
find_package(PkgConfig)
pkg_check_modules(OSGQT openscenegraph-osgQt)


FIND_PACKAGE(Qt4 REQUIRED)
INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS} "-fPIC")
SET(QT_USE_QTOPENGL TRUE)


INCLUDE_DIRECTORIES(${OPENSCENEGRAPH_INCLUDE_DIRS})


add_library( modifiable_scene scene.h scene.cpp sceneitem.h sceneitem.cpp manipulatable.h manipulatable.cpp dragger.h dragger.cpp)
TARGET_LINK_LIBRARIES( modifiable_scene ${OPENSCENEGRAPH_LIBRARIES} ${OSGQT_LIBRARIES})
install (FILES scene.h sceneitem.h manipulatable.h dragger.h DESTINATION include/${PROJECT_NAME}/modifiable_scene)

