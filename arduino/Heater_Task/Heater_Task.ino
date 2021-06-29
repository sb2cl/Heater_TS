#include "Debugger.h"
#include "Task.h"
#include "TaskScheduler.h"

#include "BlinkTask.h"
#include "StirrerTask.h"

TaskScheduler *scheduler;

Debugger *debugger;
Task *tasks[2];

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);

  debugger = new Debugger();

  tasks[0] = new BlinkTask(0,1000,debugger);
  tasks[1] = new StirrerTask(0,100,debugger);
  tasks[2] = debugger;
  scheduler = new TaskScheduler(tasks, NUM_TASKS(tasks));
}

// the loop function runs over and over again forever
void loop() {
  scheduler->run(millis()); 
}
