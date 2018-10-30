/* Original Code Written by Roy Pe'er. Saya gunakan code ini sebagai contoh karena struktur pengkodeannya cukup mudah dimengerti bagi pemula
 *  , bagi anda para master mohon keritik dan masukannya
 *  
 *  Terimakasih untuk Takana Media -- http://www.takanamedia.com/ untuk support-nya di tutorial kali ini
*/





#include <AFMotor.h> //import  library motor shield l293d buatan Adafruit
#define trigPin 12 // menetapkan pin 12 trig pin - ultrasonic sensor HC-SR04 - sesuai pengkabelan yang sudah saya jelaskan sebelumnya
#define echoPin 13 // menetapkan pin 13 echo pin - ultrasonic sensor HC-SR04 - sesuai pengkabelan yang sudah saya jelaskan sebelumnya
AF_DCMotor motor1(1,MOTOR12_64KHZ); // men-setup port motor shield l293d motor 1
AF_DCMotor motor2(2, MOTOR12_8KHZ); // men-setup port motor shield l293d motor 2
 
void setup() {
  Serial.begin(9600); // memanggil/menggunakan serial komunikasi dengan laptop/PC dengan serial nomor 9600 
  Serial.println("Motor test!"); // menampikan pesan "Motor test" pada serial monitor
   pinMode(trigPin, OUTPUT);// Men-setup trig pin sebagai output (yang menembakan glombang suara ultrasonic)
  pinMode(echoPin, INPUT);// Men-setup echo pin sebagai input (yang menerima glombang suara ultrasonic setelah pantulan terjadi)
  motor1.setSpeed(105); //Men-setup kecepatan motor, keceptannya antara 0-255
motor2.setSpeed (105);  
}
 
void loop() {

   long duration, distance; // memulai untuk men-scan area menggunakan sensor ultrasonic
  digitalWrite(trigPin, LOW);  
  delayMicroseconds(2); // jeda dibutuhkan agar kinerja sensor ultrasonic lebih baik
  digitalWrite(trigPin, HIGH);

  delayMicroseconds(10); //jeda
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;// mengkonversikan jarak yang diterima (akibat pantulan gelombang yang diterima dalam satuan waktu tertentu) dalam hitungan centimeter
  if (distance < 25)/*jika benda terditeksi dalam jarak kurang dari 25 cm, maka lakuan perintah ini: */ {   
   Serial.println ("Close Obstacle detected!" );
Serial.println ("Obstacle Details:");
Serial.print ("Distance From Robot is " );
Serial.print ( distance);
Serial.print ( " CM!");// print jarak terditeksi pada serial monitor

Serial.println (" The obstacle is declared a threat due to close distance. ");
Serial.println (" Turning !");
    motor1.run(FORWARD);  // melakuan gerakan memutar selama didepan terdapat benda yang menghalangi
    motor2.run (BACKWARD);

}
  else {
   Serial.println ("No obstacle detected. going forward");
   delay (15);
   motor1.run(FORWARD); //jika tidak ada benda di depan, maka lakukan gerakan maju ke depan
    motor2.run(FORWARD);  
  }  
  
  

  
  
  
 
}
