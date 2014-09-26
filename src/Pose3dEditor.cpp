#include "Pose3dEditor.hpp"
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/TrackballManipulator>
#include <osg/DisplaySettings>
#include <osg/GraphicsContext>
#include <osg/Viewport>
#include <osgQt/GraphicsWindowQt>

Pose3dEditor::Pose3dEditor(QWidget *parent)
    : QWidget(parent)
{
    resize(300,120);

    _viewer = new osgViewer::CompositeViewer;
    _viewer->setThreadingModel(osgViewer::CompositeViewer::SingleThreaded);

    QWidget* widget1 = addViewWidget( 0,0,100,100 );

    QGridLayout* grid = new QGridLayout;
    grid->addWidget( widget1, 0, 0 );

    setLayout( grid );

    connect( &_timer, SIGNAL(timeout()), this, SLOT(update()) );
    _timer.start( 10 );

    _scene = new modifiable_scene::Scene();
    _view->setSceneData(_scene);

    show();
}


QWidget* Pose3dEditor::addViewWidget( int x, int y, int w, int h, const std::string& name, bool windowDecoration )
{
    osg::DisplaySettings* ds = osg::DisplaySettings::instance();
    osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
    traits->windowName = name;
    traits->windowDecoration = windowDecoration;
    traits->x = x;
    traits->y = y;
    traits->width = w;
    traits->height = h;
    traits->doubleBuffer = true;
    traits->alpha = ds->getMinimumNumAlphaBits();
    traits->stencil = ds->getMinimumNumStencilBits();
    traits->sampleBuffers = ds->getMultiSamples();
    traits->samples = ds->getNumMultiSamples();


    osg::ref_ptr<osg::Camera> camera = new osg::Camera;
    _gc = new osgQt::GraphicsWindowQt(traits.get());
    camera->setGraphicsContext( _gc );

    camera->setClearColor( osg::Vec4(0.2, 0.2, 0.6, 1.0) );

    camera->setViewport( 0, 0, traits->width, traits->height);
    camera->setProjectionMatrixAsPerspective(
                30.0f, static_cast<double>(traits->width)/static_cast<double>(traits->height), 1.0f, 10000.0f );


    _view = new osgViewer::View;
    _view->setCamera( camera );
    _viewer->addView( _view.get() );

    _view->addEventHandler( new osgViewer::StatsHandler );
    _view->setCameraManipulator( new osgGA::TrackballManipulator );


    return _gc->getGraphWidget();
}

Pose3dEditor::~Pose3dEditor()
{
}
