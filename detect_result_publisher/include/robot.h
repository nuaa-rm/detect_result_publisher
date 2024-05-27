//
// Created by zhu on 24-5-27.
//

#ifndef ROBOT_H
#define ROBOT_H
#include "geometry_msgs/msg/pose_stamped.hpp"
#include "cmath"
typedef double angle;
/*
 *默认原点为我方机器人观测点
 *R为装甲板与中心轴的距离
 *theta设置为机器人正方向与x轴之间的夹角
 *omega设置为机器人绕中心轴旋转角速度，以逆时针为正,单位为度每秒
 */
class robot
{
public:
    robot(double R=100,double omega=3);
    angle get_near_theta();
    //返回离我方最近的装甲板角度
    void get_position(geometry_msgs::msg::PoseStamped &position);
    //返回目标机器人所在位置
    void param_fresh(double* a,double dt);
    //自动参数更新
private:
    double R,omega,theta;
    double v[3]={0},a[3]={0},position[3]={5,5,5};
};
#endif //ROBOT_H
