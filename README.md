# evo64picoromswitch
Use a RPi Pico microcontroller as a WiFi ReProm controller on the Commodore Evo 64 Motherboard

I need to start out by saying I am not a programmer, coder or anything of the like.  I wouldn't even consider myself a script kiddy. Before this project I've never used a Pico or written anything in C.  I have the HTML skills of a 4 year old.

That being said, this thing works pretty well!

I had originally written this thing in MicroPython but it ran like ass.  If you clicked on too many things too quickly it would crash.  Hell, every now and then it would crash on boot with nothing even connected to the GPIO pins.  The web interface was also very slow.  It's probably my shitty coding that led to some of that bad behavior but even a poorly written compiled binary would probably be faster than Python.  IDK my ass from a hole in the ground, but MicroPython seems to suck for performance.

So I rewrote this version in C using the Arduino IDE with the Raspberry Pi Pico/RP2040 board manager package (v3.1.1 by Earle F. Philhower, III).  This C version is much more responsive and has been rock solid.  I borrowed the web server code from an ESP32 tutorial on randomnerdtutorials.com.  It basically just worked, didn't change much of anything on the web side.

This is setup to work with 29F040 ROM chip (512Kb x8) and should work with any other 512k chip as-is.  If you use a 256k chip you just wont have access to the upper end of the cart images.  If you want to use a larger ROM then you'll have to add 3 more GPIO's to the code but it should be pretty cookier cutter easy to do so.

All the pin names in the code are based on the names silk screened on the Evo motherboard, it should be pretty self explanatory on how to wire things up.  Remember, all of these lines are ACTIVE LOW from the QaPla FPGA.  So OFF is pin high on the Pico and ON is when you pull the pin low to 0v.

All the use cases are written in the same order the ROM should be written in.  Check out the Evo ROM documentation for more details.  The high/low configs came right off their spreadsheet.

DISCLAIMER:
I just wired this bastard directly in and the Pico pins are always outputs driven high or low.  No level shifters or floating inputs when the line should be high or anything like that.  The voltages on the PLA side sit around 3.5 and the Pico high is 3.3.  So honestly the way I did this probably isn't 100% sane but I've been abusing this thing for about a week now and nothings blown up.  The 3.5v on the PLA is within the Pico's 3.6v tolerance and the line settles at 3.3 when the Pico is powered on.  Neither the PLA or the RP2040 get very warm so I think it'll probably be ok.  I suppose the Pico is sinking that .2v somewhere so if anything's going to blow up, it's probably the Pico and not the Evo PLA so I'm good with the risk.

DO NOT USE THIS ON A STANDARD 5v C64 WITHOUT A LEVEL SHIFTER ON THE GPIO LINES.  YOU WILL INCENERATE YOUR PI!  NO ONE LIKES BURNT PI!

In the future I'd like to add filesystem support (if I ever figure it out) in order to use WiFi manager so that you don't have to hard code SSID and password at compile time and to remember the state of the GPIO pins through reboots.  In all honesty, I really don't know what the hell I'm doing so it would be great if someone forked this thing and made it more useful.  I'm sure I could figure it out in a matter of weeks, while someone who actually knows what they're doing could probably get it done in an hour or less.

Anyway, good luck, have fun and go wire something directly into something else whether it likes it or not!
73
