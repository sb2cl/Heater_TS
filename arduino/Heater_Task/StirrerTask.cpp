#include "StirrerTask.h"

/**
   @brief: Constructor of StirrerTask.

   @param: uint64_t _now           Time in 100ns of first execution of the task.
         : uint64_t _rate          Time interval in 100ns of execution of the task.
         : Debugger *_ptrDebugger  Pointer to debugger.

*/
StirrerTask::StirrerTask(uint64_t _now, uint64_t _rate, Debugger *_ptrDebugger)
  : TimedTask(_now),
    rate(_rate),
    ptrDebugger(_ptrDebugger)
{
  pinMode(b1, OUTPUT);
  pinMode(b2, OUTPUT);
  pinMode(b3, OUTPUT);
  pinMode(b4, OUTPUT);

  pos = 0;
}

/**
   @brief: Destructor of StirrerTask.

*/
StirrerTask::~StirrerTask() {}

/**
   @brief: Do a step in the stirrer.

   @param: uint64_t now Current time in 100 nanoseconds.

   @return: void
*/
void StirrerTask::run(uint64_t now) {
  pos ++;

  if (pos > 7) pos = 0;

  switch (pos) {
    case 0:
      digitalWrite(b1, HIGH);
      digitalWrite(b2, LOW);
      digitalWrite(b3, LOW);
      digitalWrite(b4, LOW);
      break;

    case 1:
      digitalWrite(b1, HIGH);
      digitalWrite(b2, HIGH);
      digitalWrite(b3, LOW);
      digitalWrite(b4, LOW);
      break;
    case 2:
      digitalWrite(b1, LOW);
      digitalWrite(b2, HIGH);
      digitalWrite(b3, LOW);
      digitalWrite(b4, LOW);
      break;

    case 3:
      digitalWrite(b1, LOW);
      digitalWrite(b2, HIGH);
      digitalWrite(b3, HIGH);
      digitalWrite(b4, LOW);
      break;

    case 4:
      digitalWrite(b1, LOW);
      digitalWrite(b2, LOW);
      digitalWrite(b3, HIGH);
      digitalWrite(b4, LOW);
      break;

    case 5:
      digitalWrite(b1, LOW);
      digitalWrite(b2, LOW);
      digitalWrite(b3, HIGH);
      digitalWrite(b4, HIGH);
      break;

    case 6:
      digitalWrite(b1, LOW);
      digitalWrite(b2, LOW);
      digitalWrite(b3, LOW);
      digitalWrite(b4, HIGH);
      break;

    case 7:
      digitalWrite(b1, HIGH);
      digitalWrite(b2, LOW);
      digitalWrite(b3, LOW);
      digitalWrite(b4, HIGH);
      break;

  }

  if (ptrDebugger) {
    char buffer[50];
    sprintf(buffer, "StirrerTask: One step %d", pos);
    ptrDebugger->debugWrite(buffer);
  }

  // Run again in the specified time.
  incRunTime(rate);
}
