#ifndef CONTROLLERTASK_H
#define CONTROLLERTASK_H

#include <inttypes.h>

#include "Task.h"
#include "Debugger.h"

/**
   @brief This class implements the temperature controller.


*/
class ControllerTask: public TimedTask {
  public:
    ControllerTask(uint64_t now, uint64_t rate, Debugger *_ptrDebugger = NULL);
    ~ControllerTask();

    // Simulator variables.
    float a = 0.00549;  // Heating constant.
    float b = 0.03;     // Cooling constant.
    float h = 0.1;      // Integration time.
    float T_ini = 25;   // Initial temperature.
    float T_amb = 25;   // Ambient temperature.
    float T;            // Actual temperature.
    float dT;           // Derivative temperature.
    float t;            // Actual time in simulation.

    // Controller variables.
    float K_p = 10;      // Proportional gain.
    float K_i = 0.1;      // Integral gain.
    float T_ref = 30;   // Reference temperature.
    float u1;           // Last control action.
    float u;            // Actual control action.
    float error1;       // Last error.

    // Reference controller.
    float alpha;

  private:
    uint64_t rate; // Delay between steps.
    Debugger *ptrDebugger;

    void simulate();
    void controller();
    void run(uint64_t now) override;

};

#endif /* end of include guard: ControllerTask */
