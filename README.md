# Tipping Cup

Prop design by Dustin Grau

Originally created for use in Matilda the Musical, this device can also be used as a "possessed item" which will randomly move on its own.

## Operation

There are 2 primary modes for operation: wobbling and tipping. In the wobble mode, the servo will randomly move a short distance to make the prop tilt, return to normal, then wait a random time before repeating. In the tipping mode the servo will go through a full 180&deg; movement to cause the cup to tip over.

## Parts

* [SG90 9g Micro Servo](https://a.co/d/7Wwkuhb) - This is a good balance between size and torque needed
* [Arduino Nano](https://a.co/d/5m9NQ1E) - We need a controller which can take inputs and use PWM control
* [2.4GHz RC Remote](https://a.co/d/b6ze1Bv) - Any micro remote transmitter/receiver is viable for use
* [DC Buck Converter](https://a.co/d/8IMmLeA) - Needed to bring the 9V power source down to 5V
* [9V Battery Connector](https://a.co/d/fDPGKFS) - Easy connector to a standard 9V battery
* Plastic Cup - Ideally no more than 6" tall, designed around a 84mm/3.3" base

## Models

See the "stl" folder for the necessary brackets and components for housing the electronics. The main bracket is a 2-part design which can be screwed together using M3 screws. The servo foot can be attached with a small length of metal such as a bent paperclip.