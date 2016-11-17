// подключаем библиотеку для работы с EEPROM
#include <EEPROM.h>
// пин с кнопкой +
#define BTN_UP 5
// пин с кнопкой -
#define BTN_DOWN 6
// пин с Бендером
#define BENDER 9
// шаг изменения яркости Бендера
#define STEP 10
// адрес в EEPROM который читаем/пишем
#define ADDR 0
// яркость Бендера
uint8_t benderShine = 50;

// размещаем счетчик отключения в EEPROM
int EEMEM gameOver = 5;
// таймер для уменьшения счетчика отключения
unsigned long gameOverTimer = 0;

void setup(){
  // пины с кнопками назначаем как входы с подтяжкой
  pinMode(BTN_UP, INPUT_PULLUP);
  pinMode(BTN_DOWN, INPUT_PULLUP);
}

void loop(){
  // пока читаем из EEPROM по адресу счетчика не ноль
  while(EEPROM.read(ADDR)){
    // если нажата кнопка +
    if (!digitalRead(BTN_UP)){
      // увеличиваем яркость Бендера на величинц STEP
      // а если уже хватит, то делаем ее 255
      benderShine = (benderShine >= 255 - STEP) ? 255 : benderShine += STEP;
      // исключение повторного срабатывания кнопки, 
      // пока ее не отпустили 
      while(!digitalRead(BTN_UP));
    }
    // если нажата кнопка -
    if (!digitalRead(BTN_DOWN)){
      // уменьшаем яркость Бендера на величинц STEP
      // а если уже хватит, то делаем ее 0
      benderShine = (benderShine <= STEP) ? 0 : benderShine -= STEP;
      // исключение повторного срабатывания кнопки, 
      // пока ее не отпустили 
      while(!digitalRead(BTN_DOWN));
    }
    // записываем яркость Бендера в ШИМ выход
    analogWrite(BENDER,benderShine);
    // если таймер отключения насчитал одну секунду
    if ((millis() - gameOverTimer) > 1000){
      // уменьшаем счетчик отключения в EEPROM
      EEPROM.write(ADDR,EEPROM.read(ADDR)-1);
      // обновляем текущее значения таймера
      gameOverTimer = millis();
    }
  }
  // ГАСИМ БЕНДЕРА, ЕСЛИ СЧЕТЧИК ЗАШЕЛ В НОЛЬ
  // И БОЛЬШЕ НИЧЕГО НЕ ДЕЛАЕМ ДО ПЕРЕПРОШИВКИ ПЛАТЫ
  analogWrite(BENDER,0);
}