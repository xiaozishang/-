/*#include <Adafruit_NeoPixel.h> //引用此文件

#define PIN_NUM 2 //允许接的led灯的个数
   
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIN_NUM, PIN, NEO_GRB + NEO_KHZ800);  //该函数第一个参数控制串联灯的个数，第二个是控制用哪个pin脚输出，第三个显示颜色和变化闪烁频率
//mcookie的LED
*/

#define val_max 255
#define val_min 0
#include <ESP8266.h>
#ifdef ESP32
#error "This code is not recommended to run on the ESP32 platform! Please check your Tools->Board setting."
#endif
#if defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega1284P__) || defined (__AVR_ATmega644P__) || defined(__AVR_ATmega128RFA1__)
#define EspSerial Serial1
#define UARTSPEED  115200
#endif
#if defined (__AVR_ATmega168__) || defined (__AVR_ATmega328__) || defined (__AVR_ATmega328P__)
#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); 
#define EspSerial mySerial
#define UARTSPEED  9600
#endif
#define SSID        F("wifi")//WIFI名
#define PASSWORD    F("wifiwifi")//WIFI密码
#define HOST_NAME   F("api.heclouds.com")//域名
#define HOST_PORT   (80)
static const byte  GETDATA[]  PROGMEM = {
  "GET https://api.heclouds.com/devices/503092674/datapoints?datastream_id=datao,datat,datath&limit=1 HTTP/1.1\r\nHost:api.heclouds.com\r\napi-key:WgySE7y=0=BzIjL6WxErlSsi4dQ=\r\nConnection: close\r\n\r\n"
};//关键头文件
/* "GET https://api.heclouds.com/devices/23334240/datapoints?datastream_id=id,status,precent&limit=1 //url+  【 datapoints？datastream id=】 你的几个数据名称【&limit=】（几个数据1个表示最近）
 *  HTTP/1.1\r\n
 *  Host:api.heclouds.com//域名
 *  \r\n
 *  api-key:sCCE3BRbnvyyKsX1iWY7=dSFlME=///API
 *  \r\nConnection: close\r\n\r\n"
*/
ESP8266 wifi(&EspSerial);
//wifi
#include <Servo.h>
Servo myservo;  // 定义舵机对象，最多八个
int pose=5, angle = 20;    // 定义舵机转动位置
int t1;   //设置现在到早上响铃倒计时的时间(第二个传)
int t2=30;     //设置早上到晚上响铃倒计时的时间减去t1
int d=10;   //设置每次响铃的时间
int h;    //控制白天灯开关的数据（第一个传）
int j;    //控制窗帘的开关（第三个传）
int a1=t1, a2=t2, m=d, h1=h, j1=j;
bool Rstatus=0,ws=0,tcp=0;
void setup()
{
   myservo.attach(9);  // 设置舵机控制针脚
   Serial.begin(115200);   //串口初始化
   analogReference(INTERNAL);  //调用板载1.1V基准源
    Serial.begin(115200);
  while (!Serial); // wait for Leonardo enumeration, others continue immediately
  Serial.print(F("setup begin\r\n"));
  delay(100);

  WifiInit(EspSerial, UARTSPEED);

  Serial.print(F("FW Version:"));
  Serial.println(wifi.getVersion().c_str());

  if (wifi.setOprToStationSoftAP()) {
    Serial.print(F("to station + softap ok\r\n"));
  } else {
    Serial.print(F("to station + softap err\r\n"));
  }

  if (wifi.joinAP(SSID, PASSWORD)) {
    Serial.print(F("Join AP success\r\n"));

    Serial.print(F("IP:"));
    Serial.println( wifi.getLocalIP().c_str());
  } else {
    Serial.print(F("Join AP failure\r\n"));
  }

  if (wifi.disableMUX()) {
    Serial.print(F("single ok\r\n"));
  } else {
    Serial.print(F("single err\r\n"));
  }

  Serial.print(F("setup end\r\n"));
}

void loop()
{
  if (wifi.createTCP(HOST_NAME, HOST_PORT)) {
    Serial.print(F("create tcp ok\r\n"));
  } else {
    Serial.print(F("create tcp err\r\n"));
  }

  //char *hello = "GET /testwifi/index.html HTTP/1.0\r\nHost: www.adafruit.com\r\nConnection: close\r\n\r\n";
  //wifi.send((const uint8_t*)hello, strlen(hello));  //直接发送

  wifi.sendFromFlash(GETDATA, sizeof(GETDATA)); //从Flash读取发送内容，节约内存

  uint8_t buffer[512] = {0};
  uint32_t len = wifi.recv(buffer, sizeof(buffer), 20000);
  if (len > 0)
  {
     short k=0,temp=0;
    for (uint32_t i = 0; i < len; i++) {
      if((char)buffer[i]=='v'&&(char)buffer[i+1]=='a'&&(char)buffer[i+2]=='l'&&(char)buffer[i+3]=='u'&&(char)buffer[i+4]=='e')
      {
          for (uint32_t j = 0;(char)buffer[i+j+8]>='0'&&(char)buffer[i+j+7]<='9' ;j++)
              {if((char)buffer[i+j+8]>='0'&&(char)buffer[i+j+8]<='9')
              {char op[1];int num;int mici;
                op[0]=buffer[i+j+8];
                num=atoi(op);
                mici=(int)pow(10,j);
                temp=temp+num*mici;
                
              }}
              Serial.print('\n');
              if(k==0){h=temp,h1=temp;}//（根据顺序自己赋值）
              else if(k==1){t1=temp,a1=temp;}
              else if(k==2){j=temp,j1=temp;}
              k++;  
              Serial.println(temp);
              temp=0;
          }
    } }

  if (wifi.releaseTCP()) {
    Serial.print(F("release tcp ok\r\n"));
  } else {
    Serial.print(F("release tcp err\r\n"));
  }

  //while (1);
  delay(3000);
   int k=1,s1=1,s2=1;
   //早上的闹铃
   do
   {
      Serial.print(t1);    //显示倒计时
      Serial.print("\n");
      t1=t1-1;
      delay(1000);
    }   
   while(t1!=0);
   analogWrite(11,500);   //小灯亮
   analogWrite(6, 10);   //蜂鸣器响
   myservo.write(angle);   //舵机正向转
   for(int i=0;i<10;i++)
   {
      analogWrite(10, 255);    //发动机1转拉窗帘
      delay(100);
   }
   analogWrite(10, 0);    //发动机1停
    Serial.print("time to get up""\n");
   do
   {
      Serial.print(d);    //显示倒计时
      Serial.print("\n");
      d=d-1;
      delay(1000);
   }
   while(d!=0);
   analogWrite(11,0);   //小灯灭
   analogWrite(6,0);   //蜂鸣器停
   //白天的各个数据调用
   do
   {
      Serial.print(t2);    //显示倒计时
      Serial.print("\t");
      t2=t2-1;
      int n=analogRead(A4);   //读取模拟口数据   
      int light=analogRead(A3);  //读取光强
      if(n>300)     //有电压反应就运行以下程序
         {
             if(k%2==1)
             {
                 myservo.write(angle);   //舵机正向转
                 k=k+1;
             }
             else
             {
                 myservo.write(-angle);   //舵机负向转
                 k=k+1;
             }
         }
     if(h==1)
     {
          analogWrite(11,500);   //小灯亮
      }
      if(j==1)
      {
          for(int i=0;i<10;i++)
         {
            analogWrite(10, 255);    //发动机1转拉窗帘
            delay(100);
         } 
      }
     Serial.println(n);    //串口监视
     Serial.print("light:    ");
     Serial.println(light);
     Serial.print('\n');
     d=m;
      delay(500);   //延时，控制刷新速率
     }   
   while(t2!=0);
   //晚上的闹铃
   analogWrite(11,500);   //小灯亮
   analogWrite(6, 10);   //蜂鸣器响
   myservo.write(-angle);   //舵机负向转
   for(int i=0;i<20;i++)
   {
    analogWrite(5, 255);    //发动机2转关窗帘
    delay(100);
   }
   analogWrite(5, 0);    //发动机2停
   Serial.print("time to go to bed""\n");
   do
   {
      Serial.print(d);    //显示倒计时
      Serial.print("\n");
      d=d-1;
      delay(1000);
   }
   while(d!=0);
   analogWrite(11,0);   //小灯灭
   analogWrite(6,0);   //蜂鸣器停
   t1=a1;t2=a2;d=m;h=h1;j=j1;
}
  
