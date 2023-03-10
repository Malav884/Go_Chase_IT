#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>

// Define a global client that can request services
ros::ServiceClient client;
//ball_chaser::DriveToTarget srv;
int direction = 0; 
ball_chaser::DriveToTarget srv;	
// This function calls the command_robot service to drive the robot in the specified direction
void drive_robot(float lin_x, float ang_z)
{
    // TODO: Request a service and pass the velocities to it to drive the robot
	ball_chaser::DriveToTarget srv;
	
    //Turn Left
   /* if (direction = 1)
    {
        lin_x = 0;
        ang_z = -0.2;
    }

    //Turn Right
    if (direction = 1)
    {
        lin_x = 0;
        ang_z = 0.2;
    }

    //Move Forward
    if (direction = 1)
    {
        lin_x = 0.3;
        ang_z = 0;
    }*/

    srv.request.linear_x = lin_x;
	srv.request.angular_z = ang_z;

	//Calling Service /ball_chaser/command_robot
	if (!client.call(srv))
	   ROS_ERROR("Failed to call Service command_robot");
}

// This callback function continuously executes and reads the image data
void process_image_callback(const sensor_msgs::Image img)
{

    int white_pixel = 255;
     
    // TODO: Loop through each pixel in the image and check if there's a bright white one
    // Then, identify if this pixel falls in the left, mid, or right side of the image
    // Depending on the white ball position, call the drive_bot function and pass velocities to it
    // Request a stop when there's no white ball seen by the camera
    for(int i =0; i < img.height * img.step; i++)
	{  ROS_INFO("img.data[i] == %1d", img.data[i]);
        if(img.data[i] - white_pixel == 0)
        {
        //direction = 1; // Turn Left
       // {ROS_INFO("Ball on Left ");
        drive_robot(0.2,0);}
        else
        {
             drive_robot(0,0);
        }
        
        
        
        //ROS_INFO("Ball in sight ");
      /*  ROS_INFO("img.data[i] == %1d", img.data[i]);
        //ROS_INFO("direction value == %d", direction);
        while( i > 0 && i < img.height * (img.step/3))
	  {if(img.data[i] - white_pixel == 0)
       { //direction = 1; // Turn Left
        ROS_INFO("Ball on Left ");
        drive_robot(0,-0.2);}
      }

         while( i > (img.height * (img.step/3)) && i < img.height * (2*img.step/3))
	  {if(img.data[i] - white_pixel == 0)
       { // direction = 2;
        ROS_INFO("Ball in front");
        drive_robot(0.3,0.0);}
      }
      

        while( i > (img.height * (2*img.step/3)) && i < img.height * (img.step))
	  {if(img.data[i] - white_pixel == 0)
         {//direction = 3; // Turn Right 
          ROS_INFO("Ball on Right side ");
          drive_robot(0,0.2);}
      }*/
    }

     


}

int main(int argc, char** argv)
{
    // Initialize the process_image node and create a handle to it
    ros::init(argc, argv, "process_image");
    ros::NodeHandle n;

    // Define a client service capable of requesting services from command_robot
    client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

    // Subscribe to /camera/rgb/image_raw topic to read the image data inside the process_image_callback function
    ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);

    // Handle ROS communication events
    ros::spin();

    return 0;
}
