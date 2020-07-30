#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>
#include <visualization_msgs/Marker.h>
#include <std_msgs/Float64MultiArray.h>
#include <string>
#include <iostream>
#define PI 3.1415926
using namespace std;

float r1 = 3.0, r2 = 1.0;
float xe = r1*1.0, ye = 0.0;
int num = 400;
int i = 0;
int j = 0;
float angle1 = 0;
float cita = 0;

void calculate()
{
     angle1 = 2*PI*i/num;
     xe = r1*cos(angle1);
     ye = r1*sin(angle1);
}

//注意形参和实参的区别 这里必须用引用 否则无法更改
void mark_shape(visualization_msgs::Marker &m, string _frame_id, ros::Time _stamp, int _id, float _scale, float _r, float _g, float _b )
{
     m.header.frame_id = _frame_id;
     m.header.stamp = _stamp;

     m.ns = "sem";
     m.id = _id;

     m.type = visualization_msgs::Marker::SPHERE;

     m.action = visualization_msgs::Marker::ADD;

     m.pose.position.x = 0;
     m.pose.position.y = 0;
     m.pose.position.z = 0;
     m.pose.orientation.x = 0.0;
     m.pose.orientation.y = 0.0;
     m.pose.orientation.z = 0.0;
     m.pose.orientation.w = 1.0;
         
     m.scale.x = _scale;
     m.scale.y = _scale;
     m.scale.z = _scale;
         
     m.color.a = 0.7;
     m.color.r = _r;
     m.color.g = _g;
     m.color.b = _b;    
}

void mark_line(visualization_msgs::Marker &l, string _frame_id, ros::Time _stamp, int _id, float _scale, float _r, float _g, float _b,tf::StampedTransform _transform )
{
     l.header.frame_id = _frame_id;
     l.header.stamp = _stamp;

     l.ns = "sem";
     l.id = _id;

     l.type = visualization_msgs::Marker::LINE_STRIP;

     l.action = visualization_msgs::Marker::ADD;

     l.scale.x = _scale;

     l.color.a = 0.5;
     l.color.r = _r;
     l.color.g = _g;
     l.color.b = _b;

     geometry_msgs::Point p;
     p.x = _transform.getOrigin().x();
     p.y = _transform.getOrigin().y();
     p.z = _transform.getOrigin().z();

     l.points.push_back(p);
}

int main(int argc, char** argv)
{
     ros::init(argc, argv, "semi");
     ros::NodeHandle node;
     ros::Time now = ros::Time::now(); //不要在节点初始化和定义节点句柄之前加东西

     //一定要多定义几个话题名 否则会打架
     //且既然已经定义了多个话题名 那么在rviz中就要add多个marker订阅者进行接收
     ros::Publisher vis_pub1 = node.advertise<visualization_msgs::Marker>( "visualization_marker1",10);
     ros::Publisher vis_pub2 = node.advertise<visualization_msgs::Marker>( "visualization_marker2",10);
     ros::Publisher vis_pub3 = node.advertise<visualization_msgs::Marker>( "visualization_marker3",10);
     ros::Publisher vis_pub4 = node.advertise<visualization_msgs::Marker>( "visualization_marker4",10);
     ros::Publisher vis_pub5 = node.advertise<visualization_msgs::Marker>( "visualization_marker5",10);
     ros::Publisher time_pub = node.advertise<std_msgs::Float64MultiArray>("my_timer",10);

     visualization_msgs::Marker marker1,marker2,marker3,line1,line2;
     std_msgs::Float64MultiArray m_t;
     m_t.data.resize(3);
     visualization_msgs::Marker &m1 = marker1;
     visualization_msgs::Marker &m2 = marker2;
     visualization_msgs::Marker &m3 = marker3;
     visualization_msgs::Marker &l1 = line1;
     visualization_msgs::Marker &l2 = line2;

     std_msgs::Header head;

     //tf::TransformBroadcaster br1,br2,br3,br4; 广播器一个就行
     tf::TransformBroadcaster br;
     tf::Transform transform1,transform2,transform3,transform4;

     tf::TransformListener listener1,listener2;
     tf::StampedTransform m_transform1,m_transform2;

     ros::Rate rate(25.0);//如果每次循环时间不到0.04s则睡眠凑到0.04s，超过0.04s也是可行的

     double tt1 = 0;
     double tt2 = 0;
     while(node.ok())
     {
          calculate();
          i++;
          if(i == num) i=0;
          if(i==50 || i==100 || i==150 || i==200 || i==250 || i==300 || i==350 || i==399) {line1.points.clear();}
          //if(cita==10*PI/40 || cita==20*PI/40 || cita==30*PI/40 || cita==39*PI/40) {line2.points.clear();}

          transform1.setOrigin( tf::Vector3(xe, ye, 0.0) );
          tf::Quaternion q1;
          q1.setRPY(0.0,0.0,0.0);
          transform1.setRotation(q1);
          

          transform2.setOrigin( tf::Vector3(0.0, 0.0, 0.0) );
          tf::Quaternion q2;
          q2.setRPY(-PI/6*1.0,PI/6*1.0,0.0);
          transform2.setRotation(q2);
          

          transform3.setOrigin( tf::Vector3(0.0, 0.0, 0.0) );
          tf::Quaternion q3;
          q3.setRPY(0.0,0.0,cita);
          transform3.setRotation(q3);
          

          transform4.setOrigin( tf::Vector3(1.0, 0.0, 0.0) );
          tf::Quaternion q4;
          q4.setRPY(0.0,0.0,0.0);
          transform4.setRotation(q4);
          

          now = ros::Time::now();

          //注：tf是同时发布出去的！！！
          br.sendTransform( tf::StampedTransform(transform1, now, "sun", "e_help1") );
          br.sendTransform( tf::StampedTransform(transform2, now, "e_help1", "e_help2") );
          br.sendTransform( tf::StampedTransform(transform3, now, "e_help2", "earth") );
          br.sendTransform( tf::StampedTransform(transform4, now, "earth", "moon") );

          //delay
          //sleep(0.01*1000);
          ros::Time t1 = ros::Time::now();
          //用ros::Time(0)而不是now，是因为tf数据刚发布出去更新得没有那么快，无法立即在now查询到tf数据。
          try
          {
               listener1.waitForTransform("sun","earth",ros::Time(0),ros::Duration(3.0));//最多等待3.0s
               listener1.lookupTransform("sun","earth",ros::Time(0),m_transform1);
          }
          catch (tf::TransformException &ex)
          {
               ROS_ERROR("%s",ex.what());
               ros::Duration(1.0).sleep();
               continue;
          }
          ros::Time t2 = ros::Time::now();
          tt1 = t1.toSec();
          tt2 = t2.toSec();
          m_t.data[0] = tt2 - tt1;
          //cout<<m_t.data<<endl;
          //tt3 = tt2 - tt1;
          //cout<<tt3<<endl;
          //head.stamp = t2-t1;
          //ROS_INFO("rosTIME %f",(float)(head.stamp));
          //ROS_INFO(t2.toSec()*1000.0-t1.toSec()*1000.0);


          ros::Time t3 = ros::Time::now();
          try
          {
               listener2.waitForTransform("sun","moon",ros::Time(0),ros::Duration(3.0));
               listener2.lookupTransform("sun","moon",ros::Time(0),m_transform2);
          }
          catch (tf::TransformException &ex)
          {
               ROS_ERROR("%s",ex.what());
               ros::Duration(1.0).sleep();
               continue;
          }
          ros::Time t4 = ros::Time::now();
          tt1 = t3.toSec();
          tt2 = t4.toSec();
          m_t.data[1] = tt2 - tt1;
          //tt1 = t3.toSec();
          //tt2 = t4.toSec();
          //tt3 = tt2 - tt1;
          //cout<<tt3<<endl;
               
          ros::Time t5 = ros::Time::now();
          //mark太阳
          mark_shape(m1, "sun", now, 0, 0.75, 1.0, 0.0, 0.0);
          /*marker1.header.frame_id = "sun";
          marker1.header.stamp = now;

          marker1.ns = "sem";
          marker1.id = 0;

          marker1.type = visualization_msgs::Marker::SPHERE;

          marker1.action = visualization_msgs::Marker::ADD;

          marker1.pose.position.x = 0;
          marker1.pose.position.y = 0;
          marker1.pose.position.z = 0;
          marker1.pose.orientation.x = 0.0;
          marker1.pose.orientation.y = 0.0;
          marker1.pose.orientation.z = 0.0;
          marker1.pose.orientation.w = 1.0;
         
          marker1.scale.x = 0.75;
          marker1.scale.y = 0.75;
          marker1.scale.z = 0.75;
         
          marker1.color.a = 0.7;
          marker1.color.r = 1.0;
          marker1.color.g = 0.0;
          marker1.color.b = 0.0;*/ 

          //mark地球
          mark_shape(m2, "earth", now, 1, 0.25, 0.0, 0.0, 1.0);
          /*marker2.header.frame_id = "earth";
          marker2.header.stamp = now;

          marker2.ns = "sem";
          marker2.id = 1;

          marker2.type = visualization_msgs::Marker::SPHERE;

          marker2.action = visualization_msgs::Marker::ADD;

          marker2.pose.position.x = 0.0;
          marker2.pose.position.y = 0.0;
          marker2.pose.position.z = 0;
          marker2.pose.orientation.x = 0.0;
          marker2.pose.orientation.y = 0.0;
          marker2.pose.orientation.z = 0.0;
          marker2.pose.orientation.w = 1.0;
         
          marker2.scale.x = 0.25;
          marker2.scale.y = 0.25;
          marker2.scale.z = 0.25;
        
          marker2.color.a = 0.7;
          marker2.color.r = 0.0;
          marker2.color.g = 0.0;
          marker2.color.b = 1.0;*/

          //mark月球
          mark_shape(m3, "moon", now, 2, 0.2, 1.0, 1.0, 0.0);
          /*marker3.header.frame_id = "moon";
          marker3.header.stamp = now;

          marker3.ns = "sem";
          marker3.id = 2;

          marker3.type = visualization_msgs::Marker::SPHERE;

          marker3.action = visualization_msgs::Marker::ADD;

          marker3.pose.position.x = 0;
          marker3.pose.position.y = 0;
          marker3.pose.position.z = 0;
          marker3.pose.orientation.x = 0.0;
          marker3.pose.orientation.y = 0.0;
          marker3.pose.orientation.z = 0.0;
          marker3.pose.orientation.w = 1.0;
         
          marker3.scale.x = 0.2;
          marker3.scale.y = 0.2;
          marker3.scale.z = 0.2;
         
          marker3.color.a = 0.7;
          marker3.color.r = 1.0;
          marker3.color.g = 1.0;
          marker3.color.b = 0.0;*/

          //mark月球法二
          /*marker3.header.frame_id = "earth";
          marker3.header.stamp = now;

          marker3.ns = "sem";
          marker3.id = 2;

          marker3.type = visualization_msgs::Marker::SPHERE;

          marker3.action = visualization_msgs::Marker::ADD;

          marker3.pose.position.x = 1.0;
          marker3.pose.position.y = 0;
          marker3.pose.position.z = 0;
          marker3.pose.orientation.x = 0.0;
          marker3.pose.orientation.y = 0.0;
          marker3.pose.orientation.z = 0.0;
          marker3.pose.orientation.w = 1.0;

          marker3.scale.x = 0.2;
          marker3.scale.y = 0.2;
          marker3.scale.z = 0.2;

          marker3.color.a = 0.7;
          marker3.color.r = 1.0;
          marker3.color.g = 1.0;
          marker3.color.b = 0.0;*/

          //mark地球线
          mark_line(l1, "sun", now, 3, 0.1, 0.0, 0.0, 1.0, m_transform1);
          /*line1.header.frame_id = "sun";
          line1.header.stamp = now;

          line1.ns = "sem";
          line1.id = 3;
 
          line1.type = visualization_msgs::Marker::LINE_STRIP;
             
          line1.action = visualization_msgs::Marker::ADD;  
          
          line1.scale.x = 0.1;
 
          line1.color.a = 0.5;
          line1.color.r = 0.0;
          line1.color.g = 0.0;
          line1.color.b = 1.0;
      
          geometry_msgs::Point p;
          p.x = m_transform1.getOrigin().x();
          p.y = m_transform1.getOrigin().y();
          p.z = m_transform1.getOrigin().z();
            
          line1.points.push_back(p);*/

          //mark月球线
          mark_line(l2, "sun", now, 4, 0.1, 1.0, 1.0, 0.0, m_transform2);
          /*line2.header.frame_id = "sun";
          line2.header.stamp = now;

          line2.ns = "sem";
          line2.id = 4;

          line2.type = visualization_msgs::Marker::LINE_STRIP;
             
          line2.action = visualization_msgs::Marker::ADD;  
          
          line2.scale.x = 0.1;

          line2.color.a = 0.5;
          line2.color.r = 1.0;
          line2.color.g = 1.0;
          line2.color.b = 0.0; 

          geometry_msgs::Point pp;
          pp.x = m_transform2.getOrigin().x();
          pp.y = m_transform2.getOrigin().y();
          pp.z = m_transform2.getOrigin().z();

          line2.points.push_back(pp);*/

          ros::Time t6 = ros::Time::now();
          tt1 = t5.toSec();
          tt2 = t6.toSec();
          m_t.data[2] = tt2 - tt1;

          cita=cita+2*PI/80;
          if(cita == 2*PI) {cita=0;}

          vis_pub1.publish(marker1);
          vis_pub2.publish(marker2);
          vis_pub3.publish(marker3);
          vis_pub4.publish(line1);
          vis_pub5.publish(line2);
          time_pub.publish(m_t);

          rate.sleep();         
     }
     return 0;
}
