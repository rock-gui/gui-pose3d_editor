#include <iostream>
#include "Pose3dEditorVizkit.hpp"

using namespace vizkit3d;

struct Pose3dEditorVizkit::Data {
    // Copy of the value given to updateDataIntern.
    //
    // Making a copy is required because of how OSG works
     data;
};


Pose3dEditorVizkit::Pose3dEditorVizkit()
    : p(new Data)
{
}

Pose3dEditorVizkit::~Pose3dEditorVizkit()
{
    delete p;
}

osg::ref_ptr<osg::Node> Pose3dEditorVizkit::createMainNode()
{
    // Geode is a common node used for vizkit3d plugins. It allows to display
    // "arbitrary" geometries
    return new osg::Geode();
}

void Pose3dEditorVizkit::updateMainNode ( osg::Node* node )
{
    osg::Geode* geode = static_cast<osg::Geode*>(node);
    // Update the main node using the data in p->data
}

void Pose3dEditorVizkit::updateDataIntern( const& value)
{
    p->data = value;
    std::cout << "got new sample data" << std::endl;
}

//Macro that makes this plugin loadable in ruby, this is optional.
VizkitQtPlugin(Pose3dEditorVizkit)

