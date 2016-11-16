/****
 * Oscillator
 **/

//includes
#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
#endif
#include <ros.h>
// Se añade la libreria para recibir floats
#include <std_msgs/Float32.h>
// Se añade la librera para recibir unsigned ints
#include <std_msgs/UInt16.h>

//ROS variables
ros::NodeHandle nh_;
std_msgs::Float32 float_msg_;
ros::Publisher publisher_("wave", &float_msg_);

//other variables
float angle_ = 0; 
const float PI_ = 3.141592;

// Variable de inicializacin del periodo
unsigned int periodo = 20;

// Funcion para recibir los datos 
void update_Period(const std_msgs::UInt16& msg)
{
  periodo = msg.data;
}

// Se escribe el codigo del subscriber
ros::Subscriber<std_msgs::UInt16> sub("period", update_Period);

//setup 
void setup()
{ 
    //ROS init
    nh_.initNode();
    nh_.advertise(publisher_);
    // Se asocia el subscriber del que se recibiran los datos
    nh_.subscribe(sub);
}

void loop()
{
    //increment the angle
    angle_ = angle_ + PI_/100; 
    if (angle_ > 2*PI_) angle_ = angle_ - 2.0*PI_; 

    //publish
    float_msg_.data = cos(angle_); 
    publisher_.publish(&float_msg_);

    //spin (ros sync and attend callbacks, if any ...)
    nh_.spinOnce();
    
    //relax (50ms)
    delay(periodo);     
}
