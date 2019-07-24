
#include <ros.h>
#include <std_msgs/Int32.h>
std_msgs::Int32 int_msg;
ros::NodeHandle nh;

const char* ssid = "JioFi2_0B7688";
const char* password = "xu7x5n9ucp";

const uint16_t serverPort = 11411;

const int IRSensor = A0;
ros::Publisher IR_Sensor("values", &int_msg);

void setup() {
  Serial.begin(57600);
  nh.initNode();
  nh.advertise(IR_Sensor);
  pinMode(IRSensor, INPUT);
  WiFi.begin(ssid, password);
  IPAddress server(192,168,1,100);
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  nh.getHardware()->setConnection(server, serverPort);

}

void loop() {
  if (nh.connected()){
    int_msg.data = analogRead(IRSensor);
    IR_Sensor.publish(&int_msg);
    Serial.println(int_msg.data);
    Serial.println(analogRead(IRSensor));
    Serial.println("-------------");
  }

  nh.spinOnce();
  delay(1000);

}
