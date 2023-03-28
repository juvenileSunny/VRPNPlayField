#include <iostream>
#include <fstream>
#include "vrpn_Tracker.h"
#include "vrpn_Button.h"
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;

void VRPN_CALLBACK handle_tracker_position(void* userData, const vrpn_TRACKERCB t)
{
    XMLDocument doc;
    XMLNode* rootNode = doc.NewElement("tracker_position");
    doc.InsertFirstChild(rootNode);
    XMLElement* sensorNode = doc.NewElement("sensor");
    sensorNode->SetText(t.sensor);
    rootNode->InsertEndChild(sensorNode);
    XMLElement* xNode = doc.NewElement("x");
    xNode->SetText(t.pos[0]);
    rootNode->InsertEndChild(xNode);
    XMLElement* yNode = doc.NewElement("y");
    yNode->SetText(t.pos[1]);
    rootNode->InsertEndChild(yNode);
    XMLElement* zNode = doc.NewElement("z");
    zNode->SetText(t.pos[2]);
    rootNode->InsertEndChild(zNode);
    doc.SaveFile("tracker_positions.xml");
}

void VRPN_CALLBACK handle_button_press(void* userData, const vrpn_BUTTONCB b)
{
    XMLDocument doc;
    XMLNode* rootNode = doc.NewElement("button_press");
    doc.InsertFirstChild(rootNode);
    XMLElement* buttonNode = doc.NewElement("button");
    buttonNode->SetText(b.button);
    rootNode->InsertEndChild(buttonNode);
    XMLElement* stateNode = doc.NewElement("state");
    stateNode->SetText(b.state == 1 ? "pressed" : "released");
    rootNode->InsertEndChild(stateNode);
    doc.SaveFile("button_presses.xml");
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
        vrpn_SleepMsecs(10);
    }

    return 0;
}
