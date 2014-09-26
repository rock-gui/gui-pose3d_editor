#ifndef POSE3DEDITOR_HPP
#define POSE3DEDITOR_HPP

#include <QtGui>
#include <osgViewer/CompositeViewer>
#include <osgQt/GraphicsWindowQt>
#include "modifiable_scene/scene.h"
#include <osg/Camera>

class Pose3dEditor : public QWidget
{
    Q_OBJECT
public:
    Pose3dEditor(QWidget *parent = 0);
    virtual ~Pose3dEditor();
    inline osg::ref_ptr<modifiable_scene::Scene> scene(){return _scene;}

private:
    QWidget* addViewWidget( int x, int y, int w, int h, const std::string& name="", bool windowDecoration=false );

protected:
    virtual void paintEvent( QPaintEvent* event )
    { _viewer->frame(); }

protected:
    QTimer _timer;
    osg::ref_ptr<osgViewer::CompositeViewer> _viewer;
    osg::ref_ptr<osgViewer::View> _view;

    osg::ref_ptr<modifiable_scene::Scene> _scene;
    osgQt::GraphicsWindowQt* _gc;
};

#endif /* POSE3DEDITOR_HPP */
