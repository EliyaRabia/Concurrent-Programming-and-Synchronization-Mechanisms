#ifndef PRODUCER_H
#define PRODUCER_H

#include "BoundedBuffer.h"

// Function to simulate a producer producing items
void producerFunction(int id, int numProducts, BoundedBuffer& buffer);

#endif // PRODUCER_H