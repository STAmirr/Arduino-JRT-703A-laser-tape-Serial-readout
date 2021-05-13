byte buffer_a[8];// 
int dis_a;/// distance in mm as int
const char speed_mode = 'D' ;///// D:AUTO  M:SLOW  F:FAST  /////////////
const int dis_offset = 0;

void setup() {
  Serial2.begin(19200); ////// im using and arduino DUE so i used separate serial ports
  Serial.begin(115200); ////// to display on pc

  Serial2.write("O");/// turning the sensor on

  digitalWrite(32, HIGH);/// setting the sensor to single reading mode(connected pin32 to nCTRL
}

void loop() {

  measure_a();
  Serial.println(dis_a);

}

void measure_a() {
  Serial2.write(speed_mode);
  Serial2.readBytes(buffer_a, 8);
  if (buffer_a[4] == 46) {
    if (buffer_a[2] == 32) {
      dis_a = ((buffer_a[3] - '0') * 1000) + ((buffer_a[5] - '0') * 100) + ((buffer_a[6] - '0') * 10) + (buffer_a[7] - '0') ;
      Serial2.flush();
    } else {
      Serial2.flush();
      measure_a();
      //      dis_a = ((buffer_a[2] - '0') * 10000) + ((buffer_a[3] - '0') * 1000) + ((buffer_a[5] - '0') * 100) + ((buffer_a[6] - '0') * 10) + (buffer_a[7] - '0') ;
      //      Serial2.flush();
    }
  } else {
    Serial2.flush();
    measure_a();
  }
}
