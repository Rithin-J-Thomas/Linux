#!/bin/bash

g++ -g main.cpp cpu.cpp shared.cpp proc.cpp network.cpp myFunctions.cpp -o run_code -lraylib -lm -lpthread -ldl -lrt -lX11  && ./run_code
