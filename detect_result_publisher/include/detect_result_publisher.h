#ifndef DETECT_RESULT_PUBLISHER
#define DETECT_RESULT_PUBLISHER

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"
#include "detector_interfaces/msg/detect_result.hpp"
#include "random"

using namespace std::chrono_literals;

class DetectResultPublisher : public rclcpp::Node
{
public:
    DetectResultPublisher();


private:
    using DetectResult = detector_interfaces::msg::DetectResult;
    rclcpp::Publisher<DetectResult>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<geometry_msgs::msg::PoseStamped>::SharedPtr publisher_2;
    DetectResult message = DetectResult();
    geometry_msgs::msg::PoseStamped m = geometry_msgs::msg::PoseStamped();
    double v[3]={0};

    void timer_callback();
    void loca_make(geometry_msgs::msg::PoseStamped &pose,double *v);

};


#endif