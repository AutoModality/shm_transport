^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Changelog for package shm_transport
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

1.0.36 (2020-01-06)
-------------------
* Fixing package.xml to reflect original shm_transport
* fixing error with maintiner email
* Setting maintainer of package for testing out bloom version generation
* Contributors: Jimi Damon

1.0.33 (2020-01-06)
-------------------

1.0.32 (2020-01-06 11:45:35 -0800)
----------------------------------
* Fixes allow for package to be built as a ROS package feature/BB-777
* straight copy of debian and workflows from latency-testing master
* Fixes for builds
* Fixes for building packages
* Fixes for exporting packages
* Fixes that export rt shared library for other projects and prunes some unwanted code
* Removed unnecessary nose test
* :construction: fixes that fix fn signatures
* test
* Fixes for boost function
* compilation successfull for video shm_video_talker
* examples for sensor_msgs::Image
* Add wiki url into package.xml
  Add wiki url into package.xml
* remove dependence to sensor_msgs
  remove dependence to sensor_msgs
* try to make it a publishable package
* Improvements
  * do not deallocate to avoid double free problem
  * meaning of ref changed
  * do not free the message that is in use
  * remove unused counter
* Change ref for better robustness (`#7 <https://github.com/AutoModality/shm_transport/issues/7>`_)
  * debug message
  * do not deallocate to avoid double free problem
  * meaning of ref changed
  * do not free the message that is in use
  * fix
* Manage subscriber number in shm, instead of ros::getNumSubscribers(). Add timeout mechanism in case of ros messages are lost.
* Manage subscriber number in shm, instead of ros::getNumSubscribers(). Add timeout mechanism in case of ros messages are lost.
* BUGFIX TODO 1. Subscribe to the same topic in one procedure will be wrong 2. When a subscriber exit, there may be one message left in the shared memory space.
  1. Due to the implemention of normal ROS subscriber, it will be something
  wrong when subscribe to the same topic in one procedure, for the
  publisher will think there is only one subscriber listen to the topic,
  but actually there are two. Maybe we can open an issue on github ros_comm.
  2. When a subscriber exit, the publisher may not know the
  decreace of the number of subscribers, so it still publish
  more message than exactly what is. Then the extra message
  will be left in the shared memory space. If the space is not
  that big or subscribers exit many times, it will throw bad_alloc exception.
* BUGFIX
  change the condition when publisher is deleted.
* Add files via upload
* bugfix
* Update README.md
* Update README.md
* Update README.md
* Create README.md
* First commit
