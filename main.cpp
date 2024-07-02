#include <iostream>
#include <vector>
#include <thread>
#include "BoundedBuffer.h"
#include "Producer.h"
#include "Dispatcher.h"
#include "CoEditor.h"
#include "ScreenManager.h"
#include "Parser.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <config file>" << std::endl;
        return 1;
    }

    Config config;
    try {
        config = parseConfig(argv[1]);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    if (config.producers.size() != 3 || config.coEditorQueueSize <= 0) {
        std::cerr << "Error in config file format or content." << std::endl;
        return 1;
    }

    BoundedBuffer buffer1(config.producers[0].queueSize);
    BoundedBuffer buffer2(config.producers[1].queueSize);
    BoundedBuffer buffer3(config.producers[2].queueSize);
    BoundedBuffer coEditorBuffer(config.coEditorQueueSize);
    BoundedBuffer screenBuffer(config.coEditorQueueSize);

    std::vector<BoundedBuffer*> producerBuffers = {&buffer1, &buffer2, &buffer3};

    std::thread producer1(producerFunction, 1, config.producers[0].numberOfProducts, std::ref(buffer1));
    std::thread producer2(producerFunction, 2, config.producers[1].numberOfProducts, std::ref(buffer2));
    std::thread producer3(producerFunction, 3, config.producers[2].numberOfProducts, std::ref(buffer3));

    std::thread dispatcher(dispatcherFunction, std::ref(producerBuffers), std::ref(coEditorBuffer));
    
    std::thread coEditor1(coEditorFunction, std::ref(coEditorBuffer), std::ref(screenBuffer));
    std::thread coEditor2(coEditorFunction, std::ref(coEditorBuffer), std::ref(screenBuffer));
    std::thread coEditor3(coEditorFunction, std::ref(coEditorBuffer), std::ref(screenBuffer));

    std::thread screenManager(screenManagerFunction, std::ref(screenBuffer));

    producer1.join();
    producer2.join();
    producer3.join();

    // Signal end of production to dispatcher
    std::cout << "Producers finished. Signaling dispatcher." << std::endl;
    for (auto buffer : producerBuffers) {
        buffer->insert("DONE");
    }

    dispatcher.join();

    // Signal end of processing to co-editors
    std::cout << "Dispatcher finished. Signaling co-editors." << std::endl;
    for (int i = 0; i < 3; ++i) {
        coEditorBuffer.insert("DONE");
    }

    coEditor1.join();
    coEditor2.join();
    coEditor3.join();

    // Signal end of processing to screen manager
    std::cout << "Co-Editors finished. Signaling screen manager." << std::endl;
    screenBuffer.insert("DONE");

    screenManager.join();

    return 0;
}
