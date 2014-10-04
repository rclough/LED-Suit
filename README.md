LED SUIT
========

Here is the code I used to program my LED suit at Burning Man 2014. It's designed for use with an Arduino UNO, running [FastLED](https://github.com/FastLED/FastLED) version 2.1 on ws2812b strips.

The Suit
--------
The suit consisted of 2 parts: a jacket, and a pair of pants. The jacket and pants each had their own seperate arduino UNO controller and 6600mah LiPo battery.

The Jacket had 4 sections of LEDs that was split in 2 halves and generally made to be symmetrical. There was one strip that lined the lapel and the bottom of the jacket (74 LEDs), and another that lined the arm (39 LEDs). Both with separate strips on either side, totalling 226 LEDs.


The pants had 2 strips of LEDs that madde 4 horizontal rings on each leg. Each ring had 30 LEDs, totalling 240 LEDs.

Each controller had animations that ran on a timer, but could also be manually switched using a push button. 

Here's some videos of the suit in action:

* [Slow Motion](http://videos-c-7.ak.instagram.com/hphotos-ak-xaf1/10622491_271188629734287_1681579773_n.mp4)
* [Slow sparse animation](http://videos-f-18.ak.instagram.com/hphotos-ak-xaf1/10627084_1468371203418038_1837724756_n.mp4)
* [Initial version of Rainbow Seizure/full light view of suit](http://videos-e-3.ak.instagram.com/hphotos-ak-xaf1/10613671_539303312836723_948993920_n.mp4)

The Code
--------

The code was designed so that the same set of animations can be compiled for both the jacket and pants controllers, so that they can have matching animations. This switch is done at the top of the `includes.h` file so that the arduino substitutes the appropriate variables.

Animations inherit from a general animation "Interface". Initially animations were only responsible for set up/breakdown, and drawing a single frame, but for sake of my own ease, I had them also handle their own delays.

A number of compromises are found in the code that are a result of me doing last minute programming and debugging for the burn. Maybe some day i'll come back with fixes and more animations if I decide to wear the suit to a local party.

Other Notes
-----------

The suit fared fairly well at the burn. I generally wore the suit all night ~4-6 hours) and the batteries never tan out, so I'm not sure what the life of the suit actually is. The only major issue is when one of the heads of my jumper wires snapped, but I replaced it fairly easily. This was my first major micro controller project, so a lot of the wiring was very messy, and in the cuture I have alot of ideas to improve the wiring to make it more durable, but the suit was just fine.

The controller and batteries were held in elastic pockets I sewed into the inside of the jacket and pants.

There exists an error with the changing of animations based on time, and I strongly believe it has to do with an integer overflow, but I didn't figure it out in time for the burn, and mostly managed my animations manually with my push button.
