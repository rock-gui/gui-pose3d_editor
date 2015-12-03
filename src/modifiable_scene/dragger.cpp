#include "dragger.h"
#include <osg/Material>
#include <osg/BlendFunc>
#include <math.h>

namespace modifiable_scene{

TripleLineDragger::TripleLineDragger(osg::Matrixd world_coords)
{
    osg::Quat q=world_coords.getRotate();
    _line_dragger1 = new osgManipulator::Translate1DDragger(q*osg::Vec3(-0.5,0.0,0.0), q*osg::Vec3(0.5,0.0,0.0));
    _line_dragger2 = new osgManipulator::Translate1DDragger(q*osg::Vec3(0.0,-0.5,0.0), q*osg::Vec3(0.0,0.5,0.0));

    //One end is upside down
    //_line_dragger3 = new osgManipulator::Translate1DDragger(q*osg::Vec3(0.0,0.0,-0.5), q*osg::Vec3(0.0,0.0,0.5));

    //Workaround to prevent one end of the dragger to be upside down
    _line_dragger3 = new osgManipulator::Translate1DDragger(q*osg::Vec3(-0.5,0.0,0.0), q*osg::Vec3(0.5,0.0,0.0));
    _line_dragger3->setMatrix(_line_dragger3->getMatrix().rotate(M_PI_2,0,1,0));

    _line_dragger1->setColor(osg::Vec4f(1,0,0,1));
    _line_dragger1->setPickColor(osg::Vec4f(1,0,0,1));
    _line_dragger2->setColor(osg::Vec4f(0,1,0,1));
    _line_dragger2->setPickColor(osg::Vec4f(0,1,0,1));
    _line_dragger3->setColor(osg::Vec4f(0,0,1,1));
    _line_dragger3->setPickColor(osg::Vec4f(0,0,1,1));

    addChild(_line_dragger1.get());
    addDragger(_line_dragger1.get());
    addChild(_line_dragger2.get());
    addDragger(_line_dragger2.get());
    addChild(_line_dragger3.get());
    addDragger(_line_dragger3.get());

    _line_dragger1->setParentDragger(getParentDragger());
    _line_dragger2->setParentDragger(getParentDragger());
    _line_dragger3->setParentDragger(getParentDragger());
}

void TripleLineDragger::setColor(const osg::Vec4 &color)
{
    _line_dragger1->setColor(color);
    _line_dragger2->setColor(color);
    _line_dragger3->setColor(color);
}

TripleLineDragger::~TripleLineDragger(){

}


void TripleLineDragger::setupDefaultGeometry()
{
    _line_dragger1->setupDefaultGeometry();
    _line_dragger2->setupDefaultGeometry();
    _line_dragger3->setupDefaultGeometry();

}

Dragger::Dragger(osg::Matrixd world_coords)
{
    _orientation_dragger = new TrackballDragger(false);
    addChild(_orientation_dragger.get());
    addDragger(_orientation_dragger.get());

    osg::MatrixTransform* tr = new osg::MatrixTransform();
    tr->setMatrix(osg::Matrix::scale(2.1,2.1,2.1));
    _position_dragger = new TripleLineDragger(world_coords);
    tr->addChild(_position_dragger);
    addChild(tr);
    addDragger(_position_dragger.get());

    _orientation_dragger->setParentDragger(this);
    _position_dragger->setParentDragger(this);

    set_apprearence();
}

void Dragger::set_apprearence(){
    osg::StateSet* state = getOrCreateStateSet();
    //state->setMode(GL_LIGHTING, osg::StateAttribute::OFF);


    _orientation_dragger->setColor(osg::Vec4f(0,1,1,0.5));
    _position_dragger->setColor(osg::Vec4f(0,1,1,.5));


    setStateSet(state);
}

Dragger::~Dragger(){

}

void Dragger::setupDefaultGeometry()
{
    _orientation_dragger->setupDefaultGeometry();
    _position_dragger->setupDefaultGeometry();
}

}
