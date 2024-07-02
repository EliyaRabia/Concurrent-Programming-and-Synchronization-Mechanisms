#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>

// Structure to hold producer configuration
struct ProducerConfig {
    int id;                // Producer ID
    int numberOfProducts;  // Number of products to produce
    int queueSize;         // Size of the queue for this producer
};

// Structure to hold the overall configuration
struct Config {
    std::vector<ProducerConfig> producers; // List of producers
    int coEditorQueueSize;                 // Size of the co-editor queue
};

// Function to parse the configuration file
Config parseConfig(const std::string& filename);

#endif // PARSER_H