#include "detect_result_publisher.h"

int main(int argc, char **argv){
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<DetectResultPublisher>());
    rclcpp::shutdown();
    return 0;

}