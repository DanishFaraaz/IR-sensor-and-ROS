#!/usr/bin/env python

import rospy

from std_msgs.msg import Int32
from geometry_msgs.msg import Twist

def CB_Ir_values_process(data):

    velocity_msg = Twist()
    IR_values = data.data
    if IR_values > 100:
        velocity_msg.linear.x = 0.3
        print("Moving forward --->")

    else:
        velocity_msg.linear.x = 0
        print("! Stopping !")
    
    velocity_pub.publish(velocity_msg)

def L_Control_turtlesim():
    rospy.init_node("TurtleBot_IR_Control", anonymous=True)
    rospy.Subscriber("/values", Int32, CB_Ir_values_process)
    rospy.spin()

if __name__=='__main__':
    print("Getting data from IR sensor")
    velocity_pub = rospy.Publisher("/turtle1/cmd_vel", Twist, queue_size=1)
    L_Control_turtlesim()