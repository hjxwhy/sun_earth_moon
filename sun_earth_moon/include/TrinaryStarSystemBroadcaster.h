//
// Created by hjx on 7/29/20.
//

#ifndef SRC_TRINARYSTARSYSTEMBROADCASTER_H
#define SRC_TRINARYSTARSYSTEMBROADCASTER_H
#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>
//#include <visualization_msgs/Marker.h>
//#include <std_msgs/Float64MultiArray.h>
#include <string>
#include <iostream>

class TrinaryStarSystemBroadcaster{

public:
    TrinaryStarSystemBroadcaster():r1_(3.0),y_axis_(0),theta_(0),angle_(0),redraw_round_flag_(0),max_discrete_round_(400){
        x_axis_ = r1_*1.0;
    }

    ~TrinaryStarSystemBroadcaster(){}

    tf::TransformBroadcaster br;

    tf::Transform CreatTransform(tf::Vector3 vector3,float roll=0,float pitch=0,float yaw=0);
    void CalculateCoordinate();
    void UpdateTransform(tf::Transform& transform,float x=0,float y=0,float theta=0);

    int redraw_round_flag_;
    int max_discrete_round_;
    float r1_;
    float x_axis_, y_axis_;
    float theta_;
    float angle_;
};


#endif //SRC_TRINARYSTARSYSTEMBROADCASTER_H
