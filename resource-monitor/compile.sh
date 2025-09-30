#!/bin/bash

g++ -g main.cpp cpu.cpp shared.cpp proc.cpp network.cpp -o run_code  &&  ./run_code
