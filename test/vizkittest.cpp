#include <QtCore>
#include <iostream>
#include <QApplication>
#include "../src/Pose3dEditor.hpp"
#include "../viz/Pose3dEditorVizkit.hpp"
#include <vizkit3d/QVizkitMainWindow.hpp>
#include <vizkit3d/QtThreadedWidget.hpp>

int main(int argc, char** argv)
{
    QStringList paths = QCoreApplication::libraryPaths(); for (QStringList::iterator it = paths.begin(); it!=paths.end(); it++) { std::cout << "Looking for plugins at path: " << it->toStdString() << std::endl; }

    QApplication app(argc, argv);
    vizkit3d::Vizkit3DWidget* widget = new vizkit3d::Vizkit3DWidget();
    widget->show();

    //vizkit3d::Vizkit3DWidget will destroy this gui internally
    vizkit3d::Pose3dEditorVizkit* plugin =  new vizkit3d::Pose3dEditorVizkit();
    widget->addPlugin(plugin);

    plugin->scene()->add_movable_from_mesh_file("my_movable", "../../test/test_data/AILA_Head.STL", 0.001);
    plugin->setPosition(QVector3D(1,0,0));

    plugin->scene()->add_movable_from_mesh_file("my_movable2", "../../test/test_data/AILA_Head.STL", 0.001);
    plugin->setPosition(QVector3D(-1,0,0), "my_movable2");

    plugin->scene()->add_movable_from_mesh_file("my_movablegone", "../../test/test_data/AILA_Head.STL", 0.001);
    plugin->removeMovable("my_movablegone");

    plugin->scene()->add_movable_from_mesh_file("my_movable3", "../../test/test_data/AILA_Head.STL", 0.001);
    plugin->setOrientation(QQuaternion(-1,1,0,0), "my_movable3");

    app.exec();

    return 0;
}

