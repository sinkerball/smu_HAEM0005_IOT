#include <Servo.h>
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

Servo servo;
SoftwareSerial bluetooth(10, 11); // RX, TX 핀 설정
const int trigPin = 7;
const int echoPin = 6;
const int thresholdDistance = 10; // 10cm 가 기준점
const int openedAngle = 90;
const int closedAngle = 0;
const int openDelay = 1000; // 1초
const int closeDelay = 1000; // 1초

SoftwareSerial MP3Module(2, 3);
DFRobotDFPlayerMini MP3Player;

void setup() {
  servo.attach(9); 
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  bluetooth.begin(9600); // 블루투스 시리얼 통신 속도 설정

  MP3Module.begin(9600);
  if (!MP3Player.begin(MP3Module)) {
    Serial.println(F("Unable to begin MP3 player!"));
    while (true);
  }

  delay(1);
  MP3Player.volume(15); // 볼륨을 조절합니다. 0~30까지 설정이 가능합니다.
}

void loop() {
  long duration, distance;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // 거리가 10cm 이내일 경우 문 열기
  if (distance <= thresholdDistance) {
    openDoor();
  }
  // 거리가 10cm 초과일 경우 문 닫기
  else {
    closeDoor();
  }

  // 블루투스로 각도 값 전송
  bluetooth.print(servo.read());
  bluetooth.print('\n'); // 각도 값 뒤에 줄 바꿈 문자 추가
}

// 문 열기
void openDoor() {
  if (servo.read() != openedAngle) {
    servo.write(openedAngle);
    Serial.println("Opening the door");
    delay(openDelay);

    // "0001.mp3" 파일 재생
    MP3Player.playMp3Folder(1); //오픈딜레이 만큼 플레이 된다.
  }
}

// 문 닫기
void closeDoor() {
  if (servo.read() != closedAngle) {
    servo.write(closedAngle);
    Serial.println("Closing the door");
    delay(closeDelay);
  }
}
