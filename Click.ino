#include <iarduino_NeoPixel.h>                  // открытие библиотеки
#define PORT 7                                  // назначаем порт ленты
#define COUNT 174                               // кол - во светодиов
#define COLOR 0x0000ff // 0xffffff                         // цвет ленты
iarduino_NeoPixel led(PORT, COUNT);             // инициализируем ленту
// unsigned long long watch = 0;                   //создаем переменную счётчик
byte hours = 0;                                      //создаём переменную , хранящую кол-во часов
byte minutes = 0;                                     //создаём переменную, хранящую кол-во минут
byte seconds;                                    //создаём переменную , хранящую кол-во секунд (берём значение из функции-счётчика millis() )
bool seconds_flag = false;                          // flag для однократного увеличения минут при нуле секунд (60 секунд)
bool minutes_flag = false;                          // (нужна из-за ложных доп. срабатываний при нуле минут - т.к. проверка каждую миллисекунду идёт!)
// -//- аналогично для минут и часов

int color;

int btoo;                                           //блютуз  переменная для чтения от



void setup() {

  color=0x00000;

Serial.begin(9600);                               //блютуз   инициация  чтения

  beginning();                                  // проверка подключения светодиодки и работы каждой цифры

  led.setColor(NeoPixelAll, 0x000000);//выключаем все светодиоды - обнуляем это старт
  led.write();
  delay(1000);

  //write_digit(1, 2);
  //write_digit(2, 2);
  //write_digit(3, 2);
  //write_digit(4, 2);
  //write_digit(5, 2);
  //write_digit(6, 2);
  //  led.write();
  //
  //    delay(2000);
  //
  //  led.setColor(NeoPixelAll, 0x000000);//выключаем все светодиоды - обнуляем это старт
  //    led.write();
  //  delay(1000);
}

void loop() {

//color = 0x0000ff; //  при подаче сигналов звка цифры тоже красятся в дургой цвет, поэтому здесь красим в исходный

//  старт раздела чтения блютуз
    if (Serial.available())         // если блютуз доступен:
     {
                                        btoo = Serial.read();           //  прочитать строку                                                                         //  если прочитано "1"
                                                                           if (btoo != '1')
                                                                                                 {
                                                                                               led.setColor(NeoPixelAll, 0xffffff);//красим все светодиоды - обнуляем это старт
                                                                                               led.write();
                                                                                               delay(1000);     }
                                                                                               
                                                                                  // При символе "0"
                                                                                  if ( btoo == '0')
                                                                                                      {
                                                                                                   // пока н нчего
                                                                                                      } 
                                                                                                      
      }  // блютуз  конец обработки чтения
  // страт пищалки //

  if (seconds >= 27 && seconds <30  or seconds == 15 or seconds == 45 or seconds >= 57) {
     tone(8, 3000);  // пищать на пине 3, 1 кГц    и подкрашиваем цифры для глухих
   
  //                                                     color = 0xffffff;
                                                       //led.setColor(1, 0xffffff);
                                                       //led.write();
    delay(500);
    noTone(8);      // не пищать
    delay(500);

//       COLOR = red;

  //digitalWrite(8, HIGH);  для активной пищалки
     //delay(1000);
  //digitalWrite(8, LOW);  для активной пищалки
     
  }
  if (seconds == 30 or seconds == 00) {
                                tone(8, 2000);  // пищать на пине 3, 1 кГц
                                  delay(500);
                                    noTone(8);      // не пищать
                                  delay(1000);
           //digitalWrite(8, HIGH);  для активной пищалки
             //delay(1000);
               //digitalWrite(8, LOW);  для активной пищалки
  
                     }
 
  // конец раздела пищалки





  //led.setColor(NeoPixelAll, COLOR);//включает все светодиоды

  seconds = millis() / 1000 % 60;

  if (seconds == 59) {
    seconds_flag = true; // если насчитано 59 секунд, ставим флаг в положение true, чтобы ОДНОКРАТНО увеличить минуты, когда секунд будет 0 (ноль).
  }
  if (seconds == 0) {
    if (seconds_flag) minutes++;
    seconds_flag = false;
  }

  if (minutes == 59) {
    minutes_flag = true; // если насчитано 59 секунд, ставим флаг в положение true, чтобы ОДНОКРАТНО увеличить минуты, когда секунд будет 0 (ноль).
  }
  if (minutes == 0) {
    if (minutes_flag) hours++;
    minutes_flag = false;
  }

  if (hours > 23) {
    hours = 0;
  }

  write_digit(6, hours / 10);
  write_digit(5, hours % 10);
  write_digit(4, minutes / 10);
  write_digit(3, minutes % 10);
  write_digit(2, seconds / 10);
  write_digit(1, seconds % 10);

  Serial.print(hours); Serial.print(":"); Serial.print(minutes); Serial.print(":"); Serial.println(seconds);

  led.write();

}


void cleaning(int place) {                    //очищаем позицию (цифроместо) place in {1 ..6}

  for (int i = 29 * (place - 1); i < 29 * (place - 1) + 30; i++) {    // первый светодиод имеет нулевой номер
    led.setColor(i, 0x000000);
  }
}

void one (int place) {//выводим 1 на заданной позиции place

  cleaning(place);
  for (int i = (place - 1) * 29 + 11; i < (place - 1) * 29 + 21; i++) {
    led.setColor(i, COLOR);
  }

}

void two (int place) {//выводим 2 на заданной позиции place

  cleaning(place);
  for (int i = (place - 1) * 29; i < (place - 1) * 29 + 11; i++) {
    led.setColor(i, COLOR);
  }
  for (int i = (place - 1) * 29 + 16; i < (place - 1) * 29 + 24; i++) {
    led.setColor(i, COLOR);
  }
}

void three(int place) {//выводим 3 на заданной позиции place

  cleaning(place);
  for (int i = (place - 1) * 29 + 8; i < (place - 1) * 29 + 24; i++) {
    led.setColor(i, COLOR);
  }

  for (int i = (place - 1) * 29; i < (place - 1) * 29 + 3; i++) {
    led.setColor(i, COLOR);
  }
}

void four(int place) {//выводим 4 на заданной позиции place
  cleaning(place);
  for (int i = (place - 1) * 29; i < (place - 1) * 29 + 3; i++) {
    led.setColor(i, COLOR);
  }
  for (int i = (place - 1) * 29 + 11; i < (place - 1) * 29 + 21; i++) {
    led.setColor(i, COLOR);
  }
  for (int i = (place - 1) * 29 + 24; i < (place - 1) * 29 + 29; i++) {
    led.setColor(i, COLOR);
  }
}

void five(int place) {//выводит 5 на заданной позиции place
  cleaning(place);
  for (int i = (place - 1) * 29; i < (place - 1) * 29 + 3; i++) {
    led.setColor(i, COLOR);
  }
  for (int i = (place - 1) * 29 + 8; i < (place - 1) * 29 + 16; i++) {
    led.setColor(i, COLOR);
  }
  for (int i = (place - 1) * 29 + 21; i < (place - 1) * 29 + 29; i++) {
    led.setColor(i, COLOR);
  }
}

void six(int place) {//выводит 6 на заданной позиции place
  cleaning(place);
  for (int i = (place - 1) * 29 + 0; i < (place - 1) * 29 + 16; i++) {
    led.setColor(i, COLOR);
  }
  for (int i = (place - 1) * 29 + 21; i < (place - 1) * 29 + 29; i++) {
    led.setColor(i, COLOR);
  }
}

void seven(int place) {//выводит 7 на заданной позиции place
  cleaning(place);
  for (int i = (place - 1) * 29 + 11; i < (place - 1) * 29 + 24; i++) {
    led.setColor(i, COLOR);
  }
}

void eight(int place) {//выводит 8 на заданной позиции place

  cleaning(place);
  for (int i = (place - 1) * 29 + 0; i < (place - 1) * 29 + 29; i++) {
    led.setColor(i, COLOR);
  }
}

void nine(int place) {//выводит 9 на заданной позиции place

  cleaning(place);
  for (int i = (place - 1) * 29; i < (place - 1) * 29 + 3; i++) {
    led.setColor(i, COLOR);
  }
  for (int i = (place - 1) * 29 + 8; i < (place - 1) * 29 + 29; i++) {
    led.setColor(i, COLOR);
  }
}

void zero(int place) {//выводит 0 на заданной позиции place

  cleaning(place);
  for (int i = (place - 1) * 29 + 3; i < (place - 1) * 29 + 29; i++) {
    led.setColor(i, COLOR);
  }
}

void write_digit(int place, int digit) {//выводит на заданной позиции (цифроместе) place заданную цифру digit
  switch (digit) {
    case 0:
      zero(place);
      break;
    case 1:
      one(place);
      break;
    case 2:
      two(place);
      break;
    case 3:
      three(place);
      break;
    case 4:
      four(place);
      break;
    case 5:
      five(place);
      break;
    case 6:
      six(place);
      break;
    case 7:
      seven(place);
      break;
    case 8:
      eight(place);
      break;
    case 9:
      nine(place);
      break;
  }
  //led.write(); // закомментировано, т.к. отдельно указывается один раз после нескольких вызовов write_digit()
}

void beginning() {                                   // начало работы с часами проверка систем вывод различных цифр

  Serial.begin(9600);
  //analogWrite(9, 255);

  if (led.begin()) {                                 // запускает ленту и проверяет её работу
    Serial.print("Led is ready");                    // лента исправна и готова к работе
  }
  else {
    Serial.print("Led is not ready");                // лента неисправна или ошибка подключения ленты
  }

  if (Serial.available()) {
    Serial.println(" and Ready to receive messages");// готов принимать сообщения
  } else {
    Serial.println(" and Error of bluetooth module");// ошибка блютуз модуля
  }

  //  write_digit(1, 0);                                 //выводит 0 на 1 позиции
  //  write_digit(2, 1);                                 //выводит 1 на 2 позиции
  //  write_digit(3, 2);                                 //выводит 2 на 3 позиции
  //  write_digit(4, 3);                                 //выводит 3 на 4 позиции
  //  write_digit(5, 4);                                 //выводит 4 на 5 позиции
  //  write_digit(6, 5);                                 //выводит 5 на 6 позиции
  //
  //  led.write();
}
