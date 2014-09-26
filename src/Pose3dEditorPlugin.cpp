#include "Pose3dEditorPlugin.hpp"
#include "Pose3dEditor.hpp"

Q_EXPORT_PLUGIN2(Pose3dEditor, Pose3dEditorPlugin)

Pose3dEditorPlugin::Pose3dEditorPlugin(QObject *parent)
    : QObject(parent)
{
    initialized = false;
}

Pose3dEditorPlugin::~Pose3dEditorPlugin()
{
}

bool Pose3dEditorPlugin::isContainer() const
{
    return false;
}

bool Pose3dEditorPlugin::isInitialized() const
{
    return initialized;
}

QIcon Pose3dEditorPlugin::icon() const
{
    return QIcon("");
}

QString Pose3dEditorPlugin::domXml() const
{
        return "<ui language=\"c++\">\n"
            " <widget class=\"Pose3dEditor\" name=\"pose3deditor\">\n"
            "  <property name=\"geometry\">\n"
            "   <rect>\n"
            "    <x>0</x>\n"
            "    <y>0</y>\n"
            "     <width>300</width>\n"
            "     <height>120</height>\n"
            "   </rect>\n"
            "  </property>\n"
//            "  <property name=\"toolTip\" >\n"
//            "   <string>Pose3dEditor</string>\n"
//            "  </property>\n"
//            "  <property name=\"whatsThis\" >\n"
//            "   <string>Pose3dEditor</string>\n"
//            "  </property>\n"
            " </widget>\n"
            "</ui>\n";
}

QString Pose3dEditorPlugin::group() const {
    return "Rock-Robotics";
}

QString Pose3dEditorPlugin::includeFile() const {
    return "Pose3dEditor/Pose3dEditor.hpp";
}

QString Pose3dEditorPlugin::name() const {
    return "Pose3dEditor";
}

QString Pose3dEditorPlugin::toolTip() const {
    return whatsThis();
}

QString Pose3dEditorPlugin::whatsThis() const
{
    return "";
}

QWidget* Pose3dEditorPlugin::createWidget(QWidget *parent)
{
    return new Pose3dEditor(parent);
}

void Pose3dEditorPlugin::initialize(QDesignerFormEditorInterface *core)
{
     if (initialized)
         return;
     initialized = true;
}
