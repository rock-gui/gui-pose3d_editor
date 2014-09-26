#ifndef pose3d_editor_Pose3dEditorVizkit_H
#define pose3d_editor_Pose3dEditorVizkit_H

#include <boost/noncopyable.hpp>
#include <vizkit3d/Vizkit3DPlugin.hpp>
#include <base/samples/RigidBodyState.hpp>
#include <osg/Geode>
#include <modifiable_scene/scene.h>

namespace vizkit3d
{
class Pose3dEditorVizkit
        : public vizkit3d::Vizkit3DPlugin<base::samples::RigidBodyState> //just a dummy data type. we don't visualize data, we create data
        , boost::noncopyable
{
    Q_OBJECT
    Q_PROPERTY(QString modelFile READ modelFile WRITE setModelFile)
    Q_PROPERTY(QString frameName READ frameName WRITE setFrameName)
    Q_PROPERTY(double modelScale READ modelScale WRITE setModelScale)

public:
    Pose3dEditorVizkit();
    ~Pose3dEditorVizkit();

    void setModelFile(QString const name);
    QString modelFile() const;
    void setFrameName(QString const name);
    QString frameName() const;
    void setModelScale(double const scale);
    double modelScale() const{return _modelScale;}

    Q_INVOKABLE void addMovable(QString const name, QString const model_file, double scale=1.0f);

    Q_INVOKABLE void updateData( base::samples::RigidBodyState const &sample)
    {vizkit3d::Vizkit3DPlugin<base::samples::RigidBodyState>::updateData(sample);}

protected:
    virtual osg::ref_ptr<osg::Node> createMainNode();
    virtual void updateMainNode(osg::Node* node);
    virtual void updateDataIntern( base::samples::RigidBodyState const& plan);

private:
    struct Data;
    Data* p;
    modifiable_scene::Scene* _scene;
    QString _modelFile;
    QString _frameName;
    float _modelScale;
};
}
#endif
