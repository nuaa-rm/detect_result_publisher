#include "../include/detect_result_publisher.h"

DetectResultPublisher::DetectResultPublisher()
    : Node("DetectResultPublisher")
{
    publisher_ = this->create_publisher<DetectResult>("DetectResult",10);
    publisher_2 = this->create_publisher<geometry_msgs::msg::PoseStamped>("test",1);
    timer_  =  this->create_wall_timer(
        5ms, std::bind(&DetectResultPublisher::timer_callback, this));

    message.detect_success = true;
    message.id = 1;
    message.is_big = true;
    message.pose.header.frame_id="detect";
}

void DetectResultPublisher::timer_callback()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::normal_distribution<double> dist(0,0.5);
    double a[4]={dist(generator),dist(generator),dist(generator),dist(generator)};

    message.pose.header.stamp = this->get_clock()->now();

    robo.param_fresh(a,1/fps);
    posture_make(message.pose,robo.get_near_theta());
    robo.get_position(message.pose);

    publisher_->publish(message);
    publisher_2 ->publish(message.pose);
}

void DetectResultPublisher::posture_make(geometry_msgs::msg::PoseStamped &pose,angle theta)
{
    eulerToQuaternion(theta,0,0,posture);
    pose.pose.orientation.w=posture[0];
    pose.pose.orientation.x=posture[1];
    pose.pose.orientation.y=posture[2];
    pose.pose.orientation.z=posture[3];
}
void DetectResultPublisher::eulerToQuaternion(double roll, double pitch, double yaw,double *posture) {
    // 将角度转换为弧度
    roll = roll * M_PI / 180.0;
    pitch = pitch * M_PI / 180.0;
    yaw = yaw * M_PI / 180.0;

    double cX = cos(yaw * 0.5);
    double sX = sin(yaw * 0.5);
    double cY = cos(pitch * 0.5);
    double sY = sin(pitch * 0.5);
    double cZ = cos(roll * 0.5);
    double sZ = sin(roll * 0.5);

    // 构造四元数
    double w = cX * cY * cZ + sX * sY * sZ;
    double x = sX * cY * cZ - cX * sY * sZ;
    double y = cX * sY * cZ + sX * cY * sZ;
    double z = cX * cY * sZ - sX * sY * cZ;
    // 归一化四元数
    double norm = sqrt(w*w + x*x + y*y + z*z);
    w /= norm;
    x /= norm;
    y /= norm;
    z /= norm;

    posture[0]=w;
    posture[1]=x;
    posture[2]=y;
    posture[3]=z;
}

