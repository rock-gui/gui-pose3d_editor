#ifndef SCENEITEM_H
#define SCENEITEM_H

#include <string>
#include <osg/Geometry>
#include <osgDB/ReadFile>

namespace modifiable_scene{
class SceneItem
{
public:
    SceneItem();

    void attach_mesh(std::string filepath);
    void attach_scene(osg::ref_ptr<osg::Node> scene);
    void attach_urdf(std::string filepath, std::string root);

private:
    osg::ref_ptr<osg::Group> _root;
};

}

#endif // SCENEITEM_H
