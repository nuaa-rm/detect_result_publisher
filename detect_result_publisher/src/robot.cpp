//
// Created by zhu on 24-5-27.
//
#include "robot.h"
robot::robot(double R,double omega)
{
    robot::R=R;
    robot::omega=omega;
    theta=0;
}
angle robot::get_near_theta()
{
    angle ag=theta;
    double l[4]={0};
    int index=0;
    for(int i=0;i<4;i++)
    {
        l[i]=(position[0]+R*cos(ag))*(position[0]+R*cos(ag))+(position[1]*R*sin(ag)*(position[1]*R*sin(ag)));
        ag+=90;
    }
    for(int i=1;i<4;i++)
        if(l[index]>l[i])index=i;

    return theta+90.0*index;
}
void robot::param_fresh(double* a,double dt)
{
    for(int i=0;i<3;i++){
        v[i]+=a[i]*dt;
        position[i]+=v[i]*dt;
    }
    position[2]=0;
    omega+=a[3]*dt;
    theta+=omega*dt;
    theta=std::fmod(theta,360.0);
}
void robot::get_position(geometry_msgs::msg::PoseStamped& position)
{
    position.pose.position.x=robot::position[0];
    position.pose.position.y=robot::position[1];
    position.pose.position.z=robot::position[2];
}




