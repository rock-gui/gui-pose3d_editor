#include "sceneitem.h"

namespace modifiable_scene{
SceneItem::SceneItem()
{
}

void SceneItem::attach_mesh(std::string filepath){
    osg::ref_ptr<osg::Node> loadedModel = osgDB::readNodeFile(filepath);
    attach_scene(loadedModel);
}

void SceneItem::attach_scene(osg::ref_ptr<osg::Node> scene){
    _root->addChild(scene);
}

void SceneItem::attach_urdf(std::string filepath, std::string root){
    throw("Not implemented");
}
}
