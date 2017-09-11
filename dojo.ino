/* Display ClassDojo points on a 7 segment LED display
 */
 
SYSTEM_THREAD(ENABLED);

#include <FiniteStateMachine.h>
#include <Adafruit_LEDBackpack_RK.h>

#define StudentName "Maxim_Vanier"
unsigned dojoPoints = 0;

Adafruit_7segment display = Adafruit_7segment();
const auto I2CAddress = 0x70;

const auto Digits = 4;
#define countof(x) (sizeof(x) / sizeof((x)[0]))

State WaitForConnection(waitForConnection);
State WaitForData(waitForData);
State UpdatePoints(updatePoints);
State Idle(idle);
State Disconnected(disconnected);

FSM stateMachine = FSM(WaitForConnection);

void setup() {
    display.begin(I2CAddress);
    Particle.subscribe("dojoPoints/" StudentName, receivePoints, MY_DEVICES);
}

void loop() {
    stateMachine.update();
}

void waitForConnection() {
    displaySpinner();
    
    if (Particle.connected()) {
        fetchDojoPoints();
        stateMachine.transitionTo(WaitForData);
    }
}

void waitForData() {
    displaySpinner();
}

void updatePoints() {
    const auto UpdateSpinnerDuration = 2000;
    if (stateMachine.timeInCurrentState() < UpdateSpinnerDuration) {
        displaySpinner();
    } else {
        displayPoints();
        stateMachine.transitionTo(Idle);
    }
}

void idle() {
    if (!Particle.connected()) {
        stateMachine.transitionTo(Disconnected);
    }
}

void disconnected() {
    if (Particle.connected()) {
        fetchDojoPoints();
        stateMachine.transitionTo(Idle);
    }
}

void fetchDojoPoints() {
    Particle.publish("fetchDojoPoints", PRIVATE);
}

void receivePoints(const char *event, const char *data) {
    dojoPoints = String(data).toInt();
    stateMachine.transitionTo(UpdatePoints);
}

void displayPoints() {
    display.print(dojoPoints);
    display.writeDisplay();
}

void displaySpinner() {
    const auto SpinnerInterval = 100;
    static auto lastTime = millis();
    static auto pos = 0;
    const uint8_t spinnerBitmasks[] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20 };
    
    if (millis() - lastTime < SpinnerInterval) {
        return;
    }
    lastTime = millis();
    
    for (auto i = 0; i < Digits + 1; i++) {
        // Skip the colon
        if (i == 2) {
            i++;
        }
        display.writeDigitRaw(i, spinnerBitmasks[pos]);
    }
    display.writeDisplay();
    
    pos++;
    if (pos >= countof(spinnerBitmasks)) {
        pos = 0;
    }
}
