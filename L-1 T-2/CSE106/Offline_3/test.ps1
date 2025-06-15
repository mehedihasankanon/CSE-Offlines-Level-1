# Compile the queue implementations and main program
g++ -std=c++11 main.cpp arrayqueue.cpp listqueue.cpp -o main
# g++ -std=c++11 randomtester.cpp arrayqueue.cpp listqueue.cpp -o rand

# Run the main program
./main
# ./rand 1000