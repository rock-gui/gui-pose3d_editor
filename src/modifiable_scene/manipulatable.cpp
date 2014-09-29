#include "manipulatable.h"
#include <osg/io_utils>

namespace modifiable_scene{
Manipulatable::Manipulatable(osg::ref_ptr<osg::Node> manipulatable_node)
{
    _dragger = new Dragger();
    _dragger->setupDefaultGeometry();

    _manipulatable_node = manipulatable_node;
    _transform = new osg::MatrixTransform();

    manipulatable_node->getOrCreateStateSet()->setMode(GL_NORMALIZE, osg::StateAttribute::ON);
    _transform->addChild(_manipulatable_node);

    this->addChild(_transform);
    this->addChild(_dragger);

    set_transform(osg::Matrix::identity());

    _dragger->setHandleEvents(true);
    _dragger->setActivationModKeyMask(osgGA::GUIEventAdapter::MODKEY_CTRL);

    _dragger->addTransformUpdating(_transform);
}

void Manipulatable::set_transform(osg::Matrix transform){
    _transform->setMatrix(transform);

    float scale = _manipulatable_node->getBound().radius() * 1;
    osg::Matrix mat = osg::Matrix::scale(scale, scale, scale) * osg::Matrix::translate(_manipulatable_node->getBound().center() * transform);
    _dragger->setMatrix(mat);
}

osg::Matrix Manipulatable::get_transform(){
    return _transform->getMatrix();
}
}
