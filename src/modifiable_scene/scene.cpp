#include "scene.h"
#include <osg/ShapeDrawable>
#include <osg/PositionAttitudeTransform>
#include <iostream>


namespace modifiable_scene{
Scene::Scene()
{
    set_root_scene(default_root_scene());
}

osg::ref_ptr<osg::Group> Scene::empty_scene()
{
    return osg::ref_ptr<osg::Group>(new osg::Group);
}

osg::ref_ptr<osg::Group> Scene::default_root_scene()
{
    osg::ref_ptr<osg::ShapeDrawable> drawable = osg::ref_ptr<osg::ShapeDrawable>(new osg::ShapeDrawable(new osg::Sphere(osg::Vec3d(0,0,0), 0.1)));
    drawable->setColor(osg::Vec4(0.5f, 1.5f, 0.7f, 0.5f));

    osg::ref_ptr<osg::Geode> geode = osg::ref_ptr<osg::Geode>(new osg::Geode());
    geode->addDrawable(drawable);

    osg::ref_ptr<osg::Group> g = empty_scene();
    g->addChild(geode);
    return g;
}

void Scene::set_root_scene(osg::ref_ptr<osg::Group> root_scene){
    this->removeChild(_root_scene);
    _root_scene.swap(root_scene);
    this->addChild(_root_scene);
}

std::vector<std::pair<std::string, osg::Matrix> > Scene::get_transforms(){
    std::vector<std::pair<std::string, osg::Matrix> > ret(_manipulatables.size());

    for(uint i=0; i< _manipulatables.size(); i++){
        ret[i].first = _manipulatables[i].first;
        ret[i].second = _manipulatables[i].second->get_transform();
    }
    return ret;
}

osg::ref_ptr<Manipulatable> Scene::manipulatable(std::string name){
    for(uint i=0; i< _manipulatables.size(); i++){
        if(_manipulatables[i].first.compare(name)==0){
            return _manipulatables[i].second;
        }
    }
    std::cerr << "Did not find '"<<name<<"'"<<std::endl;
    throw "Not found";
}

osg::Matrix Scene::get_transform(std::string name){
    return manipulatable(name)->get_transform();
}

void Scene::add_movable(std::string name, osg::ref_ptr<osg::Node> scene, Manipulatable::Config config){

    osg::ref_ptr<Manipulatable> ptr = new Manipulatable(scene, config, this);

    _manipulatables.push_back(std::make_pair(name, ptr));
    this->addChild(ptr.get());
}

void Scene::add_movable_from_mesh_file(std::string name, std::string filepath, double scale, Manipulatable::Config config)
{
    osg::ref_ptr<osg::Node> loadedModel = osgDB::readNodeFile(filepath);
    osg::PositionAttitudeTransform* transform = new osg::PositionAttitudeTransform();
    transform->setScale(osg::Vec3f(scale, scale, scale));
    transform->addChild(loadedModel);
    add_movable(name, transform, config);
}

}
