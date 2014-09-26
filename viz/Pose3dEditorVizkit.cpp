#include <iostream>
#include "Pose3dEditorVizkit.hpp"

using namespace vizkit3d;

struct Pose3dEditorVizkit::Data {
    // Copy of the value given to updateDataIntern.
    //
    // Making a copy is required because of how OSG works
    base::samples::RigidBodyState data;
};


Pose3dEditorVizkit::Pose3dEditorVizkit()
    : p(new Data), _modelFile(""), _frameName(""), _modelScale(1.0)
{
    _scene = new modifiable_scene::Scene();
}

Pose3dEditorVizkit::~Pose3dEditorVizkit()
{
    delete p;
    delete _scene;
}

QString Pose3dEditorVizkit::modelFile() const
{
    return _modelFile;
}

QString Pose3dEditorVizkit::frameName() const{
    return _frameName;
}

void Pose3dEditorVizkit::setModelScale(double const scale){
    if(_modelFile!="")
        std::cout << "model scale should be set _before_ the mode file" <<std::endl;
    _modelScale=scale;
}


void Pose3dEditorVizkit::setModelFile(QString file_name)
{
    if(_modelFile!=""){
        throw("a model file was already set");
    }
    _modelFile = file_name;

    addMovable(_frameName, _modelFile, _modelScale);
}

void Pose3dEditorVizkit::setFrameName(QString frame_name)
{
    if(_frameName!=""){
        throw("a frame name was already set");
    }
    _frameName = frame_name;

    addMovable(_frameName, _modelFile, _modelScale);
}


void Pose3dEditorVizkit::addMovable(QString name, QString model_file, double scale)
{
    if(_frameName!="" && _modelFile!=""){
        std::cout << "adding"<<std::endl;
        _scene->add_movable_from_mesh_file(name.toLatin1().data(), model_file.toLatin1().data(), scale);
        emit childrenChanged();
        std::cout << "added"<<std::endl;
    }
}

osg::ref_ptr<osg::Node> Pose3dEditorVizkit::createMainNode()
{
    // Geode is a common node used for vizkit3d plugins. It allows to display
    // "arbitrary" geometries
    return _scene;
}

void Pose3dEditorVizkit::updateMainNode ( osg::Node* node )
{
     _scene = static_cast< modifiable_scene::Scene*>(node);
    // Update the main node using the data in p->data
     osg::Matrix transform;
     transform.setTrans(p->data.position.x(), p->data.position.y(), p->data.position.z());
     transform.setRotate(osg::Quat(p->data.orientation.x(), p->data.orientation.y(), p->data.orientation.z(), p->data.orientation.w()));
     _scene->manipulatable(p->data.sourceFrame)->set_transform(transform);
}

void Pose3dEditorVizkit::updateDataIntern( base::samples::RigidBodyState const& value)
{
    p->data = value;
}

//Macro that makes this plugin loadable in ruby, this is optional.
VizkitQtPlugin(Pose3dEditorVizkit)

