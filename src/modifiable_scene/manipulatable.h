#ifndef MANIPULATABLE_H
#define MANIPULATABLE_H

#include "sceneitem.h"
#include "dragger.h"

namespace modifiable_scene{
class Manipulatable : public osg::Group
{
public:
    Manipulatable(osg::ref_ptr<osg::Node> manipulatable_node);

    void set_transform(osg::Matrix transform);
    osg::Matrix get_transform();

    osg::ref_ptr<osgManipulator::Dragger> _dragger;

    osg::ref_ptr<osg::Node> _manipulatable_node;
    osg::ref_ptr<osg::MatrixTransform> _transform;
    //osg::ref_ptr<osg::Group> _root;
};
}

#endif // MANIPULATABLE_H
