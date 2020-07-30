//
// Created by hjx on 7/29/20.
//

#include "../include/TrinaryStarSystemListener.h"

void TrinaryStarSystemListener::mark_shape(visualization_msgs::Marker& marker, std::string frame_id, ros::Time stamp, int id, float scale, float r, float g, float b ){
    marker.header.frame_id = frame_id;
    marker.header.stamp = stamp;

    marker.ns = "sem";
    marker.id = id;

    marker.type = visualization_msgs::Marker::SPHERE;

    marker.action = visualization_msgs::Marker::ADD;

    marker.pose.position.x = 0;
    marker.pose.position.y = 0;
    marker.pose.position.z = 0;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;

    marker.scale.x = scale;
    marker.scale.y = scale;
    marker.scale.z = scale;

    marker.color.a = 0.7;
    marker.color.r = r;
    marker.color.g = g;
    marker.color.b = b;
}

void TrinaryStarSystemListener::mark_line(visualization_msgs::Marker& line, std::string frame_id, ros::Time stamp, int id, float scale, float r, float g, float b, tf::StampedTransform _transform ){
    line.header.frame_id = frame_id;
    line.header.stamp = stamp;

    line.ns = "sem";
    line.id = id;

    line.type = visualization_msgs::Marker::LINE_STRIP;

    line.action = visualization_msgs::Marker::ADD;

    line.scale.x = scale;

    line.color.a = 0.5;
    line.color.r = r;
    line.color.g = g;
    line.color.b = b;

    geometry_msgs::Point p;
    p.x = _transform.getOrigin().x();
    p.y = _transform.getOrigin().y();
    p.z = _transform.getOrigin().z();

    line.points.push_back(p);
}

int main(int argc, char** argv){

    ros::init(argc, argv, "listener");

    TrinaryStarSystemListener listener;
    ros::Rate sleep_rate(30);
    int i = 0;
    while(ros::ok()) {

        try {
            listener.listener1_.waitForTransform("sun", "earth", ros::Time(0), ros::Duration(3.0));//最多等待3.0s
            listener.listener1_.lookupTransform("sun", "earth", ros::Time(0), listener.m_transform1_);
        }
        catch (tf::TransformException &ex) {
            ROS_ERROR("%s", ex.what());
            ros::Duration(1.0).sleep();
        }

        ros::Time listen_time = listener.m_transform1_.stamp_;
        try {
            listener.listener2_.waitForTransform("sun", "moon", listen_time, ros::Duration(3.0));
            listener.listener2_.lookupTransform("sun", "moon", listen_time, listener.m_transform2_);
        }
        catch (tf::TransformException &ex) {
            ROS_ERROR("%s", ex.what());
            ros::Duration(1.0).sleep();
        }

        //mark太阳
        listener.mark_shape((visualization_msgs::Marker &) listener.marker1_, "sun", listen_time, 0, 0.75, 1.0, 0.0,
                            0.0);
        //mark地球
        listener.mark_shape((visualization_msgs::Marker &) listener.marker2_, "earth", listen_time, 1, 0.25, 0.0, 0.0,
                            1.0);
        //mark月球
        listener.mark_shape((visualization_msgs::Marker &) listener.marker3_, "moon", listen_time, 2, 0.2, 1.0, 1.0,
                            0.0);

        //mark地球线
        listener.mark_line((visualization_msgs::Marker &) listener.line1_, "sun", listen_time, 3, 0.1, 0.0, 0.0, 1.0,
                           listener.m_transform1_);
        //mark月球线
        listener.mark_line((visualization_msgs::Marker &) listener.line2_, "sun", listen_time, 4, 0.1, 1.0, 1.0, 0.0,
                           listener.m_transform2_);

        listener.vis_pub1_.publish(listener.marker1_);
        listener.vis_pub2_.publish(listener.marker2_);
        listener.vis_pub3_.publish(listener.marker3_);
        listener.vis_pub4_.publish(listener.line1_);
        listener.vis_pub5_.publish(listener.line2_);

        i++;
        if(i==50 || i==100 || i==150 || i==200 || i==250 || i==300 || i==350 || i==399) {
            listener.line1_.points.clear();
            i = 0;
        }
        //listener.time_pub.publish(listener.multi_time);
        sleep_rate.sleep();
    }
    return 0;
}

