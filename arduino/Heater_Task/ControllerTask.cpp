#include "ControllerTask.h"

/**
   @brief: Constructor of StirrerTask.

   @param: uint64_t _now           Time in 100ns of first execution of the task.
         : uint64_t _rate          Time interval in 100ns of execution of the task.
         : Debugger *_ptrDebugger  Pointer to debugger.

*/
ControllerTask::ControllerTask(uint64_t _now, uint64_t _rate, Debugger *_ptrDebugger)
  : TimedTask(_now),
    rate(_rate),
    ptrDebugger(_ptrDebugger)
{
  T = T_ini;
  t = 0;

  u1 = 0;
  error1 = 0;
}

/**
   @brief: Destructor of ControllerTask.

*/
ControllerTask::~ControllerTask() {}

/**
   @brief: Simulate an time step.

   @param: void.

   @return: void
*/
void ControllerTask::simulate() {
  dT = a * u + b * (T_amb - T);
  T = T + dT * h;
  t = t + h;
}

/**
   @brief: Execute the controller.

   @param: void

   @return: void
*/
void ControllerTask::controller() {
  float error = T_ref - T;
  u = error * K_p + K_i * error1 + u1;

  if (u > 255) {
    u = 255;
  }
  if (u < 0) {
    u = 0;
  }

  u1 = u;
  error1 = error;
}

/**
   @brief: Do a step in the stirrer.

   @param: uint64_t now Current time in 100 nanoseconds.

   @return: void
*/
void ControllerTask::run(uint64_t now) {

  controller();
  simulate();

  if (ptrDebugger) {
    Serial.print("Ref=");
    Serial.print(dT);
    Serial.print("ºC T=");
    Serial.print(T);
    Serial.print("ºC");
    Serial.print(" u=");
    Serial.print(u);
    Serial.print(" time=");
    Serial.print(t);
    Serial.print(" min");
    Serial.println();
  }

  // Run again in the specified time.
  incRunTime(rate);
}
