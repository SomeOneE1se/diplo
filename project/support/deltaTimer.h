#ifndef DELTATIMER_H
#define DELTATIMER_H

#include "project.h"

TFloat deltaTimer_getDt(void);

TInt deltaTimer_initialize(void);

void deltaTimer_tick(void);

#endif  // DELTATIMER_H
