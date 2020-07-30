#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>
#include <visualization_msgs/Marker.h>
#define PI 3.1415926

float r1 = 3, r2 =1;
float xe = r1*1.0, ye = 0.0;
float xm = r2*1.0, ym = 0.0;
int num = 400;
int numm = 400;
int i = 0;
int j = 0;
float angle1 = 0, angle2 = 0;
float cita = 0;
float l = 0, cc1 = 0, cc2 = 0;


void calculate()
{
     angle1 = 2*PI*i/num;
     xe = r1*cos(angle1);
     ye = r1*sin(angle1);

     angle2 = 2*PI*i/numm;
     xm = r2*cos(angle2);
     ym = r2*sin(angle2);
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "sem_tf_broadcaster");
    ros::NodeHandle node;
   
    ros::Publisher vis_pub1 = node.advertise<visualization_msgs::Marker>( "visualization_marker",10);
    ros::Publisher vis_pub2 = node.advertise<visualization_msgs::Marker>( "visualization_marker",10);
    ros::Publisher vis_pub3 = node.advertise<visualization_msgs::Marker>( "visualization_marker",10);
    ros::Publisher vis_pub4 = node.advertise<visualization_msgs::Marker>( "visualization_marker",10);
    ros::Publisher vis_pub5 = node.advertise<visualization_msgs::Marker>( "visualization_marker",10);
    visualization_msgs::Marker marker1,marker2,marker3,line1,line2;

    tf::TransformBroadcaster br1,br2;
    tf::Transform transform1,transform2;

    tf::TransformListener listener;
    tf::StampedTransform m_transform;
 
    ros::Rate rate(25.0); //循环的频率为50Hz
    while(node.ok())
    {
         calculate();
         i++;
         if(i == num) {i=0;}
         if(i==50 || i==100 || i==150 || i==200 || i==250 || i==300 || i==350 || i==399) {line1.points.clear();}
         //if(cita==10*PI/40 || cita==20*PI/40 || cita==30*PI/40 || cita==39*PI/40) {line2.points.clear();}
         transform1.setOrigin( tf::Vector3(xe, ye, 0.0) );
         //transform1.setRotation( tf::Quaternion(0, 0, 0 , 1) );
         tf::Quaternion q1;
         //q1.setRPY(0,0,cita);
         //q1.setRPY(-PI/6,PI/6,0);
         q1.setEuler(-PI/6*1.0,PI/6*1.0,cita);
         transform1.setRotation(q1);
         br1.sendTransform( tf::StampedTransform(transform1, ros::Time::now(), "sun", "earth") );
  


         //l = sqrt(xm*xm+ym*ym);
         //cc1 = acos(xm/l);
         //cc2 = cc1-cita;
         //xm = l*cos(cc2);
         //ym = l*sin(cc2);   
         //if(cita >= PI) ym=-ym;
       
         transform2.setOrigin( tf::Vector3(1.0, 0.0, 0.0) );
         //transform2.setRotation( tf::Quaternion(0, 0, 0 , 1) );
         tf::Quaternion q2;
         q2.setRPY(0.0,0.0,0.0);
         transform2.setRotation(q2);
         br2.sendTransform( tf::StampedTransform(transform2, ros::Time::now(), "earth", "moon") );
         
         
         /*注意！：用marker时，所有的xyz位姿均以frame_id为坐标轴
         */

         //mark太阳
         marker1.header.frame_id = "sun";
         marker1.header.stamp = ros::Time::now();

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
         marker1.color.b = 0.0;
         
         //mark地球
         marker2.header.frame_id = "earth";
         marker2.header.stamp = ros::Time::now();

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
         marker2.color.b = 1.0;

         //mark月球
         marker3.header.frame_id = "moon";
         marker3.header.stamp = ros::Time::now();

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
         marker3.color.b = 0.0;

         //mark地球线
         line1.header.frame_id = "sun";
         line1.header.stamp = ros::Time();

         line1.ns = "sem";
         line1.id = 3;

         line1.type = visualization_msgs::Marker::LINE_STRIP;
             
         line1.action = visualization_msgs::Marker::ADD;  
          
         line1.scale.x = 0.1;

         line1.color.a = 0.5;
         line1.color.r = 0.0;
         line1.color.g = 0.0;
         line1.color.b = 1.0;
         //line1.lifetime = ros::Duration(0.5);   

         geometry_msgs::Point p;
         p.x = xe;
         p.y = ye;
         p.z = 0;
            
         line1.points.push_back(p);


         //mark月球线 错误！ 因为之前存的点在动态坐标系中的坐标会发生改变 如果一直是给(1,0,0)则只能marker一个点即1 0 0
         /*line2.header.frame_id = "earth";
         line2.header.stamp = ros::Time::now();

         line2.ns = "sem";
         line2.id = 4;

         line2.type = visualization_msgs::Marker::LINE_STRIP;
             
         line2.action = visualization_msgs::Marker::ADD;  
          
         line2.scale.x = 0.1;

         line2.color.a = 0.5;
         line2.color.r = 1.0;
         line2.color.g = 1.0;
         line2.color.b = 0.0; 
         //line2.lifetime = ros::Duration(0.5);  

         geometry_msgs::Point pp;
         //pp.x = -r2*cos(cita)*1.0;
         //pp.y = -r2*sin(cita)*1.0;
         pp.x = 1.0;
         pp.y = 0.0;
         pp.z = 0;
            
         line2.points.push_back(pp);*/


         //mark月球线 正确！
         try
         {
              listener.waitForTransform("sun","moon",ros::Time(0),ros::Duration(3.0));
              listener.lookupTransform("sun","moon",ros::Time(0),m_transform);
         }
         catch (tf::TransformException &ex)
         {
              ROS_ERROR("%s",ex.what());
              ros::Duration(1.0).sleep();
              continue;
         }

         
         line2.header.frame_id = "sun";
         line2.header.stamp = ros::Time::now();

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
         pp.x = m_transform.getOrigin().x();
         pp.y = m_transform.getOrigin().y();
         pp.z = m_transform.getOrigin().z();

         line2.points.push_back(pp);
                  

         cita=cita+2*PI/80;
         if(cita == 2*PI) {cita=0;}

         vis_pub1.publish(marker1);
         vis_pub2.publish(marker2);
         vis_pub3.publish(marker3);
         vis_pub4.publish(line1);
         vis_pub5.publish(line2);


         
         rate.sleep();
    }
    
    return 0;
}
