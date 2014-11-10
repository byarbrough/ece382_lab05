ece382_lab05
============

[Interrupts - "Remote Control Decoding"](http://ece382.com/labs/lab5/index.html)

##Day 1

![alt text](https://raw.githubusercontent.com/byarbrough/ece382_lab05/master/irWave.gif "IR Waveform")


Here is a picture of my remote.

![alt text](https://raw.githubusercontent.com/byarbrough/ece382_lab05/master/remote.jpg "My remote!")

Pushing certain buttons produced a waveform such as this one.

![alt text](https://raw.githubusercontent.com/byarbrough/ece382_lab05/master/remoteWave.jpg "UP Waveform")

This is 32 (well, really more... I will get to that) packets of information that are represented by short and long HIGH pulses with relatively equal LOW times. Using the cursors. As indicated on the phto, the long pulses were subsiquently treated as '1' while the short pulses were treated as '0'. Following along the waveform generated the following results for six of the buttons. These results were used to produce the lookup table found in the header file.

| Button |               Code               |    Hex   |
|--------|:--------------------------------:|:--------:|
| UP     | 00001010111101010000111011110001 | 0AF50EF1 |
| DOWN   | 00001010111101011000111001110001 | 0AF58E71 |
| LEFT   | 00001010111101011100111000110001 | 0AF5CE31 |
| RIGHT  | 00001010111101010100111010110001 | 0AF54EB1 |
| CH +   | 00001010111101011001100001100111 | 0AF59867 |
| CH -   | 00001010111101010001100011100111 | 0AF518E7 |
| MUTE   | 00001010111101011101000000101111 | 0AF5D02F |
| EXIT   | 00001010111101010000100011110111 | 0AF508F7 |


In addition to the somewhat arbatrary "short and long" pulses, I took the time to make measurements of how long each pulse was - invevitably there was some deviation.

|            Pulse            | Average Duration (ms) | StdDev | Timer A Min | Timer A Max |
|:---------------------------:|:---------------------:|:------:|:-----------:|:-----------:|
| Start   logic 0 half-pulse  |          8.90         |  0.03  |    70966    |    71379    |
| Start   logic 1 half-pulse  |          4.45         |  0.01  |    35462    |    35657    |
| Data 1   logic 0 half-pulse |          0.48         |  0.03  |     3658    |     4061    |
| Data 1   logic 1 half-pulse |          1.61         |  0.02  |    12720    |    13040    |
| Data 0   logic 0 half-pulse |          0.64         |  0.02  |     4920    |     5266    |
| Data 0   logic 1 half-pulse |          0.64         |  0.02  |     4920    |     5266    |
| Stop   logic 0 half-pulse   |          0.59         |  0.02  |     4573    |     4935    |
| Stop   logic 1 half-pulse   |        infinite       |  0.00  |   infinite  |   infinite  |

Analysis of the above table shows that the Data 0's are almost exactly the same length, can so effectively all be treated the same.

####The Start Bit
Remember how I said that there were _32_ pulses? Well, that isn't entirely true. Look at this logic analyzer photo:

![alt text](https://raw.githubusercontent.com/byarbrough/ece382_lab05/master/startBit.jpg "Start Bit")

To the left of the dotted line is the HIGH value that the pin stays at since it is pull up. Then there is the start zero and the Start Bit (labled). This matter because it informs the chip that there is an incoming packet, but I delt with it by simply ignoring the first two values of the array. This means that the code only processes _packetData[2]_ to _packetData[33]_. This ensures that only the intended signal is being compared.

##Day 2

Day 2 was a fine example of "finding a better way." There was no reason to mess around with all of the measurements that I took on Day 1. Although they helped me to understand how the remote functioned, for actual coding purposes, they would have been a pain to work with. Running the given code generated.
