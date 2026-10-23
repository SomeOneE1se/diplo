#ifndef EVENTS_H
#define EVENTS_H

#include "project.h"

TULong events_getUpdateCounter(void);

void events_pullEvents(void);

TInt events_initialize(void);

void events_terminate(void);

#endif  // EVENTS_H
