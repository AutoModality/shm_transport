SHELL := /bin/bash

default:
	source /opt/ros/kinetic/setup.bash && cd catkin_ws && catkin clean -f -i -y && catkin build -j3
	@echo "Built!!!!"

install:
	rm -rf catkin_ws/install/share/catkin_tools_prebuild
	install -d $(DESTDIR)/opt/ros/kinetic/
	cp -f -p -r catkin_ws/install/lib $(DESTDIR)/opt/ros/kinetic
	cp -f -p -r catkin_ws/install/share $(DESTDIR)/opt/ros/kinetic
#	cp -f -p -r catkin_ws/install/include $(DESTDIR)/opt/ros/kinetic


clean:
	@echo "Cleaning"
	rm -rf catkin_ws
