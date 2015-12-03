#ifndef pose3d_editor_Pose3dEditorVizkit_H
#define pose3d_editor_Pose3dEditorVizkit_H


#include <boost/noncopyable.hpp>
#include <vizkit3d/Vizkit3DPlugin.hpp>
#include <base/samples/RigidBodyState.hpp>
#include <osg/Geode>
#include <pose3d_editor/modifiable_scene/scene.h>
#include <QVector>
#include <QQuaternion>


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
    /**
     * @deprecated
     */
    Q_PROPERTY(double x READ x WRITE setX)
    /**
     * @deprecated
     */
    Q_PROPERTY(double y READ y WRITE setY)
    /**
     * @deprecated
     */
    Q_PROPERTY(double z READ z WRITE setZ)
    /**
     * @deprecated
     */
    Q_PROPERTY(double qx READ qx WRITE setQx)
    /**
     * @deprecated
     */
    Q_PROPERTY(double qy READ qy WRITE setQy)
    /**
     * @deprecated
     */
    Q_PROPERTY(double qz READ qz WRITE setQz)
    /**
     * @deprecated
     */
    Q_PROPERTY(double qw READ qw WRITE setQw)

public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    Pose3dEditorVizkit();
    ~Pose3dEditorVizkit();

    void setModelFile(QString const name);
    QString modelFile() const;
    void setFrameName(QString const name);
    QString frameName() const;
    void setModelScale(double const scale);
    double modelScale() const{return _modelScale;}

    /**
     * @deprecated
     */
    double x();
    /**
     * @deprecated
     */
    double y();
    /**
     * @deprecated
     */
    double z();
    /**
     * @deprecated
     */
    double qx();
    /**
     * @deprecated
     */
    double qy();
    /**
     * @deprecated
     */
    double qz();
    /**
     * @deprecated
     */
    double qw();
    /**
     * @deprecated
     */
    void setX(double const &val);
    /**
     * @deprecated
     */
    void setY(double const &val);
    /**
     * @deprecated
     */
    void setZ(double const &val);
    /**
     * @deprecated
     */
    void setQx(double const &val);
    /**
     * @deprecated
     */
    void setQy(double const &val);
    /**
     * @deprecated
     */
    void setQz(double const &val);
    /**
     * @deprecated
     */
    void setQw(double const &val);

public slots:
    void syncPose();


    QVector3D position(std::string name="") const;
    void setPosition(QVector3D const &vect, std::string name="");
    QQuaternion orientation(std::string name="") const;
    void setOrientation(QQuaternion const &quat, std::string name="");
    base::samples::RigidBodyState rbs(std::string name="") const;
    void setRbs(base::samples::RigidBodyState const &rbs, std::string name="");



    Q_INVOKABLE void addMovable(QString const name, QString const model_file, double scale=1.0f);
    Q_INVOKABLE void removeMovable(QString name);

    Q_INVOKABLE void updateData( base::samples::RigidBodyState const &sample)
    {vizkit3d::Vizkit3DPlugin<base::samples::RigidBodyState>::updateData(sample);}


    modifiable_scene::Scene* scene(){return _scene;}

protected:
    virtual osg::ref_ptr<osg::Node> createMainNode();
    virtual void updateMainNode(osg::Node* node);
    virtual void updateDataIntern( base::samples::RigidBodyState const& plan);

    inline QVector3D to_qt(osg::Vec3d const vect) const {
        return QVector3D(vect.x(), vect.y(), vect.z());
    }
    inline QQuaternion to_qt(osg::Quat const quat) const {
        return QQuaternion(quat.w(), quat.x(), quat.y(), quat.z());
    }

    inline Eigen::Vector3d to_eigen(osg::Vec3d const vect) const {
        return Eigen::Vector3d(vect.x(), vect.y(), vect.z());
    }
    inline Eigen::Quaterniond to_eigen(osg::Quat const quat) const {
        return Eigen::Quaterniond(quat.w(), quat.x(), quat.y(), quat.z());
    }

    inline Eigen::Vector3d to_eigen(QVector3D const vect) const {
        return Eigen::Vector3d(vect.x(), vect.y(), vect.z());
    }
    inline Eigen::Quaterniond to_eigen(QQuaternion const quat) const {
        return Eigen::Quaterniond(quat.scalar(), quat.x(), quat.y(), quat.z());
    }

    //If no name is given automatically first transform is returned. This is for backwards compatibility and deprecated
    osg::Matrix get_transform(const std::string& name) const;
    //If no name is given automatically first transform is set. This is for backwards compatibility and deprecated
    void set_transform(const osg::Matrix& transform, const std::string &name) const;

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
