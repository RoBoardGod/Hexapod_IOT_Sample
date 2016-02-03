#include <Servo86.h>
#include <ros.h>
#include <std_msgs/String.h>
#include <geometry_msgs/Pose2D.h>
#include <time.h>

Servo myservo2;
Servo myservo3;
Servo myservo4;
Servo myservo5;
Servo myservo6;
Servo myservo7;
Servo myservo8;
Servo myservo9;
Servo myservo10;
Servo myservo11;
Servo myservo12;
Servo myservo13;

enum {_END, _HOME, _FORWARD, _LEFT, _RIGHT, _IDLE, _TITLE, _DANCE01, _DANCE02, _DANCE03, _DANCE04, _DANCE05, _DANCE06, _DANCE07, _DANCE08, _DANCE09, _DANCE10, _DANCE11, _DANCE12, _DANCE13, _DANCE14, _DANCEALL, _NONE};
int _last_motion = _NONE;
int _curr_motion = _NONE;
bool internal_trigger[23] = {0};
bool external_trigger[23] = {0};

ServoOffset myoffs("a:\\86offset.txt");	//You can move 86offset file into 86Duino Disk (A:), it will make all 86Hexapod has same action

ServoFrame _86ME_HOME;

ServoFrame END_frm[2];
ServoFrame home_frm[1];
ServoFrame forward_frm[6];
ServoFrame left_frm[6];
ServoFrame right_frm[6];
ServoFrame idle_frm[2];
int title_title = 1;
ServoFrame title_frm[3];
ServoFrame dance01_frm[2];
ServoFrame dance02_frm[8];
ServoFrame dance03_frm[6];
ServoFrame dance04_frm[15];
ServoFrame dance05_frm[6];
ServoFrame dance06_frm[3];
ServoFrame dance07_frm[16];
ServoFrame dance08_frm[12];
ServoFrame dance09_frm[8];
ServoFrame dance10_frm[6];
ServoFrame dance11_frm[8];
ServoFrame dance12_frm[8];
ServoFrame dance13_frm[14];
ServoFrame dance14_frm[4];
ServoFrame danceALL_frm[0];


char Serial1_Message[20];
bool renew_bt = true;
ros::NodeHandle  nh;
void messageCb( const std_msgs::String& cmsg)
{
	strcpy(Serial1_Message,(char*)cmsg.data);
}
ros::Subscriber<std_msgs::String> sub("chatter", &messageCb );

namespace END
{
  enum {IDLE, FRAME_0, WAIT_FRAME_0, FRAME_1, WAIT_FRAME_1};
  int state = IDLE;
}
namespace home
{
  enum {IDLE, FRAME_0, WAIT_FRAME_0};
  int state = IDLE;
}
namespace forward
{
  enum {IDLE, FRAME_0, WAIT_FRAME_0, FRAME_1, WAIT_FRAME_1, FRAME_2, WAIT_FRAME_2, FRAME_3, WAIT_FRAME_3, FRAME_4, WAIT_FRAME_4, FRAME_5, WAIT_FRAME_5};
  int state = IDLE;
}
namespace left
{
  enum {IDLE, FRAME_0, WAIT_FRAME_0, FRAME_1, WAIT_FRAME_1, FRAME_2, WAIT_FRAME_2, FRAME_3, WAIT_FRAME_3, FRAME_4, WAIT_FRAME_4, FRAME_5, WAIT_FRAME_5};
  int state = IDLE;
}
namespace right
{
  enum {IDLE, FRAME_0, WAIT_FRAME_0, FRAME_1, WAIT_FRAME_1, FRAME_2, WAIT_FRAME_2, FRAME_3, WAIT_FRAME_3, FRAME_4, WAIT_FRAME_4, FRAME_5, WAIT_FRAME_5};
  int state = IDLE;
}
namespace idle
{
  enum {IDLE, FLAG_0, FRAME_1, WAIT_FRAME_1, FRAME_2, WAIT_FRAME_2, GOTO_3};
  int state = IDLE;
  int aaa_3 = 0;
}
namespace title
{
  enum {IDLE, FLAG_0, FRAME_1, WAIT_FRAME_1, FRAME_2, WAIT_FRAME_2, GOTO_3, FRAME_4, WAIT_FRAME_4};
  int state = IDLE;
  int aaa_3 = 0;
}
namespace dance01
{
  enum {IDLE, FLAG_0, FRAME_1, WAIT_FRAME_1, DELAY_2, WAIT_DELAY_2, FRAME_3, WAIT_FRAME_3, GOTO_4};
  int state = IDLE;
  unsigned long time;
  int flag01_4 = 0;
}
namespace dance02
{
  enum {IDLE, FLAG_0, FRAME_1, WAIT_FRAME_1, DELAY_2, WAIT_DELAY_2, FRAME_3, WAIT_FRAME_3, FRAME_4, WAIT_FRAME_4, DELAY_5, WAIT_DELAY_5, FRAME_6, WAIT_FRAME_6, FRAME_7, WAIT_FRAME_7, DELAY_8, WAIT_DELAY_8, FRAME_9, WAIT_FRAME_9, FRAME_10, WAIT_FRAME_10, DELAY_11, WAIT_DELAY_11, FRAME_12, WAIT_FRAME_12, GOTO_13};
  int state = IDLE;
  unsigned long time;
  int flag02_13 = 0;
}
namespace dance03
{
  enum {IDLE, FLAG_0, FRAME_1, WAIT_FRAME_1, FRAME_2, WAIT_FRAME_2, FRAME_3, WAIT_FRAME_3, FRAME_4, WAIT_FRAME_4, GOTO_5, FRAME_6, WAIT_FRAME_6, FRAME_7, WAIT_FRAME_7, DELAY_8, WAIT_DELAY_8};
  int state = IDLE;
  unsigned long time;
  int flag03_5 = 0;
}
namespace dance04
{
  enum {IDLE, FRAME_0, WAIT_FRAME_0, FRAME_1, WAIT_FRAME_1, FRAME_2, WAIT_FRAME_2, FRAME_3, WAIT_FRAME_3, FRAME_4, WAIT_FRAME_4, FRAME_5, WAIT_FRAME_5, FRAME_6, WAIT_FRAME_6, FRAME_7, WAIT_FRAME_7, FRAME_8, WAIT_FRAME_8, FRAME_9, WAIT_FRAME_9, FRAME_10, WAIT_FRAME_10, FRAME_11, WAIT_FRAME_11, FRAME_12, WAIT_FRAME_12, DELAY_13, WAIT_DELAY_13, FRAME_14, WAIT_FRAME_14, FRAME_15, WAIT_FRAME_15};
  int state = IDLE;
  unsigned long time;
}
namespace dance05
{
  enum {IDLE, FLAG_0, FRAME_1, WAIT_FRAME_1, FRAME_2, WAIT_FRAME_2, GOTO_3, FRAME_4, WAIT_FRAME_4, FRAME_5, WAIT_FRAME_5, DELAY_6, WAIT_DELAY_6, FRAME_7, WAIT_FRAME_7, FRAME_8, WAIT_FRAME_8, DELAY_9, WAIT_DELAY_9};
  int state = IDLE;
  unsigned long time;
  int flag05_3 = 0;
}
namespace dance06
{
  enum {IDLE, DELAY_0, WAIT_DELAY_0, FRAME_1, WAIT_FRAME_1, FLAG_2, FRAME_3, WAIT_FRAME_3, FRAME_4, WAIT_FRAME_4, GOTO_5};
  int state = IDLE;
  unsigned long time;
  int flag06_5 = 0;
}
namespace dance07
{
  enum {IDLE, FRAME_0, WAIT_FRAME_0, FRAME_1, WAIT_FRAME_1, FRAME_2, WAIT_FRAME_2, FRAME_3, WAIT_FRAME_3, DELAY_4, WAIT_DELAY_4, FRAME_5, WAIT_FRAME_5, FRAME_6, WAIT_FRAME_6, FRAME_7, WAIT_FRAME_7, FRAME_8, WAIT_FRAME_8, FRAME_9, WAIT_FRAME_9, FRAME_10, WAIT_FRAME_10, FRAME_11, WAIT_FRAME_11, FRAME_12, WAIT_FRAME_12, DELAY_13, WAIT_DELAY_13, FRAME_14, WAIT_FRAME_14, FRAME_15, WAIT_FRAME_15, FRAME_16, WAIT_FRAME_16, FRAME_17, WAIT_FRAME_17};
  int state = IDLE;
  unsigned long time;
}
namespace dance08
{
  enum {IDLE, FRAME_0, WAIT_FRAME_0, FRAME_1, WAIT_FRAME_1, FRAME_2, WAIT_FRAME_2, FRAME_3, WAIT_FRAME_3, FRAME_4, WAIT_FRAME_4, FRAME_5, WAIT_FRAME_5, FRAME_6, WAIT_FRAME_6, FRAME_7, WAIT_FRAME_7, FRAME_8, WAIT_FRAME_8, FRAME_9, WAIT_FRAME_9, FRAME_10, WAIT_FRAME_10, FRAME_11, WAIT_FRAME_11};
  int state = IDLE;
}
namespace dance09
{
  enum {IDLE, FLAG_0, FRAME_1, WAIT_FRAME_1, FRAME_2, WAIT_FRAME_2, DELAY_3, WAIT_DELAY_3, FRAME_4, WAIT_FRAME_4, FRAME_5, WAIT_FRAME_5, FRAME_6, WAIT_FRAME_6, FRAME_7, WAIT_FRAME_7, FRAME_8, WAIT_FRAME_8, FRAME_9, WAIT_FRAME_9, GOTO_10};
  int state = IDLE;
  unsigned long time;
  int flag0902_10 = 0;
}
namespace dance10
{
  enum {IDLE, FRAME_0, WAIT_FRAME_0, FRAME_1, WAIT_FRAME_1, FLAG_2, FRAME_3, WAIT_FRAME_3, FRAME_4, WAIT_FRAME_4, GOTO_5, FRAME_6, WAIT_FRAME_6, FRAME_7, WAIT_FRAME_7};
  int state = IDLE;
  int flag10_5 = 0;
}
namespace dance11
{
  enum {IDLE, FLAG_0, FRAME_1, WAIT_FRAME_1, FRAME_2, WAIT_FRAME_2, GOTO_3, FRAME_4, WAIT_FRAME_4, FRAME_5, WAIT_FRAME_5, FRAME_6, WAIT_FRAME_6, FRAME_7, WAIT_FRAME_7, FRAME_8, WAIT_FRAME_8, FRAME_9, WAIT_FRAME_9};
  int state = IDLE;
  int flag11_3 = 0;
}
namespace dance12
{
  enum {IDLE, DELAY_0, WAIT_DELAY_0, FRAME_1, WAIT_FRAME_1, FRAME_2, WAIT_FRAME_2, FRAME_3, WAIT_FRAME_3, DELAY_4, WAIT_DELAY_4, FRAME_5, WAIT_FRAME_5, FRAME_6, WAIT_FRAME_6, DELAY_7, WAIT_DELAY_7, FRAME_8, WAIT_FRAME_8, FRAME_9, WAIT_FRAME_9, FRAME_10, WAIT_FRAME_10};
  int state = IDLE;
  unsigned long time;
}
namespace dance13
{
  enum {IDLE, FRAME_0, WAIT_FRAME_0, FRAME_1, WAIT_FRAME_1, FRAME_2, WAIT_FRAME_2, FRAME_3, WAIT_FRAME_3, FRAME_4, WAIT_FRAME_4, FRAME_5, WAIT_FRAME_5, FRAME_6, WAIT_FRAME_6, FRAME_7, WAIT_FRAME_7, FRAME_8, WAIT_FRAME_8, FRAME_9, WAIT_FRAME_9, FRAME_10, WAIT_FRAME_10, FRAME_11, WAIT_FRAME_11, FRAME_12, WAIT_FRAME_12, FRAME_13, WAIT_FRAME_13};
  int state = IDLE;
}
namespace dance14
{
  enum {IDLE, FRAME_0, WAIT_FRAME_0, FRAME_1, WAIT_FRAME_1, FLAG_2, FRAME_3, WAIT_FRAME_3, FRAME_4, WAIT_FRAME_4, GOTO_5};
  int state = IDLE;
  int flag14_5 = 0;
}
namespace danceALL
{
  enum {IDLE, DELAY_0, WAIT_DELAY_0, MOTION_1, WAIT_MOTION_1, MOTION_2, WAIT_MOTION_2, MOTION_3, WAIT_MOTION_3, MOTION_4, WAIT_MOTION_4, MOTION_5, WAIT_MOTION_5, MOTION_6, WAIT_MOTION_6, MOTION_7, WAIT_MOTION_7, MOTION_8, WAIT_MOTION_8, MOTION_9, WAIT_MOTION_9, MOTION_10, WAIT_MOTION_10, MOTION_11, WAIT_MOTION_11, MOTION_12, WAIT_MOTION_12, MOTION_13, WAIT_MOTION_13, DELAY_14, WAIT_DELAY_14, MOTION_15, WAIT_MOTION_15, MOTION_16, WAIT_MOTION_16, MOTION_17, WAIT_MOTION_17, MOTION_18, WAIT_MOTION_18, MOTION_19, WAIT_MOTION_19, MOTION_20, WAIT_MOTION_20, MOTION_21, WAIT_MOTION_21, MOTION_22, WAIT_MOTION_22, MOTION_23, WAIT_MOTION_23, MOTION_24, WAIT_MOTION_24, MOTION_25, WAIT_MOTION_25, MOTION_26, WAIT_MOTION_26, MOTION_27, WAIT_MOTION_27, MOTION_28, WAIT_MOTION_28, MOTION_29, WAIT_MOTION_29, MOTION_30, WAIT_MOTION_30, MOTION_31, WAIT_MOTION_31, MOTION_32, WAIT_MOTION_32, MOTION_33, WAIT_MOTION_33};
  int state = IDLE;
  unsigned long time;
}
bool isBlocked()
{
  if(external_trigger[_TITLE]) return true;
  return false;
}
void closeTriggers()
{
  external_trigger[_END]= false; internal_trigger[_END]= false;
  external_trigger[_HOME]= false; internal_trigger[_HOME]= false;
  external_trigger[_FORWARD]= false; internal_trigger[_FORWARD]= false;
  external_trigger[_LEFT]= false; internal_trigger[_LEFT]= false;
  external_trigger[_RIGHT]= false; internal_trigger[_RIGHT]= false;
  external_trigger[_IDLE]= false; internal_trigger[_IDLE]= false;
  external_trigger[_TITLE]= false; internal_trigger[_TITLE]= false;
  external_trigger[_DANCE01]= false; internal_trigger[_DANCE01]= false;
  external_trigger[_DANCE02]= false; internal_trigger[_DANCE02]= false;
  external_trigger[_DANCE03]= false; internal_trigger[_DANCE03]= false;
  external_trigger[_DANCE04]= false; internal_trigger[_DANCE04]= false;
  external_trigger[_DANCE05]= false; internal_trigger[_DANCE05]= false;
  external_trigger[_DANCE06]= false; internal_trigger[_DANCE06]= false;
  external_trigger[_DANCE07]= false; internal_trigger[_DANCE07]= false;
  external_trigger[_DANCE08]= false; internal_trigger[_DANCE08]= false;
  external_trigger[_DANCE09]= false; internal_trigger[_DANCE09]= false;
  external_trigger[_DANCE10]= false; internal_trigger[_DANCE10]= false;
  external_trigger[_DANCE11]= false; internal_trigger[_DANCE11]= false;
  external_trigger[_DANCE12]= false; internal_trigger[_DANCE12]= false;
  external_trigger[_DANCE13]= false; internal_trigger[_DANCE13]= false;
  external_trigger[_DANCE14]= false; internal_trigger[_DANCE14]= false;
  external_trigger[_DANCEALL]= false; internal_trigger[_DANCEALL]= false;
}
void updateTrigger()
{
  if(isBlocked()) return;
  if(title_title == 1) {_curr_motion = _TITLE; title_title--;}
  else if(strcmp(Serial1_Message,"END") ==0) {_curr_motion = _END;}
  else if(strcmp(Serial1_Message,"FORWARD") ==0) {_curr_motion = _FORWARD;}
  else if(strcmp(Serial1_Message,"LEFT") ==0) {_curr_motion = _LEFT;}
  else if(strcmp(Serial1_Message,"RIGHT") ==0) {_curr_motion = _RIGHT;}
  else if(strcmp(Serial1_Message,"HOME") ==0) {_curr_motion = _HOME;}
  else if(strcmp(Serial1_Message,"DANCE01") ==0) {_curr_motion = _DANCE01;}
  else if(strcmp(Serial1_Message,"DANCE02") ==0) {_curr_motion = _DANCE02;}
  else if(strcmp(Serial1_Message,"DANCE03") ==0) {_curr_motion = _DANCE03;}
  else if(strcmp(Serial1_Message,"DANCE04") ==0) {_curr_motion = _DANCE04;}
  else if(strcmp(Serial1_Message,"DANCE05") ==0) {_curr_motion = _DANCE05;}
  else if(strcmp(Serial1_Message,"DANCE06") ==0) {_curr_motion = _DANCE06;}
  else if(strcmp(Serial1_Message,"DANCE07") ==0) {_curr_motion = _DANCE07;}
  else if(strcmp(Serial1_Message,"DANCE08") ==0) {_curr_motion = _DANCE08;}
  else if(strcmp(Serial1_Message,"DANCE09") ==0) {_curr_motion = _DANCE09;}
  else if(strcmp(Serial1_Message,"DANCE10") ==0) {_curr_motion = _DANCE10;}
  else if(strcmp(Serial1_Message,"DANCE11") ==0) {_curr_motion = _DANCE11;}
  else if(strcmp(Serial1_Message,"DANCE12") ==0) {_curr_motion = _DANCE12;}
  else if(strcmp(Serial1_Message,"DANCE13") ==0) {_curr_motion = _DANCE13;}
  else if(strcmp(Serial1_Message,"DANCE14") ==0) {_curr_motion = _DANCE14;}
  else if(strcmp(Serial1_Message,"DANCEALL") ==0) {_curr_motion = _DANCEALL;}
  else { _curr_motion = _NONE; }
  if(_last_motion != _curr_motion && _curr_motion != _NONE)
  {
    closeTriggers();
    external_trigger[_curr_motion] = true;
    END::state = 0;
    home::state = 0;
    forward::state = 0;
    left::state = 0;
    right::state = 0;
    idle::state = 0;
    idle::aaa_3 = 0;
    title::state = 0;
    title::aaa_3 = 0;
    dance01::state = 0;
    dance01::flag01_4 = 0;
    dance02::state = 0;
    dance02::flag02_13 = 0;
    dance03::state = 0;
    dance03::flag03_5 = 0;
    dance04::state = 0;
    dance05::state = 0;
    dance05::flag05_3 = 0;
    dance06::state = 0;
    dance06::flag06_5 = 0;
    dance07::state = 0;
    dance08::state = 0;
    dance09::state = 0;
    dance09::flag0902_10 = 0;
    dance10::state = 0;
    dance10::flag10_5 = 0;
    dance11::state = 0;
    dance11::flag11_3 = 0;
    dance12::state = 0;
    dance13::state = 0;
    dance14::state = 0;
    dance14::flag14_5 = 0;
    danceALL::state = 0;
  }
  external_trigger[_curr_motion] = true;
  _last_motion = _curr_motion;
}
void ENDUpdate()
{
  switch(END::state)
  {
  case END::IDLE:
    if(external_trigger[_END] || internal_trigger[_END]) END::state = END::FRAME_0;
    else break;
  case END::FRAME_0:
    END_frm[0].playPositions(240);
    END::state = END::WAIT_FRAME_0;
  case END::WAIT_FRAME_0:
    if(!isServoMultiMoving())
      END::state = END::FRAME_1;
    break;
  case END::FRAME_1:
    END_frm[1].playPositions(240);
    END::state = END::WAIT_FRAME_1;
  case END::WAIT_FRAME_1:
    if(!isServoMultiMoving())
    {
      END::state = END::IDLE;
      internal_trigger[_END] = false;
      external_trigger[_END] = false;
    }
    break;
  default:
    break;
  }
}
void homeUpdate()
{
  switch(home::state)
  {
  case home::IDLE:
    if(external_trigger[_HOME] || internal_trigger[_HOME]) home::state = home::FRAME_0;
    else break;
  case home::FRAME_0:
    home_frm[0].playPositions(5000);
    home::state = home::WAIT_FRAME_0;
  case home::WAIT_FRAME_0:
    if(!isServoMultiMoving())
    {
      home::state = home::IDLE;
      internal_trigger[_HOME] = false;
      external_trigger[_HOME] = false;
    }
    break;
  default:
    break;
  }
}
void forwardUpdate()
{
  switch(forward::state)
  {
  case forward::IDLE:
    if(external_trigger[_FORWARD] || internal_trigger[_FORWARD]) forward::state = forward::FRAME_0;
    else break;
  case forward::FRAME_0:
    forward_frm[0].playPositions(300);
    forward::state = forward::WAIT_FRAME_0;
  case forward::WAIT_FRAME_0:
    if(!isServoMultiMoving())
      forward::state = forward::FRAME_1;
    break;
  case forward::FRAME_1:
    forward_frm[1].playPositions(150);
    forward::state = forward::WAIT_FRAME_1;
  case forward::WAIT_FRAME_1:
    if(!isServoMultiMoving())
      forward::state = forward::FRAME_2;
    break;
  case forward::FRAME_2:
    forward_frm[2].playPositions(150);
    forward::state = forward::WAIT_FRAME_2;
  case forward::WAIT_FRAME_2:
    if(!isServoMultiMoving())
      forward::state = forward::FRAME_3;
    break;
  case forward::FRAME_3:
    forward_frm[3].playPositions(300);
    forward::state = forward::WAIT_FRAME_3;
  case forward::WAIT_FRAME_3:
    if(!isServoMultiMoving())
      forward::state = forward::FRAME_4;
    break;
  case forward::FRAME_4:
    forward_frm[4].playPositions(150);
    forward::state = forward::WAIT_FRAME_4;
  case forward::WAIT_FRAME_4:
    if(!isServoMultiMoving())
      forward::state = forward::FRAME_5;
    break;
  case forward::FRAME_5:
    forward_frm[5].playPositions(150);
    forward::state = forward::WAIT_FRAME_5;
  case forward::WAIT_FRAME_5:
    if(!isServoMultiMoving())
    {
      forward::state = forward::IDLE;
      internal_trigger[_FORWARD] = false;
      external_trigger[_FORWARD] = false;
    }
    break;
  default:
    break;
  }
}
void leftUpdate()
{
  switch(left::state)
  {
  case left::IDLE:
    if(external_trigger[_LEFT] || internal_trigger[_LEFT]) left::state = left::FRAME_0;
    else break;
  case left::FRAME_0:
    left_frm[0].playPositions(300);
    left::state = left::WAIT_FRAME_0;
  case left::WAIT_FRAME_0:
    if(!isServoMultiMoving())
      left::state = left::FRAME_1;
    break;
  case left::FRAME_1:
    left_frm[1].playPositions(150);
    left::state = left::WAIT_FRAME_1;
  case left::WAIT_FRAME_1:
    if(!isServoMultiMoving())
      left::state = left::FRAME_2;
    break;
  case left::FRAME_2:
    left_frm[2].playPositions(150);
    left::state = left::WAIT_FRAME_2;
  case left::WAIT_FRAME_2:
    if(!isServoMultiMoving())
      left::state = left::FRAME_3;
    break;
  case left::FRAME_3:
    left_frm[3].playPositions(300);
    left::state = left::WAIT_FRAME_3;
  case left::WAIT_FRAME_3:
    if(!isServoMultiMoving())
      left::state = left::FRAME_4;
    break;
  case left::FRAME_4:
    left_frm[4].playPositions(150);
    left::state = left::WAIT_FRAME_4;
  case left::WAIT_FRAME_4:
    if(!isServoMultiMoving())
      left::state = left::FRAME_5;
    break;
  case left::FRAME_5:
    left_frm[5].playPositions(150);
    left::state = left::WAIT_FRAME_5;
  case left::WAIT_FRAME_5:
    if(!isServoMultiMoving())
    {
      left::state = left::IDLE;
      internal_trigger[_LEFT] = false;
      external_trigger[_LEFT] = false;
    }
    break;
  default:
    break;
  }
}
void rightUpdate()
{
  switch(right::state)
  {
  case right::IDLE:
    if(external_trigger[_RIGHT] || internal_trigger[_RIGHT]) right::state = right::FRAME_0;
    else break;
  case right::FRAME_0:
    right_frm[0].playPositions(300);
    right::state = right::WAIT_FRAME_0;
  case right::WAIT_FRAME_0:
    if(!isServoMultiMoving())
      right::state = right::FRAME_1;
    break;
  case right::FRAME_1:
    right_frm[1].playPositions(150);
    right::state = right::WAIT_FRAME_1;
  case right::WAIT_FRAME_1:
    if(!isServoMultiMoving())
      right::state = right::FRAME_2;
    break;
  case right::FRAME_2:
    right_frm[2].playPositions(150);
    right::state = right::WAIT_FRAME_2;
  case right::WAIT_FRAME_2:
    if(!isServoMultiMoving())
      right::state = right::FRAME_3;
    break;
  case right::FRAME_3:
    right_frm[3].playPositions(300);
    right::state = right::WAIT_FRAME_3;
  case right::WAIT_FRAME_3:
    if(!isServoMultiMoving())
      right::state = right::FRAME_4;
    break;
  case right::FRAME_4:
    right_frm[4].playPositions(150);
    right::state = right::WAIT_FRAME_4;
  case right::WAIT_FRAME_4:
    if(!isServoMultiMoving())
      right::state = right::FRAME_5;
    break;
  case right::FRAME_5:
    right_frm[5].playPositions(150);
    right::state = right::WAIT_FRAME_5;
  case right::WAIT_FRAME_5:
    if(!isServoMultiMoving())
    {
      right::state = right::IDLE;
      internal_trigger[_RIGHT] = false;
      external_trigger[_RIGHT] = false;
    }
    break;
  default:
    break;
  }
}
void idleUpdate()
{
  switch(idle::state)
  {
  case idle::IDLE:
    if(external_trigger[_IDLE] || internal_trigger[_IDLE]) idle::state = idle::FLAG_0;
    else break;
  case idle::FLAG_0:
    flag_idle_aaa_0:
  case idle::FRAME_1:
    idle_frm[0].playPositions(450);
    idle::state = idle::WAIT_FRAME_1;
  case idle::WAIT_FRAME_1:
    if(!isServoMultiMoving())
      idle::state = idle::FRAME_2;
    break;
  case idle::FRAME_2:
    idle_frm[1].playPositions(450);
    idle::state = idle::WAIT_FRAME_2;
  case idle::WAIT_FRAME_2:
    if(!isServoMultiMoving())
      idle::state = idle::GOTO_3;
    break;
  case idle::GOTO_3:
    if(idle::aaa_3++ < 2) goto flag_idle_aaa_0;
    else
    {
      idle::aaa_3 = 0;
      internal_trigger[_IDLE] = false;
      external_trigger[_IDLE] = false;
      idle::state = idle::IDLE;
    }
    break;
  default:
    break;
  }
}
void titleUpdate()
{
  switch(title::state)
  {
  case title::IDLE:
    if(external_trigger[_TITLE] || internal_trigger[_TITLE]) title::state = title::FLAG_0;
    else break;
  case title::FLAG_0:
    flag_title_aaa_0:
  case title::FRAME_1:
    title_frm[0].playPositions(300);
    title::state = title::WAIT_FRAME_1;
  case title::WAIT_FRAME_1:
    if(!isServoMultiMoving())
      title::state = title::FRAME_2;
    break;
  case title::FRAME_2:
    title_frm[1].playPositions(300);
    title::state = title::WAIT_FRAME_2;
  case title::WAIT_FRAME_2:
    if(!isServoMultiMoving())
      title::state = title::GOTO_3;
    break;
  case title::GOTO_3:
    if(title::aaa_3++ < 1) goto flag_title_aaa_0;
    title::state = title::FRAME_4;
    break;
  case title::FRAME_4:
    title_frm[2].playPositions(200);
    title::state = title::WAIT_FRAME_4;
  case title::WAIT_FRAME_4:
    if(!isServoMultiMoving())
    {
      title::state = title::IDLE;
      title::aaa_3 = 0;
      internal_trigger[_TITLE] = false;
      external_trigger[_TITLE] = false;
    }
    break;
  default:
    break;
  }
}
void dance01Update()
{
  switch(dance01::state)
  {
  case dance01::IDLE:
    if(external_trigger[_DANCE01] || internal_trigger[_DANCE01]) dance01::state = dance01::FLAG_0;
    else break;
  case dance01::FLAG_0:
    flag_dance01_flag01_0:
  case dance01::FRAME_1:
    dance01_frm[0].playPositions(240);
    dance01::state = dance01::WAIT_FRAME_1;
  case dance01::WAIT_FRAME_1:
    if(!isServoMultiMoving())
      dance01::state = dance01::DELAY_2;
    break;
  case dance01::DELAY_2:
    dance01::time = millis();
    dance01::state = dance01::WAIT_DELAY_2;
  case dance01::WAIT_DELAY_2:
    if(millis() - dance01::time >= 240)
      dance01::state = dance01::FRAME_3;
    break;
  case dance01::FRAME_3:
    dance01_frm[1].playPositions(480);
    dance01::state = dance01::WAIT_FRAME_3;
  case dance01::WAIT_FRAME_3:
    if(!isServoMultiMoving())
      dance01::state = dance01::GOTO_4;
    break;
  case dance01::GOTO_4:
    if(dance01::flag01_4++ < 3) goto flag_dance01_flag01_0;
    else
    {
      dance01::flag01_4 = 0;
      internal_trigger[_DANCE01] = false;
      external_trigger[_DANCE01] = false;
      dance01::state = dance01::IDLE;
    }
    break;
  default:
    break;
  }
}
void dance02Update()
{
  switch(dance02::state)
  {
  case dance02::IDLE:
    if(external_trigger[_DANCE02] || internal_trigger[_DANCE02]) dance02::state = dance02::FLAG_0;
    else break;
  case dance02::FLAG_0:
    flag_dance02_flag02_0:
  case dance02::FRAME_1:
    dance02_frm[0].playPositions(240);
    dance02::state = dance02::WAIT_FRAME_1;
  case dance02::WAIT_FRAME_1:
    if(!isServoMultiMoving())
      dance02::state = dance02::DELAY_2;
    break;
  case dance02::DELAY_2:
    dance02::time = millis();
    dance02::state = dance02::WAIT_DELAY_2;
  case dance02::WAIT_DELAY_2:
    if(millis() - dance02::time >= 240)
      dance02::state = dance02::FRAME_3;
    break;
  case dance02::FRAME_3:
    dance02_frm[1].playPositions(480);
    dance02::state = dance02::WAIT_FRAME_3;
  case dance02::WAIT_FRAME_3:
    if(!isServoMultiMoving())
      dance02::state = dance02::FRAME_4;
    break;
  case dance02::FRAME_4:
    dance02_frm[2].playPositions(240);
    dance02::state = dance02::WAIT_FRAME_4;
  case dance02::WAIT_FRAME_4:
    if(!isServoMultiMoving())
      dance02::state = dance02::DELAY_5;
    break;
  case dance02::DELAY_5:
    dance02::time = millis();
    dance02::state = dance02::WAIT_DELAY_5;
  case dance02::WAIT_DELAY_5:
    if(millis() - dance02::time >= 240)
      dance02::state = dance02::FRAME_6;
    break;
  case dance02::FRAME_6:
    dance02_frm[3].playPositions(480);
    dance02::state = dance02::WAIT_FRAME_6;
  case dance02::WAIT_FRAME_6:
    if(!isServoMultiMoving())
      dance02::state = dance02::FRAME_7;
    break;
  case dance02::FRAME_7:
    dance02_frm[4].playPositions(240);
    dance02::state = dance02::WAIT_FRAME_7;
  case dance02::WAIT_FRAME_7:
    if(!isServoMultiMoving())
      dance02::state = dance02::DELAY_8;
    break;
  case dance02::DELAY_8:
    dance02::time = millis();
    dance02::state = dance02::WAIT_DELAY_8;
  case dance02::WAIT_DELAY_8:
    if(millis() - dance02::time >= 240)
      dance02::state = dance02::FRAME_9;
    break;
  case dance02::FRAME_9:
    dance02_frm[5].playPositions(480);
    dance02::state = dance02::WAIT_FRAME_9;
  case dance02::WAIT_FRAME_9:
    if(!isServoMultiMoving())
      dance02::state = dance02::FRAME_10;
    break;
  case dance02::FRAME_10:
    dance02_frm[6].playPositions(240);
    dance02::state = dance02::WAIT_FRAME_10;
  case dance02::WAIT_FRAME_10:
    if(!isServoMultiMoving())
      dance02::state = dance02::DELAY_11;
    break;
  case dance02::DELAY_11:
    dance02::time = millis();
    dance02::state = dance02::WAIT_DELAY_11;
  case dance02::WAIT_DELAY_11:
    if(millis() - dance02::time >= 240)
      dance02::state = dance02::FRAME_12;
    break;
  case dance02::FRAME_12:
    dance02_frm[7].playPositions(480);
    dance02::state = dance02::WAIT_FRAME_12;
  case dance02::WAIT_FRAME_12:
    if(!isServoMultiMoving())
      dance02::state = dance02::GOTO_13;
    break;
  case dance02::GOTO_13:
    if(dance02::flag02_13++ < 1) goto flag_dance02_flag02_0;
    else
    {
      dance02::flag02_13 = 0;
      internal_trigger[_DANCE02] = false;
      external_trigger[_DANCE02] = false;
      dance02::state = dance02::IDLE;
    }
    break;
  default:
    break;
  }
}
void dance03Update()
{
  switch(dance03::state)
  {
  case dance03::IDLE:
    if(external_trigger[_DANCE03] || internal_trigger[_DANCE03]) dance03::state = dance03::FLAG_0;
    else break;
  case dance03::FLAG_0:
    flag_dance03_flag03_0:
  case dance03::FRAME_1:
    dance03_frm[0].playPositions(240);
    dance03::state = dance03::WAIT_FRAME_1;
  case dance03::WAIT_FRAME_1:
    if(!isServoMultiMoving())
      dance03::state = dance03::FRAME_2;
    break;
  case dance03::FRAME_2:
    dance03_frm[1].playPositions(240);
    dance03::state = dance03::WAIT_FRAME_2;
  case dance03::WAIT_FRAME_2:
    if(!isServoMultiMoving())
      dance03::state = dance03::FRAME_3;
    break;
  case dance03::FRAME_3:
    dance03_frm[2].playPositions(240);
    dance03::state = dance03::WAIT_FRAME_3;
  case dance03::WAIT_FRAME_3:
    if(!isServoMultiMoving())
      dance03::state = dance03::FRAME_4;
    break;
  case dance03::FRAME_4:
    dance03_frm[3].playPositions(240);
    dance03::state = dance03::WAIT_FRAME_4;
  case dance03::WAIT_FRAME_4:
    if(!isServoMultiMoving())
      dance03::state = dance03::GOTO_5;
    break;
  case dance03::GOTO_5:
    if(dance03::flag03_5++ < 2) goto flag_dance03_flag03_0;
    dance03::state = dance03::FRAME_6;
    break;
  case dance03::FRAME_6:
    dance03_frm[4].playPositions(240);
    dance03::state = dance03::WAIT_FRAME_6;
  case dance03::WAIT_FRAME_6:
    if(!isServoMultiMoving())
      dance03::state = dance03::FRAME_7;
    break;
  case dance03::FRAME_7:
    dance03_frm[5].playPositions(240);
    dance03::state = dance03::WAIT_FRAME_7;
  case dance03::WAIT_FRAME_7:
    if(!isServoMultiMoving())
      dance03::state = dance03::DELAY_8;
    break;
  case dance03::DELAY_8:
    dance03::time = millis();
    dance03::state = dance03::WAIT_DELAY_8;
  case dance03::WAIT_DELAY_8:
    if(millis() - dance03::time >= 480)
    {
      dance03::state = dance03::IDLE;
      dance03::flag03_5 = 0;
      internal_trigger[_DANCE03] = false;
      external_trigger[_DANCE03] = false;
    }
    break;
  default:
    break;
  }
}
void dance04Update()
{
  switch(dance04::state)
  {
  case dance04::IDLE:
    if(external_trigger[_DANCE04] || internal_trigger[_DANCE04]) dance04::state = dance04::FRAME_0;
    else break;
  case dance04::FRAME_0:
    dance04_frm[0].playPositions(240);
    dance04::state = dance04::WAIT_FRAME_0;
  case dance04::WAIT_FRAME_0:
    if(!isServoMultiMoving())
      dance04::state = dance04::FRAME_1;
    break;
  case dance04::FRAME_1:
    dance04_frm[1].playPositions(240);
    dance04::state = dance04::WAIT_FRAME_1;
  case dance04::WAIT_FRAME_1:
    if(!isServoMultiMoving())
      dance04::state = dance04::FRAME_2;
    break;
  case dance04::FRAME_2:
    dance04_frm[2].playPositions(240);
    dance04::state = dance04::WAIT_FRAME_2;
  case dance04::WAIT_FRAME_2:
    if(!isServoMultiMoving())
      dance04::state = dance04::FRAME_3;
    break;
  case dance04::FRAME_3:
    dance04_frm[3].playPositions(240);
    dance04::state = dance04::WAIT_FRAME_3;
  case dance04::WAIT_FRAME_3:
    if(!isServoMultiMoving())
      dance04::state = dance04::FRAME_4;
    break;
  case dance04::FRAME_4:
    dance04_frm[4].playPositions(240);
    dance04::state = dance04::WAIT_FRAME_4;
  case dance04::WAIT_FRAME_4:
    if(!isServoMultiMoving())
      dance04::state = dance04::FRAME_5;
    break;
  case dance04::FRAME_5:
    dance04_frm[5].playPositions(240);
    dance04::state = dance04::WAIT_FRAME_5;
  case dance04::WAIT_FRAME_5:
    if(!isServoMultiMoving())
      dance04::state = dance04::FRAME_6;
    break;
  case dance04::FRAME_6:
    dance04_frm[6].playPositions(240);
    dance04::state = dance04::WAIT_FRAME_6;
  case dance04::WAIT_FRAME_6:
    if(!isServoMultiMoving())
      dance04::state = dance04::FRAME_7;
    break;
  case dance04::FRAME_7:
    dance04_frm[7].playPositions(240);
    dance04::state = dance04::WAIT_FRAME_7;
  case dance04::WAIT_FRAME_7:
    if(!isServoMultiMoving())
      dance04::state = dance04::FRAME_8;
    break;
  case dance04::FRAME_8:
    dance04_frm[8].playPositions(240);
    dance04::state = dance04::WAIT_FRAME_8;
  case dance04::WAIT_FRAME_8:
    if(!isServoMultiMoving())
      dance04::state = dance04::FRAME_9;
    break;
  case dance04::FRAME_9:
    dance04_frm[9].playPositions(240);
    dance04::state = dance04::WAIT_FRAME_9;
  case dance04::WAIT_FRAME_9:
    if(!isServoMultiMoving())
      dance04::state = dance04::FRAME_10;
    break;
  case dance04::FRAME_10:
    dance04_frm[10].playPositions(240);
    dance04::state = dance04::WAIT_FRAME_10;
  case dance04::WAIT_FRAME_10:
    if(!isServoMultiMoving())
      dance04::state = dance04::FRAME_11;
    break;
  case dance04::FRAME_11:
    dance04_frm[11].playPositions(240);
    dance04::state = dance04::WAIT_FRAME_11;
  case dance04::WAIT_FRAME_11:
    if(!isServoMultiMoving())
      dance04::state = dance04::FRAME_12;
    break;
  case dance04::FRAME_12:
    dance04_frm[12].playPositions(240);
    dance04::state = dance04::WAIT_FRAME_12;
  case dance04::WAIT_FRAME_12:
    if(!isServoMultiMoving())
      dance04::state = dance04::DELAY_13;
    break;
  case dance04::DELAY_13:
    dance04::time = millis();
    dance04::state = dance04::WAIT_DELAY_13;
  case dance04::WAIT_DELAY_13:
    if(millis() - dance04::time >= 240)
      dance04::state = dance04::FRAME_14;
    break;
  case dance04::FRAME_14:
    dance04_frm[13].playPositions(240);
    dance04::state = dance04::WAIT_FRAME_14;
  case dance04::WAIT_FRAME_14:
    if(!isServoMultiMoving())
      dance04::state = dance04::FRAME_15;
    break;
  case dance04::FRAME_15:
    dance04_frm[14].playPositions(240);
    dance04::state = dance04::WAIT_FRAME_15;
  case dance04::WAIT_FRAME_15:
    if(!isServoMultiMoving())
    {
      dance04::state = dance04::IDLE;
      internal_trigger[_DANCE04] = false;
      external_trigger[_DANCE04] = false;
    }
    break;
  default:
    break;
  }
}
void dance05Update()
{
  switch(dance05::state)
  {
  case dance05::IDLE:
    if(external_trigger[_DANCE05] || internal_trigger[_DANCE05]) dance05::state = dance05::FLAG_0;
    else break;
  case dance05::FLAG_0:
    flag_dance05_flag05_0:
  case dance05::FRAME_1:
    dance05_frm[0].playPositions(240);
    dance05::state = dance05::WAIT_FRAME_1;
  case dance05::WAIT_FRAME_1:
    if(!isServoMultiMoving())
      dance05::state = dance05::FRAME_2;
    break;
  case dance05::FRAME_2:
    dance05_frm[1].playPositions(240);
    dance05::state = dance05::WAIT_FRAME_2;
  case dance05::WAIT_FRAME_2:
    if(!isServoMultiMoving())
      dance05::state = dance05::GOTO_3;
    break;
  case dance05::GOTO_3:
    if(dance05::flag05_3++ < 5) goto flag_dance05_flag05_0;
    dance05::state = dance05::FRAME_4;
    break;
  case dance05::FRAME_4:
    dance05_frm[2].playPositions(120);
    dance05::state = dance05::WAIT_FRAME_4;
  case dance05::WAIT_FRAME_4:
    if(!isServoMultiMoving())
      dance05::state = dance05::FRAME_5;
    break;
  case dance05::FRAME_5:
    dance05_frm[3].playPositions(240);
    dance05::state = dance05::WAIT_FRAME_5;
  case dance05::WAIT_FRAME_5:
    if(!isServoMultiMoving())
      dance05::state = dance05::DELAY_6;
    break;
  case dance05::DELAY_6:
    dance05::time = millis();
    dance05::state = dance05::WAIT_DELAY_6;
  case dance05::WAIT_DELAY_6:
    if(millis() - dance05::time >= 120)
      dance05::state = dance05::FRAME_7;
    break;
  case dance05::FRAME_7:
    dance05_frm[4].playPositions(120);
    dance05::state = dance05::WAIT_FRAME_7;
  case dance05::WAIT_FRAME_7:
    if(!isServoMultiMoving())
      dance05::state = dance05::FRAME_8;
    break;
  case dance05::FRAME_8:
    dance05_frm[5].playPositions(240);
    dance05::state = dance05::WAIT_FRAME_8;
  case dance05::WAIT_FRAME_8:
    if(!isServoMultiMoving())
      dance05::state = dance05::DELAY_9;
    break;
  case dance05::DELAY_9:
    dance05::time = millis();
    dance05::state = dance05::WAIT_DELAY_9;
  case dance05::WAIT_DELAY_9:
    if(millis() - dance05::time >= 120)
    {
      dance05::state = dance05::IDLE;
      dance05::flag05_3 = 0;
      internal_trigger[_DANCE05] = false;
      external_trigger[_DANCE05] = false;
    }
    break;
  default:
    break;
  }
}
void dance06Update()
{
  switch(dance06::state)
  {
  case dance06::IDLE:
    if(external_trigger[_DANCE06] || internal_trigger[_DANCE06]) dance06::state = dance06::DELAY_0;
    else break;
  case dance06::DELAY_0:
    dance06::time = millis();
    dance06::state = dance06::WAIT_DELAY_0;
  case dance06::WAIT_DELAY_0:
    if(millis() - dance06::time >= 480)
      dance06::state = dance06::FRAME_1;
    break;
  case dance06::FRAME_1:
    dance06_frm[0].playPositions(480);
    dance06::state = dance06::WAIT_FRAME_1;
  case dance06::WAIT_FRAME_1:
    if(!isServoMultiMoving())
      dance06::state = dance06::FLAG_2;
    break;
  case dance06::FLAG_2:
    flag_dance06_flag06_0:
  case dance06::FRAME_3:
    dance06_frm[1].playPositions(480);
    dance06::state = dance06::WAIT_FRAME_3;
  case dance06::WAIT_FRAME_3:
    if(!isServoMultiMoving())
      dance06::state = dance06::FRAME_4;
    break;
  case dance06::FRAME_4:
    dance06_frm[2].playPositions(480);
    dance06::state = dance06::WAIT_FRAME_4;
  case dance06::WAIT_FRAME_4:
    if(!isServoMultiMoving())
      dance06::state = dance06::GOTO_5;
    break;
  case dance06::GOTO_5:
    if(dance06::flag06_5++ < 2) goto flag_dance06_flag06_0;
    else
    {
      dance06::flag06_5 = 0;
      internal_trigger[_DANCE06] = false;
      external_trigger[_DANCE06] = false;
      dance06::state = dance06::IDLE;
    }
    break;
  default:
    break;
  }
}
void dance07Update()
{
  switch(dance07::state)
  {
  case dance07::IDLE:
    if(external_trigger[_DANCE07] || internal_trigger[_DANCE07]) dance07::state = dance07::FRAME_0;
    else break;
  case dance07::FRAME_0:
    dance07_frm[0].playPositions(120);
    dance07::state = dance07::WAIT_FRAME_0;
  case dance07::WAIT_FRAME_0:
    if(!isServoMultiMoving())
      dance07::state = dance07::FRAME_1;
    break;
  case dance07::FRAME_1:
    dance07_frm[1].playPositions(120);
    dance07::state = dance07::WAIT_FRAME_1;
  case dance07::WAIT_FRAME_1:
    if(!isServoMultiMoving())
      dance07::state = dance07::FRAME_2;
    break;
  case dance07::FRAME_2:
    dance07_frm[2].playPositions(120);
    dance07::state = dance07::WAIT_FRAME_2;
  case dance07::WAIT_FRAME_2:
    if(!isServoMultiMoving())
      dance07::state = dance07::FRAME_3;
    break;
  case dance07::FRAME_3:
    dance07_frm[3].playPositions(480);
    dance07::state = dance07::WAIT_FRAME_3;
  case dance07::WAIT_FRAME_3:
    if(!isServoMultiMoving())
      dance07::state = dance07::DELAY_4;
    break;
  case dance07::DELAY_4:
    dance07::time = millis();
    dance07::state = dance07::WAIT_DELAY_4;
  case dance07::WAIT_DELAY_4:
    if(millis() - dance07::time >= 240)
      dance07::state = dance07::FRAME_5;
    break;
  case dance07::FRAME_5:
    dance07_frm[4].playPositions(480);
    dance07::state = dance07::WAIT_FRAME_5;
  case dance07::WAIT_FRAME_5:
    if(!isServoMultiMoving())
      dance07::state = dance07::FRAME_6;
    break;
  case dance07::FRAME_6:
    dance07_frm[5].playPositions(120);
    dance07::state = dance07::WAIT_FRAME_6;
  case dance07::WAIT_FRAME_6:
    if(!isServoMultiMoving())
      dance07::state = dance07::FRAME_7;
    break;
  case dance07::FRAME_7:
    dance07_frm[6].playPositions(120);
    dance07::state = dance07::WAIT_FRAME_7;
  case dance07::WAIT_FRAME_7:
    if(!isServoMultiMoving())
      dance07::state = dance07::FRAME_8;
    break;
  case dance07::FRAME_8:
    dance07_frm[7].playPositions(120);
    dance07::state = dance07::WAIT_FRAME_8;
  case dance07::WAIT_FRAME_8:
    if(!isServoMultiMoving())
      dance07::state = dance07::FRAME_9;
    break;
  case dance07::FRAME_9:
    dance07_frm[8].playPositions(120);
    dance07::state = dance07::WAIT_FRAME_9;
  case dance07::WAIT_FRAME_9:
    if(!isServoMultiMoving())
      dance07::state = dance07::FRAME_10;
    break;
  case dance07::FRAME_10:
    dance07_frm[9].playPositions(120);
    dance07::state = dance07::WAIT_FRAME_10;
  case dance07::WAIT_FRAME_10:
    if(!isServoMultiMoving())
      dance07::state = dance07::FRAME_11;
    break;
  case dance07::FRAME_11:
    dance07_frm[10].playPositions(120);
    dance07::state = dance07::WAIT_FRAME_11;
  case dance07::WAIT_FRAME_11:
    if(!isServoMultiMoving())
      dance07::state = dance07::FRAME_12;
    break;
  case dance07::FRAME_12:
    dance07_frm[11].playPositions(480);
    dance07::state = dance07::WAIT_FRAME_12;
  case dance07::WAIT_FRAME_12:
    if(!isServoMultiMoving())
      dance07::state = dance07::DELAY_13;
    break;
  case dance07::DELAY_13:
    dance07::time = millis();
    dance07::state = dance07::WAIT_DELAY_13;
  case dance07::WAIT_DELAY_13:
    if(millis() - dance07::time >= 240)
      dance07::state = dance07::FRAME_14;
    break;
  case dance07::FRAME_14:
    dance07_frm[12].playPositions(480);
    dance07::state = dance07::WAIT_FRAME_14;
  case dance07::WAIT_FRAME_14:
    if(!isServoMultiMoving())
      dance07::state = dance07::FRAME_15;
    break;
  case dance07::FRAME_15:
    dance07_frm[13].playPositions(120);
    dance07::state = dance07::WAIT_FRAME_15;
  case dance07::WAIT_FRAME_15:
    if(!isServoMultiMoving())
      dance07::state = dance07::FRAME_16;
    break;
  case dance07::FRAME_16:
    dance07_frm[14].playPositions(120);
    dance07::state = dance07::WAIT_FRAME_16;
  case dance07::WAIT_FRAME_16:
    if(!isServoMultiMoving())
      dance07::state = dance07::FRAME_17;
    break;
  case dance07::FRAME_17:
    dance07_frm[15].playPositions(120);
    dance07::state = dance07::WAIT_FRAME_17;
  case dance07::WAIT_FRAME_17:
    if(!isServoMultiMoving())
    {
      dance07::state = dance07::IDLE;
      internal_trigger[_DANCE07] = false;
      external_trigger[_DANCE07] = false;
    }
    break;
  default:
    break;
  }
}
void dance08Update()
{
  switch(dance08::state)
  {
  case dance08::IDLE:
    if(external_trigger[_DANCE08] || internal_trigger[_DANCE08]) dance08::state = dance08::FRAME_0;
    else break;
  case dance08::FRAME_0:
    dance08_frm[0].playPositions(240);
    dance08::state = dance08::WAIT_FRAME_0;
  case dance08::WAIT_FRAME_0:
    if(!isServoMultiMoving())
      dance08::state = dance08::FRAME_1;
    break;
  case dance08::FRAME_1:
    dance08_frm[1].playPositions(360);
    dance08::state = dance08::WAIT_FRAME_1;
  case dance08::WAIT_FRAME_1:
    if(!isServoMultiMoving())
      dance08::state = dance08::FRAME_2;
    break;
  case dance08::FRAME_2:
    dance08_frm[2].playPositions(360);
    dance08::state = dance08::WAIT_FRAME_2;
  case dance08::WAIT_FRAME_2:
    if(!isServoMultiMoving())
      dance08::state = dance08::FRAME_3;
    break;
  case dance08::FRAME_3:
    dance08_frm[3].playPositions(240);
    dance08::state = dance08::WAIT_FRAME_3;
  case dance08::WAIT_FRAME_3:
    if(!isServoMultiMoving())
      dance08::state = dance08::FRAME_4;
    break;
  case dance08::FRAME_4:
    dance08_frm[4].playPositions(480);
    dance08::state = dance08::WAIT_FRAME_4;
  case dance08::WAIT_FRAME_4:
    if(!isServoMultiMoving())
      dance08::state = dance08::FRAME_5;
    break;
  case dance08::FRAME_5:
    dance08_frm[5].playPositions(240);
    dance08::state = dance08::WAIT_FRAME_5;
  case dance08::WAIT_FRAME_5:
    if(!isServoMultiMoving())
      dance08::state = dance08::FRAME_6;
    break;
  case dance08::FRAME_6:
    dance08_frm[6].playPositions(240);
    dance08::state = dance08::WAIT_FRAME_6;
  case dance08::WAIT_FRAME_6:
    if(!isServoMultiMoving())
      dance08::state = dance08::FRAME_7;
    break;
  case dance08::FRAME_7:
    dance08_frm[7].playPositions(360);
    dance08::state = dance08::WAIT_FRAME_7;
  case dance08::WAIT_FRAME_7:
    if(!isServoMultiMoving())
      dance08::state = dance08::FRAME_8;
    break;
  case dance08::FRAME_8:
    dance08_frm[8].playPositions(360);
    dance08::state = dance08::WAIT_FRAME_8;
  case dance08::WAIT_FRAME_8:
    if(!isServoMultiMoving())
      dance08::state = dance08::FRAME_9;
    break;
  case dance08::FRAME_9:
    dance08_frm[9].playPositions(240);
    dance08::state = dance08::WAIT_FRAME_9;
  case dance08::WAIT_FRAME_9:
    if(!isServoMultiMoving())
      dance08::state = dance08::FRAME_10;
    break;
  case dance08::FRAME_10:
    dance08_frm[10].playPositions(480);
    dance08::state = dance08::WAIT_FRAME_10;
  case dance08::WAIT_FRAME_10:
    if(!isServoMultiMoving())
      dance08::state = dance08::FRAME_11;
    break;
  case dance08::FRAME_11:
    dance08_frm[11].playPositions(240);
    dance08::state = dance08::WAIT_FRAME_11;
  case dance08::WAIT_FRAME_11:
    if(!isServoMultiMoving())
    {
      dance08::state = dance08::IDLE;
      internal_trigger[_DANCE08] = false;
      external_trigger[_DANCE08] = false;
    }
    break;
  default:
    break;
  }
}
void dance09Update()
{
  switch(dance09::state)
  {
  case dance09::IDLE:
    if(external_trigger[_DANCE09] || internal_trigger[_DANCE09]) dance09::state = dance09::FLAG_0;
    else break;
  case dance09::FLAG_0:
    flag_dance09_flag0902_0:
  case dance09::FRAME_1:
    dance09_frm[0].playPositions(240);
    dance09::state = dance09::WAIT_FRAME_1;
  case dance09::WAIT_FRAME_1:
    if(!isServoMultiMoving())
      dance09::state = dance09::FRAME_2;
    break;
  case dance09::FRAME_2:
    dance09_frm[1].playPositions(240);
    dance09::state = dance09::WAIT_FRAME_2;
  case dance09::WAIT_FRAME_2:
    if(!isServoMultiMoving())
      dance09::state = dance09::DELAY_3;
    break;
  case dance09::DELAY_3:
    dance09::time = millis();
    dance09::state = dance09::WAIT_DELAY_3;
  case dance09::WAIT_DELAY_3:
    if(millis() - dance09::time >= 480)
      dance09::state = dance09::FRAME_4;
    break;
  case dance09::FRAME_4:
    dance09_frm[2].playPositions(160);
    dance09::state = dance09::WAIT_FRAME_4;
  case dance09::WAIT_FRAME_4:
    if(!isServoMultiMoving())
      dance09::state = dance09::FRAME_5;
    break;
  case dance09::FRAME_5:
    dance09_frm[3].playPositions(160);
    dance09::state = dance09::WAIT_FRAME_5;
  case dance09::WAIT_FRAME_5:
    if(!isServoMultiMoving())
      dance09::state = dance09::FRAME_6;
    break;
  case dance09::FRAME_6:
    dance09_frm[4].playPositions(160);
    dance09::state = dance09::WAIT_FRAME_6;
  case dance09::WAIT_FRAME_6:
    if(!isServoMultiMoving())
      dance09::state = dance09::FRAME_7;
    break;
  case dance09::FRAME_7:
    dance09_frm[5].playPositions(160);
    dance09::state = dance09::WAIT_FRAME_7;
  case dance09::WAIT_FRAME_7:
    if(!isServoMultiMoving())
      dance09::state = dance09::FRAME_8;
    break;
  case dance09::FRAME_8:
    dance09_frm[6].playPositions(160);
    dance09::state = dance09::WAIT_FRAME_8;
  case dance09::WAIT_FRAME_8:
    if(!isServoMultiMoving())
      dance09::state = dance09::FRAME_9;
    break;
  case dance09::FRAME_9:
    dance09_frm[7].playPositions(160);
    dance09::state = dance09::WAIT_FRAME_9;
  case dance09::WAIT_FRAME_9:
    if(!isServoMultiMoving())
      dance09::state = dance09::GOTO_10;
    break;
  case dance09::GOTO_10:
    if(dance09::flag0902_10++ < 1) goto flag_dance09_flag0902_0;
    else
    {
      dance09::flag0902_10 = 0;
      internal_trigger[_DANCE09] = false;
      external_trigger[_DANCE09] = false;
      dance09::state = dance09::IDLE;
    }
    break;
  default:
    break;
  }
}
void dance10Update()
{
  switch(dance10::state)
  {
  case dance10::IDLE:
    if(external_trigger[_DANCE10] || internal_trigger[_DANCE10]) dance10::state = dance10::FRAME_0;
    else break;
  case dance10::FRAME_0:
    dance10_frm[0].playPositions(240);
    dance10::state = dance10::WAIT_FRAME_0;
  case dance10::WAIT_FRAME_0:
    if(!isServoMultiMoving())
      dance10::state = dance10::FRAME_1;
    break;
  case dance10::FRAME_1:
    dance10_frm[1].playPositions(240);
    dance10::state = dance10::WAIT_FRAME_1;
  case dance10::WAIT_FRAME_1:
    if(!isServoMultiMoving())
      dance10::state = dance10::FLAG_2;
    break;
  case dance10::FLAG_2:
    flag_dance10_flag10_0:
  case dance10::FRAME_3:
    dance10_frm[2].playPositions(240);
    dance10::state = dance10::WAIT_FRAME_3;
  case dance10::WAIT_FRAME_3:
    if(!isServoMultiMoving())
      dance10::state = dance10::FRAME_4;
    break;
  case dance10::FRAME_4:
    dance10_frm[3].playPositions(240);
    dance10::state = dance10::WAIT_FRAME_4;
  case dance10::WAIT_FRAME_4:
    if(!isServoMultiMoving())
      dance10::state = dance10::GOTO_5;
    break;
  case dance10::GOTO_5:
    if(dance10::flag10_5++ < 3) goto flag_dance10_flag10_0;
    dance10::state = dance10::FRAME_6;
    break;
  case dance10::FRAME_6:
    dance10_frm[4].playPositions(240);
    dance10::state = dance10::WAIT_FRAME_6;
  case dance10::WAIT_FRAME_6:
    if(!isServoMultiMoving())
      dance10::state = dance10::FRAME_7;
    break;
  case dance10::FRAME_7:
    dance10_frm[5].playPositions(240);
    dance10::state = dance10::WAIT_FRAME_7;
  case dance10::WAIT_FRAME_7:
    if(!isServoMultiMoving())
    {
      dance10::state = dance10::IDLE;
      dance10::flag10_5 = 0;
      internal_trigger[_DANCE10] = false;
      external_trigger[_DANCE10] = false;
    }
    break;
  default:
    break;
  }
}
void dance11Update()
{
  switch(dance11::state)
  {
  case dance11::IDLE:
    if(external_trigger[_DANCE11] || internal_trigger[_DANCE11]) dance11::state = dance11::FLAG_0;
    else break;
  case dance11::FLAG_0:
    flag_dance11_flag11_0:
  case dance11::FRAME_1:
    dance11_frm[0].playPositions(240);
    dance11::state = dance11::WAIT_FRAME_1;
  case dance11::WAIT_FRAME_1:
    if(!isServoMultiMoving())
      dance11::state = dance11::FRAME_2;
    break;
  case dance11::FRAME_2:
    dance11_frm[1].playPositions(240);
    dance11::state = dance11::WAIT_FRAME_2;
  case dance11::WAIT_FRAME_2:
    if(!isServoMultiMoving())
      dance11::state = dance11::GOTO_3;
    break;
  case dance11::GOTO_3:
    if(dance11::flag11_3++ < 4) goto flag_dance11_flag11_0;
    dance11::state = dance11::FRAME_4;
    break;
  case dance11::FRAME_4:
    dance11_frm[2].playPositions(480);
    dance11::state = dance11::WAIT_FRAME_4;
  case dance11::WAIT_FRAME_4:
    if(!isServoMultiMoving())
      dance11::state = dance11::FRAME_5;
    break;
  case dance11::FRAME_5:
    dance11_frm[3].playPositions(480);
    dance11::state = dance11::WAIT_FRAME_5;
  case dance11::WAIT_FRAME_5:
    if(!isServoMultiMoving())
      dance11::state = dance11::FRAME_6;
    break;
  case dance11::FRAME_6:
    dance11_frm[4].playPositions(480);
    dance11::state = dance11::WAIT_FRAME_6;
  case dance11::WAIT_FRAME_6:
    if(!isServoMultiMoving())
      dance11::state = dance11::FRAME_7;
    break;
  case dance11::FRAME_7:
    dance11_frm[5].playPositions(480);
    dance11::state = dance11::WAIT_FRAME_7;
  case dance11::WAIT_FRAME_7:
    if(!isServoMultiMoving())
      dance11::state = dance11::FRAME_8;
    break;
  case dance11::FRAME_8:
    dance11_frm[6].playPositions(240);
    dance11::state = dance11::WAIT_FRAME_8;
  case dance11::WAIT_FRAME_8:
    if(!isServoMultiMoving())
      dance11::state = dance11::FRAME_9;
    break;
  case dance11::FRAME_9:
    dance11_frm[7].playPositions(240);
    dance11::state = dance11::WAIT_FRAME_9;
  case dance11::WAIT_FRAME_9:
    if(!isServoMultiMoving())
    {
      dance11::state = dance11::IDLE;
      dance11::flag11_3 = 0;
      internal_trigger[_DANCE11] = false;
      external_trigger[_DANCE11] = false;
    }
    break;
  default:
    break;
  }
}
void dance12Update()
{
  switch(dance12::state)
  {
  case dance12::IDLE:
    if(external_trigger[_DANCE12] || internal_trigger[_DANCE12]) dance12::state = dance12::DELAY_0;
    else break;
  case dance12::DELAY_0:
    dance12::time = millis();
    dance12::state = dance12::WAIT_DELAY_0;
  case dance12::WAIT_DELAY_0:
    if(millis() - dance12::time >= 480)
      dance12::state = dance12::FRAME_1;
    break;
  case dance12::FRAME_1:
    dance12_frm[0].playPositions(240);
    dance12::state = dance12::WAIT_FRAME_1;
  case dance12::WAIT_FRAME_1:
    if(!isServoMultiMoving())
      dance12::state = dance12::FRAME_2;
    break;
  case dance12::FRAME_2:
    dance12_frm[1].playPositions(240);
    dance12::state = dance12::WAIT_FRAME_2;
  case dance12::WAIT_FRAME_2:
    if(!isServoMultiMoving())
      dance12::state = dance12::FRAME_3;
    break;
  case dance12::FRAME_3:
    dance12_frm[2].playPositions(120);
    dance12::state = dance12::WAIT_FRAME_3;
  case dance12::WAIT_FRAME_3:
    if(!isServoMultiMoving())
      dance12::state = dance12::DELAY_4;
    break;
  case dance12::DELAY_4:
    dance12::time = millis();
    dance12::state = dance12::WAIT_DELAY_4;
  case dance12::WAIT_DELAY_4:
    if(millis() - dance12::time >= 640)
      dance12::state = dance12::FRAME_5;
    break;
  case dance12::FRAME_5:
    dance12_frm[3].playPositions(120);
    dance12::state = dance12::WAIT_FRAME_5;
  case dance12::WAIT_FRAME_5:
    if(!isServoMultiMoving())
      dance12::state = dance12::FRAME_6;
    break;
  case dance12::FRAME_6:
    dance12_frm[4].playPositions(120);
    dance12::state = dance12::WAIT_FRAME_6;
  case dance12::WAIT_FRAME_6:
    if(!isServoMultiMoving())
      dance12::state = dance12::DELAY_7;
    break;
  case dance12::DELAY_7:
    dance12::time = millis();
    dance12::state = dance12::WAIT_DELAY_7;
  case dance12::WAIT_DELAY_7:
    if(millis() - dance12::time >= 1440)
      dance12::state = dance12::FRAME_8;
    break;
  case dance12::FRAME_8:
    dance12_frm[5].playPositions(240);
    dance12::state = dance12::WAIT_FRAME_8;
  case dance12::WAIT_FRAME_8:
    if(!isServoMultiMoving())
      dance12::state = dance12::FRAME_9;
    break;
  case dance12::FRAME_9:
    dance12_frm[6].playPositions(480);
    dance12::state = dance12::WAIT_FRAME_9;
  case dance12::WAIT_FRAME_9:
    if(!isServoMultiMoving())
      dance12::state = dance12::FRAME_10;
    break;
  case dance12::FRAME_10:
    dance12_frm[7].playPositions(240);
    dance12::state = dance12::WAIT_FRAME_10;
  case dance12::WAIT_FRAME_10:
    if(!isServoMultiMoving())
    {
      dance12::state = dance12::IDLE;
      internal_trigger[_DANCE12] = false;
      external_trigger[_DANCE12] = false;
    }
    break;
  default:
    break;
  }
}
void dance13Update()
{
  switch(dance13::state)
  {
  case dance13::IDLE:
    if(external_trigger[_DANCE13] || internal_trigger[_DANCE13]) dance13::state = dance13::FRAME_0;
    else break;
  case dance13::FRAME_0:
    dance13_frm[0].playPositions(240);
    dance13::state = dance13::WAIT_FRAME_0;
  case dance13::WAIT_FRAME_0:
    if(!isServoMultiMoving())
      dance13::state = dance13::FRAME_1;
    break;
  case dance13::FRAME_1:
    dance13_frm[1].playPositions(240);
    dance13::state = dance13::WAIT_FRAME_1;
  case dance13::WAIT_FRAME_1:
    if(!isServoMultiMoving())
      dance13::state = dance13::FRAME_2;
    break;
  case dance13::FRAME_2:
    dance13_frm[2].playPositions(240);
    dance13::state = dance13::WAIT_FRAME_2;
  case dance13::WAIT_FRAME_2:
    if(!isServoMultiMoving())
      dance13::state = dance13::FRAME_3;
    break;
  case dance13::FRAME_3:
    dance13_frm[3].playPositions(240);
    dance13::state = dance13::WAIT_FRAME_3;
  case dance13::WAIT_FRAME_3:
    if(!isServoMultiMoving())
      dance13::state = dance13::FRAME_4;
    break;
  case dance13::FRAME_4:
    dance13_frm[4].playPositions(240);
    dance13::state = dance13::WAIT_FRAME_4;
  case dance13::WAIT_FRAME_4:
    if(!isServoMultiMoving())
      dance13::state = dance13::FRAME_5;
    break;
  case dance13::FRAME_5:
    dance13_frm[5].playPositions(240);
    dance13::state = dance13::WAIT_FRAME_5;
  case dance13::WAIT_FRAME_5:
    if(!isServoMultiMoving())
      dance13::state = dance13::FRAME_6;
    break;
  case dance13::FRAME_6:
    dance13_frm[6].playPositions(240);
    dance13::state = dance13::WAIT_FRAME_6;
  case dance13::WAIT_FRAME_6:
    if(!isServoMultiMoving())
      dance13::state = dance13::FRAME_7;
    break;
  case dance13::FRAME_7:
    dance13_frm[7].playPositions(240);
    dance13::state = dance13::WAIT_FRAME_7;
  case dance13::WAIT_FRAME_7:
    if(!isServoMultiMoving())
      dance13::state = dance13::FRAME_8;
    break;
  case dance13::FRAME_8:
    dance13_frm[8].playPositions(240);
    dance13::state = dance13::WAIT_FRAME_8;
  case dance13::WAIT_FRAME_8:
    if(!isServoMultiMoving())
      dance13::state = dance13::FRAME_9;
    break;
  case dance13::FRAME_9:
    dance13_frm[9].playPositions(240);
    dance13::state = dance13::WAIT_FRAME_9;
  case dance13::WAIT_FRAME_9:
    if(!isServoMultiMoving())
      dance13::state = dance13::FRAME_10;
    break;
  case dance13::FRAME_10:
    dance13_frm[10].playPositions(240);
    dance13::state = dance13::WAIT_FRAME_10;
  case dance13::WAIT_FRAME_10:
    if(!isServoMultiMoving())
      dance13::state = dance13::FRAME_11;
    break;
  case dance13::FRAME_11:
    dance13_frm[11].playPositions(240);
    dance13::state = dance13::WAIT_FRAME_11;
  case dance13::WAIT_FRAME_11:
    if(!isServoMultiMoving())
      dance13::state = dance13::FRAME_12;
    break;
  case dance13::FRAME_12:
    dance13_frm[12].playPositions(240);
    dance13::state = dance13::WAIT_FRAME_12;
  case dance13::WAIT_FRAME_12:
    if(!isServoMultiMoving())
      dance13::state = dance13::FRAME_13;
    break;
  case dance13::FRAME_13:
    dance13_frm[13].playPositions(240);
    dance13::state = dance13::WAIT_FRAME_13;
  case dance13::WAIT_FRAME_13:
    if(!isServoMultiMoving())
    {
      dance13::state = dance13::IDLE;
      internal_trigger[_DANCE13] = false;
      external_trigger[_DANCE13] = false;
    }
    break;
  default:
    break;
  }
}
void dance14Update()
{
  switch(dance14::state)
  {
  case dance14::IDLE:
    if(external_trigger[_DANCE14] || internal_trigger[_DANCE14]) dance14::state = dance14::FRAME_0;
    else break;
  case dance14::FRAME_0:
    dance14_frm[0].playPositions(480);
    dance14::state = dance14::WAIT_FRAME_0;
  case dance14::WAIT_FRAME_0:
    if(!isServoMultiMoving())
      dance14::state = dance14::FRAME_1;
    break;
  case dance14::FRAME_1:
    dance14_frm[1].playPositions(480);
    dance14::state = dance14::WAIT_FRAME_1;
  case dance14::WAIT_FRAME_1:
    if(!isServoMultiMoving())
      dance14::state = dance14::FLAG_2;
    break;
  case dance14::FLAG_2:
    flag_dance14_flag14_0:
  case dance14::FRAME_3:
    dance14_frm[2].playPositions(480);
    dance14::state = dance14::WAIT_FRAME_3;
  case dance14::WAIT_FRAME_3:
    if(!isServoMultiMoving())
      dance14::state = dance14::FRAME_4;
    break;
  case dance14::FRAME_4:
    dance14_frm[3].playPositions(480);
    dance14::state = dance14::WAIT_FRAME_4;
  case dance14::WAIT_FRAME_4:
    if(!isServoMultiMoving())
      dance14::state = dance14::GOTO_5;
    break;
  case dance14::GOTO_5:
    if(dance14::flag14_5++ < 2) goto flag_dance14_flag14_0;
    else
    {
      dance14::flag14_5 = 0;
      internal_trigger[_DANCE14] = false;
      external_trigger[_DANCE14] = false;
      dance14::state = dance14::IDLE;
    }
    break;
  default:
    break;
  }
}
void danceALLUpdate()
{
  switch(danceALL::state)
  {
  case danceALL::IDLE:
    if(external_trigger[_DANCEALL] || internal_trigger[_DANCEALL]) danceALL::state = danceALL::DELAY_0;
    else break;
  case danceALL::DELAY_0:
    danceALL::time = millis();
    danceALL::state = danceALL::WAIT_DELAY_0;
  case danceALL::WAIT_DELAY_0:
    if(millis() - danceALL::time >= 1920)
      danceALL::state = danceALL::MOTION_1;
    break;
  case danceALL::MOTION_1:
    dance01::flag01_4 = 0;
    danceALL::state = danceALL::WAIT_MOTION_1;
    internal_trigger[_DANCE01] = true;
    dance01::state = dance01::IDLE;
  case danceALL::WAIT_MOTION_1:
    if(!internal_trigger[_DANCE01])
      danceALL::state = danceALL::MOTION_2;
    break;
  case danceALL::MOTION_2:
    dance02::flag02_13 = 0;
    danceALL::state = danceALL::WAIT_MOTION_2;
    internal_trigger[_DANCE02] = true;
    dance02::state = dance02::IDLE;
  case danceALL::WAIT_MOTION_2:
    if(!internal_trigger[_DANCE02])
      danceALL::state = danceALL::MOTION_3;
    break;
  case danceALL::MOTION_3:
    dance03::flag03_5 = 0;
    danceALL::state = danceALL::WAIT_MOTION_3;
    internal_trigger[_DANCE03] = true;
    dance03::state = dance03::IDLE;
  case danceALL::WAIT_MOTION_3:
    if(!internal_trigger[_DANCE03])
      danceALL::state = danceALL::MOTION_4;
    break;
  case danceALL::MOTION_4:
    danceALL::state = danceALL::WAIT_MOTION_4;
    internal_trigger[_DANCE04] = true;
    dance04::state = dance04::IDLE;
  case danceALL::WAIT_MOTION_4:
    if(!internal_trigger[_DANCE04])
      danceALL::state = danceALL::MOTION_5;
    break;
  case danceALL::MOTION_5:
    dance05::flag05_3 = 0;
    danceALL::state = danceALL::WAIT_MOTION_5;
    internal_trigger[_DANCE05] = true;
    dance05::state = dance05::IDLE;
  case danceALL::WAIT_MOTION_5:
    if(!internal_trigger[_DANCE05])
      danceALL::state = danceALL::MOTION_6;
    break;
  case danceALL::MOTION_6:
    dance06::flag06_5 = 0;
    danceALL::state = danceALL::WAIT_MOTION_6;
    internal_trigger[_DANCE06] = true;
    dance06::state = dance06::IDLE;
  case danceALL::WAIT_MOTION_6:
    if(!internal_trigger[_DANCE06])
      danceALL::state = danceALL::MOTION_7;
    break;
  case danceALL::MOTION_7:
    danceALL::state = danceALL::WAIT_MOTION_7;
    internal_trigger[_DANCE07] = true;
    dance07::state = dance07::IDLE;
  case danceALL::WAIT_MOTION_7:
    if(!internal_trigger[_DANCE07])
      danceALL::state = danceALL::MOTION_8;
    break;
  case danceALL::MOTION_8:
    danceALL::state = danceALL::WAIT_MOTION_8;
    internal_trigger[_DANCE08] = true;
    dance08::state = dance08::IDLE;
  case danceALL::WAIT_MOTION_8:
    if(!internal_trigger[_DANCE08])
      danceALL::state = danceALL::MOTION_9;
    break;
  case danceALL::MOTION_9:
    dance09::flag0902_10 = 0;
    danceALL::state = danceALL::WAIT_MOTION_9;
    internal_trigger[_DANCE09] = true;
    dance09::state = dance09::IDLE;
  case danceALL::WAIT_MOTION_9:
    if(!internal_trigger[_DANCE09])
      danceALL::state = danceALL::MOTION_10;
    break;
  case danceALL::MOTION_10:
    dance10::flag10_5 = 0;
    danceALL::state = danceALL::WAIT_MOTION_10;
    internal_trigger[_DANCE10] = true;
    dance10::state = dance10::IDLE;
  case danceALL::WAIT_MOTION_10:
    if(!internal_trigger[_DANCE10])
      danceALL::state = danceALL::MOTION_11;
    break;
  case danceALL::MOTION_11:
    dance11::flag11_3 = 0;
    danceALL::state = danceALL::WAIT_MOTION_11;
    internal_trigger[_DANCE11] = true;
    dance11::state = dance11::IDLE;
  case danceALL::WAIT_MOTION_11:
    if(!internal_trigger[_DANCE11])
      danceALL::state = danceALL::MOTION_12;
    break;
  case danceALL::MOTION_12:
    danceALL::state = danceALL::WAIT_MOTION_12;
    internal_trigger[_DANCE12] = true;
    dance12::state = dance12::IDLE;
  case danceALL::WAIT_MOTION_12:
    if(!internal_trigger[_DANCE12])
      danceALL::state = danceALL::MOTION_13;
    break;
  case danceALL::MOTION_13:
    danceALL::state = danceALL::WAIT_MOTION_13;
    internal_trigger[_DANCE13] = true;
    dance13::state = dance13::IDLE;
  case danceALL::WAIT_MOTION_13:
    if(!internal_trigger[_DANCE13])
      danceALL::state = danceALL::DELAY_14;
    break;
  case danceALL::DELAY_14:
    danceALL::time = millis();
    danceALL::state = danceALL::WAIT_DELAY_14;
  case danceALL::WAIT_DELAY_14:
    if(millis() - danceALL::time >= 1920)
      danceALL::state = danceALL::MOTION_15;
    break;
  case danceALL::MOTION_15:
    dance01::flag01_4 = 0;
    danceALL::state = danceALL::WAIT_MOTION_15;
    internal_trigger[_DANCE01] = true;
    dance01::state = dance01::IDLE;
  case danceALL::WAIT_MOTION_15:
    if(!internal_trigger[_DANCE01])
      danceALL::state = danceALL::MOTION_16;
    break;
  case danceALL::MOTION_16:
    dance02::flag02_13 = 0;
    danceALL::state = danceALL::WAIT_MOTION_16;
    internal_trigger[_DANCE02] = true;
    dance02::state = dance02::IDLE;
  case danceALL::WAIT_MOTION_16:
    if(!internal_trigger[_DANCE02])
      danceALL::state = danceALL::MOTION_17;
    break;
  case danceALL::MOTION_17:
    dance03::flag03_5 = 0;
    danceALL::state = danceALL::WAIT_MOTION_17;
    internal_trigger[_DANCE03] = true;
    dance03::state = dance03::IDLE;
  case danceALL::WAIT_MOTION_17:
    if(!internal_trigger[_DANCE03])
      danceALL::state = danceALL::MOTION_18;
    break;
  case danceALL::MOTION_18:
    danceALL::state = danceALL::WAIT_MOTION_18;
    internal_trigger[_DANCE04] = true;
    dance04::state = dance04::IDLE;
  case danceALL::WAIT_MOTION_18:
    if(!internal_trigger[_DANCE04])
      danceALL::state = danceALL::MOTION_19;
    break;
  case danceALL::MOTION_19:
    dance05::flag05_3 = 0;
    danceALL::state = danceALL::WAIT_MOTION_19;
    internal_trigger[_DANCE05] = true;
    dance05::state = dance05::IDLE;
  case danceALL::WAIT_MOTION_19:
    if(!internal_trigger[_DANCE05])
      danceALL::state = danceALL::MOTION_20;
    break;
  case danceALL::MOTION_20:
    dance06::flag06_5 = 0;
    danceALL::state = danceALL::WAIT_MOTION_20;
    internal_trigger[_DANCE06] = true;
    dance06::state = dance06::IDLE;
  case danceALL::WAIT_MOTION_20:
    if(!internal_trigger[_DANCE06])
      danceALL::state = danceALL::MOTION_21;
    break;
  case danceALL::MOTION_21:
    danceALL::state = danceALL::WAIT_MOTION_21;
    internal_trigger[_DANCE07] = true;
    dance07::state = dance07::IDLE;
  case danceALL::WAIT_MOTION_21:
    if(!internal_trigger[_DANCE07])
      danceALL::state = danceALL::MOTION_22;
    break;
  case danceALL::MOTION_22:
    danceALL::state = danceALL::WAIT_MOTION_22;
    internal_trigger[_DANCE08] = true;
    dance08::state = dance08::IDLE;
  case danceALL::WAIT_MOTION_22:
    if(!internal_trigger[_DANCE08])
      danceALL::state = danceALL::MOTION_23;
    break;
  case danceALL::MOTION_23:
    dance09::flag0902_10 = 0;
    danceALL::state = danceALL::WAIT_MOTION_23;
    internal_trigger[_DANCE09] = true;
    dance09::state = dance09::IDLE;
  case danceALL::WAIT_MOTION_23:
    if(!internal_trigger[_DANCE09])
      danceALL::state = danceALL::MOTION_24;
    break;
  case danceALL::MOTION_24:
    dance10::flag10_5 = 0;
    danceALL::state = danceALL::WAIT_MOTION_24;
    internal_trigger[_DANCE10] = true;
    dance10::state = dance10::IDLE;
  case danceALL::WAIT_MOTION_24:
    if(!internal_trigger[_DANCE10])
      danceALL::state = danceALL::MOTION_25;
    break;
  case danceALL::MOTION_25:
    dance11::flag11_3 = 0;
    danceALL::state = danceALL::WAIT_MOTION_25;
    internal_trigger[_DANCE11] = true;
    dance11::state = dance11::IDLE;
  case danceALL::WAIT_MOTION_25:
    if(!internal_trigger[_DANCE11])
      danceALL::state = danceALL::MOTION_26;
    break;
  case danceALL::MOTION_26:
    danceALL::state = danceALL::WAIT_MOTION_26;
    internal_trigger[_DANCE12] = true;
    dance12::state = dance12::IDLE;
  case danceALL::WAIT_MOTION_26:
    if(!internal_trigger[_DANCE12])
      danceALL::state = danceALL::MOTION_27;
    break;
  case danceALL::MOTION_27:
    danceALL::state = danceALL::WAIT_MOTION_27;
    internal_trigger[_DANCE13] = true;
    dance13::state = dance13::IDLE;
  case danceALL::WAIT_MOTION_27:
    if(!internal_trigger[_DANCE13])
      danceALL::state = danceALL::MOTION_28;
    break;
  case danceALL::MOTION_28:
    dance01::flag01_4 = 0;
    danceALL::state = danceALL::WAIT_MOTION_28;
    internal_trigger[_DANCE01] = true;
    dance01::state = dance01::IDLE;
  case danceALL::WAIT_MOTION_28:
    if(!internal_trigger[_DANCE01])
      danceALL::state = danceALL::MOTION_29;
    break;
  case danceALL::MOTION_29:
    dance02::flag02_13 = 0;
    danceALL::state = danceALL::WAIT_MOTION_29;
    internal_trigger[_DANCE02] = true;
    dance02::state = dance02::IDLE;
  case danceALL::WAIT_MOTION_29:
    if(!internal_trigger[_DANCE02])
      danceALL::state = danceALL::MOTION_30;
    break;
  case danceALL::MOTION_30:
    dance03::flag03_5 = 0;
    danceALL::state = danceALL::WAIT_MOTION_30;
    internal_trigger[_DANCE03] = true;
    dance03::state = dance03::IDLE;
  case danceALL::WAIT_MOTION_30:
    if(!internal_trigger[_DANCE03])
      danceALL::state = danceALL::MOTION_31;
    break;
  case danceALL::MOTION_31:
    danceALL::state = danceALL::WAIT_MOTION_31;
    internal_trigger[_DANCE04] = true;
    dance04::state = dance04::IDLE;
  case danceALL::WAIT_MOTION_31:
    if(!internal_trigger[_DANCE04])
      danceALL::state = danceALL::MOTION_32;
    break;
  case danceALL::MOTION_32:
    dance05::flag05_3 = 0;
    danceALL::state = danceALL::WAIT_MOTION_32;
    internal_trigger[_DANCE05] = true;
    dance05::state = dance05::IDLE;
  case danceALL::WAIT_MOTION_32:
    if(!internal_trigger[_DANCE05])
      danceALL::state = danceALL::MOTION_33;
    break;
  case danceALL::MOTION_33:
    dance14::flag14_5 = 0;
    danceALL::state = danceALL::WAIT_MOTION_33;
    internal_trigger[_DANCE14] = true;
    dance14::state = dance14::IDLE;
  case danceALL::WAIT_MOTION_33:
    if(!internal_trigger[_DANCE14])
    {
      danceALL::state = danceALL::IDLE;
      internal_trigger[_DANCEALL] = false;
      external_trigger[_DANCEALL] = false;
    }
    break;
  default:
    break;
  }
}
void setup()
{
  io_outpb(0x0A12,0x00); //enable COM1 TX pin
  io_outpb(0x0A13,0x00); //enable COM1 RX pin
  io_outpb(0x0A20,0x02); //SPICS to RX
  io_outpb(0x0A22,0x01); //SPIDI to DX
  nh.getHardware()->setESP8266(Serial1, 115200);
  nh.getHardware()->setWiFi("RoBoardGod", "00000000");
  nh.initNode("10.0.0.1");	//ROS-Host IP address
  nh.subscribe(sub);
#ifdef __86DUINO_ZERO	//Choose your correct 86Duino version when you upload
  myservo2.attach(2);
  myservo3.attach(3);
  myservo4.attach(4);
  myservo5.attach(5);
  myservo6.attach(6);
  myservo7.attach(7);
  myservo8.attach(8);
  myservo9.attach(9);
  myservo10.attach(10);
  myservo11.attach(11);
  myservo12.attach(12);
  myservo13.attach(13);
#endif
#ifdef __86DUINO_ONE
  myservo2.attach(38);
  myservo3.attach(37);
  myservo4.attach(36);
  myservo5.attach(35);
  myservo6.attach(33);
  myservo7.attach(32);
  myservo8.attach(31);
  myservo9.attach(30);
  myservo10.attach(28);
  myservo11.attach(27);
  myservo12.attach(26);
  myservo13.attach(25);
#endif


  END_frm[0].positions[0] = 1500;
  END_frm[0].positions[1] = 1200;
  END_frm[0].positions[2] = 1300;
  END_frm[0].positions[3] = 1400;
  END_frm[0].positions[4] = 1500;
  END_frm[0].positions[5] = 1800;
  END_frm[0].positions[6] = 1500;
  END_frm[0].positions[7] = 1200;
  END_frm[0].positions[8] = 1600;
  END_frm[0].positions[9] = 1400;
  END_frm[0].positions[10] = 1500;
  END_frm[0].positions[11] = 1800;

  END_frm[1].positions[0] = 1500;
  END_frm[1].positions[1] = 1800;
  END_frm[1].positions[2] = 1300;
  END_frm[1].positions[3] = 1400;
  END_frm[1].positions[4] = 1500;
  END_frm[1].positions[5] = 1800;
  END_frm[1].positions[6] = 1500;
  END_frm[1].positions[7] = 1800;
  END_frm[1].positions[8] = 1600;
  END_frm[1].positions[9] = 1400;
  END_frm[1].positions[10] = 1500;
  END_frm[1].positions[11] = 1800;

  home_frm[0].positions[0] = 1500;
  home_frm[0].positions[1] = 1500;
  home_frm[0].positions[2] = 1500;
  home_frm[0].positions[3] = 1500;
  home_frm[0].positions[4] = 1500;
  home_frm[0].positions[5] = 1500;
  home_frm[0].positions[6] = 1500;
  home_frm[0].positions[7] = 1500;
  home_frm[0].positions[8] = 1500;
  home_frm[0].positions[9] = 1500;
  home_frm[0].positions[10] = 1500;
  home_frm[0].positions[11] = 1500;

  forward_frm[0].positions[0] = 1700;
  forward_frm[0].positions[1] = 1500;
  forward_frm[0].positions[2] = 1300;
  forward_frm[0].positions[3] = 1750;
  forward_frm[0].positions[4] = 1700;
  forward_frm[0].positions[5] = 1500;
  forward_frm[0].positions[6] = 1700;
  forward_frm[0].positions[7] = 1750;
  forward_frm[0].positions[8] = 1300;
  forward_frm[0].positions[9] = 1500;
  forward_frm[0].positions[10] = 1700;
  forward_frm[0].positions[11] = 1750;

  forward_frm[1].positions[0] = 1700;
  forward_frm[1].positions[1] = 1500;
  forward_frm[1].positions[2] = 1300;
  forward_frm[1].positions[3] = 1500;
  forward_frm[1].positions[4] = 1700;
  forward_frm[1].positions[5] = 1500;
  forward_frm[1].positions[6] = 1700;
  forward_frm[1].positions[7] = 1500;
  forward_frm[1].positions[8] = 1300;
  forward_frm[1].positions[9] = 1500;
  forward_frm[1].positions[10] = 1700;
  forward_frm[1].positions[11] = 1500;

  forward_frm[2].positions[0] = 1700;
  forward_frm[2].positions[1] = 1750;
  forward_frm[2].positions[2] = 1300;
  forward_frm[2].positions[3] = 1500;
  forward_frm[2].positions[4] = 1700;
  forward_frm[2].positions[5] = 1750;
  forward_frm[2].positions[6] = 1700;
  forward_frm[2].positions[7] = 1500;
  forward_frm[2].positions[8] = 1300;
  forward_frm[2].positions[9] = 1750;
  forward_frm[2].positions[10] = 1700;
  forward_frm[2].positions[11] = 1500;

  forward_frm[3].positions[0] = 1300;
  forward_frm[3].positions[1] = 1750;
  forward_frm[3].positions[2] = 1700;
  forward_frm[3].positions[3] = 1500;
  forward_frm[3].positions[4] = 1300;
  forward_frm[3].positions[5] = 1750;
  forward_frm[3].positions[6] = 1300;
  forward_frm[3].positions[7] = 1500;
  forward_frm[3].positions[8] = 1700;
  forward_frm[3].positions[9] = 1750;
  forward_frm[3].positions[10] = 1300;
  forward_frm[3].positions[11] = 1500;

  forward_frm[4].positions[0] = 1300;
  forward_frm[4].positions[1] = 1500;
  forward_frm[4].positions[2] = 1700;
  forward_frm[4].positions[3] = 1500;
  forward_frm[4].positions[4] = 1300;
  forward_frm[4].positions[5] = 1500;
  forward_frm[4].positions[6] = 1300;
  forward_frm[4].positions[7] = 1500;
  forward_frm[4].positions[8] = 1700;
  forward_frm[4].positions[9] = 1500;
  forward_frm[4].positions[10] = 1300;
  forward_frm[4].positions[11] = 1500;

  forward_frm[5].positions[0] = 1300;
  forward_frm[5].positions[1] = 1500;
  forward_frm[5].positions[2] = 1700;
  forward_frm[5].positions[3] = 1750;
  forward_frm[5].positions[4] = 1300;
  forward_frm[5].positions[5] = 1500;
  forward_frm[5].positions[6] = 1300;
  forward_frm[5].positions[7] = 1750;
  forward_frm[5].positions[8] = 1700;
  forward_frm[5].positions[9] = 1500;
  forward_frm[5].positions[10] = 1300;
  forward_frm[5].positions[11] = 1750;

  left_frm[0].positions[0] = 1700;
  left_frm[0].positions[1] = 1750;
  left_frm[0].positions[2] = 1300;
  left_frm[0].positions[3] = 1500;
  left_frm[0].positions[4] = 1700;
  left_frm[0].positions[5] = 1750;
  left_frm[0].positions[6] = 1300;
  left_frm[0].positions[7] = 1500;
  left_frm[0].positions[8] = 1700;
  left_frm[0].positions[9] = 1750;
  left_frm[0].positions[10] = 1300;
  left_frm[0].positions[11] = 1500;

  left_frm[1].positions[0] = 1700;
  left_frm[1].positions[1] = 1500;
  left_frm[1].positions[2] = 1300;
  left_frm[1].positions[3] = 1500;
  left_frm[1].positions[4] = 1700;
  left_frm[1].positions[5] = 1500;
  left_frm[1].positions[6] = 1300;
  left_frm[1].positions[7] = 1500;
  left_frm[1].positions[8] = 1700;
  left_frm[1].positions[9] = 1500;
  left_frm[1].positions[10] = 1300;
  left_frm[1].positions[11] = 1500;

  left_frm[2].positions[0] = 1700;
  left_frm[2].positions[1] = 1500;
  left_frm[2].positions[2] = 1300;
  left_frm[2].positions[3] = 1750;
  left_frm[2].positions[4] = 1700;
  left_frm[2].positions[5] = 1500;
  left_frm[2].positions[6] = 1300;
  left_frm[2].positions[7] = 1750;
  left_frm[2].positions[8] = 1700;
  left_frm[2].positions[9] = 1500;
  left_frm[2].positions[10] = 1300;
  left_frm[2].positions[11] = 1750;

  left_frm[3].positions[0] = 1300;
  left_frm[3].positions[1] = 1500;
  left_frm[3].positions[2] = 1700;
  left_frm[3].positions[3] = 1750;
  left_frm[3].positions[4] = 1300;
  left_frm[3].positions[5] = 1500;
  left_frm[3].positions[6] = 1700;
  left_frm[3].positions[7] = 1750;
  left_frm[3].positions[8] = 1300;
  left_frm[3].positions[9] = 1500;
  left_frm[3].positions[10] = 1700;
  left_frm[3].positions[11] = 1750;

  left_frm[4].positions[0] = 1300;
  left_frm[4].positions[1] = 1500;
  left_frm[4].positions[2] = 1700;
  left_frm[4].positions[3] = 1500;
  left_frm[4].positions[4] = 1300;
  left_frm[4].positions[5] = 1500;
  left_frm[4].positions[6] = 1700;
  left_frm[4].positions[7] = 1500;
  left_frm[4].positions[8] = 1300;
  left_frm[4].positions[9] = 1500;
  left_frm[4].positions[10] = 1700;
  left_frm[4].positions[11] = 1500;

  left_frm[5].positions[0] = 1300;
  left_frm[5].positions[1] = 1750;
  left_frm[5].positions[2] = 1700;
  left_frm[5].positions[3] = 1500;
  left_frm[5].positions[4] = 1300;
  left_frm[5].positions[5] = 1750;
  left_frm[5].positions[6] = 1700;
  left_frm[5].positions[7] = 1500;
  left_frm[5].positions[8] = 1300;
  left_frm[5].positions[9] = 1750;
  left_frm[5].positions[10] = 1700;
  left_frm[5].positions[11] = 1500;

  right_frm[0].positions[0] = 1300;
  right_frm[0].positions[1] = 1750;
  right_frm[0].positions[2] = 1700;
  right_frm[0].positions[3] = 1500;
  right_frm[0].positions[4] = 1300;
  right_frm[0].positions[5] = 1750;
  right_frm[0].positions[6] = 1700;
  right_frm[0].positions[7] = 1500;
  right_frm[0].positions[8] = 1300;
  right_frm[0].positions[9] = 1750;
  right_frm[0].positions[10] = 1700;
  right_frm[0].positions[11] = 1500;

  right_frm[1].positions[0] = 1300;
  right_frm[1].positions[1] = 1500;
  right_frm[1].positions[2] = 1700;
  right_frm[1].positions[3] = 1500;
  right_frm[1].positions[4] = 1300;
  right_frm[1].positions[5] = 1500;
  right_frm[1].positions[6] = 1700;
  right_frm[1].positions[7] = 1500;
  right_frm[1].positions[8] = 1300;
  right_frm[1].positions[9] = 1500;
  right_frm[1].positions[10] = 1700;
  right_frm[1].positions[11] = 1500;

  right_frm[2].positions[0] = 1300;
  right_frm[2].positions[1] = 1500;
  right_frm[2].positions[2] = 1700;
  right_frm[2].positions[3] = 1750;
  right_frm[2].positions[4] = 1300;
  right_frm[2].positions[5] = 1500;
  right_frm[2].positions[6] = 1700;
  right_frm[2].positions[7] = 1750;
  right_frm[2].positions[8] = 1300;
  right_frm[2].positions[9] = 1500;
  right_frm[2].positions[10] = 1700;
  right_frm[2].positions[11] = 1750;

  right_frm[3].positions[0] = 1700;
  right_frm[3].positions[1] = 1500;
  right_frm[3].positions[2] = 1300;
  right_frm[3].positions[3] = 1750;
  right_frm[3].positions[4] = 1700;
  right_frm[3].positions[5] = 1500;
  right_frm[3].positions[6] = 1300;
  right_frm[3].positions[7] = 1750;
  right_frm[3].positions[8] = 1700;
  right_frm[3].positions[9] = 1500;
  right_frm[3].positions[10] = 1300;
  right_frm[3].positions[11] = 1750;

  right_frm[4].positions[0] = 1700;
  right_frm[4].positions[1] = 1500;
  right_frm[4].positions[2] = 1300;
  right_frm[4].positions[3] = 1500;
  right_frm[4].positions[4] = 1700;
  right_frm[4].positions[5] = 1500;
  right_frm[4].positions[6] = 1300;
  right_frm[4].positions[7] = 1500;
  right_frm[4].positions[8] = 1700;
  right_frm[4].positions[9] = 1500;
  right_frm[4].positions[10] = 1300;
  right_frm[4].positions[11] = 1500;

  right_frm[5].positions[0] = 1700;
  right_frm[5].positions[1] = 1750;
  right_frm[5].positions[2] = 1300;
  right_frm[5].positions[3] = 1500;
  right_frm[5].positions[4] = 1700;
  right_frm[5].positions[5] = 1750;
  right_frm[5].positions[6] = 1300;
  right_frm[5].positions[7] = 1500;
  right_frm[5].positions[8] = 1700;
  right_frm[5].positions[9] = 1750;
  right_frm[5].positions[10] = 1300;
  right_frm[5].positions[11] = 1500;

  idle_frm[0].positions[0] = 1500;
  idle_frm[0].positions[1] = 1600;
  idle_frm[0].positions[2] = 1500;
  idle_frm[0].positions[3] = 1600;
  idle_frm[0].positions[4] = 1500;
  idle_frm[0].positions[5] = 1600;
  idle_frm[0].positions[6] = 1500;
  idle_frm[0].positions[7] = 1600;
  idle_frm[0].positions[8] = 1500;
  idle_frm[0].positions[9] = 1600;
  idle_frm[0].positions[10] = 1500;
  idle_frm[0].positions[11] = 1600;

  idle_frm[1].positions[0] = 1500;
  idle_frm[1].positions[1] = 1400;
  idle_frm[1].positions[2] = 1500;
  idle_frm[1].positions[3] = 1400;
  idle_frm[1].positions[4] = 1500;
  idle_frm[1].positions[5] = 1400;
  idle_frm[1].positions[6] = 1500;
  idle_frm[1].positions[7] = 1400;
  idle_frm[1].positions[8] = 1500;
  idle_frm[1].positions[9] = 1400;
  idle_frm[1].positions[10] = 1500;
  idle_frm[1].positions[11] = 1400;

  title_frm[0].positions[0] = 1729;
  title_frm[0].positions[1] = 1950;
  title_frm[0].positions[2] = 1500;
  title_frm[0].positions[3] = 1500;
  title_frm[0].positions[4] = 1500;
  title_frm[0].positions[5] = 1500;
  title_frm[0].positions[6] = 1500;
  title_frm[0].positions[7] = 1500;
  title_frm[0].positions[8] = 1500;
  title_frm[0].positions[9] = 1500;
  title_frm[0].positions[10] = 1500;
  title_frm[0].positions[11] = 1500;

  title_frm[1].positions[0] = 1381;
  title_frm[1].positions[1] = 1950;
  title_frm[1].positions[2] = 1500;
  title_frm[1].positions[3] = 1500;
  title_frm[1].positions[4] = 1500;
  title_frm[1].positions[5] = 1500;
  title_frm[1].positions[6] = 1500;
  title_frm[1].positions[7] = 1500;
  title_frm[1].positions[8] = 1500;
  title_frm[1].positions[9] = 1500;
  title_frm[1].positions[10] = 1500;
  title_frm[1].positions[11] = 1500;

  title_frm[2].positions[0] = 1500;
  title_frm[2].positions[1] = 1500;
  title_frm[2].positions[2] = 1500;
  title_frm[2].positions[3] = 1500;
  title_frm[2].positions[4] = 1500;
  title_frm[2].positions[5] = 1500;
  title_frm[2].positions[6] = 1500;
  title_frm[2].positions[7] = 1500;
  title_frm[2].positions[8] = 1500;
  title_frm[2].positions[9] = 1500;
  title_frm[2].positions[10] = 1500;
  title_frm[2].positions[11] = 1500;

  dance01_frm[0].positions[0] = 1500;
  dance01_frm[0].positions[1] = 1700;
  dance01_frm[0].positions[2] = 1500;
  dance01_frm[0].positions[3] = 1700;
  dance01_frm[0].positions[4] = 1500;
  dance01_frm[0].positions[5] = 1700;
  dance01_frm[0].positions[6] = 1500;
  dance01_frm[0].positions[7] = 1700;
  dance01_frm[0].positions[8] = 1500;
  dance01_frm[0].positions[9] = 1700;
  dance01_frm[0].positions[10] = 1500;
  dance01_frm[0].positions[11] = 1700;

  dance01_frm[1].positions[0] = 1500;
  dance01_frm[1].positions[1] = 1500;
  dance01_frm[1].positions[2] = 1500;
  dance01_frm[1].positions[3] = 1500;
  dance01_frm[1].positions[4] = 1500;
  dance01_frm[1].positions[5] = 1500;
  dance01_frm[1].positions[6] = 1500;
  dance01_frm[1].positions[7] = 1500;
  dance01_frm[1].positions[8] = 1500;
  dance01_frm[1].positions[9] = 1500;
  dance01_frm[1].positions[10] = 1500;
  dance01_frm[1].positions[11] = 1500;

  dance02_frm[0].positions[0] = 1500;
  dance02_frm[0].positions[1] = 1700;
  dance02_frm[0].positions[2] = 1500;
  dance02_frm[0].positions[3] = 1700;
  dance02_frm[0].positions[4] = 1500;
  dance02_frm[0].positions[5] = 1700;
  dance02_frm[0].positions[6] = 1500;
  dance02_frm[0].positions[7] = 1300;
  dance02_frm[0].positions[8] = 1500;
  dance02_frm[0].positions[9] = 1200;
  dance02_frm[0].positions[10] = 1500;
  dance02_frm[0].positions[11] = 1300;

  dance02_frm[1].positions[0] = 1500;
  dance02_frm[1].positions[1] = 1500;
  dance02_frm[1].positions[2] = 1500;
  dance02_frm[1].positions[3] = 1500;
  dance02_frm[1].positions[4] = 1500;
  dance02_frm[1].positions[5] = 1500;
  dance02_frm[1].positions[6] = 1500;
  dance02_frm[1].positions[7] = 1500;
  dance02_frm[1].positions[8] = 1500;
  dance02_frm[1].positions[9] = 1500;
  dance02_frm[1].positions[10] = 1500;
  dance02_frm[1].positions[11] = 1500;

  dance02_frm[2].positions[0] = 1500;
  dance02_frm[2].positions[1] = 1200;
  dance02_frm[2].positions[2] = 1500;
  dance02_frm[2].positions[3] = 1300;
  dance02_frm[2].positions[4] = 1500;
  dance02_frm[2].positions[5] = 1200;
  dance02_frm[2].positions[6] = 1500;
  dance02_frm[2].positions[7] = 1700;
  dance02_frm[2].positions[8] = 1500;
  dance02_frm[2].positions[9] = 1700;
  dance02_frm[2].positions[10] = 1500;
  dance02_frm[2].positions[11] = 1700;

  dance02_frm[3].positions[0] = 1500;
  dance02_frm[3].positions[1] = 1500;
  dance02_frm[3].positions[2] = 1500;
  dance02_frm[3].positions[3] = 1500;
  dance02_frm[3].positions[4] = 1500;
  dance02_frm[3].positions[5] = 1500;
  dance02_frm[3].positions[6] = 1500;
  dance02_frm[3].positions[7] = 1500;
  dance02_frm[3].positions[8] = 1500;
  dance02_frm[3].positions[9] = 1500;
  dance02_frm[3].positions[10] = 1500;
  dance02_frm[3].positions[11] = 1500;

  dance02_frm[4].positions[0] = 1500;
  dance02_frm[4].positions[1] = 1200;
  dance02_frm[4].positions[2] = 1500;
  dance02_frm[4].positions[3] = 1500;
  dance02_frm[4].positions[4] = 1500;
  dance02_frm[4].positions[5] = 1700;
  dance02_frm[4].positions[6] = 1500;
  dance02_frm[4].positions[7] = 1200;
  dance02_frm[4].positions[8] = 1500;
  dance02_frm[4].positions[9] = 1500;
  dance02_frm[4].positions[10] = 1500;
  dance02_frm[4].positions[11] = 1700;

  dance02_frm[5].positions[0] = 1500;
  dance02_frm[5].positions[1] = 1500;
  dance02_frm[5].positions[2] = 1500;
  dance02_frm[5].positions[3] = 1500;
  dance02_frm[5].positions[4] = 1500;
  dance02_frm[5].positions[5] = 1500;
  dance02_frm[5].positions[6] = 1500;
  dance02_frm[5].positions[7] = 1500;
  dance02_frm[5].positions[8] = 1500;
  dance02_frm[5].positions[9] = 1500;
  dance02_frm[5].positions[10] = 1500;
  dance02_frm[5].positions[11] = 1500;

  dance02_frm[6].positions[0] = 1500;
  dance02_frm[6].positions[1] = 1200;
  dance02_frm[6].positions[2] = 1500;
  dance02_frm[6].positions[3] = 1500;
  dance02_frm[6].positions[4] = 1500;
  dance02_frm[6].positions[5] = 1700;
  dance02_frm[6].positions[6] = 1500;
  dance02_frm[6].positions[7] = 1200;
  dance02_frm[6].positions[8] = 1500;
  dance02_frm[6].positions[9] = 1500;
  dance02_frm[6].positions[10] = 1500;
  dance02_frm[6].positions[11] = 1700;

  dance02_frm[7].positions[0] = 1500;
  dance02_frm[7].positions[1] = 1500;
  dance02_frm[7].positions[2] = 1500;
  dance02_frm[7].positions[3] = 1500;
  dance02_frm[7].positions[4] = 1500;
  dance02_frm[7].positions[5] = 1500;
  dance02_frm[7].positions[6] = 1500;
  dance02_frm[7].positions[7] = 1500;
  dance02_frm[7].positions[8] = 1500;
  dance02_frm[7].positions[9] = 1500;
  dance02_frm[7].positions[10] = 1500;
  dance02_frm[7].positions[11] = 1500;

  dance03_frm[0].positions[0] = 1500;
  dance03_frm[0].positions[1] = 1600;
  dance03_frm[0].positions[2] = 1500;
  dance03_frm[0].positions[3] = 1650;
  dance03_frm[0].positions[4] = 1500;
  dance03_frm[0].positions[5] = 1600;
  dance03_frm[0].positions[6] = 1300;
  dance03_frm[0].positions[7] = 1700;
  dance03_frm[0].positions[8] = 1500;
  dance03_frm[0].positions[9] = 1200;
  dance03_frm[0].positions[10] = 1500;
  dance03_frm[0].positions[11] = 1300;

  dance03_frm[1].positions[0] = 1500;
  dance03_frm[1].positions[1] = 1600;
  dance03_frm[1].positions[2] = 1500;
  dance03_frm[1].positions[3] = 1650;
  dance03_frm[1].positions[4] = 1500;
  dance03_frm[1].positions[5] = 1600;
  dance03_frm[1].positions[6] = 1700;
  dance03_frm[1].positions[7] = 1700;
  dance03_frm[1].positions[8] = 1500;
  dance03_frm[1].positions[9] = 1200;
  dance03_frm[1].positions[10] = 1500;
  dance03_frm[1].positions[11] = 1300;

  dance03_frm[2].positions[0] = 1500;
  dance03_frm[2].positions[1] = 1200;
  dance03_frm[2].positions[2] = 1500;
  dance03_frm[2].positions[3] = 1300;
  dance03_frm[2].positions[4] = 1500;
  dance03_frm[2].positions[5] = 1200;
  dance03_frm[2].positions[6] = 1300;
  dance03_frm[2].positions[7] = 1800;
  dance03_frm[2].positions[8] = 1500;
  dance03_frm[2].positions[9] = 1650;
  dance03_frm[2].positions[10] = 1500;
  dance03_frm[2].positions[11] = 1600;

  dance03_frm[3].positions[0] = 1500;
  dance03_frm[3].positions[1] = 1200;
  dance03_frm[3].positions[2] = 1500;
  dance03_frm[3].positions[3] = 1300;
  dance03_frm[3].positions[4] = 1500;
  dance03_frm[3].positions[5] = 1200;
  dance03_frm[3].positions[6] = 1700;
  dance03_frm[3].positions[7] = 1800;
  dance03_frm[3].positions[8] = 1500;
  dance03_frm[3].positions[9] = 1650;
  dance03_frm[3].positions[10] = 1500;
  dance03_frm[3].positions[11] = 1600;

  dance03_frm[4].positions[0] = 1500;
  dance03_frm[4].positions[1] = 1500;
  dance03_frm[4].positions[2] = 1500;
  dance03_frm[4].positions[3] = 1500;
  dance03_frm[4].positions[4] = 1500;
  dance03_frm[4].positions[5] = 1500;
  dance03_frm[4].positions[6] = 1500;
  dance03_frm[4].positions[7] = 1500;
  dance03_frm[4].positions[8] = 1500;
  dance03_frm[4].positions[9] = 1500;
  dance03_frm[4].positions[10] = 1500;
  dance03_frm[4].positions[11] = 1500;

  dance03_frm[5].positions[0] = 1500;
  dance03_frm[5].positions[1] = 1200;
  dance03_frm[5].positions[2] = 1500;
  dance03_frm[5].positions[3] = 1500;
  dance03_frm[5].positions[4] = 1500;
  dance03_frm[5].positions[5] = 1700;
  dance03_frm[5].positions[6] = 1500;
  dance03_frm[5].positions[7] = 1200;
  dance03_frm[5].positions[8] = 1500;
  dance03_frm[5].positions[9] = 1500;
  dance03_frm[5].positions[10] = 1500;
  dance03_frm[5].positions[11] = 1700;

  dance04_frm[0].positions[0] = 1500;
  dance04_frm[0].positions[1] = 1600;
  dance04_frm[0].positions[2] = 1500;
  dance04_frm[0].positions[3] = 1650;
  dance04_frm[0].positions[4] = 1500;
  dance04_frm[0].positions[5] = 1600;
  dance04_frm[0].positions[6] = 1500;
  dance04_frm[0].positions[7] = 1700;
  dance04_frm[0].positions[8] = 1500;
  dance04_frm[0].positions[9] = 1200;
  dance04_frm[0].positions[10] = 1500;
  dance04_frm[0].positions[11] = 1300;

  dance04_frm[1].positions[0] = 1500;
  dance04_frm[1].positions[1] = 1600;
  dance04_frm[1].positions[2] = 1500;
  dance04_frm[1].positions[3] = 1650;
  dance04_frm[1].positions[4] = 1500;
  dance04_frm[1].positions[5] = 1600;
  dance04_frm[1].positions[6] = 1500;
  dance04_frm[1].positions[7] = 1300;
  dance04_frm[1].positions[8] = 1500;
  dance04_frm[1].positions[9] = 1700;
  dance04_frm[1].positions[10] = 1500;
  dance04_frm[1].positions[11] = 1300;

  dance04_frm[2].positions[0] = 1500;
  dance04_frm[2].positions[1] = 1600;
  dance04_frm[2].positions[2] = 1500;
  dance04_frm[2].positions[3] = 1650;
  dance04_frm[2].positions[4] = 1500;
  dance04_frm[2].positions[5] = 1600;
  dance04_frm[2].positions[6] = 1500;
  dance04_frm[2].positions[7] = 1300;
  dance04_frm[2].positions[8] = 1500;
  dance04_frm[2].positions[9] = 1200;
  dance04_frm[2].positions[10] = 1500;
  dance04_frm[2].positions[11] = 1700;

  dance04_frm[3].positions[0] = 1500;
  dance04_frm[3].positions[1] = 1600;
  dance04_frm[3].positions[2] = 1500;
  dance04_frm[3].positions[3] = 1650;
  dance04_frm[3].positions[4] = 1500;
  dance04_frm[3].positions[5] = 1600;
  dance04_frm[3].positions[6] = 1500;
  dance04_frm[3].positions[7] = 1300;
  dance04_frm[3].positions[8] = 1500;
  dance04_frm[3].positions[9] = 1200;
  dance04_frm[3].positions[10] = 1500;
  dance04_frm[3].positions[11] = 1300;

  dance04_frm[4].positions[0] = 1500;
  dance04_frm[4].positions[1] = 1300;
  dance04_frm[4].positions[2] = 1500;
  dance04_frm[4].positions[3] = 1200;
  dance04_frm[4].positions[4] = 1500;
  dance04_frm[4].positions[5] = 1700;
  dance04_frm[4].positions[6] = 1500;
  dance04_frm[4].positions[7] = 1600;
  dance04_frm[4].positions[8] = 1500;
  dance04_frm[4].positions[9] = 1650;
  dance04_frm[4].positions[10] = 1500;
  dance04_frm[4].positions[11] = 1600;

  dance04_frm[5].positions[0] = 1500;
  dance04_frm[5].positions[1] = 1300;
  dance04_frm[5].positions[2] = 1500;
  dance04_frm[5].positions[3] = 1700;
  dance04_frm[5].positions[4] = 1500;
  dance04_frm[5].positions[5] = 1300;
  dance04_frm[5].positions[6] = 1500;
  dance04_frm[5].positions[7] = 1600;
  dance04_frm[5].positions[8] = 1500;
  dance04_frm[5].positions[9] = 1650;
  dance04_frm[5].positions[10] = 1500;
  dance04_frm[5].positions[11] = 1600;

  dance04_frm[6].positions[0] = 1500;
  dance04_frm[6].positions[1] = 1700;
  dance04_frm[6].positions[2] = 1500;
  dance04_frm[6].positions[3] = 1200;
  dance04_frm[6].positions[4] = 1500;
  dance04_frm[6].positions[5] = 1300;
  dance04_frm[6].positions[6] = 1500;
  dance04_frm[6].positions[7] = 1600;
  dance04_frm[6].positions[8] = 1500;
  dance04_frm[6].positions[9] = 1650;
  dance04_frm[6].positions[10] = 1500;
  dance04_frm[6].positions[11] = 1600;

  dance04_frm[7].positions[0] = 1500;
  dance04_frm[7].positions[1] = 1300;
  dance04_frm[7].positions[2] = 1500;
  dance04_frm[7].positions[3] = 1200;
  dance04_frm[7].positions[4] = 1500;
  dance04_frm[7].positions[5] = 1300;
  dance04_frm[7].positions[6] = 1500;
  dance04_frm[7].positions[7] = 1600;
  dance04_frm[7].positions[8] = 1500;
  dance04_frm[7].positions[9] = 1650;
  dance04_frm[7].positions[10] = 1500;
  dance04_frm[7].positions[11] = 1600;

  dance04_frm[8].positions[0] = 1500;
  dance04_frm[8].positions[1] = 1600;
  dance04_frm[8].positions[2] = 1500;
  dance04_frm[8].positions[3] = 1650;
  dance04_frm[8].positions[4] = 1500;
  dance04_frm[8].positions[5] = 1600;
  dance04_frm[8].positions[6] = 1500;
  dance04_frm[8].positions[7] = 1700;
  dance04_frm[8].positions[8] = 1500;
  dance04_frm[8].positions[9] = 1200;
  dance04_frm[8].positions[10] = 1500;
  dance04_frm[8].positions[11] = 1300;

  dance04_frm[9].positions[0] = 1500;
  dance04_frm[9].positions[1] = 1600;
  dance04_frm[9].positions[2] = 1500;
  dance04_frm[9].positions[3] = 1650;
  dance04_frm[9].positions[4] = 1500;
  dance04_frm[9].positions[5] = 1600;
  dance04_frm[9].positions[6] = 1500;
  dance04_frm[9].positions[7] = 1300;
  dance04_frm[9].positions[8] = 1500;
  dance04_frm[9].positions[9] = 1700;
  dance04_frm[9].positions[10] = 1500;
  dance04_frm[9].positions[11] = 1300;

  dance04_frm[10].positions[0] = 1500;
  dance04_frm[10].positions[1] = 1600;
  dance04_frm[10].positions[2] = 1500;
  dance04_frm[10].positions[3] = 1650;
  dance04_frm[10].positions[4] = 1500;
  dance04_frm[10].positions[5] = 1600;
  dance04_frm[10].positions[6] = 1500;
  dance04_frm[10].positions[7] = 1300;
  dance04_frm[10].positions[8] = 1500;
  dance04_frm[10].positions[9] = 1200;
  dance04_frm[10].positions[10] = 1500;
  dance04_frm[10].positions[11] = 1700;

  dance04_frm[11].positions[0] = 1500;
  dance04_frm[11].positions[1] = 1500;
  dance04_frm[11].positions[2] = 1500;
  dance04_frm[11].positions[3] = 1500;
  dance04_frm[11].positions[4] = 1500;
  dance04_frm[11].positions[5] = 1500;
  dance04_frm[11].positions[6] = 1500;
  dance04_frm[11].positions[7] = 1900;
  dance04_frm[11].positions[8] = 1500;
  dance04_frm[11].positions[9] = 1500;
  dance04_frm[11].positions[10] = 1500;
  dance04_frm[11].positions[11] = 1500;

  dance04_frm[12].positions[0] = 1500;
  dance04_frm[12].positions[1] = 1500;
  dance04_frm[12].positions[2] = 1500;
  dance04_frm[12].positions[3] = 1500;
  dance04_frm[12].positions[4] = 1500;
  dance04_frm[12].positions[5] = 1500;
  dance04_frm[12].positions[6] = 1900;
  dance04_frm[12].positions[7] = 1900;
  dance04_frm[12].positions[8] = 1500;
  dance04_frm[12].positions[9] = 1500;
  dance04_frm[12].positions[10] = 1500;
  dance04_frm[12].positions[11] = 1500;

  dance04_frm[13].positions[0] = 1500;
  dance04_frm[13].positions[1] = 1900;
  dance04_frm[13].positions[2] = 1500;
  dance04_frm[13].positions[3] = 1500;
  dance04_frm[13].positions[4] = 1500;
  dance04_frm[13].positions[5] = 1500;
  dance04_frm[13].positions[6] = 1500;
  dance04_frm[13].positions[7] = 1500;
  dance04_frm[13].positions[8] = 1500;
  dance04_frm[13].positions[9] = 1500;
  dance04_frm[13].positions[10] = 1500;
  dance04_frm[13].positions[11] = 1500;

  dance04_frm[14].positions[0] = 1100;
  dance04_frm[14].positions[1] = 1900;
  dance04_frm[14].positions[2] = 1500;
  dance04_frm[14].positions[3] = 1500;
  dance04_frm[14].positions[4] = 1500;
  dance04_frm[14].positions[5] = 1500;
  dance04_frm[14].positions[6] = 1500;
  dance04_frm[14].positions[7] = 1500;
  dance04_frm[14].positions[8] = 1500;
  dance04_frm[14].positions[9] = 1500;
  dance04_frm[14].positions[10] = 1500;
  dance04_frm[14].positions[11] = 1500;

  dance05_frm[0].positions[0] = 1500;
  dance05_frm[0].positions[1] = 1100;
  dance05_frm[0].positions[2] = 1500;
  dance05_frm[0].positions[3] = 1500;
  dance05_frm[0].positions[4] = 1500;
  dance05_frm[0].positions[5] = 1100;
  dance05_frm[0].positions[6] = 1500;
  dance05_frm[0].positions[7] = 1500;
  dance05_frm[0].positions[8] = 1500;
  dance05_frm[0].positions[9] = 1900;
  dance05_frm[0].positions[10] = 1500;
  dance05_frm[0].positions[11] = 1500;

  dance05_frm[1].positions[0] = 1500;
  dance05_frm[1].positions[1] = 1500;
  dance05_frm[1].positions[2] = 1500;
  dance05_frm[1].positions[3] = 1900;
  dance05_frm[1].positions[4] = 1500;
  dance05_frm[1].positions[5] = 1500;
  dance05_frm[1].positions[6] = 1500;
  dance05_frm[1].positions[7] = 1100;
  dance05_frm[1].positions[8] = 1500;
  dance05_frm[1].positions[9] = 1500;
  dance05_frm[1].positions[10] = 1500;
  dance05_frm[1].positions[11] = 1100;

  dance05_frm[2].positions[0] = 1500;
  dance05_frm[2].positions[1] = 1500;
  dance05_frm[2].positions[2] = 1500;
  dance05_frm[2].positions[3] = 1500;
  dance05_frm[2].positions[4] = 1500;
  dance05_frm[2].positions[5] = 1500;
  dance05_frm[2].positions[6] = 1500;
  dance05_frm[2].positions[7] = 1900;
  dance05_frm[2].positions[8] = 1500;
  dance05_frm[2].positions[9] = 1500;
  dance05_frm[2].positions[10] = 1500;
  dance05_frm[2].positions[11] = 1500;

  dance05_frm[3].positions[0] = 1500;
  dance05_frm[3].positions[1] = 1500;
  dance05_frm[3].positions[2] = 1500;
  dance05_frm[3].positions[3] = 1500;
  dance05_frm[3].positions[4] = 1500;
  dance05_frm[3].positions[5] = 1500;
  dance05_frm[3].positions[6] = 1900;
  dance05_frm[3].positions[7] = 1900;
  dance05_frm[3].positions[8] = 1500;
  dance05_frm[3].positions[9] = 1500;
  dance05_frm[3].positions[10] = 1500;
  dance05_frm[3].positions[11] = 1500;

  dance05_frm[4].positions[0] = 1500;
  dance05_frm[4].positions[1] = 1900;
  dance05_frm[4].positions[2] = 1500;
  dance05_frm[4].positions[3] = 1500;
  dance05_frm[4].positions[4] = 1500;
  dance05_frm[4].positions[5] = 1500;
  dance05_frm[4].positions[6] = 1500;
  dance05_frm[4].positions[7] = 1500;
  dance05_frm[4].positions[8] = 1500;
  dance05_frm[4].positions[9] = 1500;
  dance05_frm[4].positions[10] = 1500;
  dance05_frm[4].positions[11] = 1500;

  dance05_frm[5].positions[0] = 1100;
  dance05_frm[5].positions[1] = 1900;
  dance05_frm[5].positions[2] = 1500;
  dance05_frm[5].positions[3] = 1500;
  dance05_frm[5].positions[4] = 1500;
  dance05_frm[5].positions[5] = 1500;
  dance05_frm[5].positions[6] = 1500;
  dance05_frm[5].positions[7] = 1500;
  dance05_frm[5].positions[8] = 1500;
  dance05_frm[5].positions[9] = 1500;
  dance05_frm[5].positions[10] = 1500;
  dance05_frm[5].positions[11] = 1500;

  dance06_frm[0].positions[0] = 1500;
  dance06_frm[0].positions[1] = 1500;
  dance06_frm[0].positions[2] = 1500;
  dance06_frm[0].positions[3] = 1500;
  dance06_frm[0].positions[4] = 1500;
  dance06_frm[0].positions[5] = 1500;
  dance06_frm[0].positions[6] = 1500;
  dance06_frm[0].positions[7] = 1500;
  dance06_frm[0].positions[8] = 1500;
  dance06_frm[0].positions[9] = 1500;
  dance06_frm[0].positions[10] = 1500;
  dance06_frm[0].positions[11] = 1500;

  dance06_frm[1].positions[0] = 1500;
  dance06_frm[1].positions[1] = 1700;
  dance06_frm[1].positions[2] = 1500;
  dance06_frm[1].positions[3] = 1700;
  dance06_frm[1].positions[4] = 1500;
  dance06_frm[1].positions[5] = 1700;
  dance06_frm[1].positions[6] = 1500;
  dance06_frm[1].positions[7] = 1700;
  dance06_frm[1].positions[8] = 1500;
  dance06_frm[1].positions[9] = 1700;
  dance06_frm[1].positions[10] = 1500;
  dance06_frm[1].positions[11] = 1700;

  dance06_frm[2].positions[0] = 1500;
  dance06_frm[2].positions[1] = 1500;
  dance06_frm[2].positions[2] = 1500;
  dance06_frm[2].positions[3] = 1500;
  dance06_frm[2].positions[4] = 1500;
  dance06_frm[2].positions[5] = 1500;
  dance06_frm[2].positions[6] = 1500;
  dance06_frm[2].positions[7] = 1500;
  dance06_frm[2].positions[8] = 1500;
  dance06_frm[2].positions[9] = 1500;
  dance06_frm[2].positions[10] = 1500;
  dance06_frm[2].positions[11] = 1500;

  dance07_frm[0].positions[0] = 1500;
  dance07_frm[0].positions[1] = 1800;
  dance07_frm[0].positions[2] = 1500;
  dance07_frm[0].positions[3] = 1500;
  dance07_frm[0].positions[4] = 1500;
  dance07_frm[0].positions[5] = 1800;
  dance07_frm[0].positions[6] = 1500;
  dance07_frm[0].positions[7] = 1500;
  dance07_frm[0].positions[8] = 1500;
  dance07_frm[0].positions[9] = 1800;
  dance07_frm[0].positions[10] = 1500;
  dance07_frm[0].positions[11] = 1500;

  dance07_frm[1].positions[0] = 1800;
  dance07_frm[1].positions[1] = 1500;
  dance07_frm[1].positions[2] = 1500;
  dance07_frm[1].positions[3] = 1500;
  dance07_frm[1].positions[4] = 1800;
  dance07_frm[1].positions[5] = 1500;
  dance07_frm[1].positions[6] = 1500;
  dance07_frm[1].positions[7] = 1500;
  dance07_frm[1].positions[8] = 1800;
  dance07_frm[1].positions[9] = 1500;
  dance07_frm[1].positions[10] = 1500;
  dance07_frm[1].positions[11] = 1500;

  dance07_frm[2].positions[0] = 1800;
  dance07_frm[2].positions[1] = 1500;
  dance07_frm[2].positions[2] = 1500;
  dance07_frm[2].positions[3] = 1800;
  dance07_frm[2].positions[4] = 1800;
  dance07_frm[2].positions[5] = 1500;
  dance07_frm[2].positions[6] = 1500;
  dance07_frm[2].positions[7] = 1800;
  dance07_frm[2].positions[8] = 1800;
  dance07_frm[2].positions[9] = 1500;
  dance07_frm[2].positions[10] = 1500;
  dance07_frm[2].positions[11] = 1800;

  dance07_frm[3].positions[0] = 1200;
  dance07_frm[3].positions[1] = 1500;
  dance07_frm[3].positions[2] = 1500;
  dance07_frm[3].positions[3] = 1800;
  dance07_frm[3].positions[4] = 1200;
  dance07_frm[3].positions[5] = 1500;
  dance07_frm[3].positions[6] = 1500;
  dance07_frm[3].positions[7] = 1800;
  dance07_frm[3].positions[8] = 1200;
  dance07_frm[3].positions[9] = 1500;
  dance07_frm[3].positions[10] = 1500;
  dance07_frm[3].positions[11] = 1800;

  dance07_frm[4].positions[0] = 1800;
  dance07_frm[4].positions[1] = 1500;
  dance07_frm[4].positions[2] = 1500;
  dance07_frm[4].positions[3] = 1800;
  dance07_frm[4].positions[4] = 1800;
  dance07_frm[4].positions[5] = 1500;
  dance07_frm[4].positions[6] = 1500;
  dance07_frm[4].positions[7] = 1800;
  dance07_frm[4].positions[8] = 1800;
  dance07_frm[4].positions[9] = 1500;
  dance07_frm[4].positions[10] = 1500;
  dance07_frm[4].positions[11] = 1800;

  dance07_frm[5].positions[0] = 1800;
  dance07_frm[5].positions[1] = 1500;
  dance07_frm[5].positions[2] = 1500;
  dance07_frm[5].positions[3] = 1500;
  dance07_frm[5].positions[4] = 1800;
  dance07_frm[5].positions[5] = 1500;
  dance07_frm[5].positions[6] = 1500;
  dance07_frm[5].positions[7] = 1500;
  dance07_frm[5].positions[8] = 1800;
  dance07_frm[5].positions[9] = 1500;
  dance07_frm[5].positions[10] = 1500;
  dance07_frm[5].positions[11] = 1500;

  dance07_frm[6].positions[0] = 1800;
  dance07_frm[6].positions[1] = 1800;
  dance07_frm[6].positions[2] = 1500;
  dance07_frm[6].positions[3] = 1500;
  dance07_frm[6].positions[4] = 1800;
  dance07_frm[6].positions[5] = 1800;
  dance07_frm[6].positions[6] = 1500;
  dance07_frm[6].positions[7] = 1500;
  dance07_frm[6].positions[8] = 1800;
  dance07_frm[6].positions[9] = 1800;
  dance07_frm[6].positions[10] = 1500;
  dance07_frm[6].positions[11] = 1500;

  dance07_frm[7].positions[0] = 1500;
  dance07_frm[7].positions[1] = 1500;
  dance07_frm[7].positions[2] = 1500;
  dance07_frm[7].positions[3] = 1500;
  dance07_frm[7].positions[4] = 1500;
  dance07_frm[7].positions[5] = 1500;
  dance07_frm[7].positions[6] = 1500;
  dance07_frm[7].positions[7] = 1500;
  dance07_frm[7].positions[8] = 1500;
  dance07_frm[7].positions[9] = 1500;
  dance07_frm[7].positions[10] = 1500;
  dance07_frm[7].positions[11] = 1500;

  dance07_frm[8].positions[0] = 1500;
  dance07_frm[8].positions[1] = 1500;
  dance07_frm[8].positions[2] = 1500;
  dance07_frm[8].positions[3] = 1800;
  dance07_frm[8].positions[4] = 1500;
  dance07_frm[8].positions[5] = 1500;
  dance07_frm[8].positions[6] = 1500;
  dance07_frm[8].positions[7] = 1800;
  dance07_frm[8].positions[8] = 1500;
  dance07_frm[8].positions[9] = 1500;
  dance07_frm[8].positions[10] = 1500;
  dance07_frm[8].positions[11] = 1800;

  dance07_frm[9].positions[0] = 1500;
  dance07_frm[9].positions[1] = 1500;
  dance07_frm[9].positions[2] = 1200;
  dance07_frm[9].positions[3] = 1500;
  dance07_frm[9].positions[4] = 1500;
  dance07_frm[9].positions[5] = 1500;
  dance07_frm[9].positions[6] = 1200;
  dance07_frm[9].positions[7] = 1500;
  dance07_frm[9].positions[8] = 1500;
  dance07_frm[9].positions[9] = 1500;
  dance07_frm[9].positions[10] = 1200;
  dance07_frm[9].positions[11] = 1500;

  dance07_frm[10].positions[0] = 1500;
  dance07_frm[10].positions[1] = 1800;
  dance07_frm[10].positions[2] = 1200;
  dance07_frm[10].positions[3] = 1500;
  dance07_frm[10].positions[4] = 1500;
  dance07_frm[10].positions[5] = 1800;
  dance07_frm[10].positions[6] = 1200;
  dance07_frm[10].positions[7] = 1500;
  dance07_frm[10].positions[8] = 1500;
  dance07_frm[10].positions[9] = 1800;
  dance07_frm[10].positions[10] = 1200;
  dance07_frm[10].positions[11] = 1500;

  dance07_frm[11].positions[0] = 1500;
  dance07_frm[11].positions[1] = 1800;
  dance07_frm[11].positions[2] = 1800;
  dance07_frm[11].positions[3] = 1500;
  dance07_frm[11].positions[4] = 1500;
  dance07_frm[11].positions[5] = 1800;
  dance07_frm[11].positions[6] = 1800;
  dance07_frm[11].positions[7] = 1500;
  dance07_frm[11].positions[8] = 1500;
  dance07_frm[11].positions[9] = 1800;
  dance07_frm[11].positions[10] = 1800;
  dance07_frm[11].positions[11] = 1500;

  dance07_frm[12].positions[0] = 1500;
  dance07_frm[12].positions[1] = 1800;
  dance07_frm[12].positions[2] = 1200;
  dance07_frm[12].positions[3] = 1500;
  dance07_frm[12].positions[4] = 1500;
  dance07_frm[12].positions[5] = 1800;
  dance07_frm[12].positions[6] = 1200;
  dance07_frm[12].positions[7] = 1500;
  dance07_frm[12].positions[8] = 1500;
  dance07_frm[12].positions[9] = 1800;
  dance07_frm[12].positions[10] = 1200;
  dance07_frm[12].positions[11] = 1500;

  dance07_frm[13].positions[0] = 1500;
  dance07_frm[13].positions[1] = 1500;
  dance07_frm[13].positions[2] = 1200;
  dance07_frm[13].positions[3] = 1500;
  dance07_frm[13].positions[4] = 1500;
  dance07_frm[13].positions[5] = 1500;
  dance07_frm[13].positions[6] = 1200;
  dance07_frm[13].positions[7] = 1500;
  dance07_frm[13].positions[8] = 1500;
  dance07_frm[13].positions[9] = 1500;
  dance07_frm[13].positions[10] = 1200;
  dance07_frm[13].positions[11] = 1500;

  dance07_frm[14].positions[0] = 1500;
  dance07_frm[14].positions[1] = 1500;
  dance07_frm[14].positions[2] = 1500;
  dance07_frm[14].positions[3] = 1800;
  dance07_frm[14].positions[4] = 1500;
  dance07_frm[14].positions[5] = 1500;
  dance07_frm[14].positions[6] = 1500;
  dance07_frm[14].positions[7] = 1800;
  dance07_frm[14].positions[8] = 1500;
  dance07_frm[14].positions[9] = 1500;
  dance07_frm[14].positions[10] = 1500;
  dance07_frm[14].positions[11] = 1800;

  dance07_frm[15].positions[0] = 1500;
  dance07_frm[15].positions[1] = 1500;
  dance07_frm[15].positions[2] = 1500;
  dance07_frm[15].positions[3] = 1500;
  dance07_frm[15].positions[4] = 1500;
  dance07_frm[15].positions[5] = 1500;
  dance07_frm[15].positions[6] = 1500;
  dance07_frm[15].positions[7] = 1500;
  dance07_frm[15].positions[8] = 1500;
  dance07_frm[15].positions[9] = 1500;
  dance07_frm[15].positions[10] = 1500;
  dance07_frm[15].positions[11] = 1500;

  dance08_frm[0].positions[0] = 1500;
  dance08_frm[0].positions[1] = 1800;
  dance08_frm[0].positions[2] = 1500;
  dance08_frm[0].positions[3] = 1300;
  dance08_frm[0].positions[4] = 1500;
  dance08_frm[0].positions[5] = 1800;
  dance08_frm[0].positions[6] = 1500;
  dance08_frm[0].positions[7] = 1300;
  dance08_frm[0].positions[8] = 1500;
  dance08_frm[0].positions[9] = 1800;
  dance08_frm[0].positions[10] = 1500;
  dance08_frm[0].positions[11] = 1300;

  dance08_frm[1].positions[0] = 1500;
  dance08_frm[1].positions[1] = 1800;
  dance08_frm[1].positions[2] = 1200;
  dance08_frm[1].positions[3] = 1300;
  dance08_frm[1].positions[4] = 1500;
  dance08_frm[1].positions[5] = 1800;
  dance08_frm[1].positions[6] = 1200;
  dance08_frm[1].positions[7] = 1300;
  dance08_frm[1].positions[8] = 1500;
  dance08_frm[1].positions[9] = 1800;
  dance08_frm[1].positions[10] = 1200;
  dance08_frm[1].positions[11] = 1300;

  dance08_frm[2].positions[0] = 1500;
  dance08_frm[2].positions[1] = 1800;
  dance08_frm[2].positions[2] = 1500;
  dance08_frm[2].positions[3] = 1300;
  dance08_frm[2].positions[4] = 1500;
  dance08_frm[2].positions[5] = 1800;
  dance08_frm[2].positions[6] = 1500;
  dance08_frm[2].positions[7] = 1300;
  dance08_frm[2].positions[8] = 1500;
  dance08_frm[2].positions[9] = 1800;
  dance08_frm[2].positions[10] = 1500;
  dance08_frm[2].positions[11] = 1300;

  dance08_frm[3].positions[0] = 1500;
  dance08_frm[3].positions[1] = 1500;
  dance08_frm[3].positions[2] = 1500;
  dance08_frm[3].positions[3] = 1500;
  dance08_frm[3].positions[4] = 1500;
  dance08_frm[3].positions[5] = 1500;
  dance08_frm[3].positions[6] = 1500;
  dance08_frm[3].positions[7] = 1500;
  dance08_frm[3].positions[8] = 1500;
  dance08_frm[3].positions[9] = 1500;
  dance08_frm[3].positions[10] = 1500;
  dance08_frm[3].positions[11] = 1500;

  dance08_frm[4].positions[0] = 1500;
  dance08_frm[4].positions[1] = 1200;
  dance08_frm[4].positions[2] = 1500;
  dance08_frm[4].positions[3] = 1200;
  dance08_frm[4].positions[4] = 1500;
  dance08_frm[4].positions[5] = 1200;
  dance08_frm[4].positions[6] = 1500;
  dance08_frm[4].positions[7] = 1200;
  dance08_frm[4].positions[8] = 1500;
  dance08_frm[4].positions[9] = 1200;
  dance08_frm[4].positions[10] = 1500;
  dance08_frm[4].positions[11] = 1200;

  dance08_frm[5].positions[0] = 1500;
  dance08_frm[5].positions[1] = 1500;
  dance08_frm[5].positions[2] = 1500;
  dance08_frm[5].positions[3] = 1500;
  dance08_frm[5].positions[4] = 1500;
  dance08_frm[5].positions[5] = 1500;
  dance08_frm[5].positions[6] = 1500;
  dance08_frm[5].positions[7] = 1500;
  dance08_frm[5].positions[8] = 1500;
  dance08_frm[5].positions[9] = 1500;
  dance08_frm[5].positions[10] = 1500;
  dance08_frm[5].positions[11] = 1500;

  dance08_frm[6].positions[0] = 1500;
  dance08_frm[6].positions[1] = 1300;
  dance08_frm[6].positions[2] = 1500;
  dance08_frm[6].positions[3] = 1800;
  dance08_frm[6].positions[4] = 1500;
  dance08_frm[6].positions[5] = 1300;
  dance08_frm[6].positions[6] = 1500;
  dance08_frm[6].positions[7] = 1800;
  dance08_frm[6].positions[8] = 1500;
  dance08_frm[6].positions[9] = 1300;
  dance08_frm[6].positions[10] = 1500;
  dance08_frm[6].positions[11] = 1800;

  dance08_frm[7].positions[0] = 1800;
  dance08_frm[7].positions[1] = 1300;
  dance08_frm[7].positions[2] = 1500;
  dance08_frm[7].positions[3] = 1800;
  dance08_frm[7].positions[4] = 1800;
  dance08_frm[7].positions[5] = 1300;
  dance08_frm[7].positions[6] = 1500;
  dance08_frm[7].positions[7] = 1800;
  dance08_frm[7].positions[8] = 1800;
  dance08_frm[7].positions[9] = 1300;
  dance08_frm[7].positions[10] = 1500;
  dance08_frm[7].positions[11] = 1800;

  dance08_frm[8].positions[0] = 1500;
  dance08_frm[8].positions[1] = 1300;
  dance08_frm[8].positions[2] = 1500;
  dance08_frm[8].positions[3] = 1800;
  dance08_frm[8].positions[4] = 1500;
  dance08_frm[8].positions[5] = 1300;
  dance08_frm[8].positions[6] = 1500;
  dance08_frm[8].positions[7] = 1800;
  dance08_frm[8].positions[8] = 1500;
  dance08_frm[8].positions[9] = 1300;
  dance08_frm[8].positions[10] = 1500;
  dance08_frm[8].positions[11] = 1800;

  dance08_frm[9].positions[0] = 1500;
  dance08_frm[9].positions[1] = 1500;
  dance08_frm[9].positions[2] = 1500;
  dance08_frm[9].positions[3] = 1500;
  dance08_frm[9].positions[4] = 1500;
  dance08_frm[9].positions[5] = 1500;
  dance08_frm[9].positions[6] = 1500;
  dance08_frm[9].positions[7] = 1500;
  dance08_frm[9].positions[8] = 1500;
  dance08_frm[9].positions[9] = 1500;
  dance08_frm[9].positions[10] = 1500;
  dance08_frm[9].positions[11] = 1500;

  dance08_frm[10].positions[0] = 1500;
  dance08_frm[10].positions[1] = 1200;
  dance08_frm[10].positions[2] = 1500;
  dance08_frm[10].positions[3] = 1200;
  dance08_frm[10].positions[4] = 1500;
  dance08_frm[10].positions[5] = 1200;
  dance08_frm[10].positions[6] = 1500;
  dance08_frm[10].positions[7] = 1200;
  dance08_frm[10].positions[8] = 1500;
  dance08_frm[10].positions[9] = 1200;
  dance08_frm[10].positions[10] = 1500;
  dance08_frm[10].positions[11] = 1200;

  dance08_frm[11].positions[0] = 1500;
  dance08_frm[11].positions[1] = 1500;
  dance08_frm[11].positions[2] = 1500;
  dance08_frm[11].positions[3] = 1500;
  dance08_frm[11].positions[4] = 1500;
  dance08_frm[11].positions[5] = 1500;
  dance08_frm[11].positions[6] = 1500;
  dance08_frm[11].positions[7] = 1500;
  dance08_frm[11].positions[8] = 1500;
  dance08_frm[11].positions[9] = 1500;
  dance08_frm[11].positions[10] = 1500;
  dance08_frm[11].positions[11] = 1500;

  dance09_frm[0].positions[0] = 1500;
  dance09_frm[0].positions[1] = 1200;
  dance09_frm[0].positions[2] = 1300;
  dance09_frm[0].positions[3] = 1400;
  dance09_frm[0].positions[4] = 1500;
  dance09_frm[0].positions[5] = 1800;
  dance09_frm[0].positions[6] = 1500;
  dance09_frm[0].positions[7] = 1200;
  dance09_frm[0].positions[8] = 1600;
  dance09_frm[0].positions[9] = 1400;
  dance09_frm[0].positions[10] = 1500;
  dance09_frm[0].positions[11] = 1800;

  dance09_frm[1].positions[0] = 1500;
  dance09_frm[1].positions[1] = 1800;
  dance09_frm[1].positions[2] = 1300;
  dance09_frm[1].positions[3] = 1400;
  dance09_frm[1].positions[4] = 1500;
  dance09_frm[1].positions[5] = 1800;
  dance09_frm[1].positions[6] = 1500;
  dance09_frm[1].positions[7] = 1800;
  dance09_frm[1].positions[8] = 1600;
  dance09_frm[1].positions[9] = 1400;
  dance09_frm[1].positions[10] = 1500;
  dance09_frm[1].positions[11] = 1800;

  dance09_frm[2].positions[0] = 1200;
  dance09_frm[2].positions[1] = 1800;
  dance09_frm[2].positions[2] = 1300;
  dance09_frm[2].positions[3] = 1400;
  dance09_frm[2].positions[4] = 1500;
  dance09_frm[2].positions[5] = 1800;
  dance09_frm[2].positions[6] = 1800;
  dance09_frm[2].positions[7] = 1800;
  dance09_frm[2].positions[8] = 1600;
  dance09_frm[2].positions[9] = 1400;
  dance09_frm[2].positions[10] = 1500;
  dance09_frm[2].positions[11] = 1800;

  dance09_frm[3].positions[0] = 1500;
  dance09_frm[3].positions[1] = 1800;
  dance09_frm[3].positions[2] = 1300;
  dance09_frm[3].positions[3] = 1400;
  dance09_frm[3].positions[4] = 1500;
  dance09_frm[3].positions[5] = 1800;
  dance09_frm[3].positions[6] = 1500;
  dance09_frm[3].positions[7] = 1800;
  dance09_frm[3].positions[8] = 1600;
  dance09_frm[3].positions[9] = 1400;
  dance09_frm[3].positions[10] = 1500;
  dance09_frm[3].positions[11] = 1800;

  dance09_frm[4].positions[0] = 1200;
  dance09_frm[4].positions[1] = 1800;
  dance09_frm[4].positions[2] = 1300;
  dance09_frm[4].positions[3] = 1400;
  dance09_frm[4].positions[4] = 1500;
  dance09_frm[4].positions[5] = 1800;
  dance09_frm[4].positions[6] = 1800;
  dance09_frm[4].positions[7] = 1800;
  dance09_frm[4].positions[8] = 1600;
  dance09_frm[4].positions[9] = 1400;
  dance09_frm[4].positions[10] = 1500;
  dance09_frm[4].positions[11] = 1800;

  dance09_frm[5].positions[0] = 1500;
  dance09_frm[5].positions[1] = 1800;
  dance09_frm[5].positions[2] = 1300;
  dance09_frm[5].positions[3] = 1400;
  dance09_frm[5].positions[4] = 1500;
  dance09_frm[5].positions[5] = 1800;
  dance09_frm[5].positions[6] = 1500;
  dance09_frm[5].positions[7] = 1800;
  dance09_frm[5].positions[8] = 1600;
  dance09_frm[5].positions[9] = 1400;
  dance09_frm[5].positions[10] = 1500;
  dance09_frm[5].positions[11] = 1800;

  dance09_frm[6].positions[0] = 1200;
  dance09_frm[6].positions[1] = 1800;
  dance09_frm[6].positions[2] = 1300;
  dance09_frm[6].positions[3] = 1400;
  dance09_frm[6].positions[4] = 1500;
  dance09_frm[6].positions[5] = 1800;
  dance09_frm[6].positions[6] = 1800;
  dance09_frm[6].positions[7] = 1800;
  dance09_frm[6].positions[8] = 1600;
  dance09_frm[6].positions[9] = 1400;
  dance09_frm[6].positions[10] = 1500;
  dance09_frm[6].positions[11] = 1800;

  dance09_frm[7].positions[0] = 1500;
  dance09_frm[7].positions[1] = 1800;
  dance09_frm[7].positions[2] = 1300;
  dance09_frm[7].positions[3] = 1400;
  dance09_frm[7].positions[4] = 1500;
  dance09_frm[7].positions[5] = 1800;
  dance09_frm[7].positions[6] = 1500;
  dance09_frm[7].positions[7] = 1800;
  dance09_frm[7].positions[8] = 1600;
  dance09_frm[7].positions[9] = 1400;
  dance09_frm[7].positions[10] = 1500;
  dance09_frm[7].positions[11] = 1800;

  dance10_frm[0].positions[0] = 1500;
  dance10_frm[0].positions[1] = 1200;
  dance10_frm[0].positions[2] = 1300;
  dance10_frm[0].positions[3] = 1400;
  dance10_frm[0].positions[4] = 1500;
  dance10_frm[0].positions[5] = 1800;
  dance10_frm[0].positions[6] = 1500;
  dance10_frm[0].positions[7] = 1200;
  dance10_frm[0].positions[8] = 1600;
  dance10_frm[0].positions[9] = 1400;
  dance10_frm[0].positions[10] = 1500;
  dance10_frm[0].positions[11] = 1800;

  dance10_frm[1].positions[0] = 1500;
  dance10_frm[1].positions[1] = 1800;
  dance10_frm[1].positions[2] = 1300;
  dance10_frm[1].positions[3] = 1400;
  dance10_frm[1].positions[4] = 1500;
  dance10_frm[1].positions[5] = 1800;
  dance10_frm[1].positions[6] = 1500;
  dance10_frm[1].positions[7] = 1800;
  dance10_frm[1].positions[8] = 1600;
  dance10_frm[1].positions[9] = 1400;
  dance10_frm[1].positions[10] = 1500;
  dance10_frm[1].positions[11] = 1800;

  dance10_frm[2].positions[0] = 1800;
  dance10_frm[2].positions[1] = 1800;
  dance10_frm[2].positions[2] = 1300;
  dance10_frm[2].positions[3] = 1400;
  dance10_frm[2].positions[4] = 1500;
  dance10_frm[2].positions[5] = 1800;
  dance10_frm[2].positions[6] = 1800;
  dance10_frm[2].positions[7] = 1800;
  dance10_frm[2].positions[8] = 1600;
  dance10_frm[2].positions[9] = 1400;
  dance10_frm[2].positions[10] = 1500;
  dance10_frm[2].positions[11] = 1800;

  dance10_frm[3].positions[0] = 1200;
  dance10_frm[3].positions[1] = 1800;
  dance10_frm[3].positions[2] = 1300;
  dance10_frm[3].positions[3] = 1400;
  dance10_frm[3].positions[4] = 1500;
  dance10_frm[3].positions[5] = 1800;
  dance10_frm[3].positions[6] = 1200;
  dance10_frm[3].positions[7] = 1800;
  dance10_frm[3].positions[8] = 1600;
  dance10_frm[3].positions[9] = 1400;
  dance10_frm[3].positions[10] = 1500;
  dance10_frm[3].positions[11] = 1800;

  dance10_frm[4].positions[0] = 1500;
  dance10_frm[4].positions[1] = 1200;
  dance10_frm[4].positions[2] = 1300;
  dance10_frm[4].positions[3] = 1400;
  dance10_frm[4].positions[4] = 1500;
  dance10_frm[4].positions[5] = 1800;
  dance10_frm[4].positions[6] = 1500;
  dance10_frm[4].positions[7] = 1200;
  dance10_frm[4].positions[8] = 1600;
  dance10_frm[4].positions[9] = 1400;
  dance10_frm[4].positions[10] = 1500;
  dance10_frm[4].positions[11] = 1800;

  dance10_frm[5].positions[0] = 1500;
  dance10_frm[5].positions[1] = 1500;
  dance10_frm[5].positions[2] = 1500;
  dance10_frm[5].positions[3] = 1500;
  dance10_frm[5].positions[4] = 1500;
  dance10_frm[5].positions[5] = 1500;
  dance10_frm[5].positions[6] = 1500;
  dance10_frm[5].positions[7] = 1500;
  dance10_frm[5].positions[8] = 1500;
  dance10_frm[5].positions[9] = 1500;
  dance10_frm[5].positions[10] = 1500;
  dance10_frm[5].positions[11] = 1500;

  dance11_frm[0].positions[0] = 1500;
  dance11_frm[0].positions[1] = 1500;
  dance11_frm[0].positions[2] = 1500;
  dance11_frm[0].positions[3] = 1500;
  dance11_frm[0].positions[4] = 1500;
  dance11_frm[0].positions[5] = 1500;
  dance11_frm[0].positions[6] = 1500;
  dance11_frm[0].positions[7] = 1500;
  dance11_frm[0].positions[8] = 1500;
  dance11_frm[0].positions[9] = 1500;
  dance11_frm[0].positions[10] = 1500;
  dance11_frm[0].positions[11] = 1500;

  dance11_frm[1].positions[0] = 1500;
  dance11_frm[1].positions[1] = 1200;
  dance11_frm[1].positions[2] = 1500;
  dance11_frm[1].positions[3] = 1200;
  dance11_frm[1].positions[4] = 1500;
  dance11_frm[1].positions[5] = 1200;
  dance11_frm[1].positions[6] = 1500;
  dance11_frm[1].positions[7] = 1200;
  dance11_frm[1].positions[8] = 1500;
  dance11_frm[1].positions[9] = 1200;
  dance11_frm[1].positions[10] = 1500;
  dance11_frm[1].positions[11] = 1200;

  dance11_frm[2].positions[0] = 1500;
  dance11_frm[2].positions[1] = 1200;
  dance11_frm[2].positions[2] = 1500;
  dance11_frm[2].positions[3] = 1200;
  dance11_frm[2].positions[4] = 1500;
  dance11_frm[2].positions[5] = 1200;
  dance11_frm[2].positions[6] = 1500;
  dance11_frm[2].positions[7] = 1800;
  dance11_frm[2].positions[8] = 1500;
  dance11_frm[2].positions[9] = 1800;
  dance11_frm[2].positions[10] = 1500;
  dance11_frm[2].positions[11] = 1800;

  dance11_frm[3].positions[0] = 1500;
  dance11_frm[3].positions[1] = 1800;
  dance11_frm[3].positions[2] = 1500;
  dance11_frm[3].positions[3] = 1800;
  dance11_frm[3].positions[4] = 1500;
  dance11_frm[3].positions[5] = 1800;
  dance11_frm[3].positions[6] = 1500;
  dance11_frm[3].positions[7] = 1200;
  dance11_frm[3].positions[8] = 1500;
  dance11_frm[3].positions[9] = 1200;
  dance11_frm[3].positions[10] = 1500;
  dance11_frm[3].positions[11] = 1200;

  dance11_frm[4].positions[0] = 1500;
  dance11_frm[4].positions[1] = 1500;
  dance11_frm[4].positions[2] = 1500;
  dance11_frm[4].positions[3] = 1500;
  dance11_frm[4].positions[4] = 1500;
  dance11_frm[4].positions[5] = 1500;
  dance11_frm[4].positions[6] = 1500;
  dance11_frm[4].positions[7] = 1500;
  dance11_frm[4].positions[8] = 1500;
  dance11_frm[4].positions[9] = 1500;
  dance11_frm[4].positions[10] = 1500;
  dance11_frm[4].positions[11] = 1500;

  dance11_frm[5].positions[0] = 1500;
  dance11_frm[5].positions[1] = 1200;
  dance11_frm[5].positions[2] = 1500;
  dance11_frm[5].positions[3] = 1200;
  dance11_frm[5].positions[4] = 1500;
  dance11_frm[5].positions[5] = 1200;
  dance11_frm[5].positions[6] = 1500;
  dance11_frm[5].positions[7] = 1200;
  dance11_frm[5].positions[8] = 1500;
  dance11_frm[5].positions[9] = 1200;
  dance11_frm[5].positions[10] = 1500;
  dance11_frm[5].positions[11] = 1200;

  dance11_frm[6].positions[0] = 1500;
  dance11_frm[6].positions[1] = 1500;
  dance11_frm[6].positions[2] = 1500;
  dance11_frm[6].positions[3] = 1500;
  dance11_frm[6].positions[4] = 1500;
  dance11_frm[6].positions[5] = 1500;
  dance11_frm[6].positions[6] = 1500;
  dance11_frm[6].positions[7] = 1500;
  dance11_frm[6].positions[8] = 1500;
  dance11_frm[6].positions[9] = 1500;
  dance11_frm[6].positions[10] = 1500;
  dance11_frm[6].positions[11] = 1500;

  dance11_frm[7].positions[0] = 1500;
  dance11_frm[7].positions[1] = 1500;
  dance11_frm[7].positions[2] = 1500;
  dance11_frm[7].positions[3] = 1500;
  dance11_frm[7].positions[4] = 1500;
  dance11_frm[7].positions[5] = 1500;
  dance11_frm[7].positions[6] = 1500;
  dance11_frm[7].positions[7] = 1500;
  dance11_frm[7].positions[8] = 1500;
  dance11_frm[7].positions[9] = 1500;
  dance11_frm[7].positions[10] = 1500;
  dance11_frm[7].positions[11] = 1500;

  dance12_frm[0].positions[0] = 1500;
  dance12_frm[0].positions[1] = 1200;
  dance12_frm[0].positions[2] = 1300;
  dance12_frm[0].positions[3] = 1400;
  dance12_frm[0].positions[4] = 1500;
  dance12_frm[0].positions[5] = 1800;
  dance12_frm[0].positions[6] = 1500;
  dance12_frm[0].positions[7] = 1200;
  dance12_frm[0].positions[8] = 1600;
  dance12_frm[0].positions[9] = 1400;
  dance12_frm[0].positions[10] = 1500;
  dance12_frm[0].positions[11] = 1800;

  dance12_frm[1].positions[0] = 1500;
  dance12_frm[1].positions[1] = 1800;
  dance12_frm[1].positions[2] = 1300;
  dance12_frm[1].positions[3] = 1400;
  dance12_frm[1].positions[4] = 1500;
  dance12_frm[1].positions[5] = 1800;
  dance12_frm[1].positions[6] = 1500;
  dance12_frm[1].positions[7] = 1800;
  dance12_frm[1].positions[8] = 1600;
  dance12_frm[1].positions[9] = 1400;
  dance12_frm[1].positions[10] = 1500;
  dance12_frm[1].positions[11] = 1800;

  dance12_frm[2].positions[0] = 1200;
  dance12_frm[2].positions[1] = 1800;
  dance12_frm[2].positions[2] = 1300;
  dance12_frm[2].positions[3] = 1400;
  dance12_frm[2].positions[4] = 1500;
  dance12_frm[2].positions[5] = 1800;
  dance12_frm[2].positions[6] = 1200;
  dance12_frm[2].positions[7] = 1800;
  dance12_frm[2].positions[8] = 1600;
  dance12_frm[2].positions[9] = 1400;
  dance12_frm[2].positions[10] = 1500;
  dance12_frm[2].positions[11] = 1800;

  dance12_frm[3].positions[0] = 1200;
  dance12_frm[3].positions[1] = 1800;
  dance12_frm[3].positions[2] = 1300;
  dance12_frm[3].positions[3] = 1400;
  dance12_frm[3].positions[4] = 1500;
  dance12_frm[3].positions[5] = 1800;
  dance12_frm[3].positions[6] = 1800;
  dance12_frm[3].positions[7] = 1800;
  dance12_frm[3].positions[8] = 1600;
  dance12_frm[3].positions[9] = 1400;
  dance12_frm[3].positions[10] = 1500;
  dance12_frm[3].positions[11] = 1800;

  dance12_frm[4].positions[0] = 1200;
  dance12_frm[4].positions[1] = 1800;
  dance12_frm[4].positions[2] = 1300;
  dance12_frm[4].positions[3] = 1400;
  dance12_frm[4].positions[4] = 1500;
  dance12_frm[4].positions[5] = 1800;
  dance12_frm[4].positions[6] = 1800;
  dance12_frm[4].positions[7] = 1500;
  dance12_frm[4].positions[8] = 1600;
  dance12_frm[4].positions[9] = 1400;
  dance12_frm[4].positions[10] = 1500;
  dance12_frm[4].positions[11] = 1800;

  dance12_frm[5].positions[0] = 1200;
  dance12_frm[5].positions[1] = 1800;
  dance12_frm[5].positions[2] = 1300;
  dance12_frm[5].positions[3] = 1400;
  dance12_frm[5].positions[4] = 1500;
  dance12_frm[5].positions[5] = 1800;
  dance12_frm[5].positions[6] = 1200;
  dance12_frm[5].positions[7] = 1800;
  dance12_frm[5].positions[8] = 1600;
  dance12_frm[5].positions[9] = 1400;
  dance12_frm[5].positions[10] = 1500;
  dance12_frm[5].positions[11] = 1800;

  dance12_frm[6].positions[0] = 1500;
  dance12_frm[6].positions[1] = 1200;
  dance12_frm[6].positions[2] = 1300;
  dance12_frm[6].positions[3] = 1400;
  dance12_frm[6].positions[4] = 1500;
  dance12_frm[6].positions[5] = 1800;
  dance12_frm[6].positions[6] = 1500;
  dance12_frm[6].positions[7] = 1200;
  dance12_frm[6].positions[8] = 1600;
  dance12_frm[6].positions[9] = 1400;
  dance12_frm[6].positions[10] = 1500;
  dance12_frm[6].positions[11] = 1800;

  dance12_frm[7].positions[0] = 1500;
  dance12_frm[7].positions[1] = 1500;
  dance12_frm[7].positions[2] = 1500;
  dance12_frm[7].positions[3] = 1500;
  dance12_frm[7].positions[4] = 1500;
  dance12_frm[7].positions[5] = 1500;
  dance12_frm[7].positions[6] = 1500;
  dance12_frm[7].positions[7] = 1500;
  dance12_frm[7].positions[8] = 1500;
  dance12_frm[7].positions[9] = 1500;
  dance12_frm[7].positions[10] = 1500;
  dance12_frm[7].positions[11] = 1500;

  dance13_frm[0].positions[0] = 1500;
  dance13_frm[0].positions[1] = 1600;
  dance13_frm[0].positions[2] = 1500;
  dance13_frm[0].positions[3] = 1650;
  dance13_frm[0].positions[4] = 1500;
  dance13_frm[0].positions[5] = 1600;
  dance13_frm[0].positions[6] = 1500;
  dance13_frm[0].positions[7] = 1700;
  dance13_frm[0].positions[8] = 1500;
  dance13_frm[0].positions[9] = 1200;
  dance13_frm[0].positions[10] = 1500;
  dance13_frm[0].positions[11] = 1300;

  dance13_frm[1].positions[0] = 1500;
  dance13_frm[1].positions[1] = 1600;
  dance13_frm[1].positions[2] = 1500;
  dance13_frm[1].positions[3] = 1650;
  dance13_frm[1].positions[4] = 1500;
  dance13_frm[1].positions[5] = 1600;
  dance13_frm[1].positions[6] = 1500;
  dance13_frm[1].positions[7] = 1300;
  dance13_frm[1].positions[8] = 1500;
  dance13_frm[1].positions[9] = 1700;
  dance13_frm[1].positions[10] = 1500;
  dance13_frm[1].positions[11] = 1300;

  dance13_frm[2].positions[0] = 1500;
  dance13_frm[2].positions[1] = 1600;
  dance13_frm[2].positions[2] = 1500;
  dance13_frm[2].positions[3] = 1650;
  dance13_frm[2].positions[4] = 1500;
  dance13_frm[2].positions[5] = 1600;
  dance13_frm[2].positions[6] = 1500;
  dance13_frm[2].positions[7] = 1300;
  dance13_frm[2].positions[8] = 1500;
  dance13_frm[2].positions[9] = 1200;
  dance13_frm[2].positions[10] = 1500;
  dance13_frm[2].positions[11] = 1700;

  dance13_frm[3].positions[0] = 1500;
  dance13_frm[3].positions[1] = 1600;
  dance13_frm[3].positions[2] = 1500;
  dance13_frm[3].positions[3] = 1650;
  dance13_frm[3].positions[4] = 1500;
  dance13_frm[3].positions[5] = 1600;
  dance13_frm[3].positions[6] = 1500;
  dance13_frm[3].positions[7] = 1300;
  dance13_frm[3].positions[8] = 1500;
  dance13_frm[3].positions[9] = 1200;
  dance13_frm[3].positions[10] = 1500;
  dance13_frm[3].positions[11] = 1300;

  dance13_frm[4].positions[0] = 1500;
  dance13_frm[4].positions[1] = 1300;
  dance13_frm[4].positions[2] = 1500;
  dance13_frm[4].positions[3] = 1200;
  dance13_frm[4].positions[4] = 1500;
  dance13_frm[4].positions[5] = 1700;
  dance13_frm[4].positions[6] = 1500;
  dance13_frm[4].positions[7] = 1600;
  dance13_frm[4].positions[8] = 1500;
  dance13_frm[4].positions[9] = 1650;
  dance13_frm[4].positions[10] = 1500;
  dance13_frm[4].positions[11] = 1600;

  dance13_frm[5].positions[0] = 1500;
  dance13_frm[5].positions[1] = 1300;
  dance13_frm[5].positions[2] = 1500;
  dance13_frm[5].positions[3] = 1700;
  dance13_frm[5].positions[4] = 1500;
  dance13_frm[5].positions[5] = 1300;
  dance13_frm[5].positions[6] = 1500;
  dance13_frm[5].positions[7] = 1600;
  dance13_frm[5].positions[8] = 1500;
  dance13_frm[5].positions[9] = 1650;
  dance13_frm[5].positions[10] = 1500;
  dance13_frm[5].positions[11] = 1600;

  dance13_frm[6].positions[0] = 1500;
  dance13_frm[6].positions[1] = 1700;
  dance13_frm[6].positions[2] = 1500;
  dance13_frm[6].positions[3] = 1200;
  dance13_frm[6].positions[4] = 1500;
  dance13_frm[6].positions[5] = 1300;
  dance13_frm[6].positions[6] = 1500;
  dance13_frm[6].positions[7] = 1600;
  dance13_frm[6].positions[8] = 1500;
  dance13_frm[6].positions[9] = 1650;
  dance13_frm[6].positions[10] = 1500;
  dance13_frm[6].positions[11] = 1600;

  dance13_frm[7].positions[0] = 1500;
  dance13_frm[7].positions[1] = 1300;
  dance13_frm[7].positions[2] = 1500;
  dance13_frm[7].positions[3] = 1200;
  dance13_frm[7].positions[4] = 1500;
  dance13_frm[7].positions[5] = 1300;
  dance13_frm[7].positions[6] = 1500;
  dance13_frm[7].positions[7] = 1600;
  dance13_frm[7].positions[8] = 1500;
  dance13_frm[7].positions[9] = 1650;
  dance13_frm[7].positions[10] = 1500;
  dance13_frm[7].positions[11] = 1600;

  dance13_frm[8].positions[0] = 1500;
  dance13_frm[8].positions[1] = 1600;
  dance13_frm[8].positions[2] = 1500;
  dance13_frm[8].positions[3] = 1650;
  dance13_frm[8].positions[4] = 1500;
  dance13_frm[8].positions[5] = 1600;
  dance13_frm[8].positions[6] = 1500;
  dance13_frm[8].positions[7] = 1700;
  dance13_frm[8].positions[8] = 1500;
  dance13_frm[8].positions[9] = 1200;
  dance13_frm[8].positions[10] = 1500;
  dance13_frm[8].positions[11] = 1300;

  dance13_frm[9].positions[0] = 1500;
  dance13_frm[9].positions[1] = 1600;
  dance13_frm[9].positions[2] = 1500;
  dance13_frm[9].positions[3] = 1650;
  dance13_frm[9].positions[4] = 1500;
  dance13_frm[9].positions[5] = 1600;
  dance13_frm[9].positions[6] = 1500;
  dance13_frm[9].positions[7] = 1300;
  dance13_frm[9].positions[8] = 1500;
  dance13_frm[9].positions[9] = 1700;
  dance13_frm[9].positions[10] = 1500;
  dance13_frm[9].positions[11] = 1300;

  dance13_frm[10].positions[0] = 1500;
  dance13_frm[10].positions[1] = 1600;
  dance13_frm[10].positions[2] = 1500;
  dance13_frm[10].positions[3] = 1650;
  dance13_frm[10].positions[4] = 1500;
  dance13_frm[10].positions[5] = 1600;
  dance13_frm[10].positions[6] = 1500;
  dance13_frm[10].positions[7] = 1300;
  dance13_frm[10].positions[8] = 1500;
  dance13_frm[10].positions[9] = 1200;
  dance13_frm[10].positions[10] = 1500;
  dance13_frm[10].positions[11] = 1700;

  dance13_frm[11].positions[0] = 1500;
  dance13_frm[11].positions[1] = 1600;
  dance13_frm[11].positions[2] = 1500;
  dance13_frm[11].positions[3] = 1650;
  dance13_frm[11].positions[4] = 1500;
  dance13_frm[11].positions[5] = 1600;
  dance13_frm[11].positions[6] = 1500;
  dance13_frm[11].positions[7] = 1300;
  dance13_frm[11].positions[8] = 1500;
  dance13_frm[11].positions[9] = 1200;
  dance13_frm[11].positions[10] = 1500;
  dance13_frm[11].positions[11] = 1300;

  dance13_frm[12].positions[0] = 1500;
  dance13_frm[12].positions[1] = 1500;
  dance13_frm[12].positions[2] = 1500;
  dance13_frm[12].positions[3] = 1500;
  dance13_frm[12].positions[4] = 1500;
  dance13_frm[12].positions[5] = 1500;
  dance13_frm[12].positions[6] = 1500;
  dance13_frm[12].positions[7] = 1900;
  dance13_frm[12].positions[8] = 1500;
  dance13_frm[12].positions[9] = 1500;
  dance13_frm[12].positions[10] = 1500;
  dance13_frm[12].positions[11] = 1500;

  dance13_frm[13].positions[0] = 1500;
  dance13_frm[13].positions[1] = 1500;
  dance13_frm[13].positions[2] = 1500;
  dance13_frm[13].positions[3] = 1500;
  dance13_frm[13].positions[4] = 1500;
  dance13_frm[13].positions[5] = 1500;
  dance13_frm[13].positions[6] = 1900;
  dance13_frm[13].positions[7] = 1900;
  dance13_frm[13].positions[8] = 1500;
  dance13_frm[13].positions[9] = 1500;
  dance13_frm[13].positions[10] = 1500;
  dance13_frm[13].positions[11] = 1500;

  dance14_frm[0].positions[0] = 1500;
  dance14_frm[0].positions[1] = 1500;
  dance14_frm[0].positions[2] = 1500;
  dance14_frm[0].positions[3] = 1500;
  dance14_frm[0].positions[4] = 1500;
  dance14_frm[0].positions[5] = 1500;
  dance14_frm[0].positions[6] = 1500;
  dance14_frm[0].positions[7] = 1500;
  dance14_frm[0].positions[8] = 1500;
  dance14_frm[0].positions[9] = 1500;
  dance14_frm[0].positions[10] = 1500;
  dance14_frm[0].positions[11] = 1500;

  dance14_frm[1].positions[0] = 1500;
  dance14_frm[1].positions[1] = 1500;
  dance14_frm[1].positions[2] = 1500;
  dance14_frm[1].positions[3] = 1500;
  dance14_frm[1].positions[4] = 1500;
  dance14_frm[1].positions[5] = 1500;
  dance14_frm[1].positions[6] = 1900;
  dance14_frm[1].positions[7] = 1900;
  dance14_frm[1].positions[8] = 1500;
  dance14_frm[1].positions[9] = 1500;
  dance14_frm[1].positions[10] = 1500;
  dance14_frm[1].positions[11] = 1500;

  dance14_frm[2].positions[0] = 1500;
  dance14_frm[2].positions[1] = 1200;
  dance14_frm[2].positions[2] = 1500;
  dance14_frm[2].positions[3] = 1200;
  dance14_frm[2].positions[4] = 1500;
  dance14_frm[2].positions[5] = 1200;
  dance14_frm[2].positions[6] = 1500;
  dance14_frm[2].positions[7] = 1200;
  dance14_frm[2].positions[8] = 1500;
  dance14_frm[2].positions[9] = 1200;
  dance14_frm[2].positions[10] = 1500;
  dance14_frm[2].positions[11] = 1200;

  dance14_frm[3].positions[0] = 1500;
  dance14_frm[3].positions[1] = 1500;
  dance14_frm[3].positions[2] = 1500;
  dance14_frm[3].positions[3] = 1500;
  dance14_frm[3].positions[4] = 1500;
  dance14_frm[3].positions[5] = 1500;
  dance14_frm[3].positions[6] = 1500;
  dance14_frm[3].positions[7] = 1500;
  dance14_frm[3].positions[8] = 1500;
  dance14_frm[3].positions[9] = 1500;
  dance14_frm[3].positions[10] = 1500;
  dance14_frm[3].positions[11] = 1500;

  _86ME_HOME.positions[0] = 1500;
  _86ME_HOME.positions[1] = 1500;
  _86ME_HOME.positions[2] = 1500;
  _86ME_HOME.positions[3] = 1500;
  _86ME_HOME.positions[4] = 1500;
  _86ME_HOME.positions[5] = 1500;
  _86ME_HOME.positions[6] = 1500;
  _86ME_HOME.positions[7] = 1500;
  _86ME_HOME.positions[8] = 1500;
  _86ME_HOME.positions[9] = 1500;
  _86ME_HOME.positions[10] = 1500;
  _86ME_HOME.positions[11] = 1500;

  myoffs.setOffsets();

  _86ME_HOME.playPositions(0);
}

void loop()
{
  updateTrigger();
  ENDUpdate();
  homeUpdate();
  forwardUpdate();
  leftUpdate();
  rightUpdate();
  idleUpdate();
  titleUpdate();
  dance01Update();
  dance02Update();
  dance03Update();
  dance04Update();
  dance05Update();
  dance06Update();
  dance07Update();
  dance08Update();
  dance09Update();
  dance10Update();
  dance11Update();
  dance12Update();
  dance13Update();
  dance14Update();
  danceALLUpdate();
  nh.spinOnce();
}
