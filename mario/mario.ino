int inPin = 2;
int outPin = 12;

double TIME_0 = (70.0 / 60) * 1000;
double TIME_5 = (63.0 / 60) * 1000;
double TIME_10 = (57.5 / 60) * 1000;
double TIME_15 = (54.0 / 60) * 1000;
double TIME_20 = (50.0 / 60) * 1000;
double TIME_25 = (46.5 / 60) * 1000;
double TIME_30 = (44.0 / 60) * 1000;
double TIME_35 = (41.0 / 60) * 1000;
double TIME_40 = (39.0 / 60) * 1000;
double TIME_45 = (36.5 / 60) * 1000;
double TIME_50 = (35.15 / 60) * 1000;
double TIMINGS[] = {TIME_0,TIME_5,TIME_10,TIME_15,TIME_20,TIME_25,TIME_30,TIME_35,TIME_40,TIME_45,TIME_50};

int DURATION = 100;

int reading;
int count = 0;
bool running = false;
long start = 0;
long last = 0;

void setup() {
    Serial.begin(9600);
    pinMode(inPin, INPUT_PULLUP);
    pinMode(outPin, OUTPUT);
}

void loop() {
    long time = millis();
    reading = digitalRead(inPin);

    if (!running && reading == HIGH) {
        running = true;
        start = millis();
        count = 0;
    } else if (reading == LOW) {
        running = false;
    }

    if (running) {
        long target = 0;
        for (int i=0; (i - count) && (i < 50); i++) {
            target += TIMINGS[(int)floor(i/5)];
        }
        if (count >= 50){
            target += (count - 50) * TIME_50;
        }

        if (time - start > target) {
            digitalWrite(outPin, HIGH);
            count++;
            last = time;
            Serial.print('Jump: ');
            Serial.println(count);
            if (count <= 50 && count % 5 == 0) {
                Serial.println('Faster!');
            }
        } else {
            if (time > last + DURATION) {
                digitalWrite(outPin, LOW);
            }
        }
    } else {
        digitalWrite(outPin, LOW);
    }
}
