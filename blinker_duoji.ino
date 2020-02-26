#include <Servo.h> 
#define BLINKER_WIFI
 
#include <Blinker.h>
 
char auth[] = "****";     //key
char ssid[] = "****";
char pswd[] = "****";
 
// 新建组件对象
BlinkerButton Button1("btn-max");   //位置1 按钮 数据键名
BlinkerButton Button2("btn-min");   //位置2 按钮 数据键名
BlinkerButton Button3("btn-pw");    //循环模式 按钮 数据键名  开关模式
Servo myservo;
BlinkerSlider Slider1("max-num");   //位置1 滑块 数据键名  范围1-180
BlinkerSlider Slider2("min-num");   //位置2 滑块 数据键名  范围1-180
BlinkerSlider Slider3("ser-num");   //实时位置 滑块 数据键名  范围1-180
BlinkerSlider Slider4("time-num");  //循环模式间隔时间 滑块 数据键名 范围单位毫秒

bool xunhuan_mode = false;

int servo_max,servo_min,ser_num,time_num;
  
void button1_callback(const String & state) {    //位置1按钮
    BLINKER_LOG("get button state: ", servo_max);
    myservo.write(servo_max);
    Blinker.vibrate();
}
  
void button2_callback(const String & state) {   //位置2按钮
    BLINKER_LOG("get button state: ", servo_min); 
    myservo.write(servo_min);
    Blinker.vibrate();
}

void button3_callback(const String & state) {    //位置3按钮  开关模式
   // Blinker.vibrate();
    if(state == "on"){
      xunhuan_mode = true;  
      Button3.print("on");  
      Blinker.delay(100);
    }else if (state == "off"){
      xunhuan_mode = false;
      Button3.print("off");
      Blinker.delay(100);
    }
    
    
}


void slider1_callback(int32_t value)
{
    servo_max = value;
    Slider1.color("#1E90FF");
    Slider1.print();
    
    BLINKER_LOG("get slider value: ", value);
}

void slider2_callback(int32_t value)
{
    servo_min = value;
    Slider2.color("#FFF8DC");
    Slider2.print();
    BLINKER_LOG("get slider value: ", value);
}

void slider3_callback(int32_t value)
{
    ser_num = value;
    myservo.write(ser_num);
    Blinker.delay(100);
    BLINKER_LOG("get slider value: ", value);
}

void slider4_callback(int32_t value)
{
    time_num = value;
    Blinker.delay(100);
    BLINKER_LOG("get slider value: ", value);
}

void xunhuan(){
     myservo.write(servo_max);
     Blinker.delay(time_num/2);
     myservo.write(servo_min);
     Blinker.delay(time_num/2);
}

void setup() {

    Serial.begin(115200);    
    BLINKER_DEBUG.stream(Serial);
    Blinker.begin(auth, ssid, pswd);
    Button1.attach(button1_callback);
    Button2.attach(button2_callback);
    Button3.attach(button3_callback);
    Slider1.attach(slider1_callback);
    Slider2.attach(slider2_callback);
    Slider3.attach(slider3_callback);
    Slider4.attach(slider4_callback);
    myservo.attach(2);
    myservo.write(10);
    servo_max=70;
    servo_min=120;
    time_num=500;

}

void loop() {

  Blinker.run();
  if(xunhuan_mode==true){
    xunhuan();
  }
    
}
