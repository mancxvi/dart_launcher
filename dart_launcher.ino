/* William Oberndorfer
 * Arduino Dart Launcher
 *
 * A silly program for shooting darts using solenoid air valves
 */

#define BUTTON_PIN 2
#define TONE_PIN 3
#define DART_1 7
#define DART_2 8
#define DART_3 9
#define FIRE_INDICATOR 10

#define NOTE_E7 2638

volatile enum states { INIT, WAIT, FIRE } state;

void handle_button();
void launch();

unsigned long current;
unsigned long previous;

void setup()
{
    pinMode(BUTTON_PIN, INPUT);
    pinMode(TONE_PIN, OUTPUT);
    pinMode(DART_1, OUTPUT);
    pinMode(DART_2, OUTPUT);
    pinMode(DART_3, OUTPUT);
    pinMode(FIRE_INDICATOR, OUTPUT);
    digitalWrite(TONE_PIN, LOW);
    digitalWrite(DART_1, LOW);
    digitalWrite(DART_2, LOW);
    digitalWrite(DART_3, LOW);
    digitalWrite(FIRE_INDICATOR, LOW);
    attachInterrupt(digitalPinToInterrupt(BUTTON_PIN),
                    handle_button, CHANGE);
}

void loop()
{
    switch (state) {
    case INIT:
        state = WAIT;
        break;
    case WAIT:
        digitalWrite(TONE_PIN, LOW);
        digitalWrite(DART_1, LOW);
        digitalWrite(DART_2, LOW);
        digitalWrite(DART_3, LOW);
        break;
    case FIRE:
        launch();
        state = WAIT;
        break;
    default:
        break;
    }
}

void handle_button()
{
    if (digitalRead(BUTTON_PIN) && state == WAIT) {
        state = FIRE;
    }
    else {
        state = WAIT;
    }
}

void launch()
{
    digitalWrite(FIRE_INDICATOR, HIGH);
    tone(TONE_PIN, NOTE_E7, 100);
    delay(100);
    tone(TONE_PIN, NOTE_E7, 100);
    delay(100);
    digitalWrite(DART_1, HIGH);
    delay(30);
    digitalWrite(DART_1, LOW);
    delay(2000);
    digitalWrite(DART_2, HIGH);
    delay(30);
    digitalWrite(DART_2, LOW);
    delay(2000);
    digitalWrite(DART_3, HIGH);
    delay(30);
    digitalWrite(DART_3, LOW);
    digitalWrite(FIRE_INDICATOR, LOW);
}