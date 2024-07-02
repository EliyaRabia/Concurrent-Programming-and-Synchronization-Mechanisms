#ifndef PRODUCER_H
#define PRODUCER_H

#include "BoundedBuffer.h"
#include <iostream>

void producerFunction(int producerId, int numberOfProducts, BoundedBuffer &buffer);

#endif // PRODUCER_H
