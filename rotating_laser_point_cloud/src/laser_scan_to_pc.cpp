#include <ros/ros.h>
#include <sensor_msgs/PointCloud.h>
#include <laser_geometry/laser_geometry.h>
#include <tf/transform_listener.h>

// recibe mensajes del laser scan
void scanCallback(const sensor_msgs::LaserScan::ConstPtr& scan_in);

ros::Publisher pub;

int main(int argc, char** argv) {

    ros::init(argc, argv, "laser_scan_to_pc");
    ros::NodeHandle nh;

    // se suscribe al topic rotating_laser/laser_scan en el cual recibe
    // mensajes del tipo sensor_msgs/LaserScan
    ros::Subscriber sub = nh.subscribe(
            "rotating_laser/laser_scan", 10, scanCallback);

    // se publican mensajes del tipo sensor_msgs/PointCloud
    // en el topic rotating_laser/point_cloud
    pub = nh.advertise<sensor_msgs::PointCloud>(
            "rotating_laser/point_cloud", 50);

    // loop
    ros::spin();

}

void scanCallback(const sensor_msgs::LaserScan::ConstPtr& scan_in) {

    tf::TransformListener listener;
    laser_geometry::LaserProjection projector;

    if (!listener.waitForTransform(
                scan_in->header.frame_id,
                "/sensor_link",
                scan_in->header.stamp + ros::Duration().fromSec(
                        scan_in->ranges.size()*scan_in->time_increment),
                ros::Duration(1.0))) {
         return;
    }

    sensor_msgs::PointCloud cloud;
    projector.transformLaserScanToPointCloud(
            "/sensor_link", *scan_in, cloud, listener);

    pub.publish(cloud);
}

