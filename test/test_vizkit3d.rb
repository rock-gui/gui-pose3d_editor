require 'pry'
require 'vizkit'

view3d = Vizkit.vizkit3d_widget
view3d.show
vis = Vizkit.default_loader.Pose3dEditorVizkit
#binding.pry
vis.frameName="my_movable"
vis.modelScale=0.001
vis.modelFile="test_data/AILA_Head.STL"

Vizkit.exec
