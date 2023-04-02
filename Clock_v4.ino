//  добавлен прием времени от андроид приложения по блютуз  - принимает, но записывает в разные регистры ?? почему
//  добавлены перекрашивание цвета при подаче сигналов
//  добавлены стартовые сигналы
#include <iarduino_NeoPixel.h>                  // открытие библиотеки
#define PORT 7                                  // назначаем порт ленты
#define COUNT 174                               // кол - во светодиов
//#define COLOR 0x0000ff // 0xffffff                         // цвет ленты
iarduino_NeoPixel led(PORT, COUNT);             // инициализируем ленту
// unsigned long long watch = 0;                   //создаем переменную счётчик
byte hours = 0;                                      //создаём переменную , хранящую кол-во часов
byte minutes = 0;                                     //создаём переменную, хранящую кол-во минут
byte seconds;                                    //создаём переменную , хранящую кол-во секунд (берём значение из функции-счётчика millis() )
bool seconds_flag = false;                          // flag для однократного увеличения минут при нуле секунд (60 секунд)
bool minutes_flag = false;                          // (нужна из-за ложных доп. срабатываний при нуле минут - т.к. проверка каждую миллисекунду идёт!)
// -//- аналогично для минут и часов

long color;                  //  переменная для храниения цвета 
int btoo;                       //блютуз  переменная для чтения от
int number_of_digit_in = 0;     //

#define PARSE_AMOUNT 3          // ПАРСИНГ. Число значений в массиве, который хотим получить
int intData[PARSE_AMOUNT];      // ПАРСИНГ. Массив численных значений после парсинга
boolean recievedFlag;           // ПАРСИНГ. Флаг для проверки условий
boolean getStarted;             // ПАРСИНГ. Переменная для разрешения/запрещения считывания
byte index;                     // ПАРСИНГ. Номер элемента массива intData[]
String string_convert = "";     // ПАРСИНГ. Строка для накопления данных пакета пришедшего на COM-порта с авиаджойстика.




void setup() {

color=0x00000;



  beginning();                                  // проверка подключения светодиодки и работы каждой цифры

  led.setColor(NeoPixelAll, 0x000000);//выключаем все светодиоды - обнуляем это старт
  led.write();
  delay(1000);


Serial.begin(9600);                               //блютуз   инициация  чтения
  for (int i = 0; i < PARSE_AMOUNT; i++) intData[i] = 0; // инициализируем 

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
color = 0x0000ff; //  при подаче сигналов звука цифры красятся в другой цвет, поэтому здесь красим в исходный (синий)


  // страт генерации звука //
 // страт генерации звука //
// страт генерации звука //

  if (seconds >= 27 && seconds <30  or seconds == 15 or seconds == 45 or seconds >= 57) {
     tone(8, 3000);  // пищать на пине 3, 1 кГц    и подкрашиваем цифры для глухих
   
    
                                                    //  led.setColor(1, 0xffffff);
                                                       led.write();
    delay(500);
    noTone(8);      // не пищать
    delay(500);
    color = 0xffffff;

                    //digitalWrite(8, HIGH);  для активной генерации звука
                    //delay(1000);
                    //digitalWrite(8, LOW);  для активной генерации звука
      }                      
   if (seconds == 30 or seconds == 00) {
                                          tone(8, 2000);  //  пищать на пине 3, 1 кГц
                                          delay(500);
                                          noTone(8);      // не пищать
                                          delay(1000);
           //digitalWrite(8, HIGH);  для активной генерации звука
             //delay(1000);
               //digitalWrite(8, LOW);  для активной генерации звука
                                         }
 
  // конец раздела генерации звука



//  старт раздела чтения блютуз
//------------------------------------------------//
//    получение данных из com-порта и парсинг     //
//------------------------------------------------//

    if (Serial.available())         // если блютуз доступен:
     {
                           parsing();       // функция парсинга  (сама функция внизу файла)

//if (recievedFlag) {                           // если получены данные
//
//    recievedFlag = false;
    //    for (byte i = 0; i < PARSE_AMOUNT; i++) { // выводим элементы массива для отладки
    //      Serial.print(intData[i]); Serial.print(" ");
    //    }
    //    Serial.println();

    hours = intData[0];
    minutes = intData[1];
    seconds = intData[2];           // данные приняты, мой капитан!

 
    // выводим в порт для отладки
    //    Serial.print("direction_x = "); Serial.print(direction_x); Serial.print(" ");
    //    Serial.print("direction_y = "); Serial.print(direction_y); Serial.print(" ");
    //    Serial.print("stick_pivot = "); Serial.print(stick_pivot); Serial.println(" ");
//  }
  //------------------------------------------------//
  //      завершение приёма данных из com-порта     //
  //------------------------------------------------//
         



      
//                                                                           btoo = Serial.read();           //  прочитать строку                                                                         //  если прочитано "1"
//                                                                           if (btoo != '1')
//                                                                                                 {
//                                                                                               led.setColor(NeoPixelAll, 0xffffff);//красим все светодиоды - обнуляем это старт
//                                                                                               led.write();
//                                                                                               delay(1000);     }
//                                                                                               
//                                                                                  // При символе "0"
//                                                                                  if ( btoo == '0')
//                                                                                                      {
//                                                                                                   // пока н нчего
//                                                                                                      } 
//                                                                                                      
      }  // блютуз  конец обработки чтения





  //led.setColor(NeoPixelAll, color);//включает все светодиоды

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

  // Serial.print(hours); Serial.print(":"); Serial.print(minutes); Serial.print(":"); Serial.println(seconds);  зачем?

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
    led.setColor(i, color);
  }

}

void two (int place) {//выводим 2 на заданной позиции place

  cleaning(place);
  for (int i = (place - 1) * 29; i < (place - 1) * 29 + 11; i++) {
    led.setColor(i, color);
  }
  for (int i = (place - 1) * 29 + 16; i < (place - 1) * 29 + 24; i++) {
    led.setColor(i, color);
  }
}

void three(int place) {//выводим 3 на заданной позиции place

  cleaning(place);
  for (int i = (place - 1) * 29 + 8; i < (place - 1) * 29 + 24; i++) {
    led.setColor(i, color);
  }

  for (int i = (place - 1) * 29; i < (place - 1) * 29 + 3; i++) {
    led.setColor(i, color);
  }
}

void four(int place) {//выводим 4 на заданной позиции place
  cleaning(place);
  for (int i = (place - 1) * 29; i < (place - 1) * 29 + 3; i++) {
    led.setColor(i, color);
  }
  for (int i = (place - 1) * 29 + 11; i < (place - 1) * 29 + 21; i++) {
    led.setColor(i, color);
  }
  for (int i = (place - 1) * 29 + 24; i < (place - 1) * 29 + 29; i++) {
    led.setColor(i, color);
  }
}

void five(int place) {//выводит 5 на заданной позиции place
  cleaning(place);
  for (int i = (place - 1) * 29; i < (place - 1) * 29 + 3; i++) {
    led.setColor(i, color);
  }
  for (int i = (place - 1) * 29 + 8; i < (place - 1) * 29 + 16; i++) {
    led.setColor(i, color);
  }
  for (int i = (place - 1) * 29 + 21; i < (place - 1) * 29 + 29; i++) {
    led.setColor(i, color);
  }
}

void six(int place) {//выводит 6 на заданной позиции place
  cleaning(place);
  for (int i = (place - 1) * 29 + 0; i < (place - 1) * 29 + 16; i++) {
    led.setColor(i, color);
  }
  for (int i = (place - 1) * 29 + 21; i < (place - 1) * 29 + 29; i++) {
    led.setColor(i, color);
  }
}

void seven(int place) {//выводит 7 на заданной позиции place
  cleaning(place);
  for (int i = (place - 1) * 29 + 11; i < (place - 1) * 29 + 24; i++) {
    led.setColor(i, color);
  }
}

void eight(int place) {//выводит 8 на заданной позиции place

  cleaning(place);
  for (int i = (place - 1) * 29 + 0; i < (place - 1) * 29 + 29; i++) {
    led.setColor(i, color);
  }
}

void nine(int place) {//выводит 9 на заданной позиции place

  cleaning(place);
  for (int i = (place - 1) * 29; i < (place - 1) * 29 + 3; i++) {
    led.setColor(i, color);
  }
  for (int i = (place - 1) * 29 + 8; i < (place - 1) * 29 + 29; i++) {
    led.setColor(i, color);
  }
}

void zero(int place) {//выводит 0 на заданной позиции place

  cleaning(place);
  for (int i = (place - 1) * 29 + 3; i < (place - 1) * 29 + 29; i++) {
    led.setColor(i, color);
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



//--------------------------------------------------//
//    ФУНКЦИЯ ПАРСИНГА ВХОДЯЩИХ В COM-ПОРТ ДАННЫХ   //
//--------------------------------------------------//
void parsing() {
  if (Serial.available() > 0) {
    char incomingByte = Serial.read();          // обязательно ЧИТАЕМ входящий символ
    if (getStarted) {                           // если приняли начальный символ (парсинг разрешён)
      if (incomingByte != ':' && incomingByte != ';') {   // если это не пробел И не конец

        if (number_of_digit_in < 2) {  // пробуем проверку на 2 цыфры в разряде, не помогло 
        string_convert += incomingByte; 
        }
        else {index++; number_of_digit_in = 0;}// складываем в строку
      }
      else {                                    // если это пробел или ; конец пакета
        intData[index] = string_convert.toInt();// преобразуем строку в int и кладём в массив
        string_convert = "";                    // очищаем строку
        index++;                                // переходим к парсингу следующего элемента массива
      }
    }
    if (incomingByte == '$') {                // если это $
      getStarted = true;                      // поднимаем флаг, что можно парсить
      index = 0;                              // сбрасываем индекс
      string_convert = "";                    // очищаем строку
    }
    if (incomingByte == ';') {                // если таки приняли ; - конец парсинга
      getStarted = false;                     // сброс
      recievedFlag = true;                    // флаг на принятие
    }
  }
}
//--------------------------------------------------//
//           ЗАВЕРШЕНИЕ ФУНКЦИИ ПАРСИНГА            //
//--------------------------------------------------//
