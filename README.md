ece382_lab05
============

[Interrupts - "Remote Control Decoding"](http://ece382.com/labs/lab5/index.html)

##Day 1

![alt text](https://raw.githubusercontent.com/byarbrough/ece382_lab05/master/irWave.gif "IR Waveform")

| Button |               Code               |    Hex   |
|--------|:--------------------------------:|:--------:|
| Up     | 00001010111101010000111011110001 | 0AF50EF1 |
| Down   | 00001010111101011000111001110001 | 0AF58E71 |
| Left   | 00001010111101011100111000110001 | 0AF5CE31 |
| Right  | 00001010111101010100111010110001 | 0AF54EB1 |
| CH +   | 00001010111101011001100001100111 | 0AF59867 |
| CH -   | 00001010111101010001100011100111 | 0AF518E7 |
| MUTE   | 00001010111101011101000000101111 | 0AF5D02F |
| EXIT   | 00001010111101010000100011110111 | 0AF508F7 |


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
