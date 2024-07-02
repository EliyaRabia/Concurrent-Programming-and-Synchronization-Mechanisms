#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <vector>
#include "BoundedBuffer.h"

void dispatcherFunction(std::vector<BoundedBuffer*>& buffers, BoundedBuffer& coEditorBuffer);

#endif
