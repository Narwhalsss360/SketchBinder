//Include for the sketch only, not for libraries.
#include <AutoBind.h>

#define BAUDRATE 115200

//My library function
#if __has_include(<SketchBoundLibrary.h>)
#include <SketchBoundLibrary.h>
#define MyLibrary_Bindable
#endif

void millis_printer() {
    Serial.print("Pre loop milliseconds: ");
    Serial.println(millis());
}

//If user include SketchBinder
#ifdef MyLibrary_Bindable
Function<void> millis_printer_function = Function<void>(millis_printer);
const bool successfullyBounded = addSketchBinding(bind_loop, &millis_printer_function);
#else
const bool successfullyBounded = false;
#endif

void setup() {
    Serial.begin(BAUDRATE);
}

void loop() {
    //Do nothing...
}
