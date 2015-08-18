#include <iostream>
#include "Pose3dEditorVizkit.hpp"
#include <osg/io_utils>

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
    p->data.position=Eigen::Vector3d(0,0,0);
    p->data.orientation=Eigen::Quaterniond(1,0,0,0);
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

QVector3D Pose3dEditorVizkit::position() const {
    if(_scene->get_transforms().size()){
        QVector3D ret = to_qt(_scene->get_transforms()[0].second.getTrans());
        return ret;
    }
    else
        return QVector3D();
}

base::samples::RigidBodyState Pose3dEditorVizkit::rbs() const {
    base::samples::RigidBodyState ret;

    if(_scene->get_transforms().size()){
        QVector3D p=position();
        QQuaternion q = orientation();
        ret.position.x() = p.x();
        ret.position.y() = p.y();
        ret.position.z() = p.z();

        ret.orientation.x() = q.x();
        ret.orientation.y() = q.y();
        ret.orientation.z() = q.z();
        ret.orientation.w() = q.scalar();
        ret.sourceFrame = frameName().toStdString();

        return ret;
    }
    else
        return ret;
}

void Pose3dEditorVizkit::setRbs(const base::samples::RigidBodyState &rbs){
    p->data = rbs;
    updateData(p->data);
}

void Pose3dEditorVizkit::setPosition(QVector3D const &vect){
    p->data.position = to_eigen(vect);
    updateData(p->data);
}

QQuaternion Pose3dEditorVizkit::orientation() const {
    if(_scene->get_transforms().size())
        return to_qt(_scene->get_transforms()[0].second.getRotate());
    else
        return QQuaternion();
}

void Pose3dEditorVizkit::setOrientation(QQuaternion const &quat){
    p->data.orientation = to_eigen(quat);
    updateData(p->data);
}

double Pose3dEditorVizkit::x(){
    if(_scene->get_transforms().size()){
        return _scene->get_transforms()[0].second.getTrans().x();
    }
    else
        return 0;
}
double Pose3dEditorVizkit::y(){
    if(_scene->get_transforms().size())
        return _scene->get_transforms()[0].second.getTrans().y();
    else
        return 0;
}
double Pose3dEditorVizkit::z(){
    if(_scene->get_transforms().size())
        return _scene->get_transforms()[0].second.getTrans().z();
    else
        return 0;
}
double Pose3dEditorVizkit::qx(){
    if(_scene->get_transforms().size())
        return _scene->get_transforms()[0].second.getRotate().x();
    else
        return 0;
}
double Pose3dEditorVizkit::qy(){
    if(_scene->get_transforms().size())
        return _scene->get_transforms()[0].second.getRotate().y();
    else
        return 0;
}
double Pose3dEditorVizkit::qz(){
    if(_scene->get_transforms().size())
        return _scene->get_transforms()[0].second.getRotate().z();
    else
        return 0;
}
double Pose3dEditorVizkit::qw(){
    if(_scene->get_transforms().size())
        return _scene->get_transforms()[0].second.getRotate().w();
    else
        return 0;
}
void Pose3dEditorVizkit::syncPose(){
    if(_scene->get_transforms().size()){
        p->data.position = to_eigen(_scene->get_transforms()[0].second.getTrans());
        p->data.orientation = to_eigen(_scene->get_transforms()[0].second.getRotate());
    }
}

void Pose3dEditorVizkit::setX(double const &val){
    p->data.position.x() = val;
    updateData(p->data);
}
void Pose3dEditorVizkit::setY(double const &val){
     p->data.position.y() = val;
    updateData(p->data);
}
void Pose3dEditorVizkit::setZ(double const &val){
     p->data.position.z() = val;
    updateData(p->data);
}
void Pose3dEditorVizkit::setQx(double const &val){
     p->data.orientation.x() = val;
    updateData(p->data);
}
void Pose3dEditorVizkit::setQy(double const &val){
    p->data.orientation.y() = val;
    updateData(p->data);
}
void Pose3dEditorVizkit::setQz(double const &val){
    p->data.orientation.z() = val;
    updateData(p->data);
}
void Pose3dEditorVizkit::setQw(double const &val){
    p->data.orientation.w() = val;
    updateData(p->data);
}


void Pose3dEditorVizkit::setModelFile(QString file_name)
{
    if(_modelFile!=""){
        std::cerr << "a model file was already set"<<std::endl;
        throw("a model file was already set");
    }
    _modelFile = file_name;

    addMovable(_frameName, _modelFile, _modelScale);
}

void Pose3dEditorVizkit::setFrameName(QString frame_name)
{
    if(_frameName!=""){
        std::cerr << "a frame name was already set"<<std::endl;
        throw("a frame name was already set");
    }
    _frameName = frame_name;
    p->data.sourceFrame = _frameName.toStdString();

    addMovable(_frameName, _modelFile, _modelScale);
}


void Pose3dEditorVizkit::addMovable(QString name, QString model_file, double scale)
{
    if(_frameName!="" && _modelFile!=""){
        std::cout << "adding " << name.toStdString() <<std::endl;
        _scene->add_movable_from_mesh_file(name.toStdString(), model_file.toStdString(), scale);
        emit childrenChanged();
        std::cout << "added"<<std::endl;
    }
}

void Pose3dEditorVizkit::removeMovable(QString name) 
{
    _scene->remove_movable(name.toStdString());
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
     osg::ref_ptr<modifiable_scene::Manipulatable> manipulatable = _scene->manipulatable(_frameName.toStdString());
     if(!manipulatable){
         std::stringstream ss;
         ss << "No manipulatable with name '" << p->data.sourceFrame << "' was found.";
         throw(std::runtime_error(ss.str()));
     }
     manipulatable->set_transform(transform);
     std::cout << "Update: " << p->data.position.x()<<std::endl;
}

void Pose3dEditorVizkit::updateDataIntern( base::samples::RigidBodyState const& value)
{
    p->data = value;
    std::cout << "Update intern: " << p->data.position.x()<<","<<value.position.x()<<std::endl;
    emit childrenChanged();
}

//Macro that makes this plugin loadable in ruby, this is optional.
VizkitQtPlugin(Pose3dEditorVizkit)

