#include <QtCore>
#include <iostream>
#include <QApplication>
#include "../src/Pose3dEditor.hpp"
#include "../viz/Pose3dEditorVizkit.hpp"

int main(int argc, char** argv)
{
    QStringList paths = QCoreApplication::libraryPaths(); for (QStringList::iterator it = paths.begin(); it!=paths.end(); it++) { std::cout << "Looking for plugins at path: " << it->toStdString() << std::endl; }

    QApplication app(argc, argv);

    vizkit3d::Pose3dEditorVizkit* widget = new vizkit3d::Pose3dEditorVizkit();
    widget->scene()->add_movable_from_mesh_file("my_movable", "test_data/AILA_Head.STL", 0.001);
    widget->setPosition(QVector3D(1,0,0));

    app.exec();
    return 0;
}

