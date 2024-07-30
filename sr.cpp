#include <ros/ros.h>
#include <darknet_ros_msgs/BoundingBoxes.h>
#include <gnc_functions.hpp>

int mode_g = 0;
ros::Time last_detection_time;
bool person_detected = false;

void detection_cb(const darknet_ros_msgs::BoundingBoxes::ConstPtr& msg) {
    for (int i = 0; i < msg->bounding_boxes.size(); i++) {
        ROS_INFO("%s detected", msg->bounding_boxes[i].Class.c_str());
        if (msg->bounding_boxes[i].Class == "person") {
            last_detection_time = ros::Time::now();
            person_detected = true;
            return; // Exit after the first person detection
        }
    }
    person_detected = false;
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "detection_sub");
    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe("/darknet_ros/bounding_boxes", 1, detection_cb);

    init_publisher_subscriber(n);

    // wait for FCU connection
    wait4connect();

    // wait for user to switch to mode GUIDED
    wait4start();

    // create local reference frame
    initialize_local_frame();

    takeoff(10);

    // specify some waypoints
    std::vector<gnc_api_waypoint> waypointList;
    gnc_api_waypoint nextWayPoint;
    float side_length = 30; // Starting side length for the larger area
    float min_side_length = 8; // Minimum side length to stop creating new squares

    while (side_length >= min_side_length) {

        // Move to the next point and set the yaw angle
        nextWayPoint.x = 0;
        nextWayPoint.y = 0;
        nextWayPoint.z = 10;
        nextWayPoint.psi = 0; // Facing east
        waypointList.push_back(nextWayPoint);

        nextWayPoint.x =  side_length;
        nextWayPoint.y = 0;
        nextWayPoint.z = 10;
        nextWayPoint.psi = -90; // Facing north
        waypointList.push_back(nextWayPoint);

        nextWayPoint.x =  side_length;
        nextWayPoint.y =  side_length;
        nextWayPoint.z = 10;
        nextWayPoint.psi = 0; // Facing west
        waypointList.push_back(nextWayPoint);

        nextWayPoint.x = 0;
        nextWayPoint.y =  side_length;
        nextWayPoint.z = 10;
        nextWayPoint.psi = 90; // Facing south
        waypointList.push_back(nextWayPoint);

        nextWayPoint.x = 0;
        nextWayPoint.y = 0;
        nextWayPoint.z = 10;
        nextWayPoint.psi = 180; // Facing south
        waypointList.push_back(nextWayPoint);

        side_length -= 8;
    }

    // specify control loop rate
    ros::Rate rate(2.0);
    int counter = 0;

    while (ros::ok()) {
        ros::spinOnce();
        rate.sleep();

        if (person_detected && (ros::Time::now() - last_detection_time).toSec() > 1.0) {
            mode_g = 1; // Person detected for more than 2 seconds
        }

        if (mode_g == 0) {
            if (check_waypoint_reached(0.3) == 1) {
                if (counter < waypointList.size()) {
                    set_destination(waypointList[counter].x, waypointList[counter].y, waypointList[counter].z, waypointList[counter].psi);
                    counter++;
                } else {
                    // Land after all waypoints are reached
                    land();
                }
            }
        }

        if (mode_g == 1) {
            land();
            ROS_INFO("Rescue Operation Started");
            break;
        }
    }

    return 0;
}
