# shm_transport
An attempt to communicate with shared memory for ROS 1.



| Github Action  | Debian Package |
| ------------- | ------------- |
| [![Story Development](https://github.com/AutoModality/shm_transport/workflows/Story%20Development/badge.svg)](https://github.com/AutoModality/shm_transport/actions?query=workflow%3A%22Story+Development%22) | --  |
| [![Release Candidate](https://github.com/AutoModality/shm_transport/workflows/Release%20Candidate/badge.svg)](https://github.com/AutoModality/shm_transport/actions?query=workflow%3A%22Release+Candidate%22)  | [![Latest Version @ Cloudsmith](https://api-prd.cloudsmith.io/badges/version/automodality/dev/deb/ros-kinetic-shm_transport/latest/d=ubuntu%252Fxenial;t=1/?render=true&badge_token=gAAAAABeEXmnoIyJ49KZBuqu7owI69o58O-pEmDK1uXKcvR-65M3zvVldA6lRgnSlbOXlwUdmAwIYqjEaAIZ_K0DXuO7agbeqnAtp1uXvuwoxD6KMqz3wYQ%3D)](https://cloudsmith.io/~automodality/repos/dev/packages/detail/deb/ros-kinetic-shm-transport/latest/d=ubuntu%252Fxenial;t=1/)  |
| [![Release](https://github.com/AutoModality/shm_transport/workflows/Release/badge.svg)](https://github.com/AutoModality/shm_transport/actions?query=workflow%3A%22Release)  | [![Latest Version @ Cloudsmith](https://api-prd.cloudsmith.io/badges/version/automodality/release/deb/ros-kinetic-shm-transport/latest/d=ubuntu%252Fxenial;t=1/?render=true&badge_token=gAAAAABeEYCXaXnvhWBdS0An17OCBntPch8LyCzJnPoQYMA4Ng8uIJnw2hvwdvv_NBqAOTu76_FBfvns72pfHrzV2xWoBFEvGA-hns2hV-4yu2BmqWtHCT0%3D)](https://cloudsmith.io/~automodality/repos/release/packages/detail/deb/ros-kinetic-shm-transport/latest/d=ubuntu%252Fxenial;t=1/)|



ROS 1 use socket as a communication method. If the publisher and
subscriber belong to different processes of a same machine, the socket
will go through loopback with AF_INET family (either UDP or TCP protocol).

The main purpose of this project is to use shared memory IPC instead
of loopback socket to establish publisher/subscriber communication.
And we employ boost::interprocess::managed_shared_memory to accomplish
it.

But shared memory is lack of synchronization method like poll/epoll
for socket. Even inotify does not support generating a notification
when the shared memory region is written or updated. Therefore, we
use the original transport (udp or tcp) to send the handle (essentially,
an offset pointer) from publishers to subscribers.

The hardest part is life-time management of the messages. We need to
deallocate messages when no subscribers use them (as soon as possible).
We are still improving this issue.

