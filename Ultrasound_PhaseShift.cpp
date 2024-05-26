#include <iostream>
#include <vector>
#include <cmath>
#include <complex>

const int SAMPLE_RATE = 48000; // 48 kHz
const double FREQUENCY = 23000.0; // 23 kHz
const double SPEED_OF_SOUND = 343.0; // Speed of sound in air at 20°C (343 m/s)

std::vector<double> generateContinuousWave(double frequency, double duration, int sampleRate) {
    int numSamples = static_cast<int>(duration * sampleRate);
    std::vector<double> signal(numSamples);
    for (int i = 0; i < numSamples; ++i) {
        signal[i] = std::sin(2 * M_PI * frequency * i / sampleRate);
    }
    return signal;
}

std::vector<std::complex<double>> measurePhaseShift(const std::vector<double>& transmitted, const std::vector<double>& received) {
    int size = transmitted.size();
    std::vector<std::complex<double>> phaseShifts(size);
    for (int i = 0; i < size; ++i) {
        std::complex<double> tx(transmitted[i], 0);
        std::complex<double> rx(received[i], 0);
        phaseShifts[i] = std::arg(rx * std::conj(tx));
    }
    return phaseShifts;
}

double calculateDistanceChange(const std::vector<std::complex<double>>& phaseShifts, double wavelength) {
    double totalPhaseShift = 0.0;
    for (const auto& phaseShift : phaseShifts) {
        totalPhaseShift += phaseShift;
    }
    double averagePhaseShift = totalPhaseShift / phaseShifts.size();
    return (averagePhaseShift / (2 * M_PI)) * wavelength;
}

int main() {
    double duration = 0.01; // 10 ms
    std::vector<double> transmittedSignal = generateContinuousWave(FREQUENCY, duration, SAMPLE_RATE);
    
    // Simulate received signal (this should be replaced with actual recorded data)
    std::vector<double> receivedSignal = transmittedSignal; // Placeholder for actual received signal
    
    // Measure phase shifts
    std::vector<std::complex<double>> phaseShifts = measurePhaseShift(transmittedSignal, receivedSignal);
    
    // Calculate distance change
    double wavelength = SPEED_OF_SOUND / FREQUENCY;
    double distanceChange = calculateDistanceChange(phaseShifts, wavelength);
    
    std::cout << "Distance change: " << distanceChange << " meters" << std::endl;
    
    return 0;
}
