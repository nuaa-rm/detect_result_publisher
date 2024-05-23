#ifndef DETECT_RESULT_PUBLISHER
#define DETECT_RESULT_PUBLISHER

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"
#include "detector_interfaces/msg/detect_result.hpp"
#include "random"
#include "cmath"

using namespace std::chrono_literals;

class DetectResultPublisher : public rclcpp::Node
{
public:
    DetectResultPublisher();


private:
    double v[3]={0},omiga=0;
    double posture[4]={0};
    double fps=200,T=0.3;
    using DetectResult = detector_interfaces::msg::DetectResult;
    rclcpp::Publisher<DetectResult>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<geometry_msgs::msg::PoseStamped>::SharedPtr publisher_2;
    DetectResult message = DetectResult();
    geometry_msgs::msg::PoseStamped m = geometry_msgs::msg::PoseStamped();


    void timer_callback();
    void loca_make(geometry_msgs::msg::PoseStamped &pose,double *v);
    void posture_make(geometry_msgs::msg::PoseStamped &pose,double *posture);
    void eulerToQuaternion(double roll, double pitch, double yaw,double* posture);

};


#endif