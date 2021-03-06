#include <Arduino.h>
#include "src-gen/TrafficLightCtrl.h"
#include "scutil/CPPTimerinterface.h"
#include "src/arduinoPins.h"
#include "src/TrafficLightOCBs.h"
#include "src/PushButton.h"

TrafficLightCtrl* arduino = new TrafficLightCtrl();
CPPTimerInterface* timer_sct = new CPPTimerInterface();
TrafficLightOCBs* operationCallback = new TrafficLightOCBs(arduino);

PushButton* pushButton_1;
PushButton* pushButton_2;

static void button_1_changed() {
	if (!pushButton_1->state) arduino->raise_pedestrianRequest();
}

static void button_2_changed() {
	if (!pushButton_2->state) arduino->raise_onOff();
}

//The setup function is called once at startup of the sketch
void setup()
{
	pushButton_1 = new PushButton(button_1_pin, button_1_changed);
	pushButton_2 = new PushButton(button_2_pin, button_2_changed);

	pinMode(led_green_pin, OUTPUT);
	pinMode(led_yellow_pin, OUTPUT);
	pinMode(led_red_pin, OUTPUT);

	pinMode(ped_led_red_pin, OUTPUT);
	pinMode(ped_led_green_pin, OUTPUT);
	pinMode(ped_led_request_pin, OUTPUT);

	arduino->init();
	arduino->setTimer(timer_sct);
	arduino->setDefaultSCI_OCB(operationCallback);
	arduino->enter();
}

#define CYCLE_PERIOD (10)
static unsigned long cycle_count = 0L;
static unsigned long last_cycle_time = 0L;

void loop() {

	unsigned long current_millies = millis();

	pushButton_1->readPushButton();
	pushButton_2->readPushButton();

	if ( cycle_count == 0L || (current_millies >= last_cycle_time + CYCLE_PERIOD) ) {

		timer_sct->updateActiveTimer(arduino, current_millies - last_cycle_time);
		arduino->runCycle();

		last_cycle_time = current_millies;
		cycle_count++;
	}
}



