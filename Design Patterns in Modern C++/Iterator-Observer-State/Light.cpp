#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
using namespace std;

//Implementation of "Iterator" Design Pattern to simulate the passage of time
class TimeIterator {
public:
    TimeIterator(int startHour) : currentHour(startHour) {}

    int next() {
        std::this_thread::sleep_for(std::chrono::seconds(3));  // Simulate 1 hour passing every 3 seconds
        currentHour = (currentHour + 1) % 24;  // Wrap around after 23 hours
        return currentHour;
    }

private:
    int currentHour;
};

//Observer Interface
class Observer {
public:
    virtual void update(int hour) = 0;
};

//Implementation of "State" Design Pattern
class LightState {
public:
    virtual void handle() = 0;
};

//Concrete state of Lights ON
class OnState : public LightState {
public:
    void handle() override {
        cout << "Lights are ON." << endl;
    }
};

//Concrete state of Lights OFF
class OffState : public LightState {
public:
    void handle() override {
        cout << "Lights are OFF." << endl;
    }
};

// Lights: Context class that maintains an instance of a LightState
class Lights {
public:
    Lights() : state(new OffState()) {}

    void setState(LightState* newState) {
        delete state;  // Clean up the old state
        state = newState;
        state->handle();
    }

    ~Lights() {
        delete state;
    }

private:
    LightState* state;
};

// Sensor: Implements the Observer Design Pattern to watch the time and change light states
class Sensor : public Observer {
public:
    Sensor(Lights* lights) : lights(lights) {}

    void update(int hour) override {
        if (hour == 19) {  // 7 PM
            cout << "It's 7 PM. Turning lights ON." << endl;
            lights->setState(new OnState());
        } else if (hour == 22) {  //This is the time at which the state would change
            cout << "It's 10 PM. Turning lights OFF." << endl;
            lights->setState(new OffState());
        }
    }

private:
    Lights* lights;
};

int main() {
    int startHour = 18;  //Program begins at 6pm, can modify this value, set to 6pm for demonstration

    TimeIterator timeIterator(startHour);
    Lights lights;
    Sensor sensor(&lights);

    while (true) {
        int currentHour = timeIterator.next();
        cout << "Current time: " << (currentHour % 12 == 0 ? 12 : currentHour % 12) 
             << (currentHour < 12 ? " AM" : " PM") << endl;
        sensor.update(currentHour);

        if (currentHour == 22) {  // Stop at 10 PM
            break;
        }
    }

    return 0;
}
