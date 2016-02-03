#include <ros/ros.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string.h>
#include <termios.h>
#include <irrKlang.h>
#include "std_msgs/String.h"
#include <unistd.h>
unsigned short act = 35;
long cmd_time[act] = {
		0,
		1920,
		5760,
		13440,
		17280,
		21120,
		24960,
		28800,
		32640,
		36480,
		40320,
		43200,
		48000,
		52800,
		55680,
		57600,
		61440,
		69120,
		72960,
		76800,
		80640,
		84480,
		88320,
		92160,
		96000,
		98880,
		103680,
		108480,
		111360,
		115200,
		122880,
		126720,
		130560,
		134400,
		138240
};
char* cmd[act] = {
		"HOME",
		"DANCE01",
		"DANCE02",
		"DANCE03",
		"DANCE04",
		"DANCE05",
		"DANCE06",
		"DANCE07",
		"DANCE08",
		"DANCE09",
		"DANCE10",
		"DANCE11",
		"DANCE12",
		"DANCE13",
		"HOME",
		"DANCE01",
		"DANCE02",
		"DANCE03",
		"DANCE04",
		"DANCE05",
		"DANCE06",
		"DANCE07",	
		"DANCE08",
		"DANCE09",	
		"DANCE10",	
		"DANCE11",	
		"DANCE12",	
		"DANCE13",
		"DANCE01",	
		"DANCE02",	
		"DANCE03",	
		"DANCE04",	
		"DANCE05",	
		"DANCE14",
		"END"
};
void chatterCallback(const std_msgs::String::ConstPtr& msg)
{	
	ROS_INFO("INFO: %s",msg.data());
}
char getch()
{
	fd_set set;
	struct timeval timeout;
	int rv;
	char buff = 0;
	int len = 1;
	int filedesc = 0;
	FD_ZERO(&set);
	FD_SET(filedesc, &set);
	timeout.tv_sec = 0;
	timeout.tv_usec = 1000;
	rv = select(filedesc + 1, &set, NULL, NULL, &timeout);
	struct termios old = {0};
	if (tcgetattr(filedesc, &old) < 0)
		ROS_ERROR("tcsetattr()");
	old.c_lflag &= ~ICANON;
	old.c_lflag &= ~ECHO;
	old.c_cc[VMIN] = 1;
	old.c_cc[VTIME] = 0;
	if (tcsetattr(filedesc, TCSANOW, &old) < 0)
		ROS_ERROR("tcsetattr ICANON");
	if(rv == -1)
		ROS_ERROR("select");
	else
		read(filedesc, &buff, len );
	old.c_lflag |= ICANON;
	old.c_lflag |= ECHO;
	if (tcsetattr(filedesc, TCSADRAIN, &old) < 0)
	ROS_ERROR ("tcsetattr ~ICANON");
	return (buff);
}
using namespace std;
int main(int argc, char **argv)
{
	irrklang::ISoundEngine* engine = irrklang::createIrrKlangDevice();
	irrklang::ISound *s = NULL;
	if (!engine) return 1; // could not start engine
	ros::init(argc, argv, "listener");
	ros::NodeHandle n;
	ros::NodeHandle n2;
	ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);
	ros::Subscriber sub = n2.subscribe("chatter2", 1000 ,chatterCallback);
	ros::Rate loop_rate(10);
	std_msgs::String msg;
	char str[2] = "\0";
	long RTmode = -1;
	long track_time = 0;
	unsigned short deviation = 20;
	
	while (ros::ok())
	{
		if((str[0] = getch()) != 0){
			if(s != NULL)
				s->drop();
			if(engine != NULL){
				engine->drop(); 
				engine = irrklang::createIrrKlangDevice();
			}
			switch(str[0]){
			case '1':
				s = engine->play2D("monster.wav", false, false, true);
				msg.data = "DANCEALL";
				chatter_pub.publish(msg);
				break;
			case '2':
				s = engine->play2D("monster.wav", false, false, true);
				msg.data = cmd[0];
				chatter_pub.publish(msg);
				printf("Track time: %lu(ms)\t Command: %s\n",track_time,cmd[0]);
				RTmode=1;
				break;
			case 'j':
				msg.data = "ATKL";
				chatter_pub.publish(msg);
				goto case 's';
			case 'k':
				msg.data = "ATKR";
				chatter_pub.publish(msg);
				goto case 's';
			case 'l':
				msg.data = "ATKC";
				chatter_pub.publish(msg);
				goto case 's';
			case ';':
				msg.data = "LAUGH";
				chatter_pub.publish(msg);
				goto case 's';
			case 'w':
				msg.data = "FORWARD";
				chatter_pub.publish(msg);
				break;
			case 'a':
				msg.data = "LEFT";
				chatter_pub.publish(msg);
				break;
			case 'd':
				msg.data = "RIGHT";
				chatter_pub.publish(msg);
				break;
			case 's':
				msg.data = "HOME";
				chatter_pub.publish(msg);
				break;
			case 'q':
				msg.data = "END";
				chatter_pub.publish(msg);
				break;
			default:
				RTmode = -1;
			}
		}
		if(RTmode!= -1){
			track_time = s->getPlayPosition();
			for(int i = RTmode; i < act; i++)
			if(track_time > cmd_time[i]-deviation && track_time < cmd_time[i]+deviation){
				msg.data = cmd[i];
				chatter_pub.publish(msg);
				printf("Track time: %lu(ms)\t Command: %s\n",track_time,cmd[i]);
				RTmode++;	
			}	
			if(RTmode >= act)
				RTmode = -1;
		}
		ros::spinOnce();
	}
	return 0;
}
