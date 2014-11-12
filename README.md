ece382_lab05
============

[Interrupts - "Remote Control Decoding"](http://ece382.com/labs/lab5/index.html)

The objective of this lab is to process an InfraRed remote signal from a TV remote to manipulate the MSP430; this is a building block to controlling a robot.

##Day 1
The first step to this lab was understanding the incoming IR waveform from the remote. Like all logic waveforms, it looked something like this:

![alt text](https://raw.githubusercontent.com/byarbrough/ece382_lab05/master/irWave.gif "IR Waveform")

The line labels correspond to lines within [star5.c](http://ece382.com/labs/lab5/start5.c) which generate times for different parts of the waveform.
As we will see, the most important part of this is the time that the signal is HIGH, as indicated by the label _line 37_.

####My Remote
Here is a picture of my remote.

![alt text](https://raw.githubusercontent.com/byarbrough/ece382_lab05/master/remote.jpg "My remote!")

Pushing certain buttons produced a waveform such as this one. (Read from 2.6, trigger on falling edge, 100 uS measurements)

![alt text](https://raw.githubusercontent.com/byarbrough/ece382_lab05/master/remoteWave.jpg "UP Waveform")

This shows 32 (well, really more... I will get to that) packets of information that are represented by short and long HIGH pulses with relatively equal LOW times. As indicated on the phto, the long pulses were subsiquently treated as '1' while the short pulses were treated as '0'. Following along the waveform generated the following results for six of the buttons. These results were used to produce the lookup table found in the header file.

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


In addition to the somewhat arbatrary "short and long" pulses, I took the time to make cursor measurements of how long each pulse was - invevitably there was some deviation.

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

Analysis of the above table shows that the Data 0's are almost exactly the same length, so can effectively all be treated the same. Notice that the time HIGH for a logic one is four times longer then the logic zero.

####The Start Bit
Remember how I said that there were _32_ pulses? Well, that isn't entirely true. Look at this logic analyzer photo:

![alt text](https://raw.githubusercontent.com/byarbrough/ece382_lab05/master/startBit.jpg "Start Bit")

To the left of the dotted line is the HIGH value that the pin stays at since it is pull up. Then there is the start zero and the Start Bit (labled). This matters because it informs the chip that there is an incoming packet, but I delt with it by simply ignoring the first two values of the array. This means that the code only processes _packetData[2]_ to _packetData[33]_. This ensures that only the intended signal is being compared to the defined value given to each button.

####Random Questions
The lab posed two initial questions. Seeting TACCR0 to 0xFFFF results in a Timer A rollover of 66 ms. Each timer count lasts for 8 clock cycles, or approximately 1 microsecond. 

##Day 2 - Required Functionality

Day 2 was a fine example of "finding a better way." There was no reason to mess around with all of the measurements that I took on Day 1. Although they helped me to understand how the remote functioned, for actual coding purposes, they would have been a pain to work with. Running the sampel program produced a series of pulse lengths that did not exactly match what I had expected. Instead of reconfiguring everything, I noticed that what should have been a '0' usually generated a pulse in the 400-500's while a '1' was well over 1600. I decided that it would be much easier to simply say that < 1000 was a '0' while the opposite was a '1'. This both saved me time and made the code more robust; I did not have to worry about gorss outliers or worry about taking new measurements for different remotes (see [Day Extra](https://github.com/byarbrough/ece382_lab05/blob/master/README.md#day-extra)). 

The next challenge then was to convert the _packetData_ array to a useful binary number. I had to do this because it is illegal to compare an entire array to a 32 bit integer - which is how all of the buttons are defined in the header. The for loop in [lines 44-60](https://github.com/byarbrough/ece382_lab05/blob/master/main5.c#L44-L60) completes this operation.
It accomplishes this by cerating a result variable and then beggining with the MSB sets or clears the bit accordingly. This is done with some pretty sweet XOR and AND manipulations; it also takes advantage of C's bit rotate operand to advance the setter bit easily.
A screenshot of this operation is shown below:

![alt text](https://raw.githubusercontent.com/byarbrough/ece382_lab05/master/settingBits.PNG "Debugger")

This Debugger view shows the processing of the array. the highleighted "1947" is the pulse length stored in packetData[]. Because it is greater than the threshold, the third bit in _result_ was ORed with _setter_, which was then rotated. This process is repeated for each element. (Again, the first two elements in packetData[] are ignored because I am not particularly concerend with the start bit).

###Where the problems begin

Up to this poing, there were almost no issues with the program. When I thought I had it ready to go, I hit Debug, pressed a button on the remote, and the light turned on: success!!! My elation was... elated.

But then, I hit the button again. Because I was using the XOR operand, the LED should have toggled to OFF. But it didn't. My elation was... deflated.

And so began my long, miserable process to debug. Although in the words of Captain Tirmble, it "builds character," it mostly just got me laughed at by my girlfirend when I showed her that there was apparently no rhyme or reaseon to what value _packetIndex_ felt like displaying when I tracked it in the Expressions tab. Of course, this didn't happen until I had almost figured it out.
Prior to this I realized that on the second press of a button the array was populated with random values - definitely not coorelating to any button press. I summized from this that the remote was outputting some junk after the signal that I cared about. To fix this I looked at the [handy picture](http://ece382.com/labs/lab5/schematic.jpg) provided by my insturctor and realized that I needed to employ Timer A to interrupt and wait fot the junk to pass. I verified this with breakpoints; when I manually paused the program it toggled the LED just fine. But after I made the changes that I thought would work, it still didn't!

This is where the laughing girlfirend came in. On the bright side, knowing that the index wasn't being reset showed me that the Timer A interrupt wasn't working. I verifed this by inserting a breakpoing withing the interrupt; nothing. Of course, I didn't know exactly _why_ Timer A wasn't nterrupting like it was supposed to. Comparing my code to the given code showed that I hadn't messed anything up. ****BUT**** when I looked at my code compared to the in class example, I realized that there was not _TAIE_ with I was enabling Timer A. I added that little guy in there and WHABAM! Timer A interrupt was enabled and the code worked.

##Day 3 - A functionality

##Day Extra

I realized that I had a few extra buttons that weren't being used, so I implemented a way to select any binary value for the block shade. This was simply done my ++ or -- the block color variable every time the channel button was toggled.

I also thought it would be more exciting if I could use my phone to control the device, so that way I could show all of my friends without dragging them to the ECE lab. So here is a screenshot of the phone.

![alt text](https://raw.githubusercontent.com/byarbrough/ece382_lab05/master/phoneRemote.png "Smart Remote App")

All I had to do was run the program, view the _result_ variable, and then update the lookup table!

This show that the program is robust enough to work for any remote that transmits IR data in this same format.


##Documentation
C2C Dusty Wiesner told me that I needed to reinitialize the LCD and then MSP430 for A functionality. This makes sense because the function of pin 2.6 changes each time.
