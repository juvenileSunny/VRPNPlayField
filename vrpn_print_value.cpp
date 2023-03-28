#include <iostream>
#include "vrpn_Tracker.h"
#include "vrpn_Button.h"

using namespace std;

void VRPN_CALLBACK handle_tracker_position(void* userData, const vrpn_TRACKERCB t)
{
    cout << t.sensor << " " << t.pos[0] << " " << t.pos[1] << " " << t.pos[2] << endl;
}

void VRPN_CALLBACK handle_button_press(void* userData, const vrpn_BUTTONCB b)
{
    cout << b.button << " " << (b.state == 1 ? "pressed" : "released") << endl;
}

int main()
{
    vrpn_Tracker_Remote* tracker = new vrpn_Tracker_Remote("Tracker0@localhost");
    tracker->register_change_handler(NULL, handle_tracker_position);

    vrpn_Button_Remote* button = new vrpn_Button_Remote("Button0@localhost");
    button->register_change_handler(NULL, handle_button_press);

    while (true)
    {
        tracker->mainloop();
        button->mainloop();
        // Sleep for a short period to avoid hogging the CPU
        vrpn_SleepMsecs(10);
    }

    return 0;
}
