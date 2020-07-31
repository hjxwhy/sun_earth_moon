# sun_earth_moon
This is an assignment in our laboratory，I think it's funny, so i publish in github and can continue to develop in the future if you are interest in it

前提是需要学习了ROS的相关知识，了解其中的一些概念关于roscore,roslaunch,rviz,tf tree.
需要使用到rviz中的一个工具：Marker

# Homework Description
地球绕着太阳转，太阳绕着地球转，地球又要有自己的自转，自转轴要是倾斜的

# Result
![avatar](D:\pictures/sun_earth_moon.png)

# 操作步骤
新建一个工作空间，把文件```clone```进去，```catkin_make```，然后```roslaunch sun_earth_moon sem_tf.launch```即可

# 存在问题
月亮的线越来越粗，说明不重合，不知道什么原因，后续的有兴趣的可以研究，然后有结果发Pull requests我会合并的
