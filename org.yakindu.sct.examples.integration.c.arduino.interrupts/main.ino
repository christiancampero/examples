#include "Arduino.h"

#include "src/hw_impl.h"
#include "src/timer_impl.h"
#include "src-gen/StateMachineRequired.h"

/*! Define the state machine object */
StateMachine stateMachine;

/*! Setup the Arduino */
void setup() {
	/*! Setup the hardware you're using. Activate the interrupts.
	 * Digital/Analog Ports, Sensors, Actuators, Communication */
	hw_init();

	/*! Initialize the timer service. Here you must define,
	 * how many time events you're using.
	 * The default value is 10.
	 * Will be updated via WDT Interrupt every 32 ms */
	timer_init();

	/*! Initialize and enter the state machine */
	stateMachine_init(&stateMachine);
	stateMachine_enter(&stateMachine);
}

/*! Runs forever */
void loop() {
	/*! Runs until the state machine is final.
	 * Always true, if there is no final state defined */
	while (!stateMachine_isFinal(&stateMachine)) {
		/*! Update timer if WDT interrupt has been occurred,
		 * which is set to 32 ms.*/
		handle_timer();

		/*! Handle flags, if in the meanwhile an interrupt has
		 * occurred. Status has been stored in flags. */
		handle_in_events(&stateMachine);

		/*! For @EventDriven state machines, runCycle must not be called.
		 * Use runCycle for @CycleBased state machines */
		//stateMachine_runCycle(&stateMachine);

		/*! Update your actuators */
		handle_out_events(&stateMachine);
		/*! Set Arduino in sleep mode. Can be commented out,
		 * especially if Serial is used. Won't work together. */
		sleep_mode();
	}
}

