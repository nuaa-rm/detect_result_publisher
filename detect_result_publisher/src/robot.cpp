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
    angle ag;
    double m=sqrt(position[0]*position[0]+position[1]*position[1]);
    double cos_alfa=position[0]/m;
    double sin_alfa=position[1]/m;
    double cos_alfa_theta=cos_alfa*cos(theta)+sin_alfa*sin(theta);

    if(cos_alfa_theta<=1&&cos_alfa_theta>=1/sqrt(2))
    {
        ag=theta+180.0;
    }
    else if(cos_alfa_theta>=0&&cos_alfa_theta<1/sqrt(2))
    {
        ag=theta-90.0;
    }
    else if(cos_alfa_theta>=-1&&cos_alfa_theta<-1/sqrt(2))
    {
        ag=theta;
    }
    else ag=theta+90.0;
    return ag;
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




