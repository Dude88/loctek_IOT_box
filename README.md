# loctek_IOT_box
IOT-Box for loctek standing desks

Because of lack of time i work mostly on weekends on this project.
I look forward for help, support and suggestions for improvement.

Situation: 
Got a standing desk(finally). but to see how often i use it, i want to connect it to my smarthome.
After nearly 2 days the projekt ran out of controll and now the plan is a non-destructive IOT-Box.



Build on CB28M1B(IB) and HS13A-1

should be compatible with:
1. Control Panels
   - HS13A-1 - 6 button
   - HS13B-1 - 6 button with USB
   
   only 3 memorys, reminder not controllable (at the moment)
   - HS11A-1 - 5 button with reminder
   - HS11B-1 - 5 button with reminder and USB
   - HS05A-1 - 5 button
   - HS06A-1 - 5 button
   - HS01B-1 - 5 button with reminder
   
   not working cause no memory funktion (at the moment)
   - HS04A-1 - 2 button
   - HS03A-1 - 2 button
   - HS02A-1 - 2 button

2. Control Box
   recommended:
   - CB28M1B (IB) - with 2 serial ports
   - CB38M2A (IB) - with 2 serial ports
   - CB38M3A (IB) - with 2 serial ports

   actually only works without control panel:
   - CB28M1B
   - CB38M2A
   - CB38M3A


I bought my desk at https://flexispot.com/. But no guarantee that they sell only loctek.


Planned/Done  functions:

- [x] move desk to memory position
- [x] controll over mqtt
- [x] controll with alexa
- [x] work as independent "Control Panel"
- [ ] controll memory 
- [ ] provide actual height via mqtt
- [ ] turn reminder on/off (need control Panel with "A" button to get information)
- [ ] start in AP mode, provide webpage for WIFI, MQTT and Alexa settings
- [ ] desing also as a "man in the middle" device

- [ ] maybe Apple homekit
