#ifndef POSE3DEDITORPLUGIN_HPP
#define POSE3DEDITORPLUGIN_HPP

#include <QtGui>
#include <QtDesigner/QDesignerCustomWidgetInterface>

class Pose3dEditorPlugin : public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    Pose3dEditorPlugin(QObject *parent = 0);
    virtual ~Pose3dEditorPlugin();

    bool isContainer() const;
    bool isInitialized() const;
    QIcon icon() const;
    QString domXml() const;
    QString group() const;
    QString includeFile() const;
    QString name() const;
    QString toolTip() const;
    QString whatsThis() const;
    QWidget* createWidget(QWidget *parent);
    void initialize(QDesignerFormEditorInterface *core);

private:
    bool initialized; 
};

#endif /* POSE3DEDITORPLUGIN_HPP */  
