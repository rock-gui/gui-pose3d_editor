#ifndef DRAGGER_H
#define DRAGGER_H

#include <osgManipulator/Dragger>
#include <osgManipulator/TrackballDragger>
#include <osgManipulator/Translate2DDragger>

namespace modifiable_scene{

class DualPlaneDragger: public osgManipulator::CompositeDragger
{
    public:
        osg::ref_ptr<osgManipulator::Translate2DDragger> _plane_dragger1;
        osg::ref_ptr<osgManipulator::Translate2DDragger> _plane_dragger2;

        DualPlaneDragger(osg::Matrixd world_coords);
        ~DualPlaneDragger();

        void setupDefaultGeometry();
        void setColor(const osg::Vec4& color);
};

class TrackballDragger : public osgManipulator::TrackballDragger{
public:
    inline TrackballDragger(bool useAutoTransform=false):osgManipulator::TrackballDragger(useAutoTransform){}
    inline void setColor(const osg::Vec4& color){_xDragger->setColor(color); _yDragger->setColor(color); _zDragger->setColor(color); _xyzDragger->setColor(color);}
};


class Dragger : public osgManipulator::CompositeDragger
{
public:
    osg::ref_ptr<TrackballDragger> _orientation_dragger;
    osg::ref_ptr<DualPlaneDragger> _position_dragger;
    Dragger(osg::Matrixd world_coords);

    ~Dragger();

    void setupDefaultGeometry();
    void set_apprearence();
};
}

#endif // DRAGGER_H
