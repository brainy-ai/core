#include <fstream>
#include <stdexcept>
#include <iostream>
#include <vector>
#include "brainy/brainy.hh"

// int const digits = 10;

// void swapb(uint32_t &num) {
//   num = ((num>>24)&0xff) | // move byte 3 to byte 0
//     ((num<<8)&0xff0000) | // move byte 1 to byte 2
//     ((num>>8)&0xff00) | // move byte 2 to byte 1
//     ((num<<24)&0xff000000); // byte 0 to byte 3
// }

// int main() {
//   std::ifstream imagesFile;
//   imagesFile.open("train-images-idx3-ubyte", std::ios::in | std::ios::binary);

//   std::ifstream labelsFile;
//   labelsFile.open("train-labels-idx1-ubyte", std::ios::in | std::ios::binary);

//   uint32_t magic;

//   imagesFile.read(reinterpret_cast<char*>(&magic), sizeof(magic));
//   swapb(magic);

//   if (magic != 2051) {
//     throw std::runtime_error("Bad magic number.");
//   }

//   labelsFile.read(reinterpret_cast<char*>(&magic), sizeof(magic));
//   swapb(magic);

//   if (magic != 2049) {
//     throw std::runtime_error("Bad magic number.");
//   }

//   uint32_t number;
//   imagesFile.read(reinterpret_cast<char*>(&number), sizeof(number));
//   swapb(number);
//   std::cout << "number = " << number << std::endl;

//   uint32_t labels;
//   labelsFile.read(reinterpret_cast<char*>(&labels), sizeof(labels));
//   swapb(labels);
//   std::cout << "labels = " << labels << std::endl;

//   assert(labels == number);

//   uint32_t rows;
//   imagesFile.read(reinterpret_cast<char*>(&rows), sizeof(rows));
//   swapb(rows);
//   std::cout << "rows = " << rows << std::endl;

//   uint32_t cols;
//   imagesFile.read(reinterpret_cast<char*>(&cols), sizeof(cols));
//   swapb(cols);
//   std::cout << "cols = " << cols << std::endl;

//   uint32_t pixels = rows * cols;

//   brainy::VectorTrainingSet truthTable;

//   for (uint32_t i = 0; i < 200; i++) {
//     unsigned char label;
//     labelsFile.read(reinterpret_cast<char*>(&label), sizeof(label));
//     std::cout << "label = " << (int)label << std::endl;

//     std::vector<double> output(digits, -1.0);
//     output[label] = 1.0;

//     std::vector<double> input;
//     for (uint32_t p = 0; p < pixels; p++) {
//       unsigned char pixel;
//       imagesFile.read(reinterpret_cast<char*>(&pixel), sizeof(pixel));

//       input.push_back(-1.0 + (pixel / 255.0 * 2.0));
//     }

//     truthTable.add(input, output);
//   }

//   brainy::Linear linear;
//   brainy::Tanh activation;

//   // Input layer with 2 neurons, linear activation and BIAS
//   brainy::Layer inputLayer(pixels, linear, true);
//   // Hidden layer with 2 neurons, tanh activation and BIAS
//   brainy::Layer hiddenLayer(128, activation, true);
//   // Hidden layer with 2 neurons, tanh activation and BIAS
//   brainy::Layer hiddenLayer2(32, activation, true);
//   // Output layer with 1 neuron, tanh activation
//   brainy::Layer outputLayer(digits, activation);

//   // Create network, and plug defined layers
//   brainy::FeedForward network;
//   network.addLayer(inputLayer);
//   network.addLayer(hiddenLayer);
//   network.addLayer(hiddenLayer2);
//   network.addLayer(outputLayer);
//   network.finalize();

//   brainy::BackPropagation trainer(network, truthTable);

//   brainy::Monitor monitor;
//   trainer.addPlugin(monitor);

//   brainy::SmartLearningRate slr;
//   trainer.addPlugin(slr);

//   brainy::SmartMomentum sm;
//   trainer.addPlugin(sm);

//   trainer.setGoal(0.01);
//   trainer.setLearningRate(0.7);
//   trainer.setMomentum(0.3);

//   // Use batch mode with batch size equal to training set
//   trainer.setBatchSize(100);

//   // Do training
//   trainer.train();

//   return 0;
// }

int main() { return 0; }
