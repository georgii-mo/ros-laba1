#include "ros/ros.h"
#include "ros_lab1/ruletka.h"
#include "std_msgs/String.h"
#include <cstdlib>
#include <string>
#include <cstring>
#include <ctime>
#include <string.h>

ros::ServiceServer service;
ros::Publisher publisher;
ros::Subscriber subscriber;

bool yee_boo(ros_lab1::ruletka::Request  &req,
         ros_lab1::ruletka::Response &res)
{
  srand(time(0)); 
  if (time(0) % 2 == 0) 
  {    
    res.solution = std::string("win").c_str();
  }
  else
  {
    res.solution = std::string("lose").c_str();
  }
  
  ROS_INFO("Sending back response",res.solution);
  std_msgs::String solution;
  solution.data = res.solution;
  publisher.publish(solution);
  return true;
}

void solution_callback(const std_msgs::String::ConstPtr& msg)
{
  std::string ans = msg-> data;
  if (ans == "win")
  {
    ROS_INFO("CONGRATULATIONS!!!");
  }
  else
  {
    int check = time(0) % 3; 
    if (check == 0) 
    {
      ROS_INFO("Don't be upset, next time you will win"); 
    }
     if (check == 2) 
     {
        ROS_INFO("Don't worry, the victory is near!");
     }
     if (check == 3) 
     {
       ROS_INFO("You will definitely win the next time!");
     }
   }
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "proga_rulet");
  ros::NodeHandle n;

  service = n.advertiseService("solution_roulette_bet", yee_boo);
  publisher = n.advertise<std_msgs::String>("solution", 1000);
  subscriber = n.subscribe("solution", 1000, solution_callback);

  ROS_INFO("Ready to play!");
  ros::spin();

  return 0;
}
