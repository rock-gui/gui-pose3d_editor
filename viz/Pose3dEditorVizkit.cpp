#include <iostream>
#include "Pose3dEditorVizkit.hpp"
#include <osg/io_utils>
#include <sstream>
#include <stdexcept>

using namespace vizkit3d;

struct Pose3dEditorVizkit::Data {
    // Copy of the value given to updateDataIntern.
    //
    // Making a copy is required because of how OSG works
    base::samples::RigidBodyState data;
};

void to_osg(const base::samples::RigidBodyState& a, osg::Matrix& b){
    b.setTrans(a.position.x(), a.position.y(), a.position.z());
    b.setRotate(osg::Quat(a.orientation.x(), a.orientation.y(), a.orientation.z(), a.orientation.w()));
}

void to_osg(const base::Vector3d& a, osg::Vec3d& b){
    b.set(a.x(), a.y(), a.z());
}

void to_osg(const base::Quaterniond& a, osg::Quat& b){
    b.set(a.x(), a.y(), a.z(), a.w());
}

void to_osg(const QVector3D& a, osg::Vec3d& b){
    b.set(a.x(), a.y(), a.z());
}

void to_osg(const QQuaternion& a, osg::Quat& b){
    b.set(a.x(), a.y(), a.z(), a.scalar());
}


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

osg::Matrix Pose3dEditorVizkit::get_transform(const std::string &name) const {
    if(name == ""){
        if(!_scene->get_transforms().size())
            return osg::Matrix::identity();

        return _scene->get_transforms()[0].second;
    }
    else{
        return _scene->get_transform(name);
    }
}

void Pose3dEditorVizkit::set_transform(const osg::Matrix& transform, const std::string &name) const {
    if(name == ""){
        assert(_scene->get_transforms().size());
        return _scene->set_transform(_scene->get_transforms()[0].first, transform);
    }
    else{
        return _scene->set_transform(name, transform);
    }
}

QVector3D Pose3dEditorVizkit::position(std::string name) const {
    return to_qt(get_transform(name).getTrans());
}

base::samples::RigidBodyState Pose3dEditorVizkit::rbs(std::string name) const {
    base::samples::RigidBodyState ret;

    if(_scene->get_transforms().size()){
        QVector3D p=position(name);
        QQuaternion q = orientation(name);
        ret.position.x() = p.x();
        ret.position.y() = p.y();
        ret.position.z() = p.z();

        ret.orientation.x() = q.x();
        ret.orientation.y() = q.y();
        ret.orientation.z() = q.z();
        ret.orientation.w() = q.scalar();
        if(name == "")
            ret.sourceFrame = name;
        else
            ret.sourceFrame = frameName().toStdString();

        return ret;
    }
    else
        return ret;
}

void Pose3dEditorVizkit::setRbs(const base::samples::RigidBodyState &rbs, std::string name){
    osg::Matrix transform;
    to_osg(rbs, transform);
    set_transform(transform, name);
}

void Pose3dEditorVizkit::setPosition(QVector3D const &vect, std::string name){
    osg::Matrix transform = get_transform(name);
    osg::Vec3d pos;
    to_osg(vect, pos);
    transform.setTrans(pos);
    set_transform(transform, name);
}

QQuaternion Pose3dEditorVizkit::orientation(std::string name) const {
    return to_qt(get_transform(name).getRotate());
}

void Pose3dEditorVizkit::setOrientation(QQuaternion const &quat, std::string name){
    osg::Matrix transform = get_transform(name);
    osg::Quat orient;
    to_osg(quat, orient);
    transform.setRotate(orient);
    set_transform(transform, name);
}

double Pose3dEditorVizkit::x(){
    return position().x();
}
double Pose3dEditorVizkit::y(){
    return position().y();
}
double Pose3dEditorVizkit::z(){
    return position().z();
}
double Pose3dEditorVizkit::qx(){
    return orientation().x();
}
double Pose3dEditorVizkit::qy(){
    return orientation().y();
}
double Pose3dEditorVizkit::qz(){
    return orientation().z();
}
double Pose3dEditorVizkit::qw(){
    return orientation().scalar();
}
void Pose3dEditorVizkit::syncPose(){
    if(_scene->get_transforms().size()){
        p->data.position = to_eigen(_scene->get_transforms()[0].second.getTrans());
        p->data.orientation = to_eigen(_scene->get_transforms()[0].second.getRotate());
    }
}

void Pose3dEditorVizkit::setX(double const &val){
    QVector3D pos = position();
    pos.setX(val);
    setPosition(pos);
}
void Pose3dEditorVizkit::setY(double const &val){
    QVector3D pos = position();
    pos.setY(val);
    setPosition(pos);
}
void Pose3dEditorVizkit::setZ(double const &val){
    QVector3D pos = position();
    pos.setZ(val);
    setPosition(pos);
}
void Pose3dEditorVizkit::setQx(double const &val){
    QQuaternion orient = orientation();
    orient.setX(val);
    setOrientation(orient);
}
void Pose3dEditorVizkit::setQy(double const &val){
    QQuaternion orient = orientation();
    orient.setY(val);
    setOrientation(orient);
}
void Pose3dEditorVizkit::setQz(double const &val){
    QQuaternion orient = orientation();
    orient.setZ(val);
    setOrientation(orient);
}
void Pose3dEditorVizkit::setQw(double const &val){
    QQuaternion orient = orientation();
    orient.setScalar(val);
    setOrientation(orient);
}


void Pose3dEditorVizkit::setModelFile(QString file_name)
{
    if(_modelFile!=""){
        std::cerr << "a model file was already set"<<std::endl;
        throw("a model file was already set");
    }
    _modelFile = file_name;

    if(_scene->size()){
        _scene->clear();
    }

    addMovable("", _modelFile, _modelScale);
}

void Pose3dEditorVizkit::setFrameName(QString frame_name)
{
    if(_frameName!=""){
        std::cerr << "a frame name was already set"<<std::endl;
        throw("a frame name was already set");
    }
    _frameName = frame_name;
    p->data.sourceFrame = _frameName.toStdString();
}


void Pose3dEditorVizkit::addMovable(QString name, QString model_file, double scale)
{
    if(_frameName!="" && _modelFile!=""){
        _scene->add_movable_from_mesh_file(name.toStdString(), model_file.toStdString(), scale);
        emit childrenChanged();
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
    /*osg::Matrix transform;
    to_osg(p->data, transform);
    osg::ref_ptr<modifiable_scene::Manipulatable> manipulatable = _scene->manipulatable(_frameName.toStdString());

    manipulatable->set_transform(transform);
    std::cout << "Update: " << p->data.position.x()<<std::endl;*/
}

void Pose3dEditorVizkit::updateDataIntern( base::samples::RigidBodyState const& value)
{
    p->data = value;

    //_scene = static_cast< modifiable_scene::Scene*>(node);
    // Update the main node using the data in p->data
    osg::Matrix transform;
    to_osg(p->data, transform);
    osg::ref_ptr<modifiable_scene::Manipulatable> manipulatable = _scene->manipulatable(_frameName.toStdString());

    manipulatable->set_transform(transform);
    std::cout << "Update: " << p->data.position.x()<<std::endl;

    emit childrenChanged();
}

//Macro that makes this plugin loadable in ruby, this is optional.
VizkitQtPlugin(Pose3dEditorVizkit)

