# Micro Binary Clock

Minimalistic Binary Clock using a PIC16F628a.

Uses 4 bits for the hour (0-12), 6 bits for the minutes (0-59), so it can be shown with a 10 segment LED bar.
Single button to change hours/minutes. Short presses increase the minute counter, long presses increment the hour counter.

Made by Gonzalo Ávila Alterach, 2013

## Required connections

Hour LEDs: H3 H2 H1 H0
Mins LEDs: M5 M4 M3 M2 M1 M0

1. NC
2. NC
3. NC
4. VCC direct or via 10k pullup 
5. Vss
6. Button (active low, the other side of the button should be connected to ground)
7. NC
8. M5
9. M0
10. M1
11. M2
12. M3 
13. M4
14. Vdd
15. H0 
16. H1
17. H2
18. H3

## Todo List

- Every minute or so, save the time to the internal eeprom 
- Use low power modes to avoid draining battery
- Add a combination to avoid accidental changes of hours/minutes
