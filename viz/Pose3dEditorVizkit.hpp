#ifndef pose3d_editor_Pose3dEditorVizkit_H
#define pose3d_editor_Pose3dEditorVizkit_H

#include <boost/noncopyable.hpp>
#include <vizkit3d/Vizkit3DPlugin.hpp>
#include <osg/Geode>
#include <>

namespace vizkit3d
{
    class Pose3dEditorVizkit
        : public vizkit3d::Vizkit3DPlugin<>
        , boost::noncopyable
    {
    Q_OBJECT
    public:
        Pose3dEditorVizkit();
        ~Pose3dEditorVizkit();

    Q_INVOKABLE void updateData( const &sample)
    {vizkit3d::Vizkit3DPlugin<>::updateData(sample);}

    protected:
        virtual osg::ref_ptr<osg::Node> createMainNode();
        virtual void updateMainNode(osg::Node* node);
        virtual void updateDataIntern( const& plan);
        
    private:
        struct Data;
        Data* p;
    };
}
#endif
