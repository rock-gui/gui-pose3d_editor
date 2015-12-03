#include "scene.h"
#include <osg/ShapeDrawable>
#include <osg/PositionAttitudeTransform>
#include <iostream>
#include <stdexcept>


namespace modifiable_scene{
Scene::Scene()
{
    osg::ShapeDrawable* drawable = new osg::ShapeDrawable(new osg::Box(osg::Vec3d(0,0,0), 0.1));
    drawable->setColor(osg::Vec4(0.5f, 1.5f, 0.7f, 0.5f));

    osg::Geode* g = new osg::Geode();
    g->addDrawable(drawable);
    this->addChild(g);
}

std::vector<std::pair<std::string, osg::Matrix> > Scene::get_transforms(){
    std::vector<std::pair<std::string, osg::Matrix> > ret;

    std::map<std::string, osg::ref_ptr<Manipulatable> >::iterator it;
    for(it = _manipulatables.begin(); it != _manipulatables.end(); it++)
    {
        ret.push_back(std::make_pair(it->first, it->second->get_transform()));
    }    
    return ret;
}

osg::ref_ptr<Manipulatable> Scene::manipulatable(std::string name){
    std::map<std::string, osg::ref_ptr<Manipulatable> >::iterator it = _manipulatables.find(name);
    if(it == _manipulatables.end())
        throw std::runtime_error("Error, no Manipulatable with name " + name + " registered in scene");

    return it->second;
}

osg::Matrix Scene::get_transform(std::string name){
    return manipulatable(name)->get_transform();
}

void Scene::add_movable(std::string name, osg::ref_ptr<osg::Node> scene){

    osg::ref_ptr<Manipulatable> ptr = new Manipulatable(scene);
    if(_manipulatables.count(name))
        throw std::runtime_error("Error, there is already a manipulatable with name " + name + " registered at the scene");
    _manipulatables.insert(std::make_pair(name, ptr));
    this->addChild(ptr.get());
}

void Scene::remove_movable(const std::string &name)
{
    std::map<std::string, osg::ref_ptr<Manipulatable> >::iterator it = _manipulatables.find(name);
    if(it == _manipulatables.end())
        throw std::runtime_error("Error, no Manipulatable with name " + name + " registered in scene");
    
    this->removeChild(it->second.get());
    
    _manipulatables.erase(it);
}

void Scene::add_movable_from_mesh_file(std::string name, std::string filepath, double scale)
{
    osg::ref_ptr<osg::Node> loadedModel = osgDB::readNodeFile(filepath);
    osg::PositionAttitudeTransform* transform = new osg::PositionAttitudeTransform();
    transform->setScale(osg::Vec3f(scale, scale, scale));
    transform->addChild(loadedModel);
    add_movable(name, transform);
}

}
