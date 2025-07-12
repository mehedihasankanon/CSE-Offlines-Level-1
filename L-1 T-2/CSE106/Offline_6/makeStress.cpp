#include <iostream>
#include <fstream>
#include <random>

int main() {
    // Open the file in write mode
    std::ofstream outFile("stress.txt");
    
    // Check if the file was opened successfully
    if (!outFile) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    // Initialize random number generator with random device for more randomness
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1000000000);  // Random integers between 0 and 1 billion

    // Generate 10 million random integers and write them to the file
    for (int i = 0; i < 10000000; ++i) {
        outFile << dis(gen) << "\n";
    }

    std::cout << "Random integers have been written to stress.txt" << std::endl;

    // Close the file
    outFile.close();
    
    return 0;
}
