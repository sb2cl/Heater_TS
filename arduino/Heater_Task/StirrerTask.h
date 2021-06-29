#ifndef STIRRERTASK_H
#define STIRRERTASK_H

#include <inttypes.h>

#include "Task.h"
#include "Debugger.h"

/**
   @brief This class controls the magnetic stirrer of the turbidostat.


*/
class StirrerTask: public TimedTask {
  public:
    StirrerTask(uint64_t now, uint64_t rate, Debugger *_ptrDebugger = NULL);
    ~StirrerTask();

  private:
    uint64_t rate; // Delay between steps.
    Debugger *ptrDebugger;

    uint8_t  pos; // Next step configuration for the stepper.
    int b1 = 9, b2 = 10, b3 = 11, b4 = 12; // Stepper pins.

    void run(uint64_t now) override;

};

#endif /* end of include guard: STIRRERTASK_H */
