#define Ai 8
#define Bi 9
#define Ci 10
#define Di 11
#define Digit1 2
#define Digit2 3
#define Digit3 4
#define Sensor A5
#define Trigger1 13
#define Trigger2 12
#define TemperaturePreset 0

float temp1 = 0;
float temp2 = 0;
float temp3 = 0;
float temp4 = 0;
float temp5 = 0;
float temperature = 0.0;

bool swt = true;
long int lastTime = 0;
long int currentTime = 0;
long int displayTimer = 0;
int digitSwitch = 1;

int digitArray[10][4] = {
  {LOW, LOW, LOW, LOW},   //0
  {LOW, LOW, LOW, HIGH},  //1
  {LOW, LOW, HIGH, LOW},   //2
  {LOW, LOW, HIGH, HIGH},   //3
  {LOW, HIGH, LOW, LOW},   //4
  {LOW, HIGH, LOW, HIGH},   //5
  {LOW, HIGH, HIGH, LOW},   //6
  {LOW, HIGH, HIGH, HIGH},   //7
  {HIGH, LOW, LOW, LOW},   //8
  {HIGH, LOW, LOW, HIGH},   //9
};

void setup() {
 pinMode(Sensor,INPUT);
 pinMode(Ai,OUTPUT);
 pinMode(Bi,OUTPUT);
 pinMode(Ci,OUTPUT);
 pinMode(Di,OUTPUT);
 pinMode(Digit1,OUTPUT);
 pinMode(Digit2,OUTPUT);
 pinMode(Digit3,OUTPUT);
 pinMode(Trigger1,OUTPUT);
 pinMode(Trigger2,OUTPUT);
// Serial.begin(9600);
 lastTime = millis();
 displayTimer = lastTime;
}

void loop() {
  currentTime = millis();
  int difference = currentTime - lastTime;
  if(difference >= 500 && swt) {
    digitalWrite(Trigger1, HIGH);
    digitalWrite(Trigger2, LOW);
    swt = false;
//    Serial.print("Different : " );
//    Serial.println(difference);
  }
  if(difference >= 1000) {
    digitalWrite(Trigger1, LOW);
    digitalWrite(Trigger2, HIGH);
    swt = true;
    temperature=analogRead(Sensor);   
    temperature=(temperature*500)/1023; // Storing value in Degree Celsius
    // tempf=(temperature*1.8)+32; // Converting to Fahrenheit
    temperature = temperature - TemperaturePreset;
    temp1 = temp2;
    temp2 = temp3;
    temp3 = temp4;
    temp4 = temp5;
    temp5 = temperature;
    temperature = (temp1 + temp2 + temp3 + temp4 + temp5) / 5;
    lastTime = currentTime;
  }
  separateDigits(temperature, currentTime);
}

void serialPrintTemperature(double currentValue, double displayValue) {
  Serial.print("Instant value DegreeC=");
  Serial.print("\t");
  Serial.print(currentValue);
  Serial.print(" | ");
  Serial.print("Display value Fahrenheit=");
  Serial.print("\t");
  Serial.print(displayValue);
  Serial.println();
}

void separateDigits(float number, int currentTime) {
  int integerPart = (int)number;
  int firstDigit = (integerPart / 10) % 10;
  int secondDigit = integerPart % 10;
  int decimalDigit = (number * 10) - (integerPart * 10);
  int differenceDisplayTimer = currentTime - displayTimer;
  
  if(differenceDisplayTimer >= 10 && digitSwitch == 1) {
  displayDigit(firstDigit,1,0,0);
  displayTimer = currentTime;
  digitSwitch = 2;
  }
  else if(differenceDisplayTimer >= 10 && digitSwitch == 2) {
  displayDigit(secondDigit,0,1,0);
  displayTimer = currentTime;
  digitSwitch = 3;
  }
  else if(differenceDisplayTimer >= 10 && digitSwitch == 3) {
  displayDigit(decimalDigit,0,0,1);
  displayTimer = currentTime;
  digitSwitch = 1;
  }
}

void displayDigit(int number, int digit1, int digit2, int digit3) {
  digitalWrite(Digit1, digit1);
  digitalWrite(Digit2, digit2);
  digitalWrite(Digit3, digit3);
  setDigit(number);
}

void setDigit(int number) {
  digitalWrite(Di, digitArray[number][0]);
  digitalWrite(Ci, digitArray[number][1]);
  digitalWrite(Bi, digitArray[number][2]);
  digitalWrite(Ai, digitArray[number][3]);
}
