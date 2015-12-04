#include "manipulatable.h"
#include <osg/io_utils>

namespace modifiable_scene{
Manipulatable::Manipulatable(osg::ref_ptr<osg::Node> manipulatable_node, const Config& cfg)
{
    _config = cfg;
    _manipulatable_node = manipulatable_node;
    _transform = new osg::MatrixTransform();

    _dragger = new Dragger(osg::Matrix::identity());
    _dragger->setupDefaultGeometry();
    _dragger->setNodeMask(DRAGGER_MASK);

    manipulatable_node->getOrCreateStateSet()->setMode(GL_NORMALIZE, osg::StateAttribute::ON);
    _transform->addChild(_manipulatable_node);

    this->addChild(_transform);
    this->addChild(_dragger);

    _dragger->setHandleEvents(true);
    _dragger->setActivationModKeyMask(osgGA::GUIEventAdapter::MODKEY_CTRL);

    _dragger->addTransformUpdating(_transform);

    set_transform(osg::Matrix::identity());
}

void Manipulatable::set_transform(const osg::Matrix& transform){
    _transform->setMatrix(transform);

    float scale;
    if(_config.auto_scale_dragger){
        scale = _manipulatable_node->getBound().radius() * _config.auto_scale_factor;
    }
    else{
        scale = _config.absolute_dragger_size;
    }
    osg::Matrix mat = osg::Matrix::scale(scale, scale, scale) * osg::Matrix::rotate(transform.getRotate()) * osg::Matrix::translate(transform.getTrans()) ;
    _dragger->setMatrix(mat);
}

osg::Matrix Manipulatable::get_transform(){
    return _transform->getMatrix();
}
}
