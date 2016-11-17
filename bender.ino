// пин с кнопкой +
#define BTN_UP 5
// пин с кнопкой -
#define BTN_DOWN 6
// пин с Бендером
#define BENDER 9
// шаг изменения яркости Бендера
#define STEP 10
// яркость Бендера
int benderShine = 0;

void setup(){
	// пины с кнопками назначаем как входы с подтяжкой
	pinMode(BTN_UP, INPUT_PULLUP);
	pinMode(BTN_DOWN, INPUT_PULLUP);
}

void loop(){
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
}