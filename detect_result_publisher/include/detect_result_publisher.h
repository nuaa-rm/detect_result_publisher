#ifndef DETECT_RESULT_PUBLISHER
#define DETECT_RESULT_PUBLISHER

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"
#include "detector_interfaces/msg/detect_result.hpp"
#include "random"
#include "robot.h"
#include "cmath"

using namespace std::chrono_literals;

/*
 *publisher_2用于rviz
 *robo是默认参数的机器人
 */
class DetectResultPublisher : public rclcpp::Node
{
public:
    DetectResultPublisher();

private:
    robot robo;
    double fps=200,posture[4];
    using DetectResult = detector_interfaces::msg::DetectResult;
    rclcpp::Publisher<DetectResult>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<geometry_msgs::msg::PoseStamped>::SharedPtr publisher_2;
    DetectResult message = DetectResult();
    geometry_msgs::msg::PoseStamped m = geometry_msgs::msg::PoseStamped();

    void timer_callback();
    void posture_make(geometry_msgs::msg::PoseStamped &pose,angle theta);
    void eulerToQuaternion(double roll, double pitch, double yaw,double* posture);

};

#endif