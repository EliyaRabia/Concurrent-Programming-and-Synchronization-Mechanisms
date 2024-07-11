#ifndef PRODUCER_H
#define PRODUCER_H

#include "BoundedBuffer.h"

void producerFunction(int producerId, int numberOfProducts, BoundedBuffer &buffer);

#endif // PRODUCER_H
