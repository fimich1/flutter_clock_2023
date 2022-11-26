#define PARSE_AMOUNT 3          // ПАРСИНГ. Число значений в массиве, который хотим получить
int intData[PARSE_AMOUNT];      // ПАРСИНГ. Массив численных значений после парсинга
boolean recievedFlag;           // ПАРСИНГ. Флаг для проверки условий
boolean getStarted;             // ПАРСИНГ. Переменная для разрешения/запрещения считывания
byte index;                     // ПАРСИНГ. Номер элемента массива intData[]
String string_convert = "";     // ПАРСИНГ. Строка для накопления данных пакета пришедшего на COM-порта с авиаджойстика.


//--------------------------------------------------//
//    ФУНКЦИЯ ПАРСИНГА ВХОДЯЩИХ В COM-ПОРТ ДАННЫХ   //
//--------------------------------------------------//
void parsing() {
  if (Serial.available() > 0) {
    char incomingByte = Serial.read();          // обязательно ЧИТАЕМ входящий символ
    if (getStarted) {                           // если приняли начальный символ (парсинг разрешён)
      if (incomingByte != ' ' && incomingByte != ';') {   // если это не пробел И не конец
        string_convert += incomingByte;           // складываем в строку
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

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
  for (int i = 0; i < PARSE_AMOUNT; i++) intData[i] = 0; // инициализируем начальные значения
  
}

void loop() {
  // put your main code here, to run repeatedly:
  //------------------------------------------------//
  //    получение данных из com-порта и парсинг     //
  //------------------------------------------------//

  parsing();       // функция парсинга

  if (recievedFlag) {                           // если получены данные

    recievedFlag = false;
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
  }
  //------------------------------------------------//
  //      завершение приёма данных из com-порта     //
  //------------------------------------------------//
}
