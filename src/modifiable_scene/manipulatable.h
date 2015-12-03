#ifndef MANIPULATABLE_H
#define MANIPULATABLE_H

#include "sceneitem.h"
#include "dragger.h"

namespace modifiable_scene{
// Visitor to return the world coordinates of a node.
// It traverses from the starting node to the parent.
// The first time it reaches a root node, it stores the world coordinates of
// the node it started from.  The world coordinates are found by concatenating all
// the matrix transforms found on the path from the start node to the root node.
class getWorldCoordOfNodeVisitor : public osg::NodeVisitor
{
public:
    getWorldCoordOfNodeVisitor():
        osg::NodeVisitor(NodeVisitor::TRAVERSE_PARENTS), done(false)
    {
    }
    virtual void apply(osg::Node &node)
    {
        if (!done)
        {
            if ( 0 == node.getNumParents() ) // no parents
            {
                wcMatrix.set( osg::computeLocalToWorld(this->getNodePath()) );
                done = true;
            }
            traverse(node);
        }
    }
    osg::Matrixd& giveUpDaMat()
    {
        return wcMatrix;
    }
private:
    bool done;
    osg::Matrixd wcMatrix;
};

// Given a valid node placed in a scene under a transform, return the
// world coordinates in an osg::Matrix.
// Creates a visitor that will update a matrix representing world coordinates
// of the node, return this matrix.
// (This could be a class member for something derived from node also.
inline osg::Matrixd& getWorldCoords( osg::Node* node)
{
    getWorldCoordOfNodeVisitor* ncv = new getWorldCoordOfNodeVisitor();
    if (node && ncv)
    {
        node->accept(*ncv);
        return ncv->giveUpDaMat();
    }
    else
    {
        throw("Could not find world coords for node");
    }
}

class Manipulatable : public osg::Group
{
public:
    struct Config{
        Config(bool auto_scale_dragger=true, float auto_scale_factor=1.5, float absolute_dragger_size=1.0):
            auto_scale_dragger(auto_scale_dragger), auto_scale_factor(auto_scale_factor), absolute_dragger_size(absolute_dragger_size)
        {}
        bool auto_scale_dragger;
        float auto_scale_factor;
        float absolute_dragger_size;
    };

    Manipulatable(osg::ref_ptr<osg::Node> manipulatable_node, const Config& cfg=Config());
    osg::Matrix get_transform();

    void set_transform(const osg::Matrix& transform);

public:
    osg::ref_ptr<osgManipulator::Dragger> _dragger;
    osg::ref_ptr<osg::Node> _manipulatable_node;
    osg::ref_ptr<osg::MatrixTransform> _transform;
    Config _config;
};
}

#endif // MANIPULATABLE_H
