#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
int main(int argc, char **argv)
{
ros::init(argc,argv,"robot0_commander"); // name of this node 
ros::NodeHandle nh; // two lines to create a publisher object that can talk to ROS
//stdr "robot0" is expecting to receive commands on topic: /robot0/cmd_vel
// commands are of type geometry_msgs/Twist, but they use only velocity in x dir and
//  yaw rate in z-dir; other 4 fields will be ignored
ros::Publisher cmd_publisher = nh.advertise<geometry_msgs::Twist>("/robot0/cmd_vel",1);
// change topic to command abby...
//ros::Publisher cmd_publisher = nh.advertise<geometry_msgs::Twist>("abby/cmd_vel",1);
ros::Rate sleep_timer(100); //let's make a 100Hz timer

//create a variable of type "Twist", as defined in: /opt/ros/hydro/share/geometry_msgs
// any message published on a ROS topic must have a pre-defined format, so subscribers know how to
// interpret the serialized data transmission
geometry_msgs::Twist twist_cmd;
// look at the components of a message of type geometry_msgs::Twist by typing:
// rosmsg show geometry_msgs/Twist
// It has 6 fields.  Let's fill them all in with some data:
twist_cmd.linear.x = 0.0;
twist_cmd.linear.y = 0.0;
twist_cmd.linear.z = 0.0;
twist_cmd.angular.x = 0.0;
twist_cmd.angular.y = 0.0;
twist_cmd.angular.z = 0.0;

testTimer();

moveForward(1200);
rotateRight(500);
moveForward(3000);
rotateRight(500);
moveForward(2250);
rotateRight(500);
moveForward(100);

ROS_INFO("Robot has completed all tasks.. Shutting down.");
while (ros::ok()) {
    twist_cmd.linear.x = 0.0;
    twist_cmd.angular.z = 0;
    cmd_publisher.publish(twist_cmd); // and halt
}
return 0;
}

// timer test...print out a message every 1 second
void testTimer(){
    ROS_INFO("Timer test count-down...");
     for (int j=3;j>0;j--) {
        ROS_INFO("%d",j);
        for (int i = 0; i<100;i++)
            sleep_timer.sleep();
    }
}

//Rotates the robot to the right for the provided number of iterations
//Note that 100 iterations is equivalent to 1 second.
void rotateRight(int iterations){
    twist_cmd.linear.x = 0.0;
    twist_cmd.angular.z = -0.314;
    ROS_INFO("Rotating the robot to the right for " + (iterations/100) + " seconds.");
    for (int i = 0; i < iterations; i++) {
        cmd_publisher.publish(twist_cmd);
        sleep_timer.sleep();
    }
}

//Moves the robot forward for the provided number of iterations
//Note that 100 iterations is equivalent to 1 second.
//At 10ms/iteration, and 0.2m/sec, expect 2mm/iter
//The robot should move by 2m over 10 sec
void moveForward(int iterations){
    twist_cmd.linear.x = 0.4;
    twist_cmd.angular.z = 0.0;
    ROS_INFO("Moving the robot forward for " + (iterations/100) + " seconds.");
    for (int i = 0; i < iterations; i++) {
        cmd_publisher.publish(twist_cmd);
        sleep_timer.sleep();
    }
}
} 
