
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class SmartFeederEnergyMonitor {
private:
    string feederName;
    double voltage;
    double current;
    double powerFactor;
    double operatingHours;
    double currentLimit;

public:
    SmartFeederEnergyMonitor(string name, double v, double i,
                              double pf, double hours,
                              double limit) {
        feederName = name;
        voltage = v;
        current = i;
        powerFactor = pf;
        operatingHours = hours;
        currentLimit = limit;
    }

    double calculatePower() {
        // Single-phase active power in watts
        return voltage * current * powerFactor;
    }

    double calculateEnergy() {
        // Energy in kWh
        return (calculatePower() * operatingHours) / 1000.0;
    }

    double calculateApparentPower() {
        return (voltage * current) / 1000.0;
    }

    string getFeederStatus() {
        if (voltage <= 0 || current < 0 ||
            powerFactor < 0 || powerFactor > 1 ||
            operatingHours < 0 || currentLimit <= 0) {
            return "INVALID INPUT";
        }

        if (current > currentLimit) {
            return "OVERLOAD";
        } else {
            return "NORMAL";
        }
    }

    void displayReport() {
        cout << fixed << setprecision(2);

        cout << "\n===== Smart Feeder Energy Monitor =====\n";
        cout << "Feeder Name       : " << feederName << "\n";
        cout << "Voltage           : " << voltage << " V\n";
        cout << "Current           : " << current << " A\n";
        cout << "Power Factor      : " << powerFactor << "\n";
        cout << "Operating Hours   : " << operatingHours << " h\n";
        cout << "Active Power      : "
             << calculatePower() / 1000.0 << " kW\n";
        cout << "Apparent Power    : "
             << calculateApparentPower() << " kVA\n";
        cout << "Energy Consumption: "
             << calculateEnergy() << " kWh\n";
        cout << "Feeder Status     : " << getFeederStatus() << "\n";

        if (getFeederStatus() == "OVERLOAD") {
            cout << "ALERT: Current exceeds the feeder limit!\n";
        } else if (getFeederStatus() == "NORMAL") {
            cout << "Feeder is operating within its current limit.\n";
        }
    }
};

int main() {
    // Example values for a single-phase feeder
    SmartFeederEnergyMonitor feeder(
        "Feeder-1",
        230,    // Voltage in V
        18,     // Current in A
        0.90,   // Power factor
        8,      // Operating hours
        20      // Maximum current in A
    );

    feeder.displayReport();

    return 0;
}
