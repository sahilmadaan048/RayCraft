#!/bin/bash

echo "🔧 Compiling..."
g++ main.cpp -o main || exit 1

echo "🎯 Running ray tracer..."
./main > output.ppm || exit 1

echo "🖼️ Opening in IrfanView..."
"/c/Program Files/IrfanView/i_view64.exe" output.ppm