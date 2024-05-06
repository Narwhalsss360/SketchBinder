//Include for the sketch only, not for libraries.
#include <SketchBinder.h>

#define BAUDRATE 115200

//My library function
#include <SketchBoundLibrary.h>
void millis_pinter() {
    Serial.print("Pre loop milliseconds: ");
    Serial.println(millis());
}
bool successfullyBounded = addSketchBinding(bind_loop, &invokable_get(millis_pinter));

void setup() {
    Serial.begin(BAUDRATE);
}

void loop() {
    //Do nothing...
}