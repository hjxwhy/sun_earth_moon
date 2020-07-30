//
// Created by hjx on 7/29/20.
//

#include "../include/TrinaryStarSystemBroadcaster.h"
#define PI 3.1415926
tf::Transform TrinaryStarSystemBroadcaster::CreatTransform(tf::Vector3 vector3,float roll,float pitch,float yaw) {
    tf::Transform transform;
    transform.setOrigin(vector3);
    tf::Quaternion q;
    q.setRPY(roll,pitch,yaw);
    transform.setRotation(q);
    return transform;
}

void TrinaryStarSystemBroadcaster::CalculateCoordinate() {
    theta_=theta_+2*PI/80;
    if(theta_ == 2*PI) {theta_=0;}
    angle_ = 2*PI*redraw_round_flag_/max_discrete_round_;
    x_axis_ = r1_*cos(angle_);
    y_axis_ = r1_*sin(angle_);
}

void TrinaryStarSystemBroadcaster::UpdateTransform(tf::Transform& transform,float x,float y,float theta){
    transform.setOrigin(tf::Vector3(x,y,0));
    tf::Quaternion q;
    q.setRPY(0,0,theta);
    transform.setRotation(q);
}

int main(int argc,char** argv){
    ros::init(argc, argv, "brodcaster");

    TrinaryStarSystemBroadcaster broadcaster_object;

    tf::Transform transform1 = broadcaster_object.CreatTransform(tf::Vector3(broadcaster_object.x_axis_,broadcaster_object.y_axis_, 0.0));
    tf::Transform transform2 = broadcaster_object.CreatTransform(tf::Vector3(0,0, 0.0),-PI/6*1.0,PI/6*1.0,0.0);
    tf::Transform transform3 = broadcaster_object.CreatTransform(tf::Vector3(0,0, 0.0),0,0,broadcaster_object.theta_);
    tf::Transform transform4 = broadcaster_object.CreatTransform(tf::Vector3(1.0, 0.0, 0.0),0,0,0);

    ros::Rate sleep_rate(30);

    while(ros::ok()) {
        int flag = broadcaster_object.redraw_round_flag_++;
        if(flag == broadcaster_object.max_discrete_round_) broadcaster_object.redraw_round_flag_ = 0;
        ros::Time now = ros::Time::now();
        broadcaster_object.br.sendTransform(tf::StampedTransform(transform1, now, "sun", "e_help1"));
        broadcaster_object.br.sendTransform(tf::StampedTransform(transform2, now, "e_help1", "e_help2"));
        broadcaster_object.br.sendTransform(tf::StampedTransform(transform3, now, "e_help2", "earth"));
        broadcaster_object.br.sendTransform(tf::StampedTransform(transform4, now, "earth", "moon"));
        broadcaster_object.CalculateCoordinate();
        broadcaster_object.UpdateTransform(transform1,broadcaster_object.x_axis_,broadcaster_object.y_axis_,broadcaster_object.theta_);
        broadcaster_object.UpdateTransform(transform3,0,0,broadcaster_object.theta_);

        sleep_rate.sleep();
    }
    return 0;

}
