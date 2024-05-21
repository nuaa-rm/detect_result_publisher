#include "../include/detect_result_publisher.h"

DetectResultPublisher::DetectResultPublisher()
    : Node("DetectResultPublisher")
{
    publisher_ = this->create_publisher<DetectResult>("DetectResult",10);
    publisher_2 = this->create_publisher<geometry_msgs::msg::PoseStamped>("test",1);
    timer_  =  this->create_wall_timer(
        5ms, std::bind(&DetectResultPublisher::timer_callback, this));
}

void DetectResultPublisher::timer_callback()
{
    message.detect_success = true;
    message.id = 1;
    message.is_big = true;
    message.pose.header.frame_id="detect";
    message.pose.header.stamp = this->get_clock()->now();

    loca_make(message.pose,v);

    publisher_->publish(message);
    publisher_2 ->publish(message.pose);
}

void DetectResultPublisher::loca_make(geometry_msgs::msg::PoseStamped &pose,double *v)
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::normal_distribution<double> dist(0,0.5);

    double a[3]={dist(generator),dist(generator),dist(generator)};
    
    v[0]+=a[0]*0.03;
    v[1]+=a[1]*0.03;
    v[2]+=a[2]*0.03;

    pose.pose.position.x+=v[0]*0.03;
    pose.pose.position.y+=v[1]*0.03;
    pose.pose.position.z+=v[2]*0.03;

    if(pose.pose.position.x<-10||pose.pose.position.x>10) v[0]*=-1;
    if(pose.pose.position.y<-10||pose.pose.position.y>10) v[1]*=-1;
    if(pose.pose.position.z<0||pose.pose.position.z>10) v[2]*=-1;

}


