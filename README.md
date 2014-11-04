ece382_lab05
============

Interrupts - "Remote Control Decoding"


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


|            Pulse            | Duration (ms) | Timer A counts |
|:---------------------------:|:-------------:|:--------------:|
| Start   logic 0 half-pulse  |      8.93     |      71440     |
| Start   logic 1 half-pulse  |      4.42     |      35360     |
| Data 1   logic 0 half-pulse |     0.495     |      3960      |
| Data 1   logic 1 half-pulse |      1.61     |      12880     |
| Data 0   logic 0 half-pulse |     0.620     |      4960      |
| Data 0   logic 1 half-pulse |     0.620     |      4960      |
| Stop   logic 0 half-pulse   |     0.616     |      4928      |
| Stop logic 1 half-pulse     |    infinite   |    infinite    |
