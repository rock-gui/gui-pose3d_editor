#ifndef SCENE_H
#define SCENE_H

#include "sceneitem.h"
#include "manipulatable.h"

#include <osg/Geometry>
#include <osg/CoordinateSystemNode>
#include <vector>


namespace modifiable_scene{
class Scene : public osg::Group
{
public:
    Scene();

    std::vector<std::pair<std::string, osg::Matrix> > get_transforms();
    osg::Matrix get_transform(std::string name);
    void add_movable(std::string name, osg::ref_ptr<osg::Node> scene, Manipulatable::Config config=Manipulatable::Config());
    void add_movable_from_mesh_file(std::string name, std::string filepath, double scale=1.f, Manipulatable::Config config=Manipulatable::Config());

    inline SceneItem& target(){return _target;}
    osg::ref_ptr<Manipulatable> manipulatable(std::string name);

    osg::ref_ptr<osg::Group> empty_scene();
    osg::ref_ptr<osg::Group> default_root_scene();
    void set_root_scene(osg::ref_ptr<osg::Group> root_scene);


protected:
    SceneItem _target;
    std::vector<std::pair<std::string, osg::ref_ptr<Manipulatable> > > _manipulatables;
    osg::ref_ptr<osg::Group> _root_scene;
};
}

#endif // SCENE_H
