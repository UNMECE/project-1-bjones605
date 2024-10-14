#include <iostream>
#include "cap.h"

void setupCapacitor(Capacitor &cap, int numSteps, double capValue);
void simulateConstantVoltage(Capacitor &cap, int numSteps, double deltaTime, double initialVoltage, double resistance);
void simulateConstantCurrent(Capacitor &cap, int numSteps, double deltaTime, double current);
void printValues(double time, double voltage, double current);


int main() {
    const double deltaTime = 1e-10;
    const double finalTime = 5e-6;
    int steps = finalTime / deltaTime;
    const double resistance = 1000;        // 1 kΩ
    const double capacitance = 100e-12;    // 100 pF
    const double constantCurrent = 1e-2;   // 10 mA
    const double initialVoltage = 10;      // 10 V

    Capacitor cap;
    setupCapacitor(cap, steps, capacitance);
    std::cout << "Constant Current Supply Simulation:\n";
    simulateConstantCurrent(cap, steps, deltaTime, constantCurrent);
    std::cout << "\nConstant Voltage Supply Simulation:\n";
    simulateConstantVoltage(cap, steps, deltaTime, initialVoltage, resistance);

    delete[] cap.time;
    delete[] cap.voltage;
    delete[] cap.current;

    return 0;
}

void setupCapacitor(Capacitor &cap, int numSteps, double capValue) {
    cap.time = new double[numSteps];
    cap.voltage = new double[numSteps];
    cap.current = new double[numSteps];
    cap.capacitance = capValue;
}

void printValues(double time, double voltage, double current) {
    std::cout << "Time: " << time << " s, Voltage: " << voltage << " V, Current: " << current << " A" << std::endl;
}

void simulateConstantCurrent(Capacitor &cap, int numSteps, double deltaTime, double current) {
    cap.voltage[0] = 10;

    for (int i = 0; i < numSteps; ++i) {
        cap.time[i] = i * deltaTime;
        cap.current[i] = current;

        if (i > 0) {
            cap.voltage[i] = cap.voltage[i - 1] + cap.current[i - 1] * deltaTime / cap.capacitance;
        }

        if (i % 200 == 0) {
            printValues(cap.time[i], cap.voltage[i], cap.current[i]);
        }
    }
}

void simulateConstantVoltage(Capacitor &cap, int numSteps, double deltaTime, double initialVoltage, double resistance) {
    cap.current[0] = initialVoltage / resistance;
    cap.voltage[0] = initialVoltage;

    for (int i = 0; i < numSteps; ++i) {
        cap.time[i] = i * deltaTime;

        if (i > 0) {
            cap.current[i] = cap.current[i - 1] - (cap.current[i - 1] * deltaTime) / (resistance * cap.capacitance);
            cap.voltage[i] = cap.voltage[i - 1] + cap.current[i - 1] * deltaTime / cap.capacitance;
        }

        if (i % 200 == 0) {
            printValues(cap.time[i], cap.voltage[i], cap.current[i]);
        }
    }
}