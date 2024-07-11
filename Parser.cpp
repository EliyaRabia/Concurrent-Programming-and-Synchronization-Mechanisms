#include "Parser.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

using std::string;
using std::ifstream;
using std::getline;
using std::runtime_error;
using std::vector;

Config parseConfig(const string& filename) {
    ifstream file(filename); // Open the configuration file
    if (!file.is_open()) {
        throw runtime_error("Cannot open configuration file"); // Error if file cannot be opened
    }

    Config config; // Initialize config structure
    string line;
    while (getline(file, line)) { // Read file line by line
        if (line.find("PRODUCER") != string::npos) { // Check if line indicates a producer
            ProducerConfig producer;
            std::sscanf(line.c_str(), "PRODUCER %d", &producer.id); // Parse producer ID
            getline(file, line);
            producer.numberOfProducts = std::stoi(line); // Parse number of products
            getline(file, line);
            producer.queueSize = std::stoi(line.substr(line.find("=") + 1)); // Parse queue size
            config.producers.push_back(producer); // Add producer to config
        } else if (line.find("Co-Editor queue size") != string::npos) {
            config.coEditorQueueSize = std::stoi(line.substr(line.find("=") + 1)); // Parse co-editor queue size
        }
    }
    file.close(); // Close the configuration file
    return config; // Return the parsed configuration
}
