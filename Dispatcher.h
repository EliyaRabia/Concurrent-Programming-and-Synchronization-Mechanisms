#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <vector>
#include "BoundedBuffer.h"

void dispatcherFunction(std::vector<BoundedBuffer*>& producerBuffers, 
                        BoundedBuffer& sportsBuffer, 
                        BoundedBuffer& newsBuffer, 
                        BoundedBuffer& weatherBuffer);

#endif // DISPATCHER_H
