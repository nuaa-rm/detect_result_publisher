#include "../include/detect_result_publisher.h"

DetectResultPublisher::DetectResultPublisher()
    : Node("DetectResultPublisher")
{
    publisher_ = this->create_publisher<DetectResult>("DetectResult",10);
    publisher_2 = this->create_publisher<geometry_msgs::msg::PoseStamped>("test",1);
    timer_  =  this->create_wall_timer(
        50ms, std::bind(&DetectResultPublisher::timer_callback, this));
}

void DetectResultPublisher::timer_callback()
{
    message.detect_success = true;
    message.id = 1;
    message.is_big = true;
    message.pose.header.frame_id="detect";
    message.pose.header.stamp = this->get_clock()->now();

    loca_make(message.pose,v);
    posture_make(message.pose,posture);

    publisher_->publish(message);
    publisher_2 ->publish(message.pose);
}

void DetectResultPublisher::loca_make(geometry_msgs::msg::PoseStamped &pose,double *v)
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::normal_distribution<double> dist(0,0.5);

    double a[3]={dist(generator),dist(generator),dist(generator)};
    
    v[0]+=a[0]*T;
    v[1]+=a[1]*T;
    v[2]+=a[2]*T;

    pose.pose.position.x+=v[0]*T;
    pose.pose.position.y+=v[1]*T;
    pose.pose.position.z+=v[2]*T;

    if(pose.pose.position.x<-10||pose.pose.position.x>10) v[0]*=-1;
    if(pose.pose.position.y<-10||pose.pose.position.y>10) v[1]*=-1;
    if(pose.pose.position.z<0||pose.pose.position.z>10) v[2]*=-1;

}
void DetectResultPublisher::posture_make(geometry_msgs::msg::PoseStamped &pose,double *posture)
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::normal_distribution<double> dist(0,50);
    double a=dist(generator);
    omiga+=a*T;
    eulerToQuaternion(omiga*T,0,0,posture);
    pose.pose.orientation.w=posture[0];
    pose.pose.orientation.x=posture[1];
    pose.pose.orientation.y=posture[2];
    pose.pose.orientation.z=posture[3];
}
void DetectResultPublisher::eulerToQuaternion(double roll, double pitch, double yaw,double *posture) {
    // 将角度转换为弧度
    roll = roll * M_PI / 180.0f;
    pitch = pitch * M_PI / 180.0f;
    yaw = yaw * M_PI / 180.0f;

    double cX = cos(yaw * 0.5f);
    double sX = sin(yaw * 0.5f);
    double cY = cos(pitch * 0.5f);
    double sY = sin(pitch * 0.5f);
    double cZ = cos(roll * 0.5f);
    double sZ = sin(roll * 0.5f);

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

