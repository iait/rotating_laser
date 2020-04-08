#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Float64.h>

void callback(const geometry_msgs::Twist::ConstPtr& vel);

ros::Publisher pubFrontLeftFork;
ros::Publisher pubFrontRightFork;

ros::Publisher pubFrontLeftWheel;
ros::Publisher pubFrontRightWheel;
ros::Publisher pubRearLeftWheel;
ros::Publisher pubRearRightWheel;

int main(int argc, char **argv) {

    // inicializa el nodo
    ros::init(argc, argv, "vehicle_control");
    ros::NodeHandle nh;

    // subscriber
    ros::Subscriber sub = nh.subscribe("cmd_vel", 10, callback);

    // publishers
    pubFrontLeftFork = nh.advertise<std_msgs::Float64>(
            "vehicle/front_left_fork_joint_position_controller/command", 10);
    pubFrontRightFork = nh.advertise<std_msgs::Float64>(
            "vehicle/front_right_fork_joint_position_controller/command", 10);
    pubFrontLeftWheel = nh.advertise<std_msgs::Float64>(
            "vehicle/front_left_wheel_joint_velocity_controller/command", 10);
    pubFrontRightWheel = nh.advertise<std_msgs::Float64>(
            "vehicle/front_right_wheel_joint_velocity_controller/command", 10);
    pubRearLeftWheel = nh.advertise<std_msgs::Float64>(
            "vehicle/rear_left_wheel_joint_velocity_controller/command", 10);
    pubRearRightWheel = nh.advertise<std_msgs::Float64>(
            "vehicle/rear_right_wheel_joint_velocity_controller/command", 10);

    // loop
    ros::spin();
}

void callback(const geometry_msgs::Twist::ConstPtr& vel) {
    double x = vel->linear.x;
    double z = vel->angular.z;
    ROS_INFO("velocidad lineal %f", x);
    ROS_INFO("velocidad angular de las ruedas %f", z);

    std_msgs::Float64 wheelVel;
    wheelVel.data = x;
    pubFrontLeftWheel.publish(wheelVel);
    pubFrontRightWheel.publish(wheelVel);
    pubRearLeftWheel.publish(wheelVel);
    pubRearRightWheel.publish(wheelVel);

    std_msgs::Float64 forkPosition;
    forkPosition.data = z;
    pubFrontLeftFork.publish(forkPosition);
    pubFrontRightFork.publish(forkPosition);
}

