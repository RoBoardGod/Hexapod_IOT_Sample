#include <Servo86.h>
#include <ros.h>
#include <std_msgs/String.h>
#include <geometry_msgs/Pose2D.h>
#include <SD.h>
#include <SPI.h>
#include <Audio.h>
#include <time.h>

Servo myservo2;
Servo myservo3;
Servo myservo6;
Servo myservo7;
Servo myservo10;
Servo myservo11;
Servo myservo21;
Servo myservo22;
Servo myservo23;
Servo myservo24;
Servo myservo25;
Servo myservo26;
Servo myservo27;
Servo myservo28;
Servo myservo29;
Servo myservo30;
Servo myservo31;
Servo myservo32;
Servo myservo33;
Servo myservo34;
Servo myservo35;
Servo myservo36;
Servo myservo37;
Servo myservo38;

enum {_END, _ATKL, _ATKR, _ATKC, _LAUGH, _DANCEALL, _DANCE01, _DANCE02, _DANCE03, _DANCE04, _DANCE05, _DANCE06, _DANCE07, _DANCE08, _DANCE09, _DANCE10, _DANCE11, _DANCE12, _DANCE13, _DANCE14, _HOME, _NONE};
int _last_motion = _NONE;
int _curr_motion = _NONE;
bool internal_trigger[22] = {0};
bool external_trigger[22] = {0};

ServoOffset myoffs;

ServoFrame _86ME_HOME;

ServoFrame END_frm[1];
ServoFrame atkL_frm[2];
ServoFrame atkR_frm[2];
ServoFrame atkC_frm[2];
ServoFrame laugh_frm[22];
ServoFrame danceALL_frm[0];
ServoFrame dance01_frm[2];
ServoFrame dance02_frm[8];
ServoFrame dance03_frm[6];
ServoFrame dance04_frm[15];
ServoFrame dance05_frm[4];
ServoFrame dance06_frm[3];
ServoFrame dance07_frm[8];
ServoFrame dance08_frm[8];
ServoFrame dance09_frm[9];
ServoFrame dance10_frm[21];
ServoFrame dance11_frm[7];
ServoFrame dance12_frm[4];
ServoFrame dance13_frm[8];
ServoFrame dance14_frm[5];
ServoFrame home_frm[1];

char Serial1_Message[20];
bool renew_bt = true;
ros::NodeHandle  nh;
void messageCb( const std_msgs::String& cmsg)
{
	strcpy(Serial1_Message,(char*)cmsg.data);
}
ros::Subscriber<std_msgs::String> sub("chatter", &messageCb );
File myFile ;
short buffer[1024];

namespace END
{
  enum {IDLE, FRAME_0, WAIT_FRAME_0};
  int state = IDLE;
}
namespace atkL
{
  enum {IDLE, FRAME_0, WAIT_FRAME_0, DELAY_1, WAIT_DELAY_1, FRAME_2, WAIT_FRAME_2};
  int state = IDLE;
  unsigned long time;
}
namespace atkR
{
  enum {IDLE, FRAME_0, WAIT_FRAME_0, DELAY_1, WAIT_DELAY_1, FRAME_2, WAIT_FRAME_2};
  int state = IDLE;
  unsigned long time;
}
namespace atkC
{
  enum {IDLE, FRAME_0, WAIT_FRAME_0, DELAY_1, WAIT_DELAY_1, FRAME_2, WAIT_FRAME_2};
  int state = IDLE;
  unsigned long time;
}
namespace laugh
{
  enum {IDLE, FRAME_0, WAIT_FRAME_0, FRAME_1, WAIT_FRAME_1, FRAME_2, WAIT_FRAME_2, FRAME_3, WAIT_FRAME_3, FRAME_4, WAIT_FRAME_4, FRAME_5, WAIT_FRAME_5, FRAME_6, WAIT_FRAME_6, FRAME_7, WAIT_FRAME_7, FRAME_8, WAIT_FRAME_8, FRAME_9, WAIT_FRAME_9, FRAME_10, WAIT_FRAME_10, FRAME_11, WAIT_FRAME_11, FRAME_12, WAIT_FRAME_12, FRAME_13, WAIT_FRAME_13, FRAME_14, WAIT_FRAME_14, FRAME_15, WAIT_FRAME_15, FRAME_16, WAIT_FRAME_16, FRAME_17, WAIT_FRAME_17, FRAME_18, WAIT_FRAME_18, FRAME_19, WAIT_FRAME_19, FRAME_20, WAIT_FRAME_20, FRAME_21, WAIT_FRAME_21};
  int state = IDLE;
}
namespace danceALL
{
  enum {IDLE, DELAY_0, WAIT_DELAY_0, MOTION_1, WAIT_MOTION_1, MOTION_2, WAIT_MOTION_2, MOTION_3, WAIT_MOTION_3, MOTION_4, WAIT_MOTION_4, MOTION_5, WAIT_MOTION_5, MOTION_6, WAIT_MOTION_6, MOTION_7, WAIT_MOTION_7, MOTION_8, WAIT_MOTION_8, MOTION_9, WAIT_MOTION_9, MOTION_10, WAIT_MOTION_10, MOTION_11, WAIT_MOTION_11, MOTION_12, WAIT_MOTION_12, MOTION_13, WAIT_MOTION_13, DELAY_14, WAIT_DELAY_14, MOTION_15, WAIT_MOTION_15, MOTION_16, WAIT_MOTION_16, MOTION_17, WAIT_MOTION_17, MOTION_18, WAIT_MOTION_18, MOTION_19, WAIT_MOTION_19, MOTION_20, WAIT_MOTION_20, MOTION_21, WAIT_MOTION_21, MOTION_22, WAIT_MOTION_22, MOTION_23, WAIT_MOTION_23, MOTION_24, WAIT_MOTION_24, MOTION_25, WAIT_MOTION_25, MOTION_26, WAIT_MOTION_26, MOTION_27, WAIT_MOTION_27, MOTION_28, WAIT_MOTION_28, MOTION_29, WAIT_MOTION_29, MOTION_30, WAIT_MOTION_30, MOTION_31, WAIT_MOTION_31, MOTION_32, WAIT_MOTION_32, MOTION_33, WAIT_MOTION_33};
  int state = IDLE;
  unsigned long time;
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
  enum {IDLE, FRAME_0, WAIT_FRAME_0, FRAME_1, WAIT_FRAME_1, FRAME_2, WAIT_FRAME_2, FRAME_3, WAIT_FRAME_3, FRAME_4, WAIT_FRAME_4, FRAME_5, WAIT_FRAME_5, FRAME_6, WAIT_FRAME_6, FRAME_7, WAIT_FRAME_7, FRAME_8, WAIT_FRAME_8, FRAME_9, WAIT_FRAME_9, FRAME_10, WAIT_FRAME_10, FRAME_11, WAIT_FRAME_11, FRAME_12, WAIT_FRAME_12, DELAY_13, WAIT_DELAY_13, FRAME_14, WAIT_FRAME_14, DELAY_15, WAIT_DELAY_15, FRAME_16, WAIT_FRAME_16, DELAY_17, WAIT_DELAY_17};
  int state = IDLE;
  unsigned long time;
}
namespace dance05
{
  enum {IDLE, FLAG_0, FRAME_1, WAIT_FRAME_1, FRAME_2, WAIT_FRAME_2, GOTO_3, FRAME_4, WAIT_FRAME_4, DELAY_5, WAIT_DELAY_5, FRAME_6, WAIT_FRAME_6, DELAY_7, WAIT_DELAY_7};
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
  enum {IDLE, FRAME_0, WAIT_FRAME_0, FRAME_1, WAIT_FRAME_1, FRAME_2, WAIT_FRAME_2, FRAME_3, WAIT_FRAME_3, FRAME_4, WAIT_FRAME_4, FRAME_5, WAIT_FRAME_5, FRAME_6, WAIT_FRAME_6, FRAME_7, WAIT_FRAME_7};
  int state = IDLE;
}
namespace dance08
{
  enum {IDLE, FRAME_0, WAIT_FRAME_0, FRAME_1, WAIT_FRAME_1, FRAME_2, WAIT_FRAME_2, FRAME_3, WAIT_FRAME_3, FRAME_4, WAIT_FRAME_4, FRAME_5, WAIT_FRAME_5, FRAME_6, WAIT_FRAME_6, FRAME_7, WAIT_FRAME_7};
  int state = IDLE;
}
namespace dance09
{
  enum {IDLE, FLAG_0, FRAME_1, WAIT_FRAME_1, FRAME_2, WAIT_FRAME_2, FRAME_3, WAIT_FRAME_3, DELAY_4, WAIT_DELAY_4, FRAME_5, WAIT_FRAME_5, FRAME_6, WAIT_FRAME_6, FRAME_7, WAIT_FRAME_7, FRAME_8, WAIT_FRAME_8, FRAME_9, WAIT_FRAME_9, FRAME_10, WAIT_FRAME_10, GOTO_11};
  int state = IDLE;
  unsigned long time;
  int flag0902_11 = 0;
}
namespace dance10
{
  enum {IDLE, FRAME_0, WAIT_FRAME_0, FRAME_1, WAIT_FRAME_1, FRAME_2, WAIT_FRAME_2, FRAME_3, WAIT_FRAME_3, FRAME_4, WAIT_FRAME_4, FRAME_5, WAIT_FRAME_5, FRAME_6, WAIT_FRAME_6, FRAME_7, WAIT_FRAME_7, FRAME_8, WAIT_FRAME_8, FRAME_9, WAIT_FRAME_9, FRAME_10, WAIT_FRAME_10, FRAME_11, WAIT_FRAME_11, FRAME_12, WAIT_FRAME_12, FRAME_13, WAIT_FRAME_13, FRAME_14, WAIT_FRAME_14, FRAME_15, WAIT_FRAME_15, FRAME_16, WAIT_FRAME_16, FRAME_17, WAIT_FRAME_17, FRAME_18, WAIT_FRAME_18, FRAME_19, WAIT_FRAME_19, FRAME_20, WAIT_FRAME_20};
  int state = IDLE;
}
namespace dance11
{
  enum {IDLE, FLAG_0, FRAME_1, WAIT_FRAME_1, FRAME_2, WAIT_FRAME_2, GOTO_3, FRAME_4, WAIT_FRAME_4, FRAME_5, WAIT_FRAME_5, FRAME_6, WAIT_FRAME_6, FRAME_7, WAIT_FRAME_7, FRAME_8, WAIT_FRAME_8};
  int state = IDLE;
  int flag11_3 = 0;
}
namespace dance12
{
  enum {IDLE, DELAY_0, WAIT_DELAY_0, FRAME_1, WAIT_FRAME_1, FRAME_2, WAIT_FRAME_2, DELAY_3, WAIT_DELAY_3, FRAME_4, WAIT_FRAME_4, DELAY_5, WAIT_DELAY_5, FRAME_6, WAIT_FRAME_6, DELAY_7, WAIT_DELAY_7};
  int state = IDLE;
  unsigned long time;
}
namespace dance13
{
  enum {IDLE, FRAME_0, WAIT_FRAME_0, FRAME_1, WAIT_FRAME_1, FRAME_2, WAIT_FRAME_2, FRAME_3, WAIT_FRAME_3, FRAME_4, WAIT_FRAME_4, FRAME_5, WAIT_FRAME_5, FRAME_6, WAIT_FRAME_6, FRAME_7, WAIT_FRAME_7};
  int state = IDLE;
}
namespace dance14
{
  enum {IDLE, FRAME_0, WAIT_FRAME_0, FRAME_1, WAIT_FRAME_1, FRAME_2, WAIT_FRAME_2, FRAME_3, WAIT_FRAME_3, FRAME_4, WAIT_FRAME_4};
  int state = IDLE;
}
namespace home
{
  enum {IDLE, FRAME_0, WAIT_FRAME_0};
  int state = IDLE;
}
bool isBlocked()
{
  if(external_trigger[_ATKL]) return true;
  if(external_trigger[_ATKR]) return true;
  if(external_trigger[_ATKC]) return true;
  if(external_trigger[_LAUGH]) return true;
  return false;
}
void closeTriggers()
{
  external_trigger[_END]= false; internal_trigger[_END]= false;
  external_trigger[_ATKL]= false; internal_trigger[_ATKL]= false;
  external_trigger[_ATKR]= false; internal_trigger[_ATKR]= false;
  external_trigger[_ATKC]= false; internal_trigger[_ATKC]= false;
  external_trigger[_LAUGH]= false; internal_trigger[_LAUGH]= false;
  external_trigger[_DANCEALL]= false; internal_trigger[_DANCEALL]= false;
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
  external_trigger[_HOME]= false; internal_trigger[_HOME]= false;
}
void updateTrigger()
{
  if(isBlocked()) return;
  if(strcmp(Serial1_Message,"HOME") ==0) {
	  _curr_motion = _HOME;
  }else if(strcmp(Serial1_Message,"ATKL") ==0 || strcmp(Serial1_Message,"ATKR") ==0) {
		_curr_motion = _ATKR;
		Audio.end();
		Audio.begin(88200, 100);
		switch(rand() % 7){
			case 0:		  myFile = SD.open("/sounds/skarner_move1.wav");		  break;
			case 1:		  myFile = SD.open("/sounds/skarner_move2.wav");		  break;
			case 2:		  myFile = SD.open("/sounds/skarner_move3.wav");		  break;
			case 3:		  myFile = SD.open("/sounds/skarner_move4.wav");		  break;
			case 4:		  myFile = SD.open("/sounds/skarner_move5.wav");		  break;
			case 5:		  myFile = SD.open("/sounds/skarner_move6.wav");		  break;
			case 6:		  myFile = SD.open("/sounds/skarner_move9.wav");		  break;
		 }
  }else if(strcmp(Serial1_Message,"ATKC") ==0) {
		_curr_motion = _ATKC;
		Audio.end();
		Audio.begin(88200, 100);
		switch(rand() % 5){
			case 0:		  myFile = SD.open("/sounds/skarner_attack1.wav");		  break;
			case 1:		  myFile = SD.open("/sounds/skarner_attack3.wav");		  break;
			case 2:		  myFile = SD.open("/sounds/skarner_attack5.wav");		  break;
			case 3:		  myFile = SD.open("/sounds/skarner_attack6.wav");		  break;
			case 4:		  myFile = SD.open("/sounds/skarner_attack7.wav");		  break;
		 }
  }else if(strcmp(Serial1_Message,"LAUGH") ==0) {
		_curr_motion = _LAUGH;
		Audio.end();
		Audio.begin(44100, 100);
		switch(rand() % 2){
			case 0:		  myFile = SD.open("/sounds/skarner_laugh1.wav");		  break;
			case 1:		  myFile = SD.open("/sounds/skarner_laugh4.wav");		  break;
		 }
  }
  else if(strcmp(Serial1_Message,"END") ==0) {_curr_motion = _END;}
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
    atkL::state = 0;
    atkR::state = 0;
    atkC::state = 0;
    laugh::state = 0;
    danceALL::state = 0;
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
    dance09::flag0902_11 = 0;
    dance10::state = 0;
    dance11::state = 0;
    dance11::flag11_3 = 0;
    dance12::state = 0;
    dance13::state = 0;
    dance14::state = 0;
    home::state = 0;
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
    END_frm[0].playPositions(1920);
    END::state = END::WAIT_FRAME_0;
  case END::WAIT_FRAME_0:
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
void atkLUpdate()
{
  switch(atkL::state)
  {
  case atkL::IDLE:
    if(external_trigger[_ATKL] || internal_trigger[_ATKL]) atkL::state = atkL::FRAME_0;
    else break;
  case atkL::FRAME_0:
    atkL_frm[0].playPositions(240);
    atkL::state = atkL::WAIT_FRAME_0;
  case atkL::WAIT_FRAME_0:
    if(!isServoMultiMoving())
      atkL::state = atkL::DELAY_1;
    break;
  case atkL::DELAY_1:
    atkL::time = millis();
    atkL::state = atkL::WAIT_DELAY_1;
  case atkL::WAIT_DELAY_1:
    if(millis() - atkL::time >= 240)
      atkL::state = atkL::FRAME_2;
    break;
  case atkL::FRAME_2:
    atkL_frm[1].playPositions(480);
    atkL::state = atkL::WAIT_FRAME_2;
  case atkL::WAIT_FRAME_2:
    if(!isServoMultiMoving())
    {
      atkL::state = atkL::IDLE;
      internal_trigger[_ATKL] = false;
      external_trigger[_ATKL] = false;
    }
    break;
  default:
    break;
  }
}
void atkRUpdate()
{
  switch(atkR::state)
  {
  case atkR::IDLE:
    if(external_trigger[_ATKR] || internal_trigger[_ATKR]) atkR::state = atkR::FRAME_0;
    else break;
  case atkR::FRAME_0:
    atkR_frm[0].playPositions(240);
    atkR::state = atkR::WAIT_FRAME_0;
  case atkR::WAIT_FRAME_0:
    if(!isServoMultiMoving())
      atkR::state = atkR::DELAY_1;
    break;
  case atkR::DELAY_1:
    atkR::time = millis();
    atkR::state = atkR::WAIT_DELAY_1;
  case atkR::WAIT_DELAY_1:
    if(millis() - atkR::time >= 240)
      atkR::state = atkR::FRAME_2;
    break;
  case atkR::FRAME_2:
    atkR_frm[1].playPositions(480);
    atkR::state = atkR::WAIT_FRAME_2;
  case atkR::WAIT_FRAME_2:
    if(!isServoMultiMoving())
    {
      atkR::state = atkR::IDLE;
      internal_trigger[_ATKR] = false;
      external_trigger[_ATKR] = false;
    }
    break;
  default:
    break;
  }
}
void atkCUpdate()
{
  switch(atkC::state)
  {
  case atkC::IDLE:
    if(external_trigger[_ATKC] || internal_trigger[_ATKC]) atkC::state = atkC::FRAME_0;
    else break;
  case atkC::FRAME_0:
    atkC_frm[0].playPositions(240);
    atkC::state = atkC::WAIT_FRAME_0;
  case atkC::WAIT_FRAME_0:
    if(!isServoMultiMoving())
      atkC::state = atkC::DELAY_1;
    break;
  case atkC::DELAY_1:
    atkC::time = millis();
    atkC::state = atkC::WAIT_DELAY_1;
  case atkC::WAIT_DELAY_1:
    if(millis() - atkC::time >= 240)
      atkC::state = atkC::FRAME_2;
    break;
  case atkC::FRAME_2:
    atkC_frm[1].playPositions(480);
    atkC::state = atkC::WAIT_FRAME_2;
  case atkC::WAIT_FRAME_2:
    if(!isServoMultiMoving())
    {
      atkC::state = atkC::IDLE;
      internal_trigger[_ATKC] = false;
      external_trigger[_ATKC] = false;
    }
    break;
  default:
    break;
  }
}
void laughUpdate()
{
  switch(laugh::state)
  {
  case laugh::IDLE:
    if(external_trigger[_LAUGH] || internal_trigger[_LAUGH]) laugh::state = laugh::FRAME_0;
    else break;
  case laugh::FRAME_0:
    laugh_frm[0].playPositions(240);
    laugh::state = laugh::WAIT_FRAME_0;
  case laugh::WAIT_FRAME_0:
    if(!isServoMultiMoving())
      laugh::state = laugh::FRAME_1;
    break;
  case laugh::FRAME_1:
    laugh_frm[1].playPositions(120);
    laugh::state = laugh::WAIT_FRAME_1;
  case laugh::WAIT_FRAME_1:
    if(!isServoMultiMoving())
      laugh::state = laugh::FRAME_2;
    break;
  case laugh::FRAME_2:
    laugh_frm[2].playPositions(120);
    laugh::state = laugh::WAIT_FRAME_2;
  case laugh::WAIT_FRAME_2:
    if(!isServoMultiMoving())
      laugh::state = laugh::FRAME_3;
    break;
  case laugh::FRAME_3:
    laugh_frm[3].playPositions(120);
    laugh::state = laugh::WAIT_FRAME_3;
  case laugh::WAIT_FRAME_3:
    if(!isServoMultiMoving())
      laugh::state = laugh::FRAME_4;
    break;
  case laugh::FRAME_4:
    laugh_frm[4].playPositions(120);
    laugh::state = laugh::WAIT_FRAME_4;
  case laugh::WAIT_FRAME_4:
    if(!isServoMultiMoving())
      laugh::state = laugh::FRAME_5;
    break;
  case laugh::FRAME_5:
    laugh_frm[5].playPositions(120);
    laugh::state = laugh::WAIT_FRAME_5;
  case laugh::WAIT_FRAME_5:
    if(!isServoMultiMoving())
      laugh::state = laugh::FRAME_6;
    break;
  case laugh::FRAME_6:
    laugh_frm[6].playPositions(120);
    laugh::state = laugh::WAIT_FRAME_6;
  case laugh::WAIT_FRAME_6:
    if(!isServoMultiMoving())
      laugh::state = laugh::FRAME_7;
    break;
  case laugh::FRAME_7:
    laugh_frm[7].playPositions(120);
    laugh::state = laugh::WAIT_FRAME_7;
  case laugh::WAIT_FRAME_7:
    if(!isServoMultiMoving())
      laugh::state = laugh::FRAME_8;
    break;
  case laugh::FRAME_8:
    laugh_frm[8].playPositions(120);
    laugh::state = laugh::WAIT_FRAME_8;
  case laugh::WAIT_FRAME_8:
    if(!isServoMultiMoving())
      laugh::state = laugh::FRAME_9;
    break;
  case laugh::FRAME_9:
    laugh_frm[9].playPositions(120);
    laugh::state = laugh::WAIT_FRAME_9;
  case laugh::WAIT_FRAME_9:
    if(!isServoMultiMoving())
      laugh::state = laugh::FRAME_10;
    break;
  case laugh::FRAME_10:
    laugh_frm[10].playPositions(120);
    laugh::state = laugh::WAIT_FRAME_10;
  case laugh::WAIT_FRAME_10:
    if(!isServoMultiMoving())
      laugh::state = laugh::FRAME_11;
    break;
  case laugh::FRAME_11:
    laugh_frm[11].playPositions(120);
    laugh::state = laugh::WAIT_FRAME_11;
  case laugh::WAIT_FRAME_11:
    if(!isServoMultiMoving())
      laugh::state = laugh::FRAME_12;
    break;
  case laugh::FRAME_12:
    laugh_frm[12].playPositions(120);
    laugh::state = laugh::WAIT_FRAME_12;
  case laugh::WAIT_FRAME_12:
    if(!isServoMultiMoving())
      laugh::state = laugh::FRAME_13;
    break;
  case laugh::FRAME_13:
    laugh_frm[13].playPositions(120);
    laugh::state = laugh::WAIT_FRAME_13;
  case laugh::WAIT_FRAME_13:
    if(!isServoMultiMoving())
      laugh::state = laugh::FRAME_14;
    break;
  case laugh::FRAME_14:
    laugh_frm[14].playPositions(120);
    laugh::state = laugh::WAIT_FRAME_14;
  case laugh::WAIT_FRAME_14:
    if(!isServoMultiMoving())
      laugh::state = laugh::FRAME_15;
    break;
  case laugh::FRAME_15:
    laugh_frm[15].playPositions(120);
    laugh::state = laugh::WAIT_FRAME_15;
  case laugh::WAIT_FRAME_15:
    if(!isServoMultiMoving())
      laugh::state = laugh::FRAME_16;
    break;
  case laugh::FRAME_16:
    laugh_frm[16].playPositions(120);
    laugh::state = laugh::WAIT_FRAME_16;
  case laugh::WAIT_FRAME_16:
    if(!isServoMultiMoving())
      laugh::state = laugh::FRAME_17;
    break;
  case laugh::FRAME_17:
    laugh_frm[17].playPositions(120);
    laugh::state = laugh::WAIT_FRAME_17;
  case laugh::WAIT_FRAME_17:
    if(!isServoMultiMoving())
      laugh::state = laugh::FRAME_18;
    break;
  case laugh::FRAME_18:
    laugh_frm[18].playPositions(120);
    laugh::state = laugh::WAIT_FRAME_18;
  case laugh::WAIT_FRAME_18:
    if(!isServoMultiMoving())
      laugh::state = laugh::FRAME_19;
    break;
  case laugh::FRAME_19:
    laugh_frm[19].playPositions(120);
    laugh::state = laugh::WAIT_FRAME_19;
  case laugh::WAIT_FRAME_19:
    if(!isServoMultiMoving())
      laugh::state = laugh::FRAME_20;
    break;
  case laugh::FRAME_20:
    laugh_frm[20].playPositions(120);
    laugh::state = laugh::WAIT_FRAME_20;
  case laugh::WAIT_FRAME_20:
    if(!isServoMultiMoving())
      laugh::state = laugh::FRAME_21;
    break;
  case laugh::FRAME_21:
    laugh_frm[21].playPositions(480);
    laugh::state = laugh::WAIT_FRAME_21;
  case laugh::WAIT_FRAME_21:
    if(!isServoMultiMoving())
    {
      laugh::state = laugh::IDLE;
      internal_trigger[_LAUGH] = false;
      external_trigger[_LAUGH] = false;
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
    dance09::flag0902_11 = 0;
    danceALL::state = danceALL::WAIT_MOTION_9;
    internal_trigger[_DANCE09] = true;
    dance09::state = dance09::IDLE;
  case danceALL::WAIT_MOTION_9:
    if(!internal_trigger[_DANCE09])
      danceALL::state = danceALL::MOTION_10;
    break;
  case danceALL::MOTION_10:
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
    dance09::flag0902_11 = 0;
    danceALL::state = danceALL::WAIT_MOTION_23;
    internal_trigger[_DANCE09] = true;
    dance09::state = dance09::IDLE;
  case danceALL::WAIT_MOTION_23:
    if(!internal_trigger[_DANCE09])
      danceALL::state = danceALL::MOTION_24;
    break;
  case danceALL::MOTION_24:
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
    dance04_frm[12].playPositions(120);
    dance04::state = dance04::WAIT_FRAME_12;
  case dance04::WAIT_FRAME_12:
    if(!isServoMultiMoving())
      dance04::state = dance04::DELAY_13;
    break;
  case dance04::DELAY_13:
    dance04::time = millis();
    dance04::state = dance04::WAIT_DELAY_13;
  case dance04::WAIT_DELAY_13:
    if(millis() - dance04::time >= 120)
      dance04::state = dance04::FRAME_14;
    break;
  case dance04::FRAME_14:
    dance04_frm[13].playPositions(240);
    dance04::state = dance04::WAIT_FRAME_14;
  case dance04::WAIT_FRAME_14:
    if(!isServoMultiMoving())
      dance04::state = dance04::DELAY_15;
    break;
  case dance04::DELAY_15:
    dance04::time = millis();
    dance04::state = dance04::WAIT_DELAY_15;
  case dance04::WAIT_DELAY_15:
    if(millis() - dance04::time >= 120)
      dance04::state = dance04::FRAME_16;
    break;
  case dance04::FRAME_16:
    dance04_frm[14].playPositions(240);
    dance04::state = dance04::WAIT_FRAME_16;
  case dance04::WAIT_FRAME_16:
    if(!isServoMultiMoving())
      dance04::state = dance04::DELAY_17;
    break;
  case dance04::DELAY_17:
    dance04::time = millis();
    dance04::state = dance04::WAIT_DELAY_17;
  case dance04::WAIT_DELAY_17:
    if(millis() - dance04::time >= 120)
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
    dance05_frm[2].playPositions(240);
    dance05::state = dance05::WAIT_FRAME_4;
  case dance05::WAIT_FRAME_4:
    if(!isServoMultiMoving())
      dance05::state = dance05::DELAY_5;
    break;
  case dance05::DELAY_5:
    dance05::time = millis();
    dance05::state = dance05::WAIT_DELAY_5;
  case dance05::WAIT_DELAY_5:
    if(millis() - dance05::time >= 240)
      dance05::state = dance05::FRAME_6;
    break;
  case dance05::FRAME_6:
    dance05_frm[3].playPositions(240);
    dance05::state = dance05::WAIT_FRAME_6;
  case dance05::WAIT_FRAME_6:
    if(!isServoMultiMoving())
      dance05::state = dance05::DELAY_7;
    break;
  case dance05::DELAY_7:
    dance05::time = millis();
    dance05::state = dance05::WAIT_DELAY_7;
  case dance05::WAIT_DELAY_7:
    if(millis() - dance05::time >= 240)
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
    dance07_frm[0].playPositions(480);
    dance07::state = dance07::WAIT_FRAME_0;
  case dance07::WAIT_FRAME_0:
    if(!isServoMultiMoving())
      dance07::state = dance07::FRAME_1;
    break;
  case dance07::FRAME_1:
    dance07_frm[1].playPositions(480);
    dance07::state = dance07::WAIT_FRAME_1;
  case dance07::WAIT_FRAME_1:
    if(!isServoMultiMoving())
      dance07::state = dance07::FRAME_2;
    break;
  case dance07::FRAME_2:
    dance07_frm[2].playPositions(480);
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
      dance07::state = dance07::FRAME_4;
    break;
  case dance07::FRAME_4:
    dance07_frm[4].playPositions(480);
    dance07::state = dance07::WAIT_FRAME_4;
  case dance07::WAIT_FRAME_4:
    if(!isServoMultiMoving())
      dance07::state = dance07::FRAME_5;
    break;
  case dance07::FRAME_5:
    dance07_frm[5].playPositions(480);
    dance07::state = dance07::WAIT_FRAME_5;
  case dance07::WAIT_FRAME_5:
    if(!isServoMultiMoving())
      dance07::state = dance07::FRAME_6;
    break;
  case dance07::FRAME_6:
    dance07_frm[6].playPositions(480);
    dance07::state = dance07::WAIT_FRAME_6;
  case dance07::WAIT_FRAME_6:
    if(!isServoMultiMoving())
      dance07::state = dance07::FRAME_7;
    break;
  case dance07::FRAME_7:
    dance07_frm[7].playPositions(480);
    dance07::state = dance07::WAIT_FRAME_7;
  case dance07::WAIT_FRAME_7:
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
    dance08_frm[0].playPositions(480);
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
    dance08_frm[2].playPositions(720);
    dance08::state = dance08::WAIT_FRAME_2;
  case dance08::WAIT_FRAME_2:
    if(!isServoMultiMoving())
      dance08::state = dance08::FRAME_3;
    break;
  case dance08::FRAME_3:
    dance08_frm[3].playPositions(480);
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
    dance08_frm[5].playPositions(360);
    dance08::state = dance08::WAIT_FRAME_5;
  case dance08::WAIT_FRAME_5:
    if(!isServoMultiMoving())
      dance08::state = dance08::FRAME_6;
    break;
  case dance08::FRAME_6:
    dance08_frm[6].playPositions(720);
    dance08::state = dance08::WAIT_FRAME_6;
  case dance08::WAIT_FRAME_6:
    if(!isServoMultiMoving())
      dance08::state = dance08::FRAME_7;
    break;
  case dance08::FRAME_7:
    dance08_frm[7].playPositions(480);
    dance08::state = dance08::WAIT_FRAME_7;
  case dance08::WAIT_FRAME_7:
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
    dance09_frm[0].playPositions(120);
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
      dance09::state = dance09::FRAME_3;
    break;
  case dance09::FRAME_3:
    dance09_frm[2].playPositions(120);
    dance09::state = dance09::WAIT_FRAME_3;
  case dance09::WAIT_FRAME_3:
    if(!isServoMultiMoving())
      dance09::state = dance09::DELAY_4;
    break;
  case dance09::DELAY_4:
    dance09::time = millis();
    dance09::state = dance09::WAIT_DELAY_4;
  case dance09::WAIT_DELAY_4:
    if(millis() - dance09::time >= 480)
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
      dance09::state = dance09::FRAME_10;
    break;
  case dance09::FRAME_10:
    dance09_frm[8].playPositions(160);
    dance09::state = dance09::WAIT_FRAME_10;
  case dance09::WAIT_FRAME_10:
    if(!isServoMultiMoving())
      dance09::state = dance09::GOTO_11;
    break;
  case dance09::GOTO_11:
    if(dance09::flag0902_11++ < 1) goto flag_dance09_flag0902_0;
    else
    {
      dance09::flag0902_11 = 0;
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
    dance10_frm[0].playPositions(120);
    dance10::state = dance10::WAIT_FRAME_0;
  case dance10::WAIT_FRAME_0:
    if(!isServoMultiMoving())
      dance10::state = dance10::FRAME_1;
    break;
  case dance10::FRAME_1:
    dance10_frm[1].playPositions(120);
    dance10::state = dance10::WAIT_FRAME_1;
  case dance10::WAIT_FRAME_1:
    if(!isServoMultiMoving())
      dance10::state = dance10::FRAME_2;
    break;
  case dance10::FRAME_2:
    dance10_frm[2].playPositions(120);
    dance10::state = dance10::WAIT_FRAME_2;
  case dance10::WAIT_FRAME_2:
    if(!isServoMultiMoving())
      dance10::state = dance10::FRAME_3;
    break;
  case dance10::FRAME_3:
    dance10_frm[3].playPositions(120);
    dance10::state = dance10::WAIT_FRAME_3;
  case dance10::WAIT_FRAME_3:
    if(!isServoMultiMoving())
      dance10::state = dance10::FRAME_4;
    break;
  case dance10::FRAME_4:
    dance10_frm[4].playPositions(120);
    dance10::state = dance10::WAIT_FRAME_4;
  case dance10::WAIT_FRAME_4:
    if(!isServoMultiMoving())
      dance10::state = dance10::FRAME_5;
    break;
  case dance10::FRAME_5:
    dance10_frm[5].playPositions(120);
    dance10::state = dance10::WAIT_FRAME_5;
  case dance10::WAIT_FRAME_5:
    if(!isServoMultiMoving())
      dance10::state = dance10::FRAME_6;
    break;
  case dance10::FRAME_6:
    dance10_frm[6].playPositions(120);
    dance10::state = dance10::WAIT_FRAME_6;
  case dance10::WAIT_FRAME_6:
    if(!isServoMultiMoving())
      dance10::state = dance10::FRAME_7;
    break;
  case dance10::FRAME_7:
    dance10_frm[7].playPositions(120);
    dance10::state = dance10::WAIT_FRAME_7;
  case dance10::WAIT_FRAME_7:
    if(!isServoMultiMoving())
      dance10::state = dance10::FRAME_8;
    break;
  case dance10::FRAME_8:
    dance10_frm[8].playPositions(120);
    dance10::state = dance10::WAIT_FRAME_8;
  case dance10::WAIT_FRAME_8:
    if(!isServoMultiMoving())
      dance10::state = dance10::FRAME_9;
    break;
  case dance10::FRAME_9:
    dance10_frm[9].playPositions(120);
    dance10::state = dance10::WAIT_FRAME_9;
  case dance10::WAIT_FRAME_9:
    if(!isServoMultiMoving())
      dance10::state = dance10::FRAME_10;
    break;
  case dance10::FRAME_10:
    dance10_frm[10].playPositions(120);
    dance10::state = dance10::WAIT_FRAME_10;
  case dance10::WAIT_FRAME_10:
    if(!isServoMultiMoving())
      dance10::state = dance10::FRAME_11;
    break;
  case dance10::FRAME_11:
    dance10_frm[11].playPositions(120);
    dance10::state = dance10::WAIT_FRAME_11;
  case dance10::WAIT_FRAME_11:
    if(!isServoMultiMoving())
      dance10::state = dance10::FRAME_12;
    break;
  case dance10::FRAME_12:
    dance10_frm[12].playPositions(120);
    dance10::state = dance10::WAIT_FRAME_12;
  case dance10::WAIT_FRAME_12:
    if(!isServoMultiMoving())
      dance10::state = dance10::FRAME_13;
    break;
  case dance10::FRAME_13:
    dance10_frm[13].playPositions(120);
    dance10::state = dance10::WAIT_FRAME_13;
  case dance10::WAIT_FRAME_13:
    if(!isServoMultiMoving())
      dance10::state = dance10::FRAME_14;
    break;
  case dance10::FRAME_14:
    dance10_frm[14].playPositions(120);
    dance10::state = dance10::WAIT_FRAME_14;
  case dance10::WAIT_FRAME_14:
    if(!isServoMultiMoving())
      dance10::state = dance10::FRAME_15;
    break;
  case dance10::FRAME_15:
    dance10_frm[15].playPositions(120);
    dance10::state = dance10::WAIT_FRAME_15;
  case dance10::WAIT_FRAME_15:
    if(!isServoMultiMoving())
      dance10::state = dance10::FRAME_16;
    break;
  case dance10::FRAME_16:
    dance10_frm[16].playPositions(120);
    dance10::state = dance10::WAIT_FRAME_16;
  case dance10::WAIT_FRAME_16:
    if(!isServoMultiMoving())
      dance10::state = dance10::FRAME_17;
    break;
  case dance10::FRAME_17:
    dance10_frm[17].playPositions(120);
    dance10::state = dance10::WAIT_FRAME_17;
  case dance10::WAIT_FRAME_17:
    if(!isServoMultiMoving())
      dance10::state = dance10::FRAME_18;
    break;
  case dance10::FRAME_18:
    dance10_frm[18].playPositions(120);
    dance10::state = dance10::WAIT_FRAME_18;
  case dance10::WAIT_FRAME_18:
    if(!isServoMultiMoving())
      dance10::state = dance10::FRAME_19;
    break;
  case dance10::FRAME_19:
    dance10_frm[19].playPositions(120);
    dance10::state = dance10::WAIT_FRAME_19;
  case dance10::WAIT_FRAME_19:
    if(!isServoMultiMoving())
      dance10::state = dance10::FRAME_20;
    break;
  case dance10::FRAME_20:
    dance10_frm[20].playPositions(480);
    dance10::state = dance10::WAIT_FRAME_20;
  case dance10::WAIT_FRAME_20:
    if(!isServoMultiMoving())
    {
      dance10::state = dance10::IDLE;
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
    if(dance11::flag11_3++ < 3) goto flag_dance11_flag11_0;
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
    dance11_frm[6].playPositions(480);
    dance11::state = dance11::WAIT_FRAME_8;
  case dance11::WAIT_FRAME_8:
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
    dance12_frm[0].playPositions(480);
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
      dance12::state = dance12::DELAY_3;
    break;
  case dance12::DELAY_3:
    dance12::time = millis();
    dance12::state = dance12::WAIT_DELAY_3;
  case dance12::WAIT_DELAY_3:
    if(millis() - dance12::time >= 720)
      dance12::state = dance12::FRAME_4;
    break;
  case dance12::FRAME_4:
    dance12_frm[2].playPositions(240);
    dance12::state = dance12::WAIT_FRAME_4;
  case dance12::WAIT_FRAME_4:
    if(!isServoMultiMoving())
      dance12::state = dance12::DELAY_5;
    break;
  case dance12::DELAY_5:
    dance12::time = millis();
    dance12::state = dance12::WAIT_DELAY_5;
  case dance12::WAIT_DELAY_5:
    if(millis() - dance12::time >= 1440)
      dance12::state = dance12::FRAME_6;
    break;
  case dance12::FRAME_6:
    dance12_frm[3].playPositions(720);
    dance12::state = dance12::WAIT_FRAME_6;
  case dance12::WAIT_FRAME_6:
    if(!isServoMultiMoving())
      dance12::state = dance12::DELAY_7;
    break;
  case dance12::DELAY_7:
    dance12::time = millis();
    dance12::state = dance12::WAIT_DELAY_7;
  case dance12::WAIT_DELAY_7:
    if(millis() - dance12::time >= 240)
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
    dance13_frm[0].playPositions(360);
    dance13::state = dance13::WAIT_FRAME_0;
  case dance13::WAIT_FRAME_0:
    if(!isServoMultiMoving())
      dance13::state = dance13::FRAME_1;
    break;
  case dance13::FRAME_1:
    dance13_frm[1].playPositions(360);
    dance13::state = dance13::WAIT_FRAME_1;
  case dance13::WAIT_FRAME_1:
    if(!isServoMultiMoving())
      dance13::state = dance13::FRAME_2;
    break;
  case dance13::FRAME_2:
    dance13_frm[2].playPositions(360);
    dance13::state = dance13::WAIT_FRAME_2;
  case dance13::WAIT_FRAME_2:
    if(!isServoMultiMoving())
      dance13::state = dance13::FRAME_3;
    break;
  case dance13::FRAME_3:
    dance13_frm[3].playPositions(360);
    dance13::state = dance13::WAIT_FRAME_3;
  case dance13::WAIT_FRAME_3:
    if(!isServoMultiMoving())
      dance13::state = dance13::FRAME_4;
    break;
  case dance13::FRAME_4:
    dance13_frm[4].playPositions(360);
    dance13::state = dance13::WAIT_FRAME_4;
  case dance13::WAIT_FRAME_4:
    if(!isServoMultiMoving())
      dance13::state = dance13::FRAME_5;
    break;
  case dance13::FRAME_5:
    dance13_frm[5].playPositions(360);
    dance13::state = dance13::WAIT_FRAME_5;
  case dance13::WAIT_FRAME_5:
    if(!isServoMultiMoving())
      dance13::state = dance13::FRAME_6;
    break;
  case dance13::FRAME_6:
    dance13_frm[6].playPositions(360);
    dance13::state = dance13::WAIT_FRAME_6;
  case dance13::WAIT_FRAME_6:
    if(!isServoMultiMoving())
      dance13::state = dance13::FRAME_7;
    break;
  case dance13::FRAME_7:
    dance13_frm[7].playPositions(360);
    dance13::state = dance13::WAIT_FRAME_7;
  case dance13::WAIT_FRAME_7:
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
    dance14_frm[1].playPositions(960);
    dance14::state = dance14::WAIT_FRAME_1;
  case dance14::WAIT_FRAME_1:
    if(!isServoMultiMoving())
      dance14::state = dance14::FRAME_2;
    break;
  case dance14::FRAME_2:
    dance14_frm[2].playPositions(960);
    dance14::state = dance14::WAIT_FRAME_2;
  case dance14::WAIT_FRAME_2:
    if(!isServoMultiMoving())
      dance14::state = dance14::FRAME_3;
    break;
  case dance14::FRAME_3:
    dance14_frm[3].playPositions(960);
    dance14::state = dance14::WAIT_FRAME_3;
  case dance14::WAIT_FRAME_3:
    if(!isServoMultiMoving())
      dance14::state = dance14::FRAME_4;
    break;
  case dance14::FRAME_4:
    dance14_frm[4].playPositions(960);
    dance14::state = dance14::WAIT_FRAME_4;
  case dance14::WAIT_FRAME_4:
    if(!isServoMultiMoving())
    {
      dance14::state = dance14::IDLE;
      internal_trigger[_DANCE14] = false;
      external_trigger[_DANCE14] = false;
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
    home_frm[0].playPositions(960);
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
void setup()
{
  io_outpb(0x0A12,0x00); //disable COM1 TX pin
  io_outpb(0x0A13,0x00); //disable COM1 RX pin
  io_outpb(0x0A20,0x02); //SPICS to RX
  io_outpb(0x0A22,0x01); //SPIDI to DX
  nh.getHardware()->setESP8266(Serial1, 115200);
  nh.getHardware()->setWiFi("RoBoardGod", "00000000");
  nh.initNode("10.0.0.1");	//ROS-Host IP address
  nh.subscribe(sub);
  pinMode(13, OUTPUT);	//Skarner's eyes LED
  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  Audio.begin(88200, 100);
  srand(time(NULL));

  myservo2.attach(2);
  myservo3.attach(3);
  myservo6.attach(6);
  myservo7.attach(7);
  myservo10.attach(10);
  myservo11.attach(11);
  myservo21.attach(21);
  myservo22.attach(22);
  myservo23.attach(23);
  myservo24.attach(24);
  myservo25.attach(25);
  myservo26.attach(26);
  myservo27.attach(27);
  myservo28.attach(28);
  myservo29.attach(29);
  myservo30.attach(30);
  myservo31.attach(31);
  myservo32.attach(32);
  myservo33.attach(33);
  myservo34.attach(34);
  myservo35.attach(35);
  myservo36.attach(36);
  myservo37.attach(37);
  myservo38.attach(38);

  myoffs.offsets[6] = 0;
  myoffs.offsets[7] = 0;
  myoffs.offsets[10] = 0;
  myoffs.offsets[12] = 0;
  myoffs.offsets[13] = 0;
  myoffs.offsets[14] = 0;
  myoffs.offsets[15] = 0;
  myoffs.offsets[16] = 0;
  myoffs.offsets[18] = 0;
  myoffs.offsets[19] = 0;
  myoffs.offsets[22] = 0;

  END_frm[0].positions[0] = 1223;
  END_frm[0].positions[1] = 1776;
  END_frm[0].positions[2] = 1776;
  END_frm[0].positions[3] = 853;
  END_frm[0].positions[4] = 1500;
  END_frm[0].positions[5] = 2146;
  END_frm[0].positions[6] = 1422;
  END_frm[0].positions[7] = 1340;
  END_frm[0].positions[8] = 1222;
  END_frm[0].positions[9] = 1488;
  END_frm[0].positions[10] = 1363;
  END_frm[0].positions[11] = 1346;
  END_frm[0].positions[12] = 1599;
  END_frm[0].positions[13] = 1413;
  END_frm[0].positions[14] = 1442;
  END_frm[0].positions[15] = 1400;
  END_frm[0].positions[16] = 1586;
  END_frm[0].positions[17] = 1442;
  END_frm[0].positions[18] = 1511;
  END_frm[0].positions[19] = 1636;
  END_frm[0].positions[20] = 1346;
  END_frm[0].positions[21] = 1577;
  END_frm[0].positions[22] = 1659;
  END_frm[0].positions[23] = 1222;

  atkL_frm[0].positions[0] = 1776;
  atkL_frm[0].positions[1] = 2146;
  atkL_frm[0].positions[2] = 1223;
  atkL_frm[0].positions[3] = 1315;
  atkL_frm[0].positions[4] = 1315;
  atkL_frm[0].positions[5] = 2146;
  atkL_frm[0].positions[6] = 1324;
  atkL_frm[0].positions[7] = 1085;
  atkL_frm[0].positions[8] = 1542;
  atkL_frm[0].positions[9] = 1228;
  atkL_frm[0].positions[10] = 1049;
  atkL_frm[0].positions[11] = 1637;
  atkL_frm[0].positions[12] = 1179;
  atkL_frm[0].positions[13] = 1048;
  atkL_frm[0].positions[14] = 1761;
  atkL_frm[0].positions[15] = 1278;
  atkL_frm[0].positions[16] = 1353;
  atkL_frm[0].positions[17] = 1806;
  atkL_frm[0].positions[18] = 1167;
  atkL_frm[0].positions[19] = 1289;
  atkL_frm[0].positions[20] = 1677;
  atkL_frm[0].positions[21] = 959;
  atkL_frm[0].positions[22] = 1166;
  atkL_frm[0].positions[23] = 1575;

  atkL_frm[1].positions[0] = 1776;
  atkL_frm[1].positions[1] = 2146;
  atkL_frm[1].positions[2] = 1223;
  atkL_frm[1].positions[3] = 853;
  atkL_frm[1].positions[4] = 1499;
  atkL_frm[1].positions[5] = 2146;
  atkL_frm[1].positions[6] = 1487;
  atkL_frm[1].positions[7] = 1363;
  atkL_frm[1].positions[8] = 1405;
  atkL_frm[1].positions[9] = 1477;
  atkL_frm[1].positions[10] = 1359;
  atkL_frm[1].positions[11] = 1500;
  atkL_frm[1].positions[12] = 1487;
  atkL_frm[1].positions[13] = 1363;
  atkL_frm[1].positions[14] = 1594;
  atkL_frm[1].positions[15] = 1512;
  atkL_frm[1].positions[16] = 1636;
  atkL_frm[1].positions[17] = 1594;
  atkL_frm[1].positions[18] = 1522;
  atkL_frm[1].positions[19] = 1640;
  atkL_frm[1].positions[20] = 1500;
  atkL_frm[1].positions[21] = 1512;
  atkL_frm[1].positions[22] = 1636;
  atkL_frm[1].positions[23] = 1405;

  atkR_frm[0].positions[0] = 1776;
  atkR_frm[0].positions[1] = 1684;
  atkR_frm[0].positions[2] = 1223;
  atkR_frm[0].positions[3] = 853;
  atkR_frm[0].positions[4] = 1684;
  atkR_frm[0].positions[5] = 2146;
  atkR_frm[0].positions[6] = 1721;
  atkR_frm[0].positions[7] = 1646;
  atkR_frm[0].positions[8] = 1193;
  atkR_frm[0].positions[9] = 1832;
  atkR_frm[0].positions[10] = 1710;
  atkR_frm[0].positions[11] = 1322;
  atkR_frm[0].positions[12] = 2040;
  atkR_frm[0].positions[13] = 1833;
  atkR_frm[0].positions[14] = 1424;
  atkR_frm[0].positions[15] = 1675;
  atkR_frm[0].positions[16] = 1914;
  atkR_frm[0].positions[17] = 1457;
  atkR_frm[0].positions[18] = 1771;
  atkR_frm[0].positions[19] = 1950;
  atkR_frm[0].positions[20] = 1362;
  atkR_frm[0].positions[21] = 1820;
  atkR_frm[0].positions[22] = 1951;
  atkR_frm[0].positions[23] = 1238;

  atkR_frm[1].positions[0] = 1776;
  atkR_frm[1].positions[1] = 2146;
  atkR_frm[1].positions[2] = 1223;
  atkR_frm[1].positions[3] = 853;
  atkR_frm[1].positions[4] = 1500;
  atkR_frm[1].positions[5] = 2146;
  atkR_frm[1].positions[6] = 1487;
  atkR_frm[1].positions[7] = 1363;
  atkR_frm[1].positions[8] = 1405;
  atkR_frm[1].positions[9] = 1477;
  atkR_frm[1].positions[10] = 1359;
  atkR_frm[1].positions[11] = 1499;
  atkR_frm[1].positions[12] = 1487;
  atkR_frm[1].positions[13] = 1363;
  atkR_frm[1].positions[14] = 1594;
  atkR_frm[1].positions[15] = 1512;
  atkR_frm[1].positions[16] = 1636;
  atkR_frm[1].positions[17] = 1594;
  atkR_frm[1].positions[18] = 1522;
  atkR_frm[1].positions[19] = 1640;
  atkR_frm[1].positions[20] = 1499;
  atkR_frm[1].positions[21] = 1512;
  atkR_frm[1].positions[22] = 1636;
  atkR_frm[1].positions[23] = 1405;

  atkC_frm[0].positions[0] = 1776;
  atkC_frm[0].positions[1] = 1684;
  atkC_frm[0].positions[2] = 1223;
  atkC_frm[0].positions[3] = 1315;
  atkC_frm[0].positions[4] = 1499;
  atkC_frm[0].positions[5] = 2238;
  atkC_frm[0].positions[6] = 1689;
  atkC_frm[0].positions[7] = 1574;
  atkC_frm[0].positions[8] = 1453;
  atkC_frm[0].positions[9] = 1483;
  atkC_frm[0].positions[10] = 1365;
  atkC_frm[0].positions[11] = 1540;
  atkC_frm[0].positions[12] = 1328;
  atkC_frm[0].positions[13] = 1166;
  atkC_frm[0].positions[14] = 1625;
  atkC_frm[0].positions[15] = 1310;
  atkC_frm[0].positions[16] = 1425;
  atkC_frm[0].positions[17] = 1546;
  atkC_frm[0].positions[18] = 1516;
  atkC_frm[0].positions[19] = 1634;
  atkC_frm[0].positions[20] = 1459;
  atkC_frm[0].positions[21] = 1671;
  atkC_frm[0].positions[22] = 1833;
  atkC_frm[0].positions[23] = 1374;

  atkC_frm[1].positions[0] = 1776;
  atkC_frm[1].positions[1] = 2082;
  atkC_frm[1].positions[2] = 1223;
  atkC_frm[1].positions[3] = 917;
  atkC_frm[1].positions[4] = 1500;
  atkC_frm[1].positions[5] = 2158;
  atkC_frm[1].positions[6] = 1512;
  atkC_frm[1].positions[7] = 1391;
  atkC_frm[1].positions[8] = 1410;
  atkC_frm[1].positions[9] = 1477;
  atkC_frm[1].positions[10] = 1359;
  atkC_frm[1].positions[11] = 1505;
  atkC_frm[1].positions[12] = 1463;
  atkC_frm[1].positions[13] = 1335;
  atkC_frm[1].positions[14] = 1600;
  atkC_frm[1].positions[15] = 1487;
  atkC_frm[1].positions[16] = 1608;
  atkC_frm[1].positions[17] = 1589;
  atkC_frm[1].positions[18] = 1522;
  atkC_frm[1].positions[19] = 1640;
  atkC_frm[1].positions[20] = 1494;
  atkC_frm[1].positions[21] = 1536;
  atkC_frm[1].positions[22] = 1664;
  atkC_frm[1].positions[23] = 1399;

  laugh_frm[0].positions[0] = 1776;
  laugh_frm[0].positions[1] = 2146;
  laugh_frm[0].positions[2] = 1223;
  laugh_frm[0].positions[3] = 853;
  laugh_frm[0].positions[4] = 1500;
  laugh_frm[0].positions[5] = 1499;
  laugh_frm[0].positions[6] = 1245;
  laugh_frm[0].positions[7] = 1111;
  laugh_frm[0].positions[8] = 1305;
  laugh_frm[0].positions[9] = 1205;
  laugh_frm[0].positions[10] = 1092;
  laugh_frm[0].positions[11] = 1499;
  laugh_frm[0].positions[12] = 1245;
  laugh_frm[0].positions[13] = 1111;
  laugh_frm[0].positions[14] = 1694;
  laugh_frm[0].positions[15] = 1754;
  laugh_frm[0].positions[16] = 1888;
  laugh_frm[0].positions[17] = 1694;
  laugh_frm[0].positions[18] = 1794;
  laugh_frm[0].positions[19] = 1907;
  laugh_frm[0].positions[20] = 1500;
  laugh_frm[0].positions[21] = 1754;
  laugh_frm[0].positions[22] = 1888;
  laugh_frm[0].positions[23] = 1305;

  laugh_frm[1].positions[0] = 1223;
  laugh_frm[1].positions[1] = 1961;
  laugh_frm[1].positions[2] = 1223;
  laugh_frm[1].positions[3] = 1499;
  laugh_frm[1].positions[4] = 1500;
  laugh_frm[1].positions[5] = 1869;
  laugh_frm[1].positions[6] = 1379;
  laugh_frm[1].positions[7] = 1370;
  laugh_frm[1].positions[8] = 1209;
  laugh_frm[1].positions[9] = 1223;
  laugh_frm[1].positions[10] = 1128;
  laugh_frm[1].positions[11] = 1443;
  laugh_frm[1].positions[12] = 1208;
  laugh_frm[1].positions[13] = 961;
  laugh_frm[1].positions[14] = 1602;
  laugh_frm[1].positions[15] = 1525;
  laugh_frm[1].positions[16] = 1678;
  laugh_frm[1].positions[17] = 1430;
  laugh_frm[1].positions[18] = 1794;
  laugh_frm[1].positions[19] = 1958;
  laugh_frm[1].positions[20] = 1247;
  laugh_frm[1].positions[21] = 1964;
  laugh_frm[1].positions[22] = 2083;
  laugh_frm[1].positions[23] = 1045;

  laugh_frm[2].positions[0] = 1299;
  laugh_frm[2].positions[1] = 1897;
  laugh_frm[2].positions[2] = 1299;
  laugh_frm[2].positions[3] = 1410;
  laugh_frm[2].positions[4] = 1499;
  laugh_frm[2].positions[5] = 1869;
  laugh_frm[2].positions[6] = 1377;
  laugh_frm[2].positions[7] = 1351;
  laugh_frm[2].positions[8] = 1265;
  laugh_frm[2].positions[9] = 1219;
  laugh_frm[2].positions[10] = 1119;
  laugh_frm[2].positions[11] = 1484;
  laugh_frm[2].positions[12] = 1184;
  laugh_frm[2].positions[13] = 945;
  laugh_frm[2].positions[14] = 1643;
  laugh_frm[2].positions[15] = 1552;
  laugh_frm[2].positions[16] = 1681;
  laugh_frm[2].positions[17] = 1473;
  laugh_frm[2].positions[18] = 1793;
  laugh_frm[2].positions[19] = 1941;
  laugh_frm[2].positions[20] = 1290;
  laugh_frm[2].positions[21] = 1941;
  laugh_frm[2].positions[22] = 2083;
  laugh_frm[2].positions[23] = 1098;

  laugh_frm[3].positions[0] = 1491;
  laugh_frm[3].positions[1] = 1738;
  laugh_frm[3].positions[2] = 1491;
  laugh_frm[3].positions[3] = 1187;
  laugh_frm[3].positions[4] = 1499;
  laugh_frm[3].positions[5] = 1869;
  laugh_frm[3].positions[6] = 1388;
  laugh_frm[3].positions[7] = 1314;
  laugh_frm[3].positions[8] = 1388;
  laugh_frm[3].positions[9] = 1218;
  laugh_frm[3].positions[10] = 1104;
  laugh_frm[3].positions[11] = 1582;
  laugh_frm[3].positions[12] = 1141;
  laugh_frm[3].positions[13] = 922;
  laugh_frm[3].positions[14] = 1755;
  laugh_frm[3].positions[15] = 1608;
  laugh_frm[3].positions[16] = 1686;
  laugh_frm[3].positions[17] = 1600;
  laugh_frm[3].positions[18] = 1781;
  laugh_frm[3].positions[19] = 1897;
  laugh_frm[3].positions[20] = 1407;
  laugh_frm[3].positions[21] = 1863;
  laugh_frm[3].positions[22] = 2083;
  laugh_frm[3].positions[23] = 1233;

  laugh_frm[4].positions[0] = 1687;
  laugh_frm[4].positions[1] = 1574;
  laugh_frm[4].positions[2] = 1687;
  laugh_frm[4].positions[3] = 958;
  laugh_frm[4].positions[4] = 1499;
  laugh_frm[4].positions[5] = 1869;
  laugh_frm[4].positions[6] = 1424;
  laugh_frm[4].positions[7] = 1296;
  laugh_frm[4].positions[8] = 1491;
  laugh_frm[4].positions[9] = 1231;
  laugh_frm[4].positions[10] = 1104;
  laugh_frm[4].positions[11] = 1678;
  laugh_frm[4].positions[12] = 1127;
  laugh_frm[4].positions[13] = 931;
  laugh_frm[4].positions[14] = 1878;
  laugh_frm[4].positions[15] = 1648;
  laugh_frm[4].positions[16] = 1691;
  laugh_frm[4].positions[17] = 1757;
  laugh_frm[4].positions[18] = 1759;
  laugh_frm[4].positions[19] = 1855;
  laugh_frm[4].positions[20] = 1537;
  laugh_frm[4].positions[21] = 1764;
  laugh_frm[4].positions[22] = 1968;
  laugh_frm[4].positions[23] = 1367;

  laugh_frm[5].positions[0] = 1776;
  laugh_frm[5].positions[1] = 1500;
  laugh_frm[5].positions[2] = 1776;
  laugh_frm[5].positions[3] = 853;
  laugh_frm[5].positions[4] = 1499;
  laugh_frm[5].positions[5] = 1869;
  laugh_frm[5].positions[6] = 1449;
  laugh_frm[5].positions[7] = 1295;
  laugh_frm[5].positions[8] = 1532;
  laugh_frm[5].positions[9] = 1241;
  laugh_frm[5].positions[10] = 1108;
  laugh_frm[5].positions[11] = 1720;
  laugh_frm[5].positions[12] = 1131;
  laugh_frm[5].positions[13] = 947;
  laugh_frm[5].positions[14] = 1935;
  laugh_frm[5].positions[15] = 1661;
  laugh_frm[5].positions[16] = 1696;
  laugh_frm[5].positions[17] = 1836;
  laugh_frm[5].positions[18] = 1746;
  laugh_frm[5].positions[19] = 1838;
  laugh_frm[5].positions[20] = 1597;
  laugh_frm[5].positions[21] = 1714;
  laugh_frm[5].positions[22] = 1917;
  laugh_frm[5].positions[23] = 1425;

  laugh_frm[6].positions[0] = 1700;
  laugh_frm[6].positions[1] = 1564;
  laugh_frm[6].positions[2] = 1700;
  laugh_frm[6].positions[3] = 943;
  laugh_frm[6].positions[4] = 1500;
  laugh_frm[6].positions[5] = 1869;
  laugh_frm[6].positions[6] = 1419;
  laugh_frm[6].positions[7] = 1286;
  laugh_frm[6].positions[8] = 1486;
  laugh_frm[6].positions[9] = 1242;
  laugh_frm[6].positions[10] = 1121;
  laugh_frm[6].positions[11] = 1674;
  laugh_frm[6].positions[12] = 1154;
  laugh_frm[6].positions[13] = 981;
  laugh_frm[6].positions[14] = 1879;
  laugh_frm[6].positions[15] = 1661;
  laugh_frm[6].positions[16] = 1710;
  laugh_frm[6].positions[17] = 1781;
  laugh_frm[6].positions[18] = 1749;
  laugh_frm[6].positions[19] = 1843;
  laugh_frm[6].positions[20] = 1558;
  laugh_frm[6].positions[21] = 1734;
  laugh_frm[6].positions[22] = 1925;
  laugh_frm[6].positions[23] = 1384;

  laugh_frm[7].positions[0] = 1508;
  laugh_frm[7].positions[1] = 1723;
  laugh_frm[7].positions[2] = 1508;
  laugh_frm[7].positions[3] = 1166;
  laugh_frm[7].positions[4] = 1500;
  laugh_frm[7].positions[5] = 1869;
  laugh_frm[7].positions[6] = 1358;
  laugh_frm[7].positions[7] = 1265;
  laugh_frm[7].positions[8] = 1354;
  laugh_frm[7].positions[9] = 1251;
  laugh_frm[7].positions[10] = 1152;
  laugh_frm[7].positions[11] = 1551;
  laugh_frm[7].positions[12] = 1226;
  laugh_frm[7].positions[13] = 1068;
  laugh_frm[7].positions[14] = 1737;
  laugh_frm[7].positions[15] = 1645;
  laugh_frm[7].positions[16] = 1734;
  laugh_frm[7].positions[17] = 1657;
  laugh_frm[7].positions[18] = 1747;
  laugh_frm[7].positions[19] = 1846;
  laugh_frm[7].positions[20] = 1459;
  laugh_frm[7].positions[21] = 1769;
  laugh_frm[7].positions[22] = 1927;
  laugh_frm[7].positions[23] = 1274;

  laugh_frm[8].positions[0] = 1312;
  laugh_frm[8].positions[1] = 1886;
  laugh_frm[8].positions[2] = 1312;
  laugh_frm[8].positions[3] = 1395;
  laugh_frm[8].positions[4] = 1500;
  laugh_frm[8].positions[5] = 1869;
  laugh_frm[8].positions[6] = 1313;
  laugh_frm[8].positions[7] = 1243;
  laugh_frm[8].positions[8] = 1198;
  laugh_frm[8].positions[9] = 1270;
  laugh_frm[8].positions[10] = 1179;
  laugh_frm[8].positions[11] = 1418;
  laugh_frm[8].positions[12] = 1319;
  laugh_frm[8].positions[13] = 1156;
  laugh_frm[8].positions[14] = 1599;
  laugh_frm[8].positions[15] = 1603;
  laugh_frm[8].positions[16] = 1739;
  laugh_frm[8].positions[17] = 1548;
  laugh_frm[8].positions[18] = 1732;
  laugh_frm[8].positions[19] = 1836;
  laugh_frm[8].positions[20] = 1360;
  laugh_frm[8].positions[21] = 1776;
  laugh_frm[8].positions[22] = 1903;
  laugh_frm[8].positions[23] = 1149;

  laugh_frm[9].positions[0] = 1223;
  laugh_frm[9].positions[1] = 1961;
  laugh_frm[9].positions[2] = 1223;
  laugh_frm[9].positions[3] = 1499;
  laugh_frm[9].positions[4] = 1500;
  laugh_frm[9].positions[5] = 1869;
  laugh_frm[9].positions[6] = 1299;
  laugh_frm[9].positions[7] = 1232;
  laugh_frm[9].positions[8] = 1123;
  laugh_frm[9].positions[9] = 1282;
  laugh_frm[9].positions[10] = 1189;
  laugh_frm[9].positions[11] = 1359;
  laugh_frm[9].positions[12] = 1367;
  laugh_frm[9].positions[13] = 1195;
  laugh_frm[9].positions[14] = 1542;
  laugh_frm[9].positions[15] = 1577;
  laugh_frm[9].positions[16] = 1734;
  laugh_frm[9].positions[17] = 1504;
  laugh_frm[9].positions[18] = 1721;
  laugh_frm[9].positions[19] = 1828;
  laugh_frm[9].positions[20] = 1316;
  laugh_frm[9].positions[21] = 1769;
  laugh_frm[9].positions[22] = 1883;
  laugh_frm[9].positions[23] = 1090;

  laugh_frm[10].positions[0] = 1299;
  laugh_frm[10].positions[1] = 1897;
  laugh_frm[10].positions[2] = 1299;
  laugh_frm[10].positions[3] = 1410;
  laugh_frm[10].positions[4] = 1499;
  laugh_frm[10].positions[5] = 1869;
  laugh_frm[10].positions[6] = 1301;
  laugh_frm[10].positions[7] = 1223;
  laugh_frm[10].positions[8] = 1176;
  laugh_frm[10].positions[9] = 1280;
  laugh_frm[10].positions[10] = 1189;
  laugh_frm[10].positions[11] = 1397;
  laugh_frm[10].positions[12] = 1350;
  laugh_frm[10].positions[13] = 1194;
  laugh_frm[10].positions[14] = 1580;
  laugh_frm[10].positions[15] = 1607;
  laugh_frm[10].positions[16] = 1749;
  laugh_frm[10].positions[17] = 1552;
  laugh_frm[10].positions[18] = 1721;
  laugh_frm[10].positions[19] = 1820;
  laugh_frm[10].positions[20] = 1365;
  laugh_frm[10].positions[21] = 1748;
  laugh_frm[10].positions[22] = 1857;
  laugh_frm[10].positions[23] = 1150;

  laugh_frm[11].positions[0] = 1491;
  laugh_frm[11].positions[1] = 1738;
  laugh_frm[11].positions[2] = 1491;
  laugh_frm[11].positions[3] = 1187;
  laugh_frm[11].positions[4] = 1499;
  laugh_frm[11].positions[5] = 1869;
  laugh_frm[11].positions[6] = 1321;
  laugh_frm[11].positions[7] = 1211;
  laugh_frm[11].positions[8] = 1300;
  laugh_frm[11].positions[9] = 1284;
  laugh_frm[11].positions[10] = 1196;
  laugh_frm[11].positions[11] = 1495;
  laugh_frm[11].positions[12] = 1323;
  laugh_frm[11].positions[13] = 1210;
  laugh_frm[11].positions[14] = 1688;
  laugh_frm[11].positions[15] = 1674;
  laugh_frm[11].positions[16] = 1786;
  laugh_frm[11].positions[17] = 1687;
  laugh_frm[11].positions[18] = 1715;
  laugh_frm[11].positions[19] = 1803;
  laugh_frm[11].positions[20] = 1493;
  laugh_frm[11].positions[21] = 1680;
  laugh_frm[11].positions[22] = 1791;
  laugh_frm[11].positions[23] = 1298;

  laugh_frm[12].positions[0] = 1687;
  laugh_frm[12].positions[1] = 1574;
  laugh_frm[12].positions[2] = 1687;
  laugh_frm[12].positions[3] = 958;
  laugh_frm[12].positions[4] = 1499;
  laugh_frm[12].positions[5] = 1869;
  laugh_frm[12].positions[6] = 1367;
  laugh_frm[12].positions[7] = 1220;
  laugh_frm[12].positions[8] = 1411;
  laugh_frm[12].positions[9] = 1302;
  laugh_frm[12].positions[10] = 1216;
  laugh_frm[12].positions[11] = 1595;
  laugh_frm[12].positions[12] = 1323;
  laugh_frm[12].positions[13] = 1248;
  laugh_frm[12].positions[14] = 1813;
  laugh_frm[12].positions[15] = 1722;
  laugh_frm[12].positions[16] = 1824;
  laugh_frm[12].positions[17] = 1839;
  laugh_frm[12].positions[18] = 1699;
  laugh_frm[12].positions[19] = 1791;
  laugh_frm[12].positions[20] = 1626;
  laugh_frm[12].positions[21] = 1592;
  laugh_frm[12].positions[22] = 1727;
  laugh_frm[12].positions[23] = 1438;

  laugh_frm[13].positions[0] = 1776;
  laugh_frm[13].positions[1] = 1500;
  laugh_frm[13].positions[2] = 1776;
  laugh_frm[13].positions[3] = 853;
  laugh_frm[13].positions[4] = 1499;
  laugh_frm[13].positions[5] = 1869;
  laugh_frm[13].positions[6] = 1396;
  laugh_frm[13].positions[7] = 1232;
  laugh_frm[13].positions[8] = 1457;
  laugh_frm[13].positions[9] = 1314;
  laugh_frm[13].positions[10] = 1229;
  laugh_frm[13].positions[11] = 1640;
  laugh_frm[13].positions[12] = 1332;
  laugh_frm[13].positions[13] = 1272;
  laugh_frm[13].positions[14] = 1875;
  laugh_frm[13].positions[15] = 1737;
  laugh_frm[13].positions[16] = 1841;
  laugh_frm[13].positions[17] = 1910;
  laugh_frm[13].positions[18] = 1690;
  laugh_frm[13].positions[19] = 1788;
  laugh_frm[13].positions[20] = 1683;
  laugh_frm[13].positions[21] = 1546;
  laugh_frm[13].positions[22] = 1697;
  laugh_frm[13].positions[23] = 1495;

  laugh_frm[14].positions[0] = 1700;
  laugh_frm[14].positions[1] = 1564;
  laugh_frm[14].positions[2] = 1700;
  laugh_frm[14].positions[3] = 943;
  laugh_frm[14].positions[4] = 1500;
  laugh_frm[14].positions[5] = 1869;
  laugh_frm[14].positions[6] = 1364;
  laugh_frm[14].positions[7] = 1210;
  laugh_frm[14].positions[8] = 1408;
  laugh_frm[14].positions[9] = 1313;
  laugh_frm[14].positions[10] = 1232;
  laugh_frm[14].positions[11] = 1589;
  laugh_frm[14].positions[12] = 1353;
  laugh_frm[14].positions[13] = 1292;
  laugh_frm[14].positions[14] = 1811;
  laugh_frm[14].positions[15] = 1734;
  laugh_frm[14].positions[16] = 1847;
  laugh_frm[14].positions[17] = 1859;
  laugh_frm[14].positions[18] = 1690;
  laugh_frm[14].positions[19] = 1784;
  laugh_frm[14].positions[20] = 1647;
  laugh_frm[14].positions[21] = 1560;
  laugh_frm[14].positions[22] = 1691;
  laugh_frm[14].positions[23] = 1459;

  laugh_frm[15].positions[0] = 1508;
  laugh_frm[15].positions[1] = 1723;
  laugh_frm[15].positions[2] = 1508;
  laugh_frm[15].positions[3] = 1166;
  laugh_frm[15].positions[4] = 1500;
  laugh_frm[15].positions[5] = 1869;
  laugh_frm[15].positions[6] = 1294;
  laugh_frm[15].positions[7] = 1156;
  laugh_frm[15].positions[8] = 1273;
  laugh_frm[15].positions[9] = 1316;
  laugh_frm[15].positions[10] = 1234;
  laugh_frm[15].positions[11] = 1458;
  laugh_frm[15].positions[12] = 1417;
  laugh_frm[15].positions[13] = 1338;
  laugh_frm[15].positions[14] = 1656;
  laugh_frm[15].positions[15] = 1710;
  laugh_frm[15].positions[16] = 1846;
  laugh_frm[15].positions[17] = 1739;
  laugh_frm[15].positions[18] = 1683;
  laugh_frm[15].positions[19] = 1766;
  laugh_frm[15].positions[20] = 1552;
  laugh_frm[15].positions[21] = 1578;
  laugh_frm[15].positions[22] = 1661;
  laugh_frm[15].positions[23] = 1356;

  laugh_frm[16].positions[0] = 1312;
  laugh_frm[16].positions[1] = 1886;
  laugh_frm[16].positions[2] = 1312;
  laugh_frm[16].positions[3] = 1395;
  laugh_frm[16].positions[4] = 1500;
  laugh_frm[16].positions[5] = 1869;
  laugh_frm[16].positions[6] = 1243;
  laugh_frm[16].positions[7] = 1103;
  laugh_frm[16].positions[8] = 1126;
  laugh_frm[16].positions[9] = 1328;
  laugh_frm[16].positions[10] = 1231;
  laugh_frm[16].positions[11] = 1328;
  laugh_frm[16].positions[12] = 1501;
  laugh_frm[16].positions[13] = 1383;
  laugh_frm[16].positions[14] = 1517;
  laugh_frm[16].positions[15] = 1660;
  laugh_frm[16].positions[16] = 1823;
  laugh_frm[16].positions[17] = 1626;
  laugh_frm[16].positions[18] = 1663;
  laugh_frm[16].positions[19] = 1736;
  laugh_frm[16].positions[20] = 1453;
  laugh_frm[16].positions[21] = 1571;
  laugh_frm[16].positions[22] = 1609;
  laugh_frm[16].positions[23] = 1232;

  laugh_frm[17].positions[0] = 1223;
  laugh_frm[17].positions[1] = 1961;
  laugh_frm[17].positions[2] = 1223;
  laugh_frm[17].positions[3] = 1499;
  laugh_frm[17].positions[4] = 1500;
  laugh_frm[17].positions[5] = 1869;
  laugh_frm[17].positions[6] = 1227;
  laugh_frm[17].positions[7] = 1081;
  laugh_frm[17].positions[8] = 1060;
  laugh_frm[17].positions[9] = 1337;
  laugh_frm[17].positions[10] = 1229;
  laugh_frm[17].positions[11] = 1273;
  laugh_frm[17].positions[12] = 1546;
  laugh_frm[17].positions[13] = 1404;
  laugh_frm[17].positions[14] = 1461;
  laugh_frm[17].positions[15] = 1629;
  laugh_frm[17].positions[16] = 1805;
  laugh_frm[17].positions[17] = 1579;
  laugh_frm[17].positions[18] = 1650;
  laugh_frm[17].positions[19] = 1718;
  laugh_frm[17].positions[20] = 1408;
  laugh_frm[17].positions[21] = 1560;
  laugh_frm[17].positions[22] = 1581;
  laugh_frm[17].positions[23] = 1169;

  laugh_frm[18].positions[0] = 1299;
  laugh_frm[18].positions[1] = 1897;
  laugh_frm[18].positions[2] = 1299;
  laugh_frm[18].positions[3] = 1410;
  laugh_frm[18].positions[4] = 1499;
  laugh_frm[18].positions[5] = 1869;
  laugh_frm[18].positions[6] = 1231;
  laugh_frm[18].positions[7] = 1079;
  laugh_frm[18].positions[8] = 1108;
  laugh_frm[18].positions[9] = 1337;
  laugh_frm[18].positions[10] = 1236;
  laugh_frm[18].positions[11] = 1307;
  laugh_frm[18].positions[12] = 1535;
  laugh_frm[18].positions[13] = 1415;
  laugh_frm[18].positions[14] = 1495;
  laugh_frm[18].positions[15] = 1663;
  laugh_frm[18].positions[16] = 1833;
  laugh_frm[18].positions[17] = 1629;
  laugh_frm[18].positions[18] = 1652;
  laugh_frm[18].positions[19] = 1721;
  laugh_frm[18].positions[20] = 1461;
  laugh_frm[18].positions[21] = 1539;
  laugh_frm[18].positions[22] = 1567;
  laugh_frm[18].positions[23] = 1237;

  laugh_frm[19].positions[0] = 1491;
  laugh_frm[19].positions[1] = 1738;
  laugh_frm[19].positions[2] = 1491;
  laugh_frm[19].positions[3] = 1187;
  laugh_frm[19].positions[4] = 1499;
  laugh_frm[19].positions[5] = 1869;
  laugh_frm[19].positions[6] = 1258;
  laugh_frm[19].positions[7] = 1091;
  laugh_frm[19].positions[8] = 1224;
  laugh_frm[19].positions[9] = 1347;
  laugh_frm[19].positions[10] = 1264;
  laugh_frm[19].positions[11] = 1397;
  laugh_frm[19].positions[12] = 1524;
  laugh_frm[19].positions[13] = 1459;
  laugh_frm[19].positions[14] = 1590;
  laugh_frm[19].positions[15] = 1736;
  laugh_frm[19].positions[16] = 1903;
  laugh_frm[19].positions[17] = 1762;
  laugh_frm[19].positions[18] = 1652;
  laugh_frm[19].positions[19] = 1733;
  laugh_frm[19].positions[20] = 1591;
  laugh_frm[19].positions[21] = 1478;
  laugh_frm[19].positions[22] = 1539;
  laugh_frm[19].positions[23] = 1396;

  laugh_frm[20].positions[0] = 1687;
  laugh_frm[20].positions[1] = 1574;
  laugh_frm[20].positions[2] = 1687;
  laugh_frm[20].positions[3] = 958;
  laugh_frm[20].positions[4] = 1499;
  laugh_frm[20].positions[5] = 1869;
  laugh_frm[20].positions[6] = 1312;
  laugh_frm[20].positions[7] = 1128;
  laugh_frm[20].positions[8] = 1336;
  laugh_frm[20].positions[9] = 1369;
  laugh_frm[20].positions[10] = 1304;
  laugh_frm[20].positions[11] = 1493;
  laugh_frm[20].positions[12] = 1540;
  laugh_frm[20].positions[13] = 1523;
  laugh_frm[20].positions[14] = 1709;
  laugh_frm[20].positions[15] = 1788;
  laugh_frm[20].positions[16] = 1970;
  laugh_frm[20].positions[17] = 1902;
  laugh_frm[20].positions[18] = 1643;
  laugh_frm[20].positions[19] = 1749;
  laugh_frm[20].positions[20] = 1715;
  laugh_frm[20].positions[21] = 1397;
  laugh_frm[20].positions[22] = 1511;
  laugh_frm[20].positions[23] = 1532;

  laugh_frm[21].positions[0] = 1776;
  laugh_frm[21].positions[1] = 2146;
  laugh_frm[21].positions[2] = 1223;
  laugh_frm[21].positions[3] = 853;
  laugh_frm[21].positions[4] = 1500;
  laugh_frm[21].positions[5] = 1499;
  laugh_frm[21].positions[6] = 1245;
  laugh_frm[21].positions[7] = 1111;
  laugh_frm[21].positions[8] = 1305;
  laugh_frm[21].positions[9] = 1205;
  laugh_frm[21].positions[10] = 1092;
  laugh_frm[21].positions[11] = 1499;
  laugh_frm[21].positions[12] = 1245;
  laugh_frm[21].positions[13] = 1111;
  laugh_frm[21].positions[14] = 1694;
  laugh_frm[21].positions[15] = 1754;
  laugh_frm[21].positions[16] = 1888;
  laugh_frm[21].positions[17] = 1694;
  laugh_frm[21].positions[18] = 1794;
  laugh_frm[21].positions[19] = 1907;
  laugh_frm[21].positions[20] = 1500;
  laugh_frm[21].positions[21] = 1754;
  laugh_frm[21].positions[22] = 1888;
  laugh_frm[21].positions[23] = 1305;

  dance01_frm[0].positions[0] = 1776;
  dance01_frm[0].positions[1] = 2146;
  dance01_frm[0].positions[2] = 1223;
  dance01_frm[0].positions[3] = 853;
  dance01_frm[0].positions[4] = 1499;
  dance01_frm[0].positions[5] = 2146;
  dance01_frm[0].positions[6] = 1447;
  dance01_frm[0].positions[7] = 1326;
  dance01_frm[0].positions[8] = 1505;
  dance01_frm[0].positions[9] = 1288;
  dance01_frm[0].positions[10] = 1121;
  dance01_frm[0].positions[11] = 1591;
  dance01_frm[0].positions[12] = 1167;
  dance01_frm[0].positions[13] = 917;
  dance01_frm[0].positions[14] = 1673;
  dance01_frm[0].positions[15] = 1552;
  dance01_frm[0].positions[16] = 1673;
  dance01_frm[0].positions[17] = 1494;
  dance01_frm[0].positions[18] = 1711;
  dance01_frm[0].positions[19] = 1878;
  dance01_frm[0].positions[20] = 1408;
  dance01_frm[0].positions[21] = 1832;
  dance01_frm[0].positions[22] = 2082;
  dance01_frm[0].positions[23] = 1326;

  dance01_frm[1].positions[0] = 1776;
  dance01_frm[1].positions[1] = 2146;
  dance01_frm[1].positions[2] = 1223;
  dance01_frm[1].positions[3] = 853;
  dance01_frm[1].positions[4] = 1499;
  dance01_frm[1].positions[5] = 2146;
  dance01_frm[1].positions[6] = 1482;
  dance01_frm[1].positions[7] = 1359;
  dance01_frm[1].positions[8] = 1419;
  dance01_frm[1].positions[9] = 1449;
  dance01_frm[1].positions[10] = 1328;
  dance01_frm[1].positions[11] = 1515;
  dance01_frm[1].positions[12] = 1439;
  dance01_frm[1].positions[13] = 1305;
  dance01_frm[1].positions[14] = 1609;
  dance01_frm[1].positions[15] = 1517;
  dance01_frm[1].positions[16] = 1640;
  dance01_frm[1].positions[17] = 1580;
  dance01_frm[1].positions[18] = 1550;
  dance01_frm[1].positions[19] = 1671;
  dance01_frm[1].positions[20] = 1484;
  dance01_frm[1].positions[21] = 1560;
  dance01_frm[1].positions[22] = 1694;
  dance01_frm[1].positions[23] = 1390;

  dance02_frm[0].positions[0] = 1776;
  dance02_frm[0].positions[1] = 2146;
  dance02_frm[0].positions[2] = 1223;
  dance02_frm[0].positions[3] = 1315;
  dance02_frm[0].positions[4] = 1315;
  dance02_frm[0].positions[5] = 2146;
  dance02_frm[0].positions[6] = 1324;
  dance02_frm[0].positions[7] = 1085;
  dance02_frm[0].positions[8] = 1542;
  dance02_frm[0].positions[9] = 1228;
  dance02_frm[0].positions[10] = 1049;
  dance02_frm[0].positions[11] = 1637;
  dance02_frm[0].positions[12] = 1179;
  dance02_frm[0].positions[13] = 1048;
  dance02_frm[0].positions[14] = 1761;
  dance02_frm[0].positions[15] = 1278;
  dance02_frm[0].positions[16] = 1353;
  dance02_frm[0].positions[17] = 1806;
  dance02_frm[0].positions[18] = 1167;
  dance02_frm[0].positions[19] = 1289;
  dance02_frm[0].positions[20] = 1677;
  dance02_frm[0].positions[21] = 959;
  dance02_frm[0].positions[22] = 1166;
  dance02_frm[0].positions[23] = 1575;

  dance02_frm[1].positions[0] = 1776;
  dance02_frm[1].positions[1] = 2146;
  dance02_frm[1].positions[2] = 1223;
  dance02_frm[1].positions[3] = 853;
  dance02_frm[1].positions[4] = 1499;
  dance02_frm[1].positions[5] = 2146;
  dance02_frm[1].positions[6] = 1487;
  dance02_frm[1].positions[7] = 1363;
  dance02_frm[1].positions[8] = 1405;
  dance02_frm[1].positions[9] = 1477;
  dance02_frm[1].positions[10] = 1359;
  dance02_frm[1].positions[11] = 1500;
  dance02_frm[1].positions[12] = 1487;
  dance02_frm[1].positions[13] = 1363;
  dance02_frm[1].positions[14] = 1594;
  dance02_frm[1].positions[15] = 1512;
  dance02_frm[1].positions[16] = 1636;
  dance02_frm[1].positions[17] = 1594;
  dance02_frm[1].positions[18] = 1522;
  dance02_frm[1].positions[19] = 1640;
  dance02_frm[1].positions[20] = 1500;
  dance02_frm[1].positions[21] = 1512;
  dance02_frm[1].positions[22] = 1636;
  dance02_frm[1].positions[23] = 1405;

  dance02_frm[2].positions[0] = 1776;
  dance02_frm[2].positions[1] = 1684;
  dance02_frm[2].positions[2] = 1223;
  dance02_frm[2].positions[3] = 853;
  dance02_frm[2].positions[4] = 1684;
  dance02_frm[2].positions[5] = 2146;
  dance02_frm[2].positions[6] = 1721;
  dance02_frm[2].positions[7] = 1646;
  dance02_frm[2].positions[8] = 1193;
  dance02_frm[2].positions[9] = 1832;
  dance02_frm[2].positions[10] = 1710;
  dance02_frm[2].positions[11] = 1322;
  dance02_frm[2].positions[12] = 2040;
  dance02_frm[2].positions[13] = 1833;
  dance02_frm[2].positions[14] = 1424;
  dance02_frm[2].positions[15] = 1675;
  dance02_frm[2].positions[16] = 1914;
  dance02_frm[2].positions[17] = 1457;
  dance02_frm[2].positions[18] = 1771;
  dance02_frm[2].positions[19] = 1950;
  dance02_frm[2].positions[20] = 1362;
  dance02_frm[2].positions[21] = 1820;
  dance02_frm[2].positions[22] = 1951;
  dance02_frm[2].positions[23] = 1238;

  dance02_frm[3].positions[0] = 1776;
  dance02_frm[3].positions[1] = 2146;
  dance02_frm[3].positions[2] = 1223;
  dance02_frm[3].positions[3] = 853;
  dance02_frm[3].positions[4] = 1500;
  dance02_frm[3].positions[5] = 2146;
  dance02_frm[3].positions[6] = 1487;
  dance02_frm[3].positions[7] = 1363;
  dance02_frm[3].positions[8] = 1405;
  dance02_frm[3].positions[9] = 1477;
  dance02_frm[3].positions[10] = 1359;
  dance02_frm[3].positions[11] = 1499;
  dance02_frm[3].positions[12] = 1487;
  dance02_frm[3].positions[13] = 1363;
  dance02_frm[3].positions[14] = 1594;
  dance02_frm[3].positions[15] = 1512;
  dance02_frm[3].positions[16] = 1636;
  dance02_frm[3].positions[17] = 1594;
  dance02_frm[3].positions[18] = 1522;
  dance02_frm[3].positions[19] = 1640;
  dance02_frm[3].positions[20] = 1499;
  dance02_frm[3].positions[21] = 1512;
  dance02_frm[3].positions[22] = 1636;
  dance02_frm[3].positions[23] = 1405;

  dance02_frm[4].positions[0] = 1776;
  dance02_frm[4].positions[1] = 1684;
  dance02_frm[4].positions[2] = 1223;
  dance02_frm[4].positions[3] = 1315;
  dance02_frm[4].positions[4] = 1499;
  dance02_frm[4].positions[5] = 2238;
  dance02_frm[4].positions[6] = 1689;
  dance02_frm[4].positions[7] = 1574;
  dance02_frm[4].positions[8] = 1453;
  dance02_frm[4].positions[9] = 1483;
  dance02_frm[4].positions[10] = 1365;
  dance02_frm[4].positions[11] = 1540;
  dance02_frm[4].positions[12] = 1328;
  dance02_frm[4].positions[13] = 1166;
  dance02_frm[4].positions[14] = 1625;
  dance02_frm[4].positions[15] = 1310;
  dance02_frm[4].positions[16] = 1425;
  dance02_frm[4].positions[17] = 1546;
  dance02_frm[4].positions[18] = 1516;
  dance02_frm[4].positions[19] = 1634;
  dance02_frm[4].positions[20] = 1459;
  dance02_frm[4].positions[21] = 1671;
  dance02_frm[4].positions[22] = 1833;
  dance02_frm[4].positions[23] = 1374;

  dance02_frm[5].positions[0] = 1776;
  dance02_frm[5].positions[1] = 2082;
  dance02_frm[5].positions[2] = 1223;
  dance02_frm[5].positions[3] = 917;
  dance02_frm[5].positions[4] = 1500;
  dance02_frm[5].positions[5] = 2158;
  dance02_frm[5].positions[6] = 1512;
  dance02_frm[5].positions[7] = 1391;
  dance02_frm[5].positions[8] = 1410;
  dance02_frm[5].positions[9] = 1477;
  dance02_frm[5].positions[10] = 1359;
  dance02_frm[5].positions[11] = 1505;
  dance02_frm[5].positions[12] = 1463;
  dance02_frm[5].positions[13] = 1335;
  dance02_frm[5].positions[14] = 1600;
  dance02_frm[5].positions[15] = 1487;
  dance02_frm[5].positions[16] = 1608;
  dance02_frm[5].positions[17] = 1589;
  dance02_frm[5].positions[18] = 1522;
  dance02_frm[5].positions[19] = 1640;
  dance02_frm[5].positions[20] = 1494;
  dance02_frm[5].positions[21] = 1536;
  dance02_frm[5].positions[22] = 1664;
  dance02_frm[5].positions[23] = 1399;

  dance02_frm[6].positions[0] = 1776;
  dance02_frm[6].positions[1] = 1684;
  dance02_frm[6].positions[2] = 1223;
  dance02_frm[6].positions[3] = 1315;
  dance02_frm[6].positions[4] = 1499;
  dance02_frm[6].positions[5] = 2238;
  dance02_frm[6].positions[6] = 1689;
  dance02_frm[6].positions[7] = 1574;
  dance02_frm[6].positions[8] = 1453;
  dance02_frm[6].positions[9] = 1483;
  dance02_frm[6].positions[10] = 1365;
  dance02_frm[6].positions[11] = 1540;
  dance02_frm[6].positions[12] = 1328;
  dance02_frm[6].positions[13] = 1166;
  dance02_frm[6].positions[14] = 1625;
  dance02_frm[6].positions[15] = 1310;
  dance02_frm[6].positions[16] = 1425;
  dance02_frm[6].positions[17] = 1546;
  dance02_frm[6].positions[18] = 1516;
  dance02_frm[6].positions[19] = 1634;
  dance02_frm[6].positions[20] = 1459;
  dance02_frm[6].positions[21] = 1671;
  dance02_frm[6].positions[22] = 1833;
  dance02_frm[6].positions[23] = 1374;

  dance02_frm[7].positions[0] = 1776;
  dance02_frm[7].positions[1] = 2082;
  dance02_frm[7].positions[2] = 1223;
  dance02_frm[7].positions[3] = 917;
  dance02_frm[7].positions[4] = 1500;
  dance02_frm[7].positions[5] = 2158;
  dance02_frm[7].positions[6] = 1512;
  dance02_frm[7].positions[7] = 1391;
  dance02_frm[7].positions[8] = 1410;
  dance02_frm[7].positions[9] = 1477;
  dance02_frm[7].positions[10] = 1359;
  dance02_frm[7].positions[11] = 1505;
  dance02_frm[7].positions[12] = 1463;
  dance02_frm[7].positions[13] = 1335;
  dance02_frm[7].positions[14] = 1600;
  dance02_frm[7].positions[15] = 1487;
  dance02_frm[7].positions[16] = 1608;
  dance02_frm[7].positions[17] = 1589;
  dance02_frm[7].positions[18] = 1522;
  dance02_frm[7].positions[19] = 1640;
  dance02_frm[7].positions[20] = 1494;
  dance02_frm[7].positions[21] = 1536;
  dance02_frm[7].positions[22] = 1664;
  dance02_frm[7].positions[23] = 1399;

  dance03_frm[0].positions[0] = 1223;
  dance03_frm[0].positions[1] = 2146;
  dance03_frm[0].positions[2] = 1223;
  dance03_frm[0].positions[3] = 1130;
  dance03_frm[0].positions[4] = 1499;
  dance03_frm[0].positions[5] = 2146;
  dance03_frm[0].positions[6] = 1487;
  dance03_frm[0].positions[7] = 1363;
  dance03_frm[0].positions[8] = 1405;
  dance03_frm[0].positions[9] = 1477;
  dance03_frm[0].positions[10] = 1359;
  dance03_frm[0].positions[11] = 1500;
  dance03_frm[0].positions[12] = 1487;
  dance03_frm[0].positions[13] = 1363;
  dance03_frm[0].positions[14] = 1594;
  dance03_frm[0].positions[15] = 1512;
  dance03_frm[0].positions[16] = 1636;
  dance03_frm[0].positions[17] = 1594;
  dance03_frm[0].positions[18] = 1522;
  dance03_frm[0].positions[19] = 1640;
  dance03_frm[0].positions[20] = 1500;
  dance03_frm[0].positions[21] = 1512;
  dance03_frm[0].positions[22] = 1636;
  dance03_frm[0].positions[23] = 1405;

  dance03_frm[1].positions[0] = 1223;
  dance03_frm[1].positions[1] = 2146;
  dance03_frm[1].positions[2] = 1223;
  dance03_frm[1].positions[3] = 853;
  dance03_frm[1].positions[4] = 1684;
  dance03_frm[1].positions[5] = 2146;
  dance03_frm[1].positions[6] = 1356;
  dance03_frm[1].positions[7] = 1325;
  dance03_frm[1].positions[8] = 1191;
  dance03_frm[1].positions[9] = 1406;
  dance03_frm[1].positions[10] = 1336;
  dance03_frm[1].positions[11] = 1337;
  dance03_frm[1].positions[12] = 1499;
  dance03_frm[1].positions[13] = 1368;
  dance03_frm[1].positions[14] = 1447;
  dance03_frm[1].positions[15] = 1278;
  dance03_frm[1].positions[16] = 1523;
  dance03_frm[1].positions[17] = 1439;
  dance03_frm[1].positions[18] = 1414;
  dance03_frm[1].positions[19] = 1593;
  dance03_frm[1].positions[20] = 1353;
  dance03_frm[1].positions[21] = 1497;
  dance03_frm[1].positions[22] = 1630;
  dance03_frm[1].positions[23] = 1245;

  dance03_frm[2].positions[0] = 1223;
  dance03_frm[2].positions[1] = 2146;
  dance03_frm[2].positions[2] = 1223;
  dance03_frm[2].positions[3] = 1130;
  dance03_frm[2].positions[4] = 1500;
  dance03_frm[2].positions[5] = 2146;
  dance03_frm[2].positions[6] = 1487;
  dance03_frm[2].positions[7] = 1363;
  dance03_frm[2].positions[8] = 1405;
  dance03_frm[2].positions[9] = 1477;
  dance03_frm[2].positions[10] = 1359;
  dance03_frm[2].positions[11] = 1499;
  dance03_frm[2].positions[12] = 1487;
  dance03_frm[2].positions[13] = 1363;
  dance03_frm[2].positions[14] = 1594;
  dance03_frm[2].positions[15] = 1512;
  dance03_frm[2].positions[16] = 1636;
  dance03_frm[2].positions[17] = 1594;
  dance03_frm[2].positions[18] = 1522;
  dance03_frm[2].positions[19] = 1640;
  dance03_frm[2].positions[20] = 1499;
  dance03_frm[2].positions[21] = 1512;
  dance03_frm[2].positions[22] = 1636;
  dance03_frm[2].positions[23] = 1405;

  dance03_frm[3].positions[0] = 1223;
  dance03_frm[3].positions[1] = 2146;
  dance03_frm[3].positions[2] = 1223;
  dance03_frm[3].positions[3] = 853;
  dance03_frm[3].positions[4] = 1315;
  dance03_frm[3].positions[5] = 2146;
  dance03_frm[3].positions[6] = 1721;
  dance03_frm[3].positions[7] = 1476;
  dance03_frm[3].positions[8] = 1560;
  dance03_frm[3].positions[9] = 1585;
  dance03_frm[3].positions[10] = 1406;
  dance03_frm[3].positions[11] = 1646;
  dance03_frm[3].positions[12] = 1502;
  dance03_frm[3].positions[13] = 1369;
  dance03_frm[3].positions[14] = 1754;
  dance03_frm[3].positions[15] = 1643;
  dance03_frm[3].positions[16] = 1674;
  dance03_frm[3].positions[17] = 1808;
  dance03_frm[3].positions[18] = 1593;
  dance03_frm[3].positions[19] = 1663;
  dance03_frm[3].positions[20] = 1662;
  dance03_frm[3].positions[21] = 1500;
  dance03_frm[3].positions[22] = 1631;
  dance03_frm[3].positions[23] = 1552;

  dance03_frm[4].positions[0] = 1776;
  dance03_frm[4].positions[1] = 1869;
  dance03_frm[4].positions[2] = 1223;
  dance03_frm[4].positions[3] = 1130;
  dance03_frm[4].positions[4] = 1500;
  dance03_frm[4].positions[5] = 1961;
  dance03_frm[4].positions[6] = 1337;
  dance03_frm[4].positions[7] = 1155;
  dance03_frm[4].positions[8] = 1310;
  dance03_frm[4].positions[9] = 1473;
  dance03_frm[4].positions[10] = 1345;
  dance03_frm[4].positions[11] = 1390;
  dance03_frm[4].positions[12] = 1658;
  dance03_frm[4].positions[13] = 1547;
  dance03_frm[4].positions[14] = 1476;
  dance03_frm[4].positions[15] = 1662;
  dance03_frm[4].positions[16] = 1844;
  dance03_frm[4].positions[17] = 1689;
  dance03_frm[4].positions[18] = 1526;
  dance03_frm[4].positions[19] = 1654;
  dance03_frm[4].positions[20] = 1609;
  dance03_frm[4].positions[21] = 1341;
  dance03_frm[4].positions[22] = 1452;
  dance03_frm[4].positions[23] = 1523;

  dance03_frm[5].positions[0] = 1776;
  dance03_frm[5].positions[1] = 2146;
  dance03_frm[5].positions[2] = 1223;
  dance03_frm[5].positions[3] = 853;
  dance03_frm[5].positions[4] = 1499;
  dance03_frm[5].positions[5] = 2146;
  dance03_frm[5].positions[6] = 1487;
  dance03_frm[5].positions[7] = 1363;
  dance03_frm[5].positions[8] = 1405;
  dance03_frm[5].positions[9] = 1477;
  dance03_frm[5].positions[10] = 1359;
  dance03_frm[5].positions[11] = 1499;
  dance03_frm[5].positions[12] = 1487;
  dance03_frm[5].positions[13] = 1363;
  dance03_frm[5].positions[14] = 1594;
  dance03_frm[5].positions[15] = 1512;
  dance03_frm[5].positions[16] = 1636;
  dance03_frm[5].positions[17] = 1594;
  dance03_frm[5].positions[18] = 1522;
  dance03_frm[5].positions[19] = 1640;
  dance03_frm[5].positions[20] = 1500;
  dance03_frm[5].positions[21] = 1512;
  dance03_frm[5].positions[22] = 1636;
  dance03_frm[5].positions[23] = 1405;

  dance04_frm[0].positions[0] = 1776;
  dance04_frm[0].positions[1] = 2146;
  dance04_frm[0].positions[2] = 1223;
  dance04_frm[0].positions[3] = 1223;
  dance04_frm[0].positions[4] = 1315;
  dance04_frm[0].positions[5] = 2146;
  dance04_frm[0].positions[6] = 1371;
  dance04_frm[0].positions[7] = 1109;
  dance04_frm[0].positions[8] = 1544;
  dance04_frm[0].positions[9] = 1269;
  dance04_frm[0].positions[10] = 1065;
  dance04_frm[0].positions[11] = 1634;
  dance04_frm[0].positions[12] = 1212;
  dance04_frm[0].positions[13] = 1056;
  dance04_frm[0].positions[14] = 1750;
  dance04_frm[0].positions[15] = 1328;
  dance04_frm[0].positions[16] = 1375;
  dance04_frm[0].positions[17] = 1822;
  dance04_frm[0].positions[18] = 1232;
  dance04_frm[0].positions[19] = 1321;
  dance04_frm[0].positions[20] = 1683;
  dance04_frm[0].positions[21] = 1065;
  dance04_frm[0].positions[22] = 1229;
  dance04_frm[0].positions[23] = 1574;

  dance04_frm[1].positions[0] = 1776;
  dance04_frm[1].positions[1] = 2146;
  dance04_frm[1].positions[2] = 1223;
  dance04_frm[1].positions[3] = 1038;
  dance04_frm[1].positions[4] = 1315;
  dance04_frm[1].positions[5] = 2146;
  dance04_frm[1].positions[6] = 1420;
  dance04_frm[1].positions[7] = 1232;
  dance04_frm[1].positions[8] = 1482;
  dance04_frm[1].positions[9] = 1365;
  dance04_frm[1].positions[10] = 1210;
  dance04_frm[1].positions[11] = 1571;
  dance04_frm[1].positions[12] = 1338;
  dance04_frm[1].positions[13] = 1203;
  dance04_frm[1].positions[14] = 1673;
  dance04_frm[1].positions[15] = 1428;
  dance04_frm[1].positions[16] = 1503;
  dance04_frm[1].positions[17] = 1694;
  dance04_frm[1].positions[18] = 1392;
  dance04_frm[1].positions[19] = 1486;
  dance04_frm[1].positions[20] = 1584;
  dance04_frm[1].positions[21] = 1327;
  dance04_frm[1].positions[22] = 1456;
  dance04_frm[1].positions[23] = 1487;

  dance04_frm[2].positions[0] = 1776;
  dance04_frm[2].positions[1] = 2146;
  dance04_frm[2].positions[2] = 1223;
  dance04_frm[2].positions[3] = 1223;
  dance04_frm[2].positions[4] = 1315;
  dance04_frm[2].positions[5] = 2146;
  dance04_frm[2].positions[6] = 1371;
  dance04_frm[2].positions[7] = 1108;
  dance04_frm[2].positions[8] = 1544;
  dance04_frm[2].positions[9] = 1269;
  dance04_frm[2].positions[10] = 1065;
  dance04_frm[2].positions[11] = 1634;
  dance04_frm[2].positions[12] = 1212;
  dance04_frm[2].positions[13] = 1056;
  dance04_frm[2].positions[14] = 1750;
  dance04_frm[2].positions[15] = 1328;
  dance04_frm[2].positions[16] = 1375;
  dance04_frm[2].positions[17] = 1822;
  dance04_frm[2].positions[18] = 1232;
  dance04_frm[2].positions[19] = 1321;
  dance04_frm[2].positions[20] = 1683;
  dance04_frm[2].positions[21] = 1065;
  dance04_frm[2].positions[22] = 1229;
  dance04_frm[2].positions[23] = 1574;

  dance04_frm[3].positions[0] = 1776;
  dance04_frm[3].positions[1] = 2146;
  dance04_frm[3].positions[2] = 1223;
  dance04_frm[3].positions[3] = 853;
  dance04_frm[3].positions[4] = 1499;
  dance04_frm[3].positions[5] = 2146;
  dance04_frm[3].positions[6] = 1487;
  dance04_frm[3].positions[7] = 1363;
  dance04_frm[3].positions[8] = 1405;
  dance04_frm[3].positions[9] = 1477;
  dance04_frm[3].positions[10] = 1359;
  dance04_frm[3].positions[11] = 1500;
  dance04_frm[3].positions[12] = 1487;
  dance04_frm[3].positions[13] = 1363;
  dance04_frm[3].positions[14] = 1594;
  dance04_frm[3].positions[15] = 1512;
  dance04_frm[3].positions[16] = 1636;
  dance04_frm[3].positions[17] = 1594;
  dance04_frm[3].positions[18] = 1522;
  dance04_frm[3].positions[19] = 1640;
  dance04_frm[3].positions[20] = 1500;
  dance04_frm[3].positions[21] = 1512;
  dance04_frm[3].positions[22] = 1636;
  dance04_frm[3].positions[23] = 1405;

  dance04_frm[4].positions[0] = 1776;
  dance04_frm[4].positions[1] = 1776;
  dance04_frm[4].positions[2] = 1223;
  dance04_frm[4].positions[3] = 853;
  dance04_frm[4].positions[4] = 1684;
  dance04_frm[4].positions[5] = 2146;
  dance04_frm[4].positions[6] = 1671;
  dance04_frm[4].positions[7] = 1624;
  dance04_frm[4].positions[8] = 1177;
  dance04_frm[4].positions[9] = 1767;
  dance04_frm[4].positions[10] = 1678;
  dance04_frm[4].positions[11] = 1316;
  dance04_frm[4].positions[12] = 1934;
  dance04_frm[4].positions[13] = 1770;
  dance04_frm[4].positions[14] = 1425;
  dance04_frm[4].positions[15] = 1628;
  dance04_frm[4].positions[16] = 1890;
  dance04_frm[4].positions[17] = 1455;
  dance04_frm[4].positions[18] = 1730;
  dance04_frm[4].positions[19] = 1934;
  dance04_frm[4].positions[20] = 1365;
  dance04_frm[4].positions[21] = 1787;
  dance04_frm[4].positions[22] = 1943;
  dance04_frm[4].positions[23] = 1249;

  dance04_frm[5].positions[0] = 1776;
  dance04_frm[5].positions[1] = 1961;
  dance04_frm[5].positions[2] = 1223;
  dance04_frm[5].positions[3] = 853;
  dance04_frm[5].positions[4] = 1684;
  dance04_frm[5].positions[5] = 2146;
  dance04_frm[5].positions[6] = 1571;
  dance04_frm[5].positions[7] = 1496;
  dance04_frm[5].positions[8] = 1305;
  dance04_frm[5].positions[9] = 1607;
  dance04_frm[5].positions[10] = 1513;
  dance04_frm[5].positions[11] = 1415;
  dance04_frm[5].positions[12] = 1672;
  dance04_frm[5].positions[13] = 1543;
  dance04_frm[5].positions[14] = 1512;
  dance04_frm[5].positions[15] = 1579;
  dance04_frm[5].positions[16] = 1767;
  dance04_frm[5].positions[17] = 1517;
  dance04_frm[5].positions[18] = 1634;
  dance04_frm[5].positions[19] = 1789;
  dance04_frm[5].positions[20] = 1428;
  dance04_frm[5].positions[21] = 1661;
  dance04_frm[5].positions[22] = 1796;
  dance04_frm[5].positions[23] = 1326;

  dance04_frm[6].positions[0] = 1776;
  dance04_frm[6].positions[1] = 1776;
  dance04_frm[6].positions[2] = 1223;
  dance04_frm[6].positions[3] = 853;
  dance04_frm[6].positions[4] = 1684;
  dance04_frm[6].positions[5] = 2146;
  dance04_frm[6].positions[6] = 1671;
  dance04_frm[6].positions[7] = 1624;
  dance04_frm[6].positions[8] = 1177;
  dance04_frm[6].positions[9] = 1767;
  dance04_frm[6].positions[10] = 1678;
  dance04_frm[6].positions[11] = 1316;
  dance04_frm[6].positions[12] = 1934;
  dance04_frm[6].positions[13] = 1770;
  dance04_frm[6].positions[14] = 1425;
  dance04_frm[6].positions[15] = 1628;
  dance04_frm[6].positions[16] = 1891;
  dance04_frm[6].positions[17] = 1455;
  dance04_frm[6].positions[18] = 1730;
  dance04_frm[6].positions[19] = 1934;
  dance04_frm[6].positions[20] = 1365;
  dance04_frm[6].positions[21] = 1787;
  dance04_frm[6].positions[22] = 1943;
  dance04_frm[6].positions[23] = 1249;

  dance04_frm[7].positions[0] = 1776;
  dance04_frm[7].positions[1] = 2146;
  dance04_frm[7].positions[2] = 1223;
  dance04_frm[7].positions[3] = 853;
  dance04_frm[7].positions[4] = 1500;
  dance04_frm[7].positions[5] = 2146;
  dance04_frm[7].positions[6] = 1487;
  dance04_frm[7].positions[7] = 1363;
  dance04_frm[7].positions[8] = 1405;
  dance04_frm[7].positions[9] = 1477;
  dance04_frm[7].positions[10] = 1359;
  dance04_frm[7].positions[11] = 1499;
  dance04_frm[7].positions[12] = 1487;
  dance04_frm[7].positions[13] = 1363;
  dance04_frm[7].positions[14] = 1594;
  dance04_frm[7].positions[15] = 1512;
  dance04_frm[7].positions[16] = 1636;
  dance04_frm[7].positions[17] = 1594;
  dance04_frm[7].positions[18] = 1522;
  dance04_frm[7].positions[19] = 1640;
  dance04_frm[7].positions[20] = 1499;
  dance04_frm[7].positions[21] = 1512;
  dance04_frm[7].positions[22] = 1636;
  dance04_frm[7].positions[23] = 1405;

  dance04_frm[8].positions[0] = 1776;
  dance04_frm[8].positions[1] = 2146;
  dance04_frm[8].positions[2] = 1223;
  dance04_frm[8].positions[3] = 1223;
  dance04_frm[8].positions[4] = 1315;
  dance04_frm[8].positions[5] = 2146;
  dance04_frm[8].positions[6] = 1371;
  dance04_frm[8].positions[7] = 1109;
  dance04_frm[8].positions[8] = 1544;
  dance04_frm[8].positions[9] = 1269;
  dance04_frm[8].positions[10] = 1065;
  dance04_frm[8].positions[11] = 1634;
  dance04_frm[8].positions[12] = 1212;
  dance04_frm[8].positions[13] = 1056;
  dance04_frm[8].positions[14] = 1750;
  dance04_frm[8].positions[15] = 1328;
  dance04_frm[8].positions[16] = 1375;
  dance04_frm[8].positions[17] = 1822;
  dance04_frm[8].positions[18] = 1232;
  dance04_frm[8].positions[19] = 1321;
  dance04_frm[8].positions[20] = 1683;
  dance04_frm[8].positions[21] = 1065;
  dance04_frm[8].positions[22] = 1229;
  dance04_frm[8].positions[23] = 1574;

  dance04_frm[9].positions[0] = 1776;
  dance04_frm[9].positions[1] = 2146;
  dance04_frm[9].positions[2] = 1223;
  dance04_frm[9].positions[3] = 1038;
  dance04_frm[9].positions[4] = 1315;
  dance04_frm[9].positions[5] = 2146;
  dance04_frm[9].positions[6] = 1420;
  dance04_frm[9].positions[7] = 1232;
  dance04_frm[9].positions[8] = 1482;
  dance04_frm[9].positions[9] = 1365;
  dance04_frm[9].positions[10] = 1210;
  dance04_frm[9].positions[11] = 1571;
  dance04_frm[9].positions[12] = 1338;
  dance04_frm[9].positions[13] = 1203;
  dance04_frm[9].positions[14] = 1673;
  dance04_frm[9].positions[15] = 1428;
  dance04_frm[9].positions[16] = 1503;
  dance04_frm[9].positions[17] = 1694;
  dance04_frm[9].positions[18] = 1392;
  dance04_frm[9].positions[19] = 1486;
  dance04_frm[9].positions[20] = 1584;
  dance04_frm[9].positions[21] = 1327;
  dance04_frm[9].positions[22] = 1456;
  dance04_frm[9].positions[23] = 1487;

  dance04_frm[10].positions[0] = 1776;
  dance04_frm[10].positions[1] = 2146;
  dance04_frm[10].positions[2] = 1223;
  dance04_frm[10].positions[3] = 1223;
  dance04_frm[10].positions[4] = 1315;
  dance04_frm[10].positions[5] = 2146;
  dance04_frm[10].positions[6] = 1371;
  dance04_frm[10].positions[7] = 1108;
  dance04_frm[10].positions[8] = 1544;
  dance04_frm[10].positions[9] = 1269;
  dance04_frm[10].positions[10] = 1065;
  dance04_frm[10].positions[11] = 1634;
  dance04_frm[10].positions[12] = 1212;
  dance04_frm[10].positions[13] = 1056;
  dance04_frm[10].positions[14] = 1750;
  dance04_frm[10].positions[15] = 1328;
  dance04_frm[10].positions[16] = 1375;
  dance04_frm[10].positions[17] = 1822;
  dance04_frm[10].positions[18] = 1232;
  dance04_frm[10].positions[19] = 1321;
  dance04_frm[10].positions[20] = 1683;
  dance04_frm[10].positions[21] = 1065;
  dance04_frm[10].positions[22] = 1229;
  dance04_frm[10].positions[23] = 1574;

  dance04_frm[11].positions[0] = 1776;
  dance04_frm[11].positions[1] = 2146;
  dance04_frm[11].positions[2] = 1223;
  dance04_frm[11].positions[3] = 853;
  dance04_frm[11].positions[4] = 1499;
  dance04_frm[11].positions[5] = 2146;
  dance04_frm[11].positions[6] = 1487;
  dance04_frm[11].positions[7] = 1363;
  dance04_frm[11].positions[8] = 1405;
  dance04_frm[11].positions[9] = 1477;
  dance04_frm[11].positions[10] = 1359;
  dance04_frm[11].positions[11] = 1500;
  dance04_frm[11].positions[12] = 1487;
  dance04_frm[11].positions[13] = 1363;
  dance04_frm[11].positions[14] = 1594;
  dance04_frm[11].positions[15] = 1512;
  dance04_frm[11].positions[16] = 1636;
  dance04_frm[11].positions[17] = 1594;
  dance04_frm[11].positions[18] = 1522;
  dance04_frm[11].positions[19] = 1640;
  dance04_frm[11].positions[20] = 1500;
  dance04_frm[11].positions[21] = 1512;
  dance04_frm[11].positions[22] = 1636;
  dance04_frm[11].positions[23] = 1405;

  dance04_frm[12].positions[0] = 1223;
  dance04_frm[12].positions[1] = 1684;
  dance04_frm[12].positions[2] = 1776;
  dance04_frm[12].positions[3] = 1315;
  dance04_frm[12].positions[4] = 1499;
  dance04_frm[12].positions[5] = 2146;
  dance04_frm[12].positions[6] = 1599;
  dance04_frm[12].positions[7] = 1413;
  dance04_frm[12].positions[8] = 1557;
  dance04_frm[12].positions[9] = 1488;
  dance04_frm[12].positions[10] = 1363;
  dance04_frm[12].positions[11] = 1653;
  dance04_frm[12].positions[12] = 1422;
  dance04_frm[12].positions[13] = 1340;
  dance04_frm[12].positions[14] = 1777;
  dance04_frm[12].positions[15] = 1577;
  dance04_frm[12].positions[16] = 1659;
  dance04_frm[12].positions[17] = 1777;
  dance04_frm[12].positions[18] = 1511;
  dance04_frm[12].positions[19] = 1636;
  dance04_frm[12].positions[20] = 1653;
  dance04_frm[12].positions[21] = 1400;
  dance04_frm[12].positions[22] = 1586;
  dance04_frm[12].positions[23] = 1557;

  dance04_frm[13].positions[0] = 1223;
  dance04_frm[13].positions[1] = 1684;
  dance04_frm[13].positions[2] = 1776;
  dance04_frm[13].positions[3] = 853;
  dance04_frm[13].positions[4] = 1500;
  dance04_frm[13].positions[5] = 2146;
  dance04_frm[13].positions[6] = 1422;
  dance04_frm[13].positions[7] = 1340;
  dance04_frm[13].positions[8] = 1222;
  dance04_frm[13].positions[9] = 1488;
  dance04_frm[13].positions[10] = 1363;
  dance04_frm[13].positions[11] = 1346;
  dance04_frm[13].positions[12] = 1599;
  dance04_frm[13].positions[13] = 1413;
  dance04_frm[13].positions[14] = 1442;
  dance04_frm[13].positions[15] = 1400;
  dance04_frm[13].positions[16] = 1586;
  dance04_frm[13].positions[17] = 1442;
  dance04_frm[13].positions[18] = 1511;
  dance04_frm[13].positions[19] = 1636;
  dance04_frm[13].positions[20] = 1346;
  dance04_frm[13].positions[21] = 1577;
  dance04_frm[13].positions[22] = 1659;
  dance04_frm[13].positions[23] = 1222;

  dance04_frm[14].positions[0] = 1223;
  dance04_frm[14].positions[1] = 2146;
  dance04_frm[14].positions[2] = 1776;
  dance04_frm[14].positions[3] = 853;
  dance04_frm[14].positions[4] = 1499;
  dance04_frm[14].positions[5] = 2146;
  dance04_frm[14].positions[6] = 1599;
  dance04_frm[14].positions[7] = 1413;
  dance04_frm[14].positions[8] = 1557;
  dance04_frm[14].positions[9] = 1488;
  dance04_frm[14].positions[10] = 1363;
  dance04_frm[14].positions[11] = 1653;
  dance04_frm[14].positions[12] = 1422;
  dance04_frm[14].positions[13] = 1340;
  dance04_frm[14].positions[14] = 1777;
  dance04_frm[14].positions[15] = 1577;
  dance04_frm[14].positions[16] = 1659;
  dance04_frm[14].positions[17] = 1777;
  dance04_frm[14].positions[18] = 1511;
  dance04_frm[14].positions[19] = 1636;
  dance04_frm[14].positions[20] = 1653;
  dance04_frm[14].positions[21] = 1400;
  dance04_frm[14].positions[22] = 1586;
  dance04_frm[14].positions[23] = 1557;

  dance05_frm[0].positions[0] = 1776;
  dance05_frm[0].positions[1] = 2146;
  dance05_frm[0].positions[2] = 1223;
  dance05_frm[0].positions[3] = 1223;
  dance05_frm[0].positions[4] = 1500;
  dance05_frm[0].positions[5] = 2146;
  dance05_frm[0].positions[6] = 1417;
  dance05_frm[0].positions[7] = 1231;
  dance05_frm[0].positions[8] = 1413;
  dance05_frm[0].positions[9] = 1406;
  dance05_frm[0].positions[10] = 1226;
  dance05_frm[0].positions[11] = 1499;
  dance05_frm[0].positions[12] = 1417;
  dance05_frm[0].positions[13] = 1231;
  dance05_frm[0].positions[14] = 1586;
  dance05_frm[0].positions[15] = 1430;
  dance05_frm[0].positions[16] = 1501;
  dance05_frm[0].positions[17] = 1606;
  dance05_frm[0].positions[18] = 1441;
  dance05_frm[0].positions[19] = 1504;
  dance05_frm[0].positions[20] = 1500;
  dance05_frm[0].positions[21] = 1430;
  dance05_frm[0].positions[22] = 1501;
  dance05_frm[0].positions[23] = 1393;

  dance05_frm[1].positions[0] = 1776;
  dance05_frm[1].positions[1] = 1776;
  dance05_frm[1].positions[2] = 1223;
  dance05_frm[1].positions[3] = 853;
  dance05_frm[1].positions[4] = 1499;
  dance05_frm[1].positions[5] = 2146;
  dance05_frm[1].positions[6] = 1569;
  dance05_frm[1].positions[7] = 1498;
  dance05_frm[1].positions[8] = 1393;
  dance05_frm[1].positions[9] = 1558;
  dance05_frm[1].positions[10] = 1495;
  dance05_frm[1].positions[11] = 1499;
  dance05_frm[1].positions[12] = 1569;
  dance05_frm[1].positions[13] = 1498;
  dance05_frm[1].positions[14] = 1606;
  dance05_frm[1].positions[15] = 1582;
  dance05_frm[1].positions[16] = 1768;
  dance05_frm[1].positions[17] = 1586;
  dance05_frm[1].positions[18] = 1593;
  dance05_frm[1].positions[19] = 1773;
  dance05_frm[1].positions[20] = 1500;
  dance05_frm[1].positions[21] = 1582;
  dance05_frm[1].positions[22] = 1768;
  dance05_frm[1].positions[23] = 1413;

  dance05_frm[2].positions[0] = 1223;
  dance05_frm[2].positions[1] = 1776;
  dance05_frm[2].positions[2] = 1776;
  dance05_frm[2].positions[3] = 853;
  dance05_frm[2].positions[4] = 1500;
  dance05_frm[2].positions[5] = 2146;
  dance05_frm[2].positions[6] = 1422;
  dance05_frm[2].positions[7] = 1340;
  dance05_frm[2].positions[8] = 1222;
  dance05_frm[2].positions[9] = 1488;
  dance05_frm[2].positions[10] = 1363;
  dance05_frm[2].positions[11] = 1346;
  dance05_frm[2].positions[12] = 1599;
  dance05_frm[2].positions[13] = 1413;
  dance05_frm[2].positions[14] = 1442;
  dance05_frm[2].positions[15] = 1400;
  dance05_frm[2].positions[16] = 1586;
  dance05_frm[2].positions[17] = 1442;
  dance05_frm[2].positions[18] = 1511;
  dance05_frm[2].positions[19] = 1636;
  dance05_frm[2].positions[20] = 1346;
  dance05_frm[2].positions[21] = 1577;
  dance05_frm[2].positions[22] = 1659;
  dance05_frm[2].positions[23] = 1222;

  dance05_frm[3].positions[0] = 1223;
  dance05_frm[3].positions[1] = 2146;
  dance05_frm[3].positions[2] = 1776;
  dance05_frm[3].positions[3] = 853;
  dance05_frm[3].positions[4] = 1499;
  dance05_frm[3].positions[5] = 2146;
  dance05_frm[3].positions[6] = 1599;
  dance05_frm[3].positions[7] = 1413;
  dance05_frm[3].positions[8] = 1557;
  dance05_frm[3].positions[9] = 1488;
  dance05_frm[3].positions[10] = 1363;
  dance05_frm[3].positions[11] = 1653;
  dance05_frm[3].positions[12] = 1422;
  dance05_frm[3].positions[13] = 1340;
  dance05_frm[3].positions[14] = 1777;
  dance05_frm[3].positions[15] = 1577;
  dance05_frm[3].positions[16] = 1659;
  dance05_frm[3].positions[17] = 1777;
  dance05_frm[3].positions[18] = 1511;
  dance05_frm[3].positions[19] = 1636;
  dance05_frm[3].positions[20] = 1653;
  dance05_frm[3].positions[21] = 1400;
  dance05_frm[3].positions[22] = 1586;
  dance05_frm[3].positions[23] = 1557;

  dance06_frm[0].positions[0] = 1776;
  dance06_frm[0].positions[1] = 2100;
  dance06_frm[0].positions[2] = 1223;
  dance06_frm[0].positions[3] = 921;
  dance06_frm[0].positions[4] = 1500;
  dance06_frm[0].positions[5] = 2146;
  dance06_frm[0].positions[6] = 1250;
  dance06_frm[0].positions[7] = 1111;
  dance06_frm[0].positions[8] = 1292;
  dance06_frm[0].positions[9] = 1231;
  dance06_frm[0].positions[10] = 1127;
  dance06_frm[0].positions[11] = 1484;
  dance06_frm[0].positions[12] = 1292;
  dance06_frm[0].positions[13] = 1177;
  dance06_frm[0].positions[14] = 1680;
  dance06_frm[0].positions[15] = 1749;
  dance06_frm[0].positions[16] = 1888;
  dance06_frm[0].positions[17] = 1707;
  dance06_frm[0].positions[18] = 1768;
  dance06_frm[0].positions[19] = 1872;
  dance06_frm[0].positions[20] = 1515;
  dance06_frm[0].positions[21] = 1707;
  dance06_frm[0].positions[22] = 1822;
  dance06_frm[0].positions[23] = 1319;

  dance06_frm[1].positions[0] = 1776;
  dance06_frm[1].positions[1] = 2100;
  dance06_frm[1].positions[2] = 1223;
  dance06_frm[1].positions[3] = 921;
  dance06_frm[1].positions[4] = 1500;
  dance06_frm[1].positions[5] = 2146;
  dance06_frm[1].positions[6] = 1293;
  dance06_frm[1].positions[7] = 1141;
  dance06_frm[1].positions[8] = 1236;
  dance06_frm[1].positions[9] = 1370;
  dance06_frm[1].positions[10] = 1293;
  dance06_frm[1].positions[11] = 1410;
  dance06_frm[1].positions[12] = 1533;
  dance06_frm[1].positions[13] = 1469;
  dance06_frm[1].positions[14] = 1605;
  dance06_frm[1].positions[15] = 1706;
  dance06_frm[1].positions[16] = 1858;
  dance06_frm[1].positions[17] = 1763;
  dance06_frm[1].positions[18] = 1629;
  dance06_frm[1].positions[19] = 1706;
  dance06_frm[1].positions[20] = 1589;
  dance06_frm[1].positions[21] = 1466;
  dance06_frm[1].positions[22] = 1530;
  dance06_frm[1].positions[23] = 1394;

  dance06_frm[2].positions[0] = 1776;
  dance06_frm[2].positions[1] = 2100;
  dance06_frm[2].positions[2] = 1223;
  dance06_frm[2].positions[3] = 921;
  dance06_frm[2].positions[4] = 1500;
  dance06_frm[2].positions[5] = 2146;
  dance06_frm[2].positions[6] = 1403;
  dance06_frm[2].positions[7] = 1332;
  dance06_frm[2].positions[8] = 1414;
  dance06_frm[2].positions[9] = 1201;
  dance06_frm[2].positions[10] = 1077;
  dance06_frm[2].positions[11] = 1604;
  dance06_frm[2].positions[12] = 1098;
  dance06_frm[2].positions[13] = 846;
  dance06_frm[2].positions[14] = 1771;
  dance06_frm[2].positions[15] = 1596;
  dance06_frm[2].positions[16] = 1667;
  dance06_frm[2].positions[17] = 1585;
  dance06_frm[2].positions[18] = 1798;
  dance06_frm[2].positions[19] = 1922;
  dance06_frm[2].positions[20] = 1395;
  dance06_frm[2].positions[21] = 1901;
  dance06_frm[2].positions[22] = 2153;
  dance06_frm[2].positions[23] = 1228;

  dance07_frm[0].positions[0] = 1776;
  dance07_frm[0].positions[1] = 2238;
  dance07_frm[0].positions[2] = 1223;
  dance07_frm[0].positions[3] = 1499;
  dance07_frm[0].positions[4] = 1676;
  dance07_frm[0].positions[5] = 2146;
  dance07_frm[0].positions[6] = 1714;
  dance07_frm[0].positions[7] = 1632;
  dance07_frm[0].positions[8] = 1098;
  dance07_frm[0].positions[9] = 1773;
  dance07_frm[0].positions[10] = 1681;
  dance07_frm[0].positions[11] = 1317;
  dance07_frm[0].positions[12] = 1970;
  dance07_frm[0].positions[13] = 1792;
  dance07_frm[0].positions[14] = 1500;
  dance07_frm[0].positions[15] = 1780;
  dance07_frm[0].positions[16] = 1958;
  dance07_frm[0].positions[17] = 1550;
  dance07_frm[0].positions[18] = 1871;
  dance07_frm[0].positions[19] = 1975;
  dance07_frm[0].positions[20] = 1352;
  dance07_frm[0].positions[21] = 1849;
  dance07_frm[0].positions[22] = 1929;
  dance07_frm[0].positions[23] = 1096;

  dance07_frm[1].positions[0] = 1776;
  dance07_frm[1].positions[1] = 2238;
  dance07_frm[1].positions[2] = 1223;
  dance07_frm[1].positions[3] = 1223;
  dance07_frm[1].positions[4] = 1676;
  dance07_frm[1].positions[5] = 2146;
  dance07_frm[1].positions[6] = 1515;
  dance07_frm[1].positions[7] = 1479;
  dance07_frm[1].positions[8] = 1059;
  dance07_frm[1].positions[9] = 1554;
  dance07_frm[1].positions[10] = 1521;
  dance07_frm[1].positions[11] = 1306;
  dance07_frm[1].positions[12] = 1688;
  dance07_frm[1].positions[13] = 1586;
  dance07_frm[1].positions[14] = 1513;
  dance07_frm[1].positions[15] = 1788;
  dance07_frm[1].positions[16] = 2047;
  dance07_frm[1].positions[17] = 1534;
  dance07_frm[1].positions[18] = 1908;
  dance07_frm[1].positions[19] = 2105;
  dance07_frm[1].positions[20] = 1357;
  dance07_frm[1].positions[21] = 1905;
  dance07_frm[1].positions[22] = 2071;
  dance07_frm[1].positions[23] = 1133;

  dance07_frm[2].positions[0] = 1776;
  dance07_frm[2].positions[1] = 2238;
  dance07_frm[2].positions[2] = 1223;
  dance07_frm[2].positions[3] = 1499;
  dance07_frm[2].positions[4] = 1676;
  dance07_frm[2].positions[5] = 2146;
  dance07_frm[2].positions[6] = 1714;
  dance07_frm[2].positions[7] = 1632;
  dance07_frm[2].positions[8] = 1098;
  dance07_frm[2].positions[9] = 1773;
  dance07_frm[2].positions[10] = 1681;
  dance07_frm[2].positions[11] = 1317;
  dance07_frm[2].positions[12] = 1970;
  dance07_frm[2].positions[13] = 1792;
  dance07_frm[2].positions[14] = 1500;
  dance07_frm[2].positions[15] = 1780;
  dance07_frm[2].positions[16] = 1958;
  dance07_frm[2].positions[17] = 1550;
  dance07_frm[2].positions[18] = 1871;
  dance07_frm[2].positions[19] = 1975;
  dance07_frm[2].positions[20] = 1352;
  dance07_frm[2].positions[21] = 1849;
  dance07_frm[2].positions[22] = 1929;
  dance07_frm[2].positions[23] = 1096;

  dance07_frm[3].positions[0] = 1776;
  dance07_frm[3].positions[1] = 2238;
  dance07_frm[3].positions[2] = 1223;
  dance07_frm[3].positions[3] = 921;
  dance07_frm[3].positions[4] = 1500;
  dance07_frm[3].positions[5] = 2146;
  dance07_frm[3].positions[6] = 1245;
  dance07_frm[3].positions[7] = 1111;
  dance07_frm[3].positions[8] = 1305;
  dance07_frm[3].positions[9] = 1205;
  dance07_frm[3].positions[10] = 1092;
  dance07_frm[3].positions[11] = 1499;
  dance07_frm[3].positions[12] = 1245;
  dance07_frm[3].positions[13] = 1111;
  dance07_frm[3].positions[14] = 1694;
  dance07_frm[3].positions[15] = 1754;
  dance07_frm[3].positions[16] = 1888;
  dance07_frm[3].positions[17] = 1694;
  dance07_frm[3].positions[18] = 1794;
  dance07_frm[3].positions[19] = 1907;
  dance07_frm[3].positions[20] = 1499;
  dance07_frm[3].positions[21] = 1754;
  dance07_frm[3].positions[22] = 1888;
  dance07_frm[3].positions[23] = 1305;

  dance07_frm[4].positions[0] = 1776;
  dance07_frm[4].positions[1] = 1500;
  dance07_frm[4].positions[2] = 1223;
  dance07_frm[4].positions[3] = 921;
  dance07_frm[4].positions[4] = 1323;
  dance07_frm[4].positions[5] = 2146;
  dance07_frm[4].positions[6] = 1219;
  dance07_frm[4].positions[7] = 1041;
  dance07_frm[4].positions[8] = 1449;
  dance07_frm[4].positions[9] = 1128;
  dance07_frm[4].positions[10] = 1024;
  dance07_frm[4].positions[11] = 1647;
  dance07_frm[4].positions[12] = 1150;
  dance07_frm[4].positions[13] = 1071;
  dance07_frm[4].positions[14] = 1903;
  dance07_frm[4].positions[15] = 1285;
  dance07_frm[4].positions[16] = 1367;
  dance07_frm[4].positions[17] = 1901;
  dance07_frm[4].positions[18] = 1226;
  dance07_frm[4].positions[19] = 1318;
  dance07_frm[4].positions[20] = 1682;
  dance07_frm[4].positions[21] = 1029;
  dance07_frm[4].positions[22] = 1207;
  dance07_frm[4].positions[23] = 1499;

  dance07_frm[5].positions[0] = 1776;
  dance07_frm[5].positions[1] = 1776;
  dance07_frm[5].positions[2] = 1223;
  dance07_frm[5].positions[3] = 921;
  dance07_frm[5].positions[4] = 1323;
  dance07_frm[5].positions[5] = 2146;
  dance07_frm[5].positions[6] = 1211;
  dance07_frm[5].positions[7] = 952;
  dance07_frm[5].positions[8] = 1465;
  dance07_frm[5].positions[9] = 1091;
  dance07_frm[5].positions[10] = 894;
  dance07_frm[5].positions[11] = 1642;
  dance07_frm[5].positions[12] = 1094;
  dance07_frm[5].positions[13] = 928;
  dance07_frm[5].positions[14] = 1866;
  dance07_frm[5].positions[15] = 1484;
  dance07_frm[5].positions[16] = 1520;
  dance07_frm[5].positions[17] = 1940;
  dance07_frm[5].positions[18] = 1445;
  dance07_frm[5].positions[19] = 1478;
  dance07_frm[5].positions[20] = 1693;
  dance07_frm[5].positions[21] = 1311;
  dance07_frm[5].positions[22] = 1413;
  dance07_frm[5].positions[23] = 1486;

  dance07_frm[6].positions[0] = 1776;
  dance07_frm[6].positions[1] = 1500;
  dance07_frm[6].positions[2] = 1223;
  dance07_frm[6].positions[3] = 921;
  dance07_frm[6].positions[4] = 1323;
  dance07_frm[6].positions[5] = 2146;
  dance07_frm[6].positions[6] = 1219;
  dance07_frm[6].positions[7] = 1041;
  dance07_frm[6].positions[8] = 1449;
  dance07_frm[6].positions[9] = 1128;
  dance07_frm[6].positions[10] = 1024;
  dance07_frm[6].positions[11] = 1647;
  dance07_frm[6].positions[12] = 1150;
  dance07_frm[6].positions[13] = 1070;
  dance07_frm[6].positions[14] = 1903;
  dance07_frm[6].positions[15] = 1285;
  dance07_frm[6].positions[16] = 1367;
  dance07_frm[6].positions[17] = 1901;
  dance07_frm[6].positions[18] = 1226;
  dance07_frm[6].positions[19] = 1318;
  dance07_frm[6].positions[20] = 1682;
  dance07_frm[6].positions[21] = 1029;
  dance07_frm[6].positions[22] = 1207;
  dance07_frm[6].positions[23] = 1499;

  dance07_frm[7].positions[0] = 1776;
  dance07_frm[7].positions[1] = 2238;
  dance07_frm[7].positions[2] = 1223;
  dance07_frm[7].positions[3] = 921;
  dance07_frm[7].positions[4] = 1499;
  dance07_frm[7].positions[5] = 2146;
  dance07_frm[7].positions[6] = 1245;
  dance07_frm[7].positions[7] = 1111;
  dance07_frm[7].positions[8] = 1305;
  dance07_frm[7].positions[9] = 1205;
  dance07_frm[7].positions[10] = 1092;
  dance07_frm[7].positions[11] = 1500;
  dance07_frm[7].positions[12] = 1245;
  dance07_frm[7].positions[13] = 1111;
  dance07_frm[7].positions[14] = 1694;
  dance07_frm[7].positions[15] = 1754;
  dance07_frm[7].positions[16] = 1888;
  dance07_frm[7].positions[17] = 1694;
  dance07_frm[7].positions[18] = 1794;
  dance07_frm[7].positions[19] = 1907;
  dance07_frm[7].positions[20] = 1500;
  dance07_frm[7].positions[21] = 1754;
  dance07_frm[7].positions[22] = 1888;
  dance07_frm[7].positions[23] = 1305;

  dance08_frm[0].positions[0] = 1776;
  dance08_frm[0].positions[1] = 2238;
  dance08_frm[0].positions[2] = 1223;
  dance08_frm[0].positions[3] = 921;
  dance08_frm[0].positions[4] = 1500;
  dance08_frm[0].positions[5] = 2146;
  dance08_frm[0].positions[6] = 1746;
  dance08_frm[0].positions[7] = 1636;
  dance08_frm[0].positions[8] = 1278;
  dance08_frm[0].positions[9] = 1597;
  dance08_frm[0].positions[10] = 1434;
  dance08_frm[0].positions[11] = 1452;
  dance08_frm[0].positions[12] = 1594;
  dance08_frm[0].positions[13] = 1317;
  dance08_frm[0].positions[14] = 1578;
  dance08_frm[0].positions[15] = 1469;
  dance08_frm[0].positions[16] = 1499;
  dance08_frm[0].positions[17] = 1414;
  dance08_frm[0].positions[18] = 1730;
  dance08_frm[0].positions[19] = 1746;
  dance08_frm[0].positions[20] = 1165;
  dance08_frm[0].positions[21] = 1895;
  dance08_frm[0].positions[22] = 2015;
  dance08_frm[0].positions[23] = 918;

  dance08_frm[1].positions[0] = 1776;
  dance08_frm[1].positions[1] = 2190;
  dance08_frm[1].positions[2] = 1223;
  dance08_frm[1].positions[3] = 809;
  dance08_frm[1].positions[4] = 1499;
  dance08_frm[1].positions[5] = 2146;
  dance08_frm[1].positions[6] = 1088;
  dance08_frm[1].positions[7] = 878;
  dance08_frm[1].positions[8] = 1300;
  dance08_frm[1].positions[9] = 1047;
  dance08_frm[1].positions[10] = 859;
  dance08_frm[1].positions[11] = 1494;
  dance08_frm[1].positions[12] = 1108;
  dance08_frm[1].positions[13] = 914;
  dance08_frm[1].positions[14] = 1689;
  dance08_frm[1].positions[15] = 1911;
  dance08_frm[1].positions[16] = 2121;
  dance08_frm[1].positions[17] = 1699;
  dance08_frm[1].positions[18] = 1952;
  dance08_frm[1].positions[19] = 2140;
  dance08_frm[1].positions[20] = 1505;
  dance08_frm[1].positions[21] = 1891;
  dance08_frm[1].positions[22] = 2085;
  dance08_frm[1].positions[23] = 1310;

  dance08_frm[2].positions[0] = 1776;
  dance08_frm[2].positions[1] = 1500;
  dance08_frm[2].positions[2] = 1223;
  dance08_frm[2].positions[3] = 1499;
  dance08_frm[2].positions[4] = 1499;
  dance08_frm[2].positions[5] = 2146;
  dance08_frm[2].positions[6] = 1469;
  dance08_frm[2].positions[7] = 1333;
  dance08_frm[2].positions[8] = 1197;
  dance08_frm[2].positions[9] = 1612;
  dance08_frm[2].positions[10] = 1541;
  dance08_frm[2].positions[11] = 1355;
  dance08_frm[2].positions[12] = 1896;
  dance08_frm[2].positions[13] = 1806;
  dance08_frm[2].positions[14] = 1543;
  dance08_frm[2].positions[15] = 1530;
  dance08_frm[2].positions[16] = 1666;
  dance08_frm[2].positions[17] = 1802;
  dance08_frm[2].positions[18] = 1387;
  dance08_frm[2].positions[19] = 1458;
  dance08_frm[2].positions[20] = 1644;
  dance08_frm[2].positions[21] = 1103;
  dance08_frm[2].positions[22] = 1193;
  dance08_frm[2].positions[23] = 1456;

  dance08_frm[3].positions[0] = 1776;
  dance08_frm[3].positions[1] = 2146;
  dance08_frm[3].positions[2] = 1223;
  dance08_frm[3].positions[3] = 853;
  dance08_frm[3].positions[4] = 1500;
  dance08_frm[3].positions[5] = 2146;
  dance08_frm[3].positions[6] = 1245;
  dance08_frm[3].positions[7] = 1111;
  dance08_frm[3].positions[8] = 1305;
  dance08_frm[3].positions[9] = 1205;
  dance08_frm[3].positions[10] = 1092;
  dance08_frm[3].positions[11] = 1499;
  dance08_frm[3].positions[12] = 1245;
  dance08_frm[3].positions[13] = 1111;
  dance08_frm[3].positions[14] = 1694;
  dance08_frm[3].positions[15] = 1754;
  dance08_frm[3].positions[16] = 1888;
  dance08_frm[3].positions[17] = 1694;
  dance08_frm[3].positions[18] = 1794;
  dance08_frm[3].positions[19] = 1907;
  dance08_frm[3].positions[20] = 1500;
  dance08_frm[3].positions[21] = 1754;
  dance08_frm[3].positions[22] = 1888;
  dance08_frm[3].positions[23] = 1305;

  dance08_frm[4].positions[0] = 1776;
  dance08_frm[4].positions[1] = 2238;
  dance08_frm[4].positions[2] = 1223;
  dance08_frm[4].positions[3] = 921;
  dance08_frm[4].positions[4] = 1499;
  dance08_frm[4].positions[5] = 2146;
  dance08_frm[4].positions[6] = 1530;
  dance08_frm[4].positions[7] = 1500;
  dance08_frm[4].positions[8] = 1585;
  dance08_frm[4].positions[9] = 1269;
  dance08_frm[4].positions[10] = 1253;
  dance08_frm[4].positions[11] = 1834;
  dance08_frm[4].positions[12] = 1104;
  dance08_frm[4].positions[13] = 984;
  dance08_frm[4].positions[14] = 2081;
  dance08_frm[4].positions[15] = 1253;
  dance08_frm[4].positions[16] = 1363;
  dance08_frm[4].positions[17] = 1721;
  dance08_frm[4].positions[18] = 1402;
  dance08_frm[4].positions[19] = 1565;
  dance08_frm[4].positions[20] = 1547;
  dance08_frm[4].positions[21] = 1405;
  dance08_frm[4].positions[22] = 1682;
  dance08_frm[4].positions[23] = 1421;

  dance08_frm[5].positions[0] = 1776;
  dance08_frm[5].positions[1] = 2190;
  dance08_frm[5].positions[2] = 1223;
  dance08_frm[5].positions[3] = 809;
  dance08_frm[5].positions[4] = 1499;
  dance08_frm[5].positions[5] = 2146;
  dance08_frm[5].positions[6] = 1088;
  dance08_frm[5].positions[7] = 878;
  dance08_frm[5].positions[8] = 1300;
  dance08_frm[5].positions[9] = 1047;
  dance08_frm[5].positions[10] = 859;
  dance08_frm[5].positions[11] = 1494;
  dance08_frm[5].positions[12] = 1108;
  dance08_frm[5].positions[13] = 914;
  dance08_frm[5].positions[14] = 1689;
  dance08_frm[5].positions[15] = 1911;
  dance08_frm[5].positions[16] = 2121;
  dance08_frm[5].positions[17] = 1699;
  dance08_frm[5].positions[18] = 1952;
  dance08_frm[5].positions[19] = 2140;
  dance08_frm[5].positions[20] = 1505;
  dance08_frm[5].positions[21] = 1891;
  dance08_frm[5].positions[22] = 2085;
  dance08_frm[5].positions[23] = 1310;

  dance08_frm[6].positions[0] = 1776;
  dance08_frm[6].positions[1] = 1500;
  dance08_frm[6].positions[2] = 1223;
  dance08_frm[6].positions[3] = 1499;
  dance08_frm[6].positions[4] = 1500;
  dance08_frm[6].positions[5] = 2146;
  dance08_frm[6].positions[6] = 1469;
  dance08_frm[6].positions[7] = 1333;
  dance08_frm[6].positions[8] = 1197;
  dance08_frm[6].positions[9] = 1612;
  dance08_frm[6].positions[10] = 1541;
  dance08_frm[6].positions[11] = 1355;
  dance08_frm[6].positions[12] = 1896;
  dance08_frm[6].positions[13] = 1806;
  dance08_frm[6].positions[14] = 1543;
  dance08_frm[6].positions[15] = 1530;
  dance08_frm[6].positions[16] = 1666;
  dance08_frm[6].positions[17] = 1802;
  dance08_frm[6].positions[18] = 1387;
  dance08_frm[6].positions[19] = 1458;
  dance08_frm[6].positions[20] = 1644;
  dance08_frm[6].positions[21] = 1103;
  dance08_frm[6].positions[22] = 1193;
  dance08_frm[6].positions[23] = 1456;

  dance08_frm[7].positions[0] = 1776;
  dance08_frm[7].positions[1] = 2146;
  dance08_frm[7].positions[2] = 1223;
  dance08_frm[7].positions[3] = 853;
  dance08_frm[7].positions[4] = 1500;
  dance08_frm[7].positions[5] = 2146;
  dance08_frm[7].positions[6] = 1245;
  dance08_frm[7].positions[7] = 1111;
  dance08_frm[7].positions[8] = 1305;
  dance08_frm[7].positions[9] = 1205;
  dance08_frm[7].positions[10] = 1092;
  dance08_frm[7].positions[11] = 1499;
  dance08_frm[7].positions[12] = 1245;
  dance08_frm[7].positions[13] = 1111;
  dance08_frm[7].positions[14] = 1694;
  dance08_frm[7].positions[15] = 1754;
  dance08_frm[7].positions[16] = 1888;
  dance08_frm[7].positions[17] = 1694;
  dance08_frm[7].positions[18] = 1794;
  dance08_frm[7].positions[19] = 1907;
  dance08_frm[7].positions[20] = 1500;
  dance08_frm[7].positions[21] = 1754;
  dance08_frm[7].positions[22] = 1888;
  dance08_frm[7].positions[23] = 1305;

  dance09_frm[0].positions[0] = 1776;
  dance09_frm[0].positions[1] = 2146;
  dance09_frm[0].positions[2] = 1223;
  dance09_frm[0].positions[3] = 853;
  dance09_frm[0].positions[4] = 1500;
  dance09_frm[0].positions[5] = 2146;
  dance09_frm[0].positions[6] = 1245;
  dance09_frm[0].positions[7] = 1111;
  dance09_frm[0].positions[8] = 1305;
  dance09_frm[0].positions[9] = 1205;
  dance09_frm[0].positions[10] = 1092;
  dance09_frm[0].positions[11] = 1499;
  dance09_frm[0].positions[12] = 1245;
  dance09_frm[0].positions[13] = 1111;
  dance09_frm[0].positions[14] = 1694;
  dance09_frm[0].positions[15] = 1754;
  dance09_frm[0].positions[16] = 1888;
  dance09_frm[0].positions[17] = 1694;
  dance09_frm[0].positions[18] = 1794;
  dance09_frm[0].positions[19] = 1907;
  dance09_frm[0].positions[20] = 1500;
  dance09_frm[0].positions[21] = 1754;
  dance09_frm[0].positions[22] = 1888;
  dance09_frm[0].positions[23] = 1305;

  dance09_frm[1].positions[0] = 1776;
  dance09_frm[1].positions[1] = 1776;
  dance09_frm[1].positions[2] = 1223;
  dance09_frm[1].positions[3] = 1223;
  dance09_frm[1].positions[4] = 1499;
  dance09_frm[1].positions[5] = 2146;
  dance09_frm[1].positions[6] = 1278;
  dance09_frm[1].positions[7] = 1105;
  dance09_frm[1].positions[8] = 1212;
  dance09_frm[1].positions[9] = 1396;
  dance09_frm[1].positions[10] = 1317;
  dance09_frm[1].positions[11] = 1375;
  dance09_frm[1].positions[12] = 1615;
  dance09_frm[1].positions[13] = 1554;
  dance09_frm[1].positions[14] = 1564;
  dance09_frm[1].positions[15] = 1721;
  dance09_frm[1].positions[16] = 1894;
  dance09_frm[1].positions[17] = 1787;
  dance09_frm[1].positions[18] = 1603;
  dance09_frm[1].positions[19] = 1682;
  dance09_frm[1].positions[20] = 1624;
  dance09_frm[1].positions[21] = 1384;
  dance09_frm[1].positions[22] = 1445;
  dance09_frm[1].positions[23] = 1435;

  dance09_frm[2].positions[0] = 1776;
  dance09_frm[2].positions[1] = 2146;
  dance09_frm[2].positions[2] = 1223;
  dance09_frm[2].positions[3] = 853;
  dance09_frm[2].positions[4] = 1499;
  dance09_frm[2].positions[5] = 2146;
  dance09_frm[2].positions[6] = 1323;
  dance09_frm[2].positions[7] = 1227;
  dance09_frm[2].positions[8] = 1356;
  dance09_frm[2].positions[9] = 1204;
  dance09_frm[2].positions[10] = 1088;
  dance09_frm[2].positions[11] = 1552;
  dance09_frm[2].positions[12] = 1170;
  dance09_frm[2].positions[13] = 984;
  dance09_frm[2].positions[14] = 1736;
  dance09_frm[2].positions[15] = 1676;
  dance09_frm[2].positions[16] = 1772;
  dance09_frm[2].positions[17] = 1643;
  dance09_frm[2].positions[18] = 1795;
  dance09_frm[2].positions[19] = 1911;
  dance09_frm[2].positions[20] = 1447;
  dance09_frm[2].positions[21] = 1829;
  dance09_frm[2].positions[22] = 2015;
  dance09_frm[2].positions[23] = 1263;

  dance09_frm[3].positions[0] = 1223;
  dance09_frm[3].positions[1] = 2146;
  dance09_frm[3].positions[2] = 1776;
  dance09_frm[3].positions[3] = 853;
  dance09_frm[3].positions[4] = 1684;
  dance09_frm[3].positions[5] = 2146;
  dance09_frm[3].positions[6] = 1323;
  dance09_frm[3].positions[7] = 1227;
  dance09_frm[3].positions[8] = 1356;
  dance09_frm[3].positions[9] = 1204;
  dance09_frm[3].positions[10] = 1088;
  dance09_frm[3].positions[11] = 1552;
  dance09_frm[3].positions[12] = 1170;
  dance09_frm[3].positions[13] = 984;
  dance09_frm[3].positions[14] = 1736;
  dance09_frm[3].positions[15] = 1676;
  dance09_frm[3].positions[16] = 1772;
  dance09_frm[3].positions[17] = 1643;
  dance09_frm[3].positions[18] = 1795;
  dance09_frm[3].positions[19] = 1911;
  dance09_frm[3].positions[20] = 1447;
  dance09_frm[3].positions[21] = 1829;
  dance09_frm[3].positions[22] = 2015;
  dance09_frm[3].positions[23] = 1263;

  dance09_frm[4].positions[0] = 1223;
  dance09_frm[4].positions[1] = 1961;
  dance09_frm[4].positions[2] = 1776;
  dance09_frm[4].positions[3] = 1038;
  dance09_frm[4].positions[4] = 1315;
  dance09_frm[4].positions[5] = 2146;
  dance09_frm[4].positions[6] = 1323;
  dance09_frm[4].positions[7] = 1227;
  dance09_frm[4].positions[8] = 1356;
  dance09_frm[4].positions[9] = 1204;
  dance09_frm[4].positions[10] = 1088;
  dance09_frm[4].positions[11] = 1553;
  dance09_frm[4].positions[12] = 1170;
  dance09_frm[4].positions[13] = 984;
  dance09_frm[4].positions[14] = 1736;
  dance09_frm[4].positions[15] = 1676;
  dance09_frm[4].positions[16] = 1772;
  dance09_frm[4].positions[17] = 1643;
  dance09_frm[4].positions[18] = 1795;
  dance09_frm[4].positions[19] = 1911;
  dance09_frm[4].positions[20] = 1446;
  dance09_frm[4].positions[21] = 1829;
  dance09_frm[4].positions[22] = 2015;
  dance09_frm[4].positions[23] = 1263;

  dance09_frm[5].positions[0] = 1223;
  dance09_frm[5].positions[1] = 2146;
  dance09_frm[5].positions[2] = 1776;
  dance09_frm[5].positions[3] = 853;
  dance09_frm[5].positions[4] = 1684;
  dance09_frm[5].positions[5] = 2146;
  dance09_frm[5].positions[6] = 1323;
  dance09_frm[5].positions[7] = 1227;
  dance09_frm[5].positions[8] = 1356;
  dance09_frm[5].positions[9] = 1204;
  dance09_frm[5].positions[10] = 1088;
  dance09_frm[5].positions[11] = 1552;
  dance09_frm[5].positions[12] = 1170;
  dance09_frm[5].positions[13] = 984;
  dance09_frm[5].positions[14] = 1736;
  dance09_frm[5].positions[15] = 1676;
  dance09_frm[5].positions[16] = 1772;
  dance09_frm[5].positions[17] = 1643;
  dance09_frm[5].positions[18] = 1795;
  dance09_frm[5].positions[19] = 1911;
  dance09_frm[5].positions[20] = 1447;
  dance09_frm[5].positions[21] = 1829;
  dance09_frm[5].positions[22] = 2015;
  dance09_frm[5].positions[23] = 1263;

  dance09_frm[6].positions[0] = 1223;
  dance09_frm[6].positions[1] = 1961;
  dance09_frm[6].positions[2] = 1776;
  dance09_frm[6].positions[3] = 1038;
  dance09_frm[6].positions[4] = 1315;
  dance09_frm[6].positions[5] = 2146;
  dance09_frm[6].positions[6] = 1323;
  dance09_frm[6].positions[7] = 1227;
  dance09_frm[6].positions[8] = 1356;
  dance09_frm[6].positions[9] = 1204;
  dance09_frm[6].positions[10] = 1088;
  dance09_frm[6].positions[11] = 1553;
  dance09_frm[6].positions[12] = 1170;
  dance09_frm[6].positions[13] = 984;
  dance09_frm[6].positions[14] = 1736;
  dance09_frm[6].positions[15] = 1676;
  dance09_frm[6].positions[16] = 1772;
  dance09_frm[6].positions[17] = 1643;
  dance09_frm[6].positions[18] = 1795;
  dance09_frm[6].positions[19] = 1911;
  dance09_frm[6].positions[20] = 1446;
  dance09_frm[6].positions[21] = 1829;
  dance09_frm[6].positions[22] = 2015;
  dance09_frm[6].positions[23] = 1263;

  dance09_frm[7].positions[0] = 1223;
  dance09_frm[7].positions[1] = 2146;
  dance09_frm[7].positions[2] = 1776;
  dance09_frm[7].positions[3] = 853;
  dance09_frm[7].positions[4] = 1684;
  dance09_frm[7].positions[5] = 2146;
  dance09_frm[7].positions[6] = 1323;
  dance09_frm[7].positions[7] = 1227;
  dance09_frm[7].positions[8] = 1356;
  dance09_frm[7].positions[9] = 1204;
  dance09_frm[7].positions[10] = 1088;
  dance09_frm[7].positions[11] = 1552;
  dance09_frm[7].positions[12] = 1170;
  dance09_frm[7].positions[13] = 984;
  dance09_frm[7].positions[14] = 1736;
  dance09_frm[7].positions[15] = 1676;
  dance09_frm[7].positions[16] = 1772;
  dance09_frm[7].positions[17] = 1643;
  dance09_frm[7].positions[18] = 1795;
  dance09_frm[7].positions[19] = 1911;
  dance09_frm[7].positions[20] = 1447;
  dance09_frm[7].positions[21] = 1829;
  dance09_frm[7].positions[22] = 2015;
  dance09_frm[7].positions[23] = 1263;

  dance09_frm[8].positions[0] = 1223;
  dance09_frm[8].positions[1] = 1961;
  dance09_frm[8].positions[2] = 1776;
  dance09_frm[8].positions[3] = 1038;
  dance09_frm[8].positions[4] = 1315;
  dance09_frm[8].positions[5] = 2146;
  dance09_frm[8].positions[6] = 1323;
  dance09_frm[8].positions[7] = 1227;
  dance09_frm[8].positions[8] = 1356;
  dance09_frm[8].positions[9] = 1204;
  dance09_frm[8].positions[10] = 1088;
  dance09_frm[8].positions[11] = 1553;
  dance09_frm[8].positions[12] = 1170;
  dance09_frm[8].positions[13] = 984;
  dance09_frm[8].positions[14] = 1736;
  dance09_frm[8].positions[15] = 1676;
  dance09_frm[8].positions[16] = 1772;
  dance09_frm[8].positions[17] = 1643;
  dance09_frm[8].positions[18] = 1795;
  dance09_frm[8].positions[19] = 1911;
  dance09_frm[8].positions[20] = 1446;
  dance09_frm[8].positions[21] = 1829;
  dance09_frm[8].positions[22] = 2015;
  dance09_frm[8].positions[23] = 1263;

  dance10_frm[0].positions[0] = 1223;
  dance10_frm[0].positions[1] = 1961;
  dance10_frm[0].positions[2] = 1223;
  dance10_frm[0].positions[3] = 1499;
  dance10_frm[0].positions[4] = 1500;
  dance10_frm[0].positions[5] = 1869;
  dance10_frm[0].positions[6] = 1379;
  dance10_frm[0].positions[7] = 1370;
  dance10_frm[0].positions[8] = 1209;
  dance10_frm[0].positions[9] = 1223;
  dance10_frm[0].positions[10] = 1128;
  dance10_frm[0].positions[11] = 1443;
  dance10_frm[0].positions[12] = 1208;
  dance10_frm[0].positions[13] = 961;
  dance10_frm[0].positions[14] = 1602;
  dance10_frm[0].positions[15] = 1525;
  dance10_frm[0].positions[16] = 1678;
  dance10_frm[0].positions[17] = 1430;
  dance10_frm[0].positions[18] = 1794;
  dance10_frm[0].positions[19] = 1958;
  dance10_frm[0].positions[20] = 1247;
  dance10_frm[0].positions[21] = 1964;
  dance10_frm[0].positions[22] = 2083;
  dance10_frm[0].positions[23] = 1045;

  dance10_frm[1].positions[0] = 1299;
  dance10_frm[1].positions[1] = 1897;
  dance10_frm[1].positions[2] = 1299;
  dance10_frm[1].positions[3] = 1410;
  dance10_frm[1].positions[4] = 1499;
  dance10_frm[1].positions[5] = 1869;
  dance10_frm[1].positions[6] = 1377;
  dance10_frm[1].positions[7] = 1351;
  dance10_frm[1].positions[8] = 1265;
  dance10_frm[1].positions[9] = 1219;
  dance10_frm[1].positions[10] = 1119;
  dance10_frm[1].positions[11] = 1484;
  dance10_frm[1].positions[12] = 1184;
  dance10_frm[1].positions[13] = 945;
  dance10_frm[1].positions[14] = 1643;
  dance10_frm[1].positions[15] = 1552;
  dance10_frm[1].positions[16] = 1681;
  dance10_frm[1].positions[17] = 1473;
  dance10_frm[1].positions[18] = 1793;
  dance10_frm[1].positions[19] = 1941;
  dance10_frm[1].positions[20] = 1290;
  dance10_frm[1].positions[21] = 1941;
  dance10_frm[1].positions[22] = 2083;
  dance10_frm[1].positions[23] = 1098;

  dance10_frm[2].positions[0] = 1491;
  dance10_frm[2].positions[1] = 1738;
  dance10_frm[2].positions[2] = 1491;
  dance10_frm[2].positions[3] = 1187;
  dance10_frm[2].positions[4] = 1499;
  dance10_frm[2].positions[5] = 1869;
  dance10_frm[2].positions[6] = 1388;
  dance10_frm[2].positions[7] = 1314;
  dance10_frm[2].positions[8] = 1388;
  dance10_frm[2].positions[9] = 1218;
  dance10_frm[2].positions[10] = 1104;
  dance10_frm[2].positions[11] = 1582;
  dance10_frm[2].positions[12] = 1141;
  dance10_frm[2].positions[13] = 922;
  dance10_frm[2].positions[14] = 1755;
  dance10_frm[2].positions[15] = 1608;
  dance10_frm[2].positions[16] = 1686;
  dance10_frm[2].positions[17] = 1600;
  dance10_frm[2].positions[18] = 1781;
  dance10_frm[2].positions[19] = 1897;
  dance10_frm[2].positions[20] = 1407;
  dance10_frm[2].positions[21] = 1863;
  dance10_frm[2].positions[22] = 2083;
  dance10_frm[2].positions[23] = 1233;

  dance10_frm[3].positions[0] = 1687;
  dance10_frm[3].positions[1] = 1574;
  dance10_frm[3].positions[2] = 1687;
  dance10_frm[3].positions[3] = 958;
  dance10_frm[3].positions[4] = 1499;
  dance10_frm[3].positions[5] = 1869;
  dance10_frm[3].positions[6] = 1424;
  dance10_frm[3].positions[7] = 1296;
  dance10_frm[3].positions[8] = 1491;
  dance10_frm[3].positions[9] = 1231;
  dance10_frm[3].positions[10] = 1104;
  dance10_frm[3].positions[11] = 1678;
  dance10_frm[3].positions[12] = 1127;
  dance10_frm[3].positions[13] = 931;
  dance10_frm[3].positions[14] = 1878;
  dance10_frm[3].positions[15] = 1648;
  dance10_frm[3].positions[16] = 1691;
  dance10_frm[3].positions[17] = 1757;
  dance10_frm[3].positions[18] = 1759;
  dance10_frm[3].positions[19] = 1855;
  dance10_frm[3].positions[20] = 1537;
  dance10_frm[3].positions[21] = 1764;
  dance10_frm[3].positions[22] = 1968;
  dance10_frm[3].positions[23] = 1367;

  dance10_frm[4].positions[0] = 1776;
  dance10_frm[4].positions[1] = 1500;
  dance10_frm[4].positions[2] = 1776;
  dance10_frm[4].positions[3] = 853;
  dance10_frm[4].positions[4] = 1499;
  dance10_frm[4].positions[5] = 1869;
  dance10_frm[4].positions[6] = 1449;
  dance10_frm[4].positions[7] = 1295;
  dance10_frm[4].positions[8] = 1532;
  dance10_frm[4].positions[9] = 1241;
  dance10_frm[4].positions[10] = 1108;
  dance10_frm[4].positions[11] = 1720;
  dance10_frm[4].positions[12] = 1131;
  dance10_frm[4].positions[13] = 947;
  dance10_frm[4].positions[14] = 1935;
  dance10_frm[4].positions[15] = 1661;
  dance10_frm[4].positions[16] = 1696;
  dance10_frm[4].positions[17] = 1836;
  dance10_frm[4].positions[18] = 1746;
  dance10_frm[4].positions[19] = 1838;
  dance10_frm[4].positions[20] = 1597;
  dance10_frm[4].positions[21] = 1714;
  dance10_frm[4].positions[22] = 1917;
  dance10_frm[4].positions[23] = 1425;

  dance10_frm[5].positions[0] = 1700;
  dance10_frm[5].positions[1] = 1564;
  dance10_frm[5].positions[2] = 1700;
  dance10_frm[5].positions[3] = 943;
  dance10_frm[5].positions[4] = 1500;
  dance10_frm[5].positions[5] = 1869;
  dance10_frm[5].positions[6] = 1419;
  dance10_frm[5].positions[7] = 1286;
  dance10_frm[5].positions[8] = 1486;
  dance10_frm[5].positions[9] = 1242;
  dance10_frm[5].positions[10] = 1121;
  dance10_frm[5].positions[11] = 1674;
  dance10_frm[5].positions[12] = 1154;
  dance10_frm[5].positions[13] = 981;
  dance10_frm[5].positions[14] = 1879;
  dance10_frm[5].positions[15] = 1661;
  dance10_frm[5].positions[16] = 1710;
  dance10_frm[5].positions[17] = 1781;
  dance10_frm[5].positions[18] = 1749;
  dance10_frm[5].positions[19] = 1843;
  dance10_frm[5].positions[20] = 1558;
  dance10_frm[5].positions[21] = 1734;
  dance10_frm[5].positions[22] = 1925;
  dance10_frm[5].positions[23] = 1384;

  dance10_frm[6].positions[0] = 1508;
  dance10_frm[6].positions[1] = 1723;
  dance10_frm[6].positions[2] = 1508;
  dance10_frm[6].positions[3] = 1166;
  dance10_frm[6].positions[4] = 1500;
  dance10_frm[6].positions[5] = 1869;
  dance10_frm[6].positions[6] = 1358;
  dance10_frm[6].positions[7] = 1265;
  dance10_frm[6].positions[8] = 1354;
  dance10_frm[6].positions[9] = 1251;
  dance10_frm[6].positions[10] = 1152;
  dance10_frm[6].positions[11] = 1551;
  dance10_frm[6].positions[12] = 1226;
  dance10_frm[6].positions[13] = 1068;
  dance10_frm[6].positions[14] = 1737;
  dance10_frm[6].positions[15] = 1645;
  dance10_frm[6].positions[16] = 1734;
  dance10_frm[6].positions[17] = 1657;
  dance10_frm[6].positions[18] = 1747;
  dance10_frm[6].positions[19] = 1846;
  dance10_frm[6].positions[20] = 1459;
  dance10_frm[6].positions[21] = 1769;
  dance10_frm[6].positions[22] = 1927;
  dance10_frm[6].positions[23] = 1274;

  dance10_frm[7].positions[0] = 1312;
  dance10_frm[7].positions[1] = 1886;
  dance10_frm[7].positions[2] = 1312;
  dance10_frm[7].positions[3] = 1395;
  dance10_frm[7].positions[4] = 1500;
  dance10_frm[7].positions[5] = 1869;
  dance10_frm[7].positions[6] = 1313;
  dance10_frm[7].positions[7] = 1243;
  dance10_frm[7].positions[8] = 1198;
  dance10_frm[7].positions[9] = 1270;
  dance10_frm[7].positions[10] = 1179;
  dance10_frm[7].positions[11] = 1418;
  dance10_frm[7].positions[12] = 1319;
  dance10_frm[7].positions[13] = 1156;
  dance10_frm[7].positions[14] = 1599;
  dance10_frm[7].positions[15] = 1603;
  dance10_frm[7].positions[16] = 1739;
  dance10_frm[7].positions[17] = 1548;
  dance10_frm[7].positions[18] = 1732;
  dance10_frm[7].positions[19] = 1836;
  dance10_frm[7].positions[20] = 1360;
  dance10_frm[7].positions[21] = 1776;
  dance10_frm[7].positions[22] = 1903;
  dance10_frm[7].positions[23] = 1149;

  dance10_frm[8].positions[0] = 1223;
  dance10_frm[8].positions[1] = 1961;
  dance10_frm[8].positions[2] = 1223;
  dance10_frm[8].positions[3] = 1499;
  dance10_frm[8].positions[4] = 1500;
  dance10_frm[8].positions[5] = 1869;
  dance10_frm[8].positions[6] = 1299;
  dance10_frm[8].positions[7] = 1232;
  dance10_frm[8].positions[8] = 1123;
  dance10_frm[8].positions[9] = 1282;
  dance10_frm[8].positions[10] = 1189;
  dance10_frm[8].positions[11] = 1359;
  dance10_frm[8].positions[12] = 1367;
  dance10_frm[8].positions[13] = 1195;
  dance10_frm[8].positions[14] = 1542;
  dance10_frm[8].positions[15] = 1577;
  dance10_frm[8].positions[16] = 1734;
  dance10_frm[8].positions[17] = 1504;
  dance10_frm[8].positions[18] = 1721;
  dance10_frm[8].positions[19] = 1828;
  dance10_frm[8].positions[20] = 1316;
  dance10_frm[8].positions[21] = 1769;
  dance10_frm[8].positions[22] = 1883;
  dance10_frm[8].positions[23] = 1090;

  dance10_frm[9].positions[0] = 1299;
  dance10_frm[9].positions[1] = 1897;
  dance10_frm[9].positions[2] = 1299;
  dance10_frm[9].positions[3] = 1410;
  dance10_frm[9].positions[4] = 1499;
  dance10_frm[9].positions[5] = 1869;
  dance10_frm[9].positions[6] = 1301;
  dance10_frm[9].positions[7] = 1223;
  dance10_frm[9].positions[8] = 1176;
  dance10_frm[9].positions[9] = 1280;
  dance10_frm[9].positions[10] = 1189;
  dance10_frm[9].positions[11] = 1397;
  dance10_frm[9].positions[12] = 1350;
  dance10_frm[9].positions[13] = 1194;
  dance10_frm[9].positions[14] = 1580;
  dance10_frm[9].positions[15] = 1607;
  dance10_frm[9].positions[16] = 1749;
  dance10_frm[9].positions[17] = 1552;
  dance10_frm[9].positions[18] = 1721;
  dance10_frm[9].positions[19] = 1820;
  dance10_frm[9].positions[20] = 1365;
  dance10_frm[9].positions[21] = 1748;
  dance10_frm[9].positions[22] = 1857;
  dance10_frm[9].positions[23] = 1150;

  dance10_frm[10].positions[0] = 1491;
  dance10_frm[10].positions[1] = 1738;
  dance10_frm[10].positions[2] = 1491;
  dance10_frm[10].positions[3] = 1187;
  dance10_frm[10].positions[4] = 1499;
  dance10_frm[10].positions[5] = 1869;
  dance10_frm[10].positions[6] = 1321;
  dance10_frm[10].positions[7] = 1211;
  dance10_frm[10].positions[8] = 1300;
  dance10_frm[10].positions[9] = 1284;
  dance10_frm[10].positions[10] = 1196;
  dance10_frm[10].positions[11] = 1495;
  dance10_frm[10].positions[12] = 1323;
  dance10_frm[10].positions[13] = 1210;
  dance10_frm[10].positions[14] = 1688;
  dance10_frm[10].positions[15] = 1674;
  dance10_frm[10].positions[16] = 1786;
  dance10_frm[10].positions[17] = 1687;
  dance10_frm[10].positions[18] = 1715;
  dance10_frm[10].positions[19] = 1803;
  dance10_frm[10].positions[20] = 1493;
  dance10_frm[10].positions[21] = 1680;
  dance10_frm[10].positions[22] = 1791;
  dance10_frm[10].positions[23] = 1298;

  dance10_frm[11].positions[0] = 1687;
  dance10_frm[11].positions[1] = 1574;
  dance10_frm[11].positions[2] = 1687;
  dance10_frm[11].positions[3] = 958;
  dance10_frm[11].positions[4] = 1499;
  dance10_frm[11].positions[5] = 1869;
  dance10_frm[11].positions[6] = 1367;
  dance10_frm[11].positions[7] = 1220;
  dance10_frm[11].positions[8] = 1411;
  dance10_frm[11].positions[9] = 1302;
  dance10_frm[11].positions[10] = 1216;
  dance10_frm[11].positions[11] = 1595;
  dance10_frm[11].positions[12] = 1323;
  dance10_frm[11].positions[13] = 1248;
  dance10_frm[11].positions[14] = 1813;
  dance10_frm[11].positions[15] = 1722;
  dance10_frm[11].positions[16] = 1824;
  dance10_frm[11].positions[17] = 1839;
  dance10_frm[11].positions[18] = 1699;
  dance10_frm[11].positions[19] = 1791;
  dance10_frm[11].positions[20] = 1626;
  dance10_frm[11].positions[21] = 1592;
  dance10_frm[11].positions[22] = 1727;
  dance10_frm[11].positions[23] = 1438;

  dance10_frm[12].positions[0] = 1776;
  dance10_frm[12].positions[1] = 1500;
  dance10_frm[12].positions[2] = 1776;
  dance10_frm[12].positions[3] = 853;
  dance10_frm[12].positions[4] = 1499;
  dance10_frm[12].positions[5] = 1869;
  dance10_frm[12].positions[6] = 1396;
  dance10_frm[12].positions[7] = 1232;
  dance10_frm[12].positions[8] = 1457;
  dance10_frm[12].positions[9] = 1314;
  dance10_frm[12].positions[10] = 1229;
  dance10_frm[12].positions[11] = 1640;
  dance10_frm[12].positions[12] = 1332;
  dance10_frm[12].positions[13] = 1272;
  dance10_frm[12].positions[14] = 1875;
  dance10_frm[12].positions[15] = 1737;
  dance10_frm[12].positions[16] = 1841;
  dance10_frm[12].positions[17] = 1910;
  dance10_frm[12].positions[18] = 1690;
  dance10_frm[12].positions[19] = 1788;
  dance10_frm[12].positions[20] = 1683;
  dance10_frm[12].positions[21] = 1546;
  dance10_frm[12].positions[22] = 1697;
  dance10_frm[12].positions[23] = 1495;

  dance10_frm[13].positions[0] = 1700;
  dance10_frm[13].positions[1] = 1564;
  dance10_frm[13].positions[2] = 1700;
  dance10_frm[13].positions[3] = 943;
  dance10_frm[13].positions[4] = 1500;
  dance10_frm[13].positions[5] = 1869;
  dance10_frm[13].positions[6] = 1364;
  dance10_frm[13].positions[7] = 1210;
  dance10_frm[13].positions[8] = 1408;
  dance10_frm[13].positions[9] = 1313;
  dance10_frm[13].positions[10] = 1232;
  dance10_frm[13].positions[11] = 1589;
  dance10_frm[13].positions[12] = 1353;
  dance10_frm[13].positions[13] = 1292;
  dance10_frm[13].positions[14] = 1811;
  dance10_frm[13].positions[15] = 1734;
  dance10_frm[13].positions[16] = 1847;
  dance10_frm[13].positions[17] = 1859;
  dance10_frm[13].positions[18] = 1690;
  dance10_frm[13].positions[19] = 1784;
  dance10_frm[13].positions[20] = 1647;
  dance10_frm[13].positions[21] = 1560;
  dance10_frm[13].positions[22] = 1691;
  dance10_frm[13].positions[23] = 1459;

  dance10_frm[14].positions[0] = 1508;
  dance10_frm[14].positions[1] = 1723;
  dance10_frm[14].positions[2] = 1508;
  dance10_frm[14].positions[3] = 1166;
  dance10_frm[14].positions[4] = 1500;
  dance10_frm[14].positions[5] = 1869;
  dance10_frm[14].positions[6] = 1294;
  dance10_frm[14].positions[7] = 1156;
  dance10_frm[14].positions[8] = 1273;
  dance10_frm[14].positions[9] = 1316;
  dance10_frm[14].positions[10] = 1234;
  dance10_frm[14].positions[11] = 1458;
  dance10_frm[14].positions[12] = 1417;
  dance10_frm[14].positions[13] = 1338;
  dance10_frm[14].positions[14] = 1656;
  dance10_frm[14].positions[15] = 1710;
  dance10_frm[14].positions[16] = 1846;
  dance10_frm[14].positions[17] = 1739;
  dance10_frm[14].positions[18] = 1683;
  dance10_frm[14].positions[19] = 1766;
  dance10_frm[14].positions[20] = 1552;
  dance10_frm[14].positions[21] = 1578;
  dance10_frm[14].positions[22] = 1661;
  dance10_frm[14].positions[23] = 1356;

  dance10_frm[15].positions[0] = 1312;
  dance10_frm[15].positions[1] = 1886;
  dance10_frm[15].positions[2] = 1312;
  dance10_frm[15].positions[3] = 1395;
  dance10_frm[15].positions[4] = 1500;
  dance10_frm[15].positions[5] = 1869;
  dance10_frm[15].positions[6] = 1243;
  dance10_frm[15].positions[7] = 1103;
  dance10_frm[15].positions[8] = 1126;
  dance10_frm[15].positions[9] = 1328;
  dance10_frm[15].positions[10] = 1231;
  dance10_frm[15].positions[11] = 1328;
  dance10_frm[15].positions[12] = 1501;
  dance10_frm[15].positions[13] = 1383;
  dance10_frm[15].positions[14] = 1517;
  dance10_frm[15].positions[15] = 1660;
  dance10_frm[15].positions[16] = 1823;
  dance10_frm[15].positions[17] = 1626;
  dance10_frm[15].positions[18] = 1663;
  dance10_frm[15].positions[19] = 1736;
  dance10_frm[15].positions[20] = 1453;
  dance10_frm[15].positions[21] = 1571;
  dance10_frm[15].positions[22] = 1609;
  dance10_frm[15].positions[23] = 1232;

  dance10_frm[16].positions[0] = 1223;
  dance10_frm[16].positions[1] = 1961;
  dance10_frm[16].positions[2] = 1223;
  dance10_frm[16].positions[3] = 1499;
  dance10_frm[16].positions[4] = 1500;
  dance10_frm[16].positions[5] = 1869;
  dance10_frm[16].positions[6] = 1227;
  dance10_frm[16].positions[7] = 1081;
  dance10_frm[16].positions[8] = 1060;
  dance10_frm[16].positions[9] = 1337;
  dance10_frm[16].positions[10] = 1229;
  dance10_frm[16].positions[11] = 1273;
  dance10_frm[16].positions[12] = 1546;
  dance10_frm[16].positions[13] = 1404;
  dance10_frm[16].positions[14] = 1461;
  dance10_frm[16].positions[15] = 1629;
  dance10_frm[16].positions[16] = 1805;
  dance10_frm[16].positions[17] = 1579;
  dance10_frm[16].positions[18] = 1650;
  dance10_frm[16].positions[19] = 1718;
  dance10_frm[16].positions[20] = 1408;
  dance10_frm[16].positions[21] = 1560;
  dance10_frm[16].positions[22] = 1581;
  dance10_frm[16].positions[23] = 1169;

  dance10_frm[17].positions[0] = 1299;
  dance10_frm[17].positions[1] = 1897;
  dance10_frm[17].positions[2] = 1299;
  dance10_frm[17].positions[3] = 1410;
  dance10_frm[17].positions[4] = 1499;
  dance10_frm[17].positions[5] = 1869;
  dance10_frm[17].positions[6] = 1231;
  dance10_frm[17].positions[7] = 1079;
  dance10_frm[17].positions[8] = 1108;
  dance10_frm[17].positions[9] = 1337;
  dance10_frm[17].positions[10] = 1236;
  dance10_frm[17].positions[11] = 1307;
  dance10_frm[17].positions[12] = 1535;
  dance10_frm[17].positions[13] = 1415;
  dance10_frm[17].positions[14] = 1495;
  dance10_frm[17].positions[15] = 1663;
  dance10_frm[17].positions[16] = 1833;
  dance10_frm[17].positions[17] = 1629;
  dance10_frm[17].positions[18] = 1652;
  dance10_frm[17].positions[19] = 1721;
  dance10_frm[17].positions[20] = 1461;
  dance10_frm[17].positions[21] = 1539;
  dance10_frm[17].positions[22] = 1567;
  dance10_frm[17].positions[23] = 1237;

  dance10_frm[18].positions[0] = 1491;
  dance10_frm[18].positions[1] = 1738;
  dance10_frm[18].positions[2] = 1491;
  dance10_frm[18].positions[3] = 1187;
  dance10_frm[18].positions[4] = 1499;
  dance10_frm[18].positions[5] = 1869;
  dance10_frm[18].positions[6] = 1258;
  dance10_frm[18].positions[7] = 1091;
  dance10_frm[18].positions[8] = 1224;
  dance10_frm[18].positions[9] = 1347;
  dance10_frm[18].positions[10] = 1264;
  dance10_frm[18].positions[11] = 1397;
  dance10_frm[18].positions[12] = 1524;
  dance10_frm[18].positions[13] = 1459;
  dance10_frm[18].positions[14] = 1590;
  dance10_frm[18].positions[15] = 1736;
  dance10_frm[18].positions[16] = 1903;
  dance10_frm[18].positions[17] = 1762;
  dance10_frm[18].positions[18] = 1652;
  dance10_frm[18].positions[19] = 1733;
  dance10_frm[18].positions[20] = 1591;
  dance10_frm[18].positions[21] = 1478;
  dance10_frm[18].positions[22] = 1539;
  dance10_frm[18].positions[23] = 1396;

  dance10_frm[19].positions[0] = 1687;
  dance10_frm[19].positions[1] = 1574;
  dance10_frm[19].positions[2] = 1687;
  dance10_frm[19].positions[3] = 958;
  dance10_frm[19].positions[4] = 1499;
  dance10_frm[19].positions[5] = 1869;
  dance10_frm[19].positions[6] = 1312;
  dance10_frm[19].positions[7] = 1128;
  dance10_frm[19].positions[8] = 1336;
  dance10_frm[19].positions[9] = 1369;
  dance10_frm[19].positions[10] = 1304;
  dance10_frm[19].positions[11] = 1493;
  dance10_frm[19].positions[12] = 1540;
  dance10_frm[19].positions[13] = 1523;
  dance10_frm[19].positions[14] = 1709;
  dance10_frm[19].positions[15] = 1788;
  dance10_frm[19].positions[16] = 1970;
  dance10_frm[19].positions[17] = 1902;
  dance10_frm[19].positions[18] = 1643;
  dance10_frm[19].positions[19] = 1749;
  dance10_frm[19].positions[20] = 1715;
  dance10_frm[19].positions[21] = 1397;
  dance10_frm[19].positions[22] = 1511;
  dance10_frm[19].positions[23] = 1532;

  dance10_frm[20].positions[0] = 1776;
  dance10_frm[20].positions[1] = 2146;
  dance10_frm[20].positions[2] = 1223;
  dance10_frm[20].positions[3] = 853;
  dance10_frm[20].positions[4] = 1500;
  dance10_frm[20].positions[5] = 2146;
  dance10_frm[20].positions[6] = 1245;
  dance10_frm[20].positions[7] = 1111;
  dance10_frm[20].positions[8] = 1305;
  dance10_frm[20].positions[9] = 1205;
  dance10_frm[20].positions[10] = 1092;
  dance10_frm[20].positions[11] = 1499;
  dance10_frm[20].positions[12] = 1245;
  dance10_frm[20].positions[13] = 1111;
  dance10_frm[20].positions[14] = 1694;
  dance10_frm[20].positions[15] = 1754;
  dance10_frm[20].positions[16] = 1888;
  dance10_frm[20].positions[17] = 1694;
  dance10_frm[20].positions[18] = 1794;
  dance10_frm[20].positions[19] = 1907;
  dance10_frm[20].positions[20] = 1500;
  dance10_frm[20].positions[21] = 1754;
  dance10_frm[20].positions[22] = 1888;
  dance10_frm[20].positions[23] = 1305;

  dance11_frm[0].positions[0] = 1776;
  dance11_frm[0].positions[1] = 2053;
  dance11_frm[0].positions[2] = 1223;
  dance11_frm[0].positions[3] = 946;
  dance11_frm[0].positions[4] = 1499;
  dance11_frm[0].positions[5] = 2146;
  dance11_frm[0].positions[6] = 1577;
  dance11_frm[0].positions[7] = 1494;
  dance11_frm[0].positions[8] = 1305;
  dance11_frm[0].positions[9] = 1541;
  dance11_frm[0].positions[10] = 1485;
  dance11_frm[0].positions[11] = 1499;
  dance11_frm[0].positions[12] = 1577;
  dance11_frm[0].positions[13] = 1494;
  dance11_frm[0].positions[14] = 1694;
  dance11_frm[0].positions[15] = 1422;
  dance11_frm[0].positions[16] = 1505;
  dance11_frm[0].positions[17] = 1694;
  dance11_frm[0].positions[18] = 1458;
  dance11_frm[0].positions[19] = 1514;
  dance11_frm[0].positions[20] = 1500;
  dance11_frm[0].positions[21] = 1422;
  dance11_frm[0].positions[22] = 1505;
  dance11_frm[0].positions[23] = 1305;

  dance11_frm[1].positions[0] = 1776;
  dance11_frm[1].positions[1] = 2146;
  dance11_frm[1].positions[2] = 1223;
  dance11_frm[1].positions[3] = 853;
  dance11_frm[1].positions[4] = 1500;
  dance11_frm[1].positions[5] = 1869;
  dance11_frm[1].positions[6] = 1245;
  dance11_frm[1].positions[7] = 1111;
  dance11_frm[1].positions[8] = 1305;
  dance11_frm[1].positions[9] = 1205;
  dance11_frm[1].positions[10] = 1092;
  dance11_frm[1].positions[11] = 1499;
  dance11_frm[1].positions[12] = 1245;
  dance11_frm[1].positions[13] = 1111;
  dance11_frm[1].positions[14] = 1694;
  dance11_frm[1].positions[15] = 1754;
  dance11_frm[1].positions[16] = 1888;
  dance11_frm[1].positions[17] = 1694;
  dance11_frm[1].positions[18] = 1794;
  dance11_frm[1].positions[19] = 1907;
  dance11_frm[1].positions[20] = 1500;
  dance11_frm[1].positions[21] = 1754;
  dance11_frm[1].positions[22] = 1888;
  dance11_frm[1].positions[23] = 1305;

  dance11_frm[2].positions[0] = 1776;
  dance11_frm[2].positions[1] = 1499;
  dance11_frm[2].positions[2] = 1223;
  dance11_frm[2].positions[3] = 1500;
  dance11_frm[2].positions[4] = 1499;
  dance11_frm[2].positions[5] = 2146;
  dance11_frm[2].positions[6] = 1469;
  dance11_frm[2].positions[7] = 1333;
  dance11_frm[2].positions[8] = 1197;
  dance11_frm[2].positions[9] = 1612;
  dance11_frm[2].positions[10] = 1541;
  dance11_frm[2].positions[11] = 1355;
  dance11_frm[2].positions[12] = 1896;
  dance11_frm[2].positions[13] = 1806;
  dance11_frm[2].positions[14] = 1543;
  dance11_frm[2].positions[15] = 1530;
  dance11_frm[2].positions[16] = 1666;
  dance11_frm[2].positions[17] = 1802;
  dance11_frm[2].positions[18] = 1387;
  dance11_frm[2].positions[19] = 1458;
  dance11_frm[2].positions[20] = 1644;
  dance11_frm[2].positions[21] = 1103;
  dance11_frm[2].positions[22] = 1193;
  dance11_frm[2].positions[23] = 1456;

  dance11_frm[3].positions[0] = 1223;
  dance11_frm[3].positions[1] = 1499;
  dance11_frm[3].positions[2] = 1223;
  dance11_frm[3].positions[3] = 853;
  dance11_frm[3].positions[4] = 1500;
  dance11_frm[3].positions[5] = 2146;
  dance11_frm[3].positions[6] = 1547;
  dance11_frm[3].positions[7] = 1388;
  dance11_frm[3].positions[8] = 1175;
  dance11_frm[3].positions[9] = 1591;
  dance11_frm[3].positions[10] = 1409;
  dance11_frm[3].positions[11] = 1353;
  dance11_frm[3].positions[12] = 1746;
  dance11_frm[3].positions[13] = 1490;
  dance11_frm[3].positions[14] = 1500;
  dance11_frm[3].positions[15] = 1635;
  dance11_frm[3].positions[16] = 1673;
  dance11_frm[3].positions[17] = 1562;
  dance11_frm[3].positions[18] = 1710;
  dance11_frm[3].positions[19] = 1673;
  dance11_frm[3].positions[20] = 1307;
  dance11_frm[3].positions[21] = 1699;
  dance11_frm[3].positions[22] = 1675;
  dance11_frm[3].positions[23] = 988;

  dance11_frm[4].positions[0] = 1776;
  dance11_frm[4].positions[1] = 2146;
  dance11_frm[4].positions[2] = 1223;
  dance11_frm[4].positions[3] = 853;
  dance11_frm[4].positions[4] = 1499;
  dance11_frm[4].positions[5] = 2146;
  dance11_frm[4].positions[6] = 1403;
  dance11_frm[4].positions[7] = 1332;
  dance11_frm[4].positions[8] = 1414;
  dance11_frm[4].positions[9] = 1201;
  dance11_frm[4].positions[10] = 1077;
  dance11_frm[4].positions[11] = 1604;
  dance11_frm[4].positions[12] = 1098;
  dance11_frm[4].positions[13] = 846;
  dance11_frm[4].positions[14] = 1771;
  dance11_frm[4].positions[15] = 1596;
  dance11_frm[4].positions[16] = 1667;
  dance11_frm[4].positions[17] = 1585;
  dance11_frm[4].positions[18] = 1798;
  dance11_frm[4].positions[19] = 1922;
  dance11_frm[4].positions[20] = 1395;
  dance11_frm[4].positions[21] = 1901;
  dance11_frm[4].positions[22] = 2153;
  dance11_frm[4].positions[23] = 1228;

  dance11_frm[5].positions[0] = 1776;
  dance11_frm[5].positions[1] = 2146;
  dance11_frm[5].positions[2] = 1776;
  dance11_frm[5].positions[3] = 1499;
  dance11_frm[5].positions[4] = 1499;
  dance11_frm[5].positions[5] = 2146;
  dance11_frm[5].positions[6] = 1364;
  dance11_frm[5].positions[7] = 1326;
  dance11_frm[5].positions[8] = 1437;
  dance11_frm[5].positions[9] = 1289;
  dance11_frm[5].positions[10] = 1326;
  dance11_frm[5].positions[11] = 1692;
  dance11_frm[5].positions[12] = 1300;
  dance11_frm[5].positions[13] = 1324;
  dance11_frm[5].positions[14] = 2011;
  dance11_frm[5].positions[15] = 1452;
  dance11_frm[5].positions[16] = 1611;
  dance11_frm[5].positions[17] = 1824;
  dance11_frm[5].positions[18] = 1408;
  dance11_frm[5].positions[19] = 1590;
  dance11_frm[5].positions[20] = 1646;
  dance11_frm[5].positions[21] = 1253;
  dance11_frm[5].positions[22] = 1509;
  dance11_frm[5].positions[23] = 1499;

  dance11_frm[6].positions[0] = 1776;
  dance11_frm[6].positions[1] = 1500;
  dance11_frm[6].positions[2] = 1223;
  dance11_frm[6].positions[3] = 1500;
  dance11_frm[6].positions[4] = 1500;
  dance11_frm[6].positions[5] = 2146;
  dance11_frm[6].positions[6] = 1469;
  dance11_frm[6].positions[7] = 1333;
  dance11_frm[6].positions[8] = 1197;
  dance11_frm[6].positions[9] = 1612;
  dance11_frm[6].positions[10] = 1541;
  dance11_frm[6].positions[11] = 1355;
  dance11_frm[6].positions[12] = 1896;
  dance11_frm[6].positions[13] = 1806;
  dance11_frm[6].positions[14] = 1543;
  dance11_frm[6].positions[15] = 1530;
  dance11_frm[6].positions[16] = 1666;
  dance11_frm[6].positions[17] = 1802;
  dance11_frm[6].positions[18] = 1387;
  dance11_frm[6].positions[19] = 1458;
  dance11_frm[6].positions[20] = 1644;
  dance11_frm[6].positions[21] = 1103;
  dance11_frm[6].positions[22] = 1193;
  dance11_frm[6].positions[23] = 1456;

  dance12_frm[0].positions[0] = 1776;
  dance12_frm[0].positions[1] = 1776;
  dance12_frm[0].positions[2] = 1223;
  dance12_frm[0].positions[3] = 1223;
  dance12_frm[0].positions[4] = 1499;
  dance12_frm[0].positions[5] = 2146;
  dance12_frm[0].positions[6] = 1245;
  dance12_frm[0].positions[7] = 1111;
  dance12_frm[0].positions[8] = 1305;
  dance12_frm[0].positions[9] = 1205;
  dance12_frm[0].positions[10] = 1092;
  dance12_frm[0].positions[11] = 1499;
  dance12_frm[0].positions[12] = 1245;
  dance12_frm[0].positions[13] = 1111;
  dance12_frm[0].positions[14] = 1694;
  dance12_frm[0].positions[15] = 1754;
  dance12_frm[0].positions[16] = 1888;
  dance12_frm[0].positions[17] = 1694;
  dance12_frm[0].positions[18] = 1794;
  dance12_frm[0].positions[19] = 1907;
  dance12_frm[0].positions[20] = 1500;
  dance12_frm[0].positions[21] = 1754;
  dance12_frm[0].positions[22] = 1888;
  dance12_frm[0].positions[23] = 1305;

  dance12_frm[1].positions[0] = 1223;
  dance12_frm[1].positions[1] = 2146;
  dance12_frm[1].positions[2] = 1223;
  dance12_frm[1].positions[3] = 1223;
  dance12_frm[1].positions[4] = 1499;
  dance12_frm[1].positions[5] = 2146;
  dance12_frm[1].positions[6] = 1336;
  dance12_frm[1].positions[7] = 1157;
  dance12_frm[1].positions[8] = 1476;
  dance12_frm[1].positions[9] = 1216;
  dance12_frm[1].positions[10] = 1097;
  dance12_frm[1].positions[11] = 1662;
  dance12_frm[1].positions[12] = 1200;
  dance12_frm[1].positions[13] = 1090;
  dance12_frm[1].positions[14] = 1893;
  dance12_frm[1].positions[15] = 1799;
  dance12_frm[1].positions[16] = 1909;
  dance12_frm[1].positions[17] = 1893;
  dance12_frm[1].positions[18] = 1783;
  dance12_frm[1].positions[19] = 1902;
  dance12_frm[1].positions[20] = 1662;
  dance12_frm[1].positions[21] = 1663;
  dance12_frm[1].positions[22] = 1842;
  dance12_frm[1].positions[23] = 1476;

  dance12_frm[2].positions[0] = 1223;
  dance12_frm[2].positions[1] = 2146;
  dance12_frm[2].positions[2] = 1223;
  dance12_frm[2].positions[3] = 853;
  dance12_frm[2].positions[4] = 1499;
  dance12_frm[2].positions[5] = 2146;
  dance12_frm[2].positions[6] = 1200;
  dance12_frm[2].positions[7] = 1090;
  dance12_frm[2].positions[8] = 1106;
  dance12_frm[2].positions[9] = 1216;
  dance12_frm[2].positions[10] = 1097;
  dance12_frm[2].positions[11] = 1337;
  dance12_frm[2].positions[12] = 1336;
  dance12_frm[2].positions[13] = 1157;
  dance12_frm[2].positions[14] = 1523;
  dance12_frm[2].positions[15] = 1663;
  dance12_frm[2].positions[16] = 1842;
  dance12_frm[2].positions[17] = 1523;
  dance12_frm[2].positions[18] = 1783;
  dance12_frm[2].positions[19] = 1902;
  dance12_frm[2].positions[20] = 1337;
  dance12_frm[2].positions[21] = 1799;
  dance12_frm[2].positions[22] = 1909;
  dance12_frm[2].positions[23] = 1106;

  dance12_frm[3].positions[0] = 1223;
  dance12_frm[3].positions[1] = 2146;
  dance12_frm[3].positions[2] = 1223;
  dance12_frm[3].positions[3] = 1499;
  dance12_frm[3].positions[4] = 1500;
  dance12_frm[3].positions[5] = 2146;
  dance12_frm[3].positions[6] = 1160;
  dance12_frm[3].positions[7] = 1036;
  dance12_frm[3].positions[8] = 1288;
  dance12_frm[3].positions[9] = 1116;
  dance12_frm[3].positions[10] = 1015;
  dance12_frm[3].positions[11] = 1499;
  dance12_frm[3].positions[12] = 1160;
  dance12_frm[3].positions[13] = 1036;
  dance12_frm[3].positions[14] = 1711;
  dance12_frm[3].positions[15] = 1196;
  dance12_frm[3].positions[16] = 1304;
  dance12_frm[3].positions[17] = 1688;
  dance12_frm[3].positions[18] = 1237;
  dance12_frm[3].positions[19] = 1318;
  dance12_frm[3].positions[20] = 1499;
  dance12_frm[3].positions[21] = 1196;
  dance12_frm[3].positions[22] = 1304;
  dance12_frm[3].positions[23] = 1311;

  dance13_frm[0].positions[0] = 1592;
  dance13_frm[0].positions[1] = 1500;
  dance13_frm[0].positions[2] = 1223;
  dance13_frm[0].positions[3] = 1500;
  dance13_frm[0].positions[4] = 1407;
  dance13_frm[0].positions[5] = 2146;
  dance13_frm[0].positions[6] = 1285;
  dance13_frm[0].positions[7] = 1130;
  dance13_frm[0].positions[8] = 1395;
  dance13_frm[0].positions[9] = 1011;
  dance13_frm[0].positions[10] = 798;
  dance13_frm[0].positions[11] = 1581;
  dance13_frm[0].positions[12] = 1217;
  dance13_frm[0].positions[13] = 1097;
  dance13_frm[0].positions[14] = 1791;
  dance13_frm[0].positions[15] = 1975;
  dance13_frm[0].positions[16] = 2191;
  dance13_frm[0].positions[17] = 1791;
  dance13_frm[0].positions[18] = 1791;
  dance13_frm[0].positions[19] = 1906;
  dance13_frm[0].positions[20] = 1581;
  dance13_frm[0].positions[21] = 1886;
  dance13_frm[0].positions[22] = 2122;
  dance13_frm[0].positions[23] = 1395;

  dance13_frm[1].positions[0] = 1776;
  dance13_frm[1].positions[1] = 1499;
  dance13_frm[1].positions[2] = 1407;
  dance13_frm[1].positions[3] = 1499;
  dance13_frm[1].positions[4] = 1592;
  dance13_frm[1].positions[5] = 2146;
  dance13_frm[1].positions[6] = 1024;
  dance13_frm[1].positions[7] = 808;
  dance13_frm[1].positions[8] = 1208;
  dance13_frm[1].positions[9] = 1208;
  dance13_frm[1].positions[10] = 1093;
  dance13_frm[1].positions[11] = 1418;
  dance13_frm[1].positions[12] = 1113;
  dance13_frm[1].positions[13] = 877;
  dance13_frm[1].positions[14] = 1604;
  dance13_frm[1].positions[15] = 1714;
  dance13_frm[1].positions[16] = 1869;
  dance13_frm[1].positions[17] = 1604;
  dance13_frm[1].positions[18] = 1988;
  dance13_frm[1].positions[19] = 2201;
  dance13_frm[1].positions[20] = 1418;
  dance13_frm[1].positions[21] = 1782;
  dance13_frm[1].positions[22] = 1902;
  dance13_frm[1].positions[23] = 1208;

  dance13_frm[2].positions[0] = 1592;
  dance13_frm[2].positions[1] = 1500;
  dance13_frm[2].positions[2] = 1223;
  dance13_frm[2].positions[3] = 1500;
  dance13_frm[2].positions[4] = 1407;
  dance13_frm[2].positions[5] = 2146;
  dance13_frm[2].positions[6] = 1285;
  dance13_frm[2].positions[7] = 1130;
  dance13_frm[2].positions[8] = 1395;
  dance13_frm[2].positions[9] = 1011;
  dance13_frm[2].positions[10] = 798;
  dance13_frm[2].positions[11] = 1581;
  dance13_frm[2].positions[12] = 1217;
  dance13_frm[2].positions[13] = 1097;
  dance13_frm[2].positions[14] = 1791;
  dance13_frm[2].positions[15] = 1975;
  dance13_frm[2].positions[16] = 2191;
  dance13_frm[2].positions[17] = 1791;
  dance13_frm[2].positions[18] = 1791;
  dance13_frm[2].positions[19] = 1906;
  dance13_frm[2].positions[20] = 1581;
  dance13_frm[2].positions[21] = 1886;
  dance13_frm[2].positions[22] = 2122;
  dance13_frm[2].positions[23] = 1395;

  dance13_frm[3].positions[0] = 1776;
  dance13_frm[3].positions[1] = 1499;
  dance13_frm[3].positions[2] = 1407;
  dance13_frm[3].positions[3] = 1499;
  dance13_frm[3].positions[4] = 1592;
  dance13_frm[3].positions[5] = 2146;
  dance13_frm[3].positions[6] = 1024;
  dance13_frm[3].positions[7] = 808;
  dance13_frm[3].positions[8] = 1208;
  dance13_frm[3].positions[9] = 1208;
  dance13_frm[3].positions[10] = 1093;
  dance13_frm[3].positions[11] = 1418;
  dance13_frm[3].positions[12] = 1113;
  dance13_frm[3].positions[13] = 877;
  dance13_frm[3].positions[14] = 1604;
  dance13_frm[3].positions[15] = 1714;
  dance13_frm[3].positions[16] = 1869;
  dance13_frm[3].positions[17] = 1604;
  dance13_frm[3].positions[18] = 1988;
  dance13_frm[3].positions[19] = 2201;
  dance13_frm[3].positions[20] = 1418;
  dance13_frm[3].positions[21] = 1782;
  dance13_frm[3].positions[22] = 1902;
  dance13_frm[3].positions[23] = 1208;

  dance13_frm[4].positions[0] = 1592;
  dance13_frm[4].positions[1] = 1500;
  dance13_frm[4].positions[2] = 1223;
  dance13_frm[4].positions[3] = 1500;
  dance13_frm[4].positions[4] = 1407;
  dance13_frm[4].positions[5] = 2146;
  dance13_frm[4].positions[6] = 1285;
  dance13_frm[4].positions[7] = 1130;
  dance13_frm[4].positions[8] = 1395;
  dance13_frm[4].positions[9] = 1011;
  dance13_frm[4].positions[10] = 798;
  dance13_frm[4].positions[11] = 1581;
  dance13_frm[4].positions[12] = 1217;
  dance13_frm[4].positions[13] = 1097;
  dance13_frm[4].positions[14] = 1791;
  dance13_frm[4].positions[15] = 1975;
  dance13_frm[4].positions[16] = 2191;
  dance13_frm[4].positions[17] = 1791;
  dance13_frm[4].positions[18] = 1791;
  dance13_frm[4].positions[19] = 1906;
  dance13_frm[4].positions[20] = 1581;
  dance13_frm[4].positions[21] = 1886;
  dance13_frm[4].positions[22] = 2122;
  dance13_frm[4].positions[23] = 1395;

  dance13_frm[5].positions[0] = 1776;
  dance13_frm[5].positions[1] = 1499;
  dance13_frm[5].positions[2] = 1407;
  dance13_frm[5].positions[3] = 1499;
  dance13_frm[5].positions[4] = 1592;
  dance13_frm[5].positions[5] = 2146;
  dance13_frm[5].positions[6] = 1024;
  dance13_frm[5].positions[7] = 808;
  dance13_frm[5].positions[8] = 1208;
  dance13_frm[5].positions[9] = 1208;
  dance13_frm[5].positions[10] = 1093;
  dance13_frm[5].positions[11] = 1418;
  dance13_frm[5].positions[12] = 1113;
  dance13_frm[5].positions[13] = 877;
  dance13_frm[5].positions[14] = 1604;
  dance13_frm[5].positions[15] = 1714;
  dance13_frm[5].positions[16] = 1869;
  dance13_frm[5].positions[17] = 1604;
  dance13_frm[5].positions[18] = 1988;
  dance13_frm[5].positions[19] = 2201;
  dance13_frm[5].positions[20] = 1418;
  dance13_frm[5].positions[21] = 1782;
  dance13_frm[5].positions[22] = 1902;
  dance13_frm[5].positions[23] = 1208;

  dance13_frm[6].positions[0] = 1592;
  dance13_frm[6].positions[1] = 1500;
  dance13_frm[6].positions[2] = 1223;
  dance13_frm[6].positions[3] = 1500;
  dance13_frm[6].positions[4] = 1407;
  dance13_frm[6].positions[5] = 2146;
  dance13_frm[6].positions[6] = 1285;
  dance13_frm[6].positions[7] = 1130;
  dance13_frm[6].positions[8] = 1395;
  dance13_frm[6].positions[9] = 1011;
  dance13_frm[6].positions[10] = 798;
  dance13_frm[6].positions[11] = 1581;
  dance13_frm[6].positions[12] = 1217;
  dance13_frm[6].positions[13] = 1097;
  dance13_frm[6].positions[14] = 1791;
  dance13_frm[6].positions[15] = 1975;
  dance13_frm[6].positions[16] = 2191;
  dance13_frm[6].positions[17] = 1791;
  dance13_frm[6].positions[18] = 1791;
  dance13_frm[6].positions[19] = 1906;
  dance13_frm[6].positions[20] = 1581;
  dance13_frm[6].positions[21] = 1886;
  dance13_frm[6].positions[22] = 2122;
  dance13_frm[6].positions[23] = 1395;

  dance13_frm[7].positions[0] = 1776;
  dance13_frm[7].positions[1] = 1499;
  dance13_frm[7].positions[2] = 1407;
  dance13_frm[7].positions[3] = 1499;
  dance13_frm[7].positions[4] = 1592;
  dance13_frm[7].positions[5] = 2146;
  dance13_frm[7].positions[6] = 1024;
  dance13_frm[7].positions[7] = 808;
  dance13_frm[7].positions[8] = 1208;
  dance13_frm[7].positions[9] = 1208;
  dance13_frm[7].positions[10] = 1093;
  dance13_frm[7].positions[11] = 1418;
  dance13_frm[7].positions[12] = 1113;
  dance13_frm[7].positions[13] = 877;
  dance13_frm[7].positions[14] = 1604;
  dance13_frm[7].positions[15] = 1714;
  dance13_frm[7].positions[16] = 1869;
  dance13_frm[7].positions[17] = 1604;
  dance13_frm[7].positions[18] = 1988;
  dance13_frm[7].positions[19] = 2201;
  dance13_frm[7].positions[20] = 1418;
  dance13_frm[7].positions[21] = 1782;
  dance13_frm[7].positions[22] = 1902;
  dance13_frm[7].positions[23] = 1208;

  dance14_frm[0].positions[0] = 1223;
  dance14_frm[0].positions[1] = 2146;
  dance14_frm[0].positions[2] = 1776;
  dance14_frm[0].positions[3] = 853;
  dance14_frm[0].positions[4] = 1223;
  dance14_frm[0].positions[5] = 2146;
  dance14_frm[0].positions[6] = 1404;
  dance14_frm[0].positions[7] = 1243;
  dance14_frm[0].positions[8] = 1521;
  dance14_frm[0].positions[9] = 1211;
  dance14_frm[0].positions[10] = 1072;
  dance14_frm[0].positions[11] = 1709;
  dance14_frm[0].positions[12] = 1115;
  dance14_frm[0].positions[13] = 932;
  dance14_frm[0].positions[14] = 1928;
  dance14_frm[0].positions[15] = 1711;
  dance14_frm[0].positions[16] = 1763;
  dance14_frm[0].positions[17] = 1848;
  dance14_frm[0].positions[18] = 1778;
  dance14_frm[0].positions[19] = 1883;
  dance14_frm[0].positions[20] = 1610;
  dance14_frm[0].positions[21] = 1728;
  dance14_frm[0].positions[22] = 1936;
  dance14_frm[0].positions[23] = 1434;

  dance14_frm[1].positions[0] = 1687;
  dance14_frm[1].positions[1] = 2068;
  dance14_frm[1].positions[2] = 1312;
  dance14_frm[1].positions[3] = 931;
  dance14_frm[1].positions[4] = 1455;
  dance14_frm[1].positions[5] = 2008;
  dance14_frm[1].positions[6] = 1269;
  dance14_frm[1].positions[7] = 1135;
  dance14_frm[1].positions[8] = 1343;
  dance14_frm[1].positions[9] = 1205;
  dance14_frm[1].positions[10] = 1091;
  dance14_frm[1].positions[11] = 1535;
  dance14_frm[1].positions[12] = 1222;
  dance14_frm[1].positions[13] = 1085;
  dance14_frm[1].positions[14] = 1732;
  dance14_frm[1].positions[15] = 1751;
  dance14_frm[1].positions[16] = 1873;
  dance14_frm[1].positions[17] = 1717;
  dance14_frm[1].positions[18] = 1794;
  dance14_frm[1].positions[19] = 1906;
  dance14_frm[1].positions[20] = 1517;
  dance14_frm[1].positions[21] = 1754;
  dance14_frm[1].positions[22] = 1902;
  dance14_frm[1].positions[23] = 1328;

  dance14_frm[2].positions[0] = 1776;
  dance14_frm[2].positions[1] = 1714;
  dance14_frm[2].positions[2] = 1223;
  dance14_frm[2].positions[3] = 1285;
  dance14_frm[2].positions[4] = 1500;
  dance14_frm[2].positions[5] = 2053;
  dance14_frm[2].positions[6] = 1164;
  dance14_frm[2].positions[7] = 952;
  dance14_frm[2].positions[8] = 1229;
  dance14_frm[2].positions[9] = 1261;
  dance14_frm[2].positions[10] = 1157;
  dance14_frm[2].positions[11] = 1397;
  dance14_frm[2].positions[12] = 1450;
  dance14_frm[2].positions[13] = 1384;
  dance14_frm[2].positions[14] = 1589;
  dance14_frm[2].positions[15] = 1835;
  dance14_frm[2].positions[16] = 2047;
  dance14_frm[2].positions[17] = 1770;
  dance14_frm[2].positions[18] = 1738;
  dance14_frm[2].positions[19] = 1842;
  dance14_frm[2].positions[20] = 1602;
  dance14_frm[2].positions[21] = 1549;
  dance14_frm[2].positions[22] = 1615;
  dance14_frm[2].positions[23] = 1410;

  dance14_frm[3].positions[0] = 1268;
  dance14_frm[3].positions[1] = 1684;
  dance14_frm[3].positions[2] = 1731;
  dance14_frm[3].positions[3] = 1315;
  dance14_frm[3].positions[4] = 1499;
  dance14_frm[3].positions[5] = 2053;
  dance14_frm[3].positions[6] = 1151;
  dance14_frm[3].positions[7] = 923;
  dance14_frm[3].positions[8] = 1217;
  dance14_frm[3].positions[9] = 1270;
  dance14_frm[3].positions[10] = 1165;
  dance14_frm[3].positions[11] = 1379;
  dance14_frm[3].positions[12] = 1489;
  dance14_frm[3].positions[13] = 1428;
  dance14_frm[3].positions[14] = 1567;
  dance14_frm[3].positions[15] = 1848;
  dance14_frm[3].positions[16] = 2076;
  dance14_frm[3].positions[17] = 1782;
  dance14_frm[3].positions[18] = 1729;
  dance14_frm[3].positions[19] = 1834;
  dance14_frm[3].positions[20] = 1620;
  dance14_frm[3].positions[21] = 1510;
  dance14_frm[3].positions[22] = 1571;
  dance14_frm[3].positions[23] = 1432;

  dance14_frm[4].positions[0] = 1776;
  dance14_frm[4].positions[1] = 2053;
  dance14_frm[4].positions[2] = 1223;
  dance14_frm[4].positions[3] = 946;
  dance14_frm[4].positions[4] = 1499;
  dance14_frm[4].positions[5] = 2053;
  dance14_frm[4].positions[6] = 1245;
  dance14_frm[4].positions[7] = 1111;
  dance14_frm[4].positions[8] = 1305;
  dance14_frm[4].positions[9] = 1205;
  dance14_frm[4].positions[10] = 1092;
  dance14_frm[4].positions[11] = 1499;
  dance14_frm[4].positions[12] = 1245;
  dance14_frm[4].positions[13] = 1111;
  dance14_frm[4].positions[14] = 1694;
  dance14_frm[4].positions[15] = 1754;
  dance14_frm[4].positions[16] = 1888;
  dance14_frm[4].positions[17] = 1694;
  dance14_frm[4].positions[18] = 1794;
  dance14_frm[4].positions[19] = 1907;
  dance14_frm[4].positions[20] = 1500;
  dance14_frm[4].positions[21] = 1754;
  dance14_frm[4].positions[22] = 1888;
  dance14_frm[4].positions[23] = 1305;

  home_frm[0].positions[0] = 1776;
  home_frm[0].positions[1] = 2146;
  home_frm[0].positions[2] = 1223;
  home_frm[0].positions[3] = 853;
  home_frm[0].positions[4] = 1499;
  home_frm[0].positions[5] = 2146;
  home_frm[0].positions[6] = 1487;
  home_frm[0].positions[7] = 1363;
  home_frm[0].positions[8] = 1405;
  home_frm[0].positions[9] = 1477;
  home_frm[0].positions[10] = 1359;
  home_frm[0].positions[11] = 1500;
  home_frm[0].positions[12] = 1487;
  home_frm[0].positions[13] = 1363;
  home_frm[0].positions[14] = 1594;
  home_frm[0].positions[15] = 1512;
  home_frm[0].positions[16] = 1636;
  home_frm[0].positions[17] = 1594;
  home_frm[0].positions[18] = 1522;
  home_frm[0].positions[19] = 1640;
  home_frm[0].positions[20] = 1499;
  home_frm[0].positions[21] = 1512;
  home_frm[0].positions[22] = 1636;
  home_frm[0].positions[23] = 1405;

  _86ME_HOME.positions[0] = 1776;
  _86ME_HOME.positions[1] = 2146;
  _86ME_HOME.positions[2] = 1223;
  _86ME_HOME.positions[3] = 853;
  _86ME_HOME.positions[4] = 1499;
  _86ME_HOME.positions[5] = 2146;
  _86ME_HOME.positions[6] = 1487;
  _86ME_HOME.positions[7] = 1363;
  _86ME_HOME.positions[8] = 1405;
  _86ME_HOME.positions[9] = 1477;
  _86ME_HOME.positions[10] = 1359;
  _86ME_HOME.positions[11] = 1500;
  _86ME_HOME.positions[12] = 1487;
  _86ME_HOME.positions[13] = 1363;
  _86ME_HOME.positions[14] = 1594;
  _86ME_HOME.positions[15] = 1512;
  _86ME_HOME.positions[16] = 1636;
  _86ME_HOME.positions[17] = 1594;
  _86ME_HOME.positions[18] = 1522;
  _86ME_HOME.positions[19] = 1640;
  _86ME_HOME.positions[20] = 1499;
  _86ME_HOME.positions[21] = 1512;
  _86ME_HOME.positions[22] = 1636;
  _86ME_HOME.positions[23] = 1405;

  myoffs.setOffsets();

  _86ME_HOME.playPositions(0);
}

void loop()
{
  updateTrigger();
  ENDUpdate();
  atkLUpdate();
  atkRUpdate();
  atkCUpdate();
  laughUpdate();
  danceALLUpdate();
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
  homeUpdate();
  nh.spinOnce();
  
	if (myFile.available()) {
		myFile.read(buffer, sizeof(buffer));
		Audio.prepare(buffer, 1024, 1024);
		Audio.write(buffer, 1024);
	}else{
		_curr_motion = _HOME;
		for(int i = 0; i < 1024; i++)
			buffer[i] - 0;
		Audio.prepare(buffer, 1024, 0);
		Audio.write(buffer, 1024);
		myFile.close();
	}
}
