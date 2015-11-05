require 'pry'
require 'vizkit'

view3d = Vizkit.vizkit3d_widget
view3d.show
vis = Vizkit.default_loader.Pose3dEditorVizkit
#binding.pry

vis.frameName="Interaction Frame"
vis.frame = 'world_osg'
vis.modelScale=0.001

timer = Qt::Timer.new
timer.setSingleShot(true)
timer.start(4000)
timer.connect(SIGNAL('timeout()')) do
    vis.modelFile="test_data/AILA_Head.STL"
end

btn=Qt::PushButton.new("Random Move")
btn.show
btn.connect(SIGNAL("clicked()")) do

	puts "READ"
	rbs = vis.rbs()
	puts "got this:"
	puts rbs.position
	puts rbs.orientation

	rbs.position.x = rbs.position.x + 0.5-rand()
	rbs.position.y = rbs.position.y + 0.5-rand()
	rbs.position.z = rbs.position.z + 0.5-rand()

	puts "WRITE"
	vis.setRbs(rbs)
	puts "okay"
end

Vizkit.exec
