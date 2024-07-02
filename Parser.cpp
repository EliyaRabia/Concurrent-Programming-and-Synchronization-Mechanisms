#include "Parser.h"
#include <iostream>
#include <fstream>
#include <sstream>

// Function to parse the configuration file
Config parseConfig(const std::string& filename) {
    std::ifstream file(filename); // Open the configuration file
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open configuration file"); // Error if file cannot be opened
    }

    Config config; // Initialize config structure
    std::string line;
    while (std::getline(file, line)) { // Read file line by line
        if (line.find("PRODUCER") != std::string::npos) { // Check if line indicates a producer
            ProducerConfig producer;
            std::sscanf(line.c_str(), "PRODUCER %d", &producer.id); // Parse producer ID
            std::getline(file, line);
            producer.numberOfProducts = std::stoi(line); // Parse number of products
            std::getline(file, line);
            producer.queueSize = std::stoi(line.substr(line.find("=") + 1)); // Parse queue size
            config.producers.push_back(producer); // Add producer to config
        } else if (line.find("Co-Editor queue size") != std::string::npos) {
            config.coEditorQueueSize = std::stoi(line.substr(line.find("=") + 1)); // Parse co-editor queue size
        }
    }
    file.close(); // Close the configuration file
    return config; // Return the parsed configuration
}