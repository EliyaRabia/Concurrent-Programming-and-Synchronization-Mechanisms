// main.cpp
#include "BoundedBuffer.h"
#include "Parser.h"
#include "Producer.h"
#include "Dispatcher.h"
#include "CoEditor.h"
#include "ScreenManager.h"
#include <iostream>
#include <thread>
#include <vector>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " config.txt" << std::endl;
        return 1; // Exit if configuration file is not provided
    }

    Config config = parseConfig(argv[1]); // Parse the configuration file
    
    std::vector<BoundedBuffer*> producerBuffers;
    for (const auto& producer : config.producers) {
        producerBuffers.push_back(new BoundedBuffer(producer.queueSize)); // Create producer buffers
    }
    
    // Create co-editor and screen manager buffers
    BoundedBuffer sportsBuffer(config.coEditorQueueSize);
    BoundedBuffer newsBuffer(config.coEditorQueueSize);
    BoundedBuffer weatherBuffer(config.coEditorQueueSize);
    BoundedBuffer screenBuffer(config.coEditorQueueSize);
    
    std::vector<std::thread> producerThreads;
    for (size_t i = 0; i < config.producers.size(); ++i) {
        producerThreads.emplace_back(producerFunction, config.producers[i].id, config.producers[i].numberOfProducts, std::ref(*producerBuffers[i])); // Create producer threads
    }

    // Create dispatcher and co-editor threads
    std::thread dispatcherThread(dispatcherFunction, std::ref(producerBuffers), std::ref(sportsBuffer), std::ref(newsBuffer), std::ref(weatherBuffer));
    
    std::thread sportsEditorThread(coEditorFunction, std::ref(sportsBuffer), std::ref(screenBuffer));
    std::thread newsEditorThread(coEditorFunction, std::ref(newsBuffer), std::ref(screenBuffer));
    std::thread weatherEditorThread(coEditorFunction, std::ref(weatherBuffer), std::ref(screenBuffer));

    // Create screen manager thread
    std::thread screenManagerThread(screenManagerFunction, std::ref(screenBuffer));
    
    // Join all threads
    for (auto& t : producerThreads) {
        t.join();
    }
    
    dispatcherThread.join();
    sportsEditorThread.join();
    newsEditorThread.join();
    weatherEditorThread.join();
    screenManagerThread.join();
    
    // Clean up dynamically allocated buffers
    for (auto buffer : producerBuffers) {
        delete buffer;
    }

    return 0;
}
