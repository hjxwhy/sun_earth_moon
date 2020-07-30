//
// Created by hjx on 7/29/20.
//

#ifndef SRC_TRINARYSTARSYSTEM_H
#define SRC_TRINARYSTARSYSTEM_H
#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>
#include <visualization_msgs/Marker.h>
#include <std_msgs/Float64MultiArray.h>
#include <string>
#include <iostream>

class TrinaryStarSystemListener {
public:
    TrinaryStarSystemListener(){
        vis_pub1_ = nh_.advertise<visualization_msgs::Marker>( "visualization_marker1",10);
        vis_pub2_ = nh_.advertise<visualization_msgs::Marker>( "visualization_marker2",10);
        vis_pub3_ = nh_.advertise<visualization_msgs::Marker>( "visualization_marker3",10);
        vis_pub4_ = nh_.advertise<visualization_msgs::Marker>( "visualization_marker4",10);
        vis_pub5_ = nh_.advertise<visualization_msgs::Marker>( "visualization_marker5",10);
        //time_pub_ = nh_.advertise<std_msgs::Float64MultiArray>("my_timer",10);
        //multi_time.data.resize(3);
    };
    ~TrinaryStarSystemListener(){};
    void mark_shape(visualization_msgs::Marker& marker, std::string frame_id, ros::Time stamp, int id, float scale, float r, float g, float b );
    void mark_line(visualization_msgs::Marker& line, std::string frame_id, ros::Time stamp, int id, float scale, float r, float g, float b,tf::StampedTransform _transform );


    ros::Publisher vis_pub1_;
    ros::Publisher vis_pub2_;
    ros::Publisher vis_pub3_;
    ros::Publisher vis_pub4_;
    ros::Publisher vis_pub5_;
    //ros::Publisher time_pub;

    visualization_msgs::Marker marker1_,marker2_,marker3_,line1_,line2_;
    //std_msgs::Float64MultiArray multi_time;

    //std_msgs::Header head;

    ros::NodeHandle nh_;

    tf::StampedTransform m_transform1_,m_transform2_;
    tf::TransformListener listener1_,listener2_;
};


#endif //SRC_TRINARYSTARSYSTEM_H
