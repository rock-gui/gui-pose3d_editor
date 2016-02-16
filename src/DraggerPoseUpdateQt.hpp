#include <QtGui>
#include "modifiable_scene/scene.h"
#include <osgManipulator/Dragger>
#include <assert.h>

class DraggerPoseUpdateQt : public QObject, public osgManipulator::DraggerCallback
{
    Q_OBJECT
public:
        DraggerPoseUpdateQt(modifiable_scene::Manipulatable* manipulatable )
            : manipulatable( manipulatable )
        {
            assert(manipulatable);

            // register callbacks
            manipulatable->_dragger->addDraggerCallback( this );
        }

        ~DraggerPoseUpdateQt()
        {
            // remove callbacks
            manipulatable->_dragger->removeDraggerCallback( this );
        }


        bool receive( const osgManipulator::MotionCommand& cmd )
        {
            transformUpdated(manipulatable->get_transform());
            return true;
        }

protected:
        modifiable_scene::Manipulatable* manipulatable;

signals:
        void transformUpdated(osg::Matrix);
};
