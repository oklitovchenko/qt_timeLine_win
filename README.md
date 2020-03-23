A Qt desktop application that contains a Timeline control that displays events by time.

All necessary standard controls are also presented, which completely cover the demonstration of functionality.
 
The event is determined by the string type and the time interval, on which its location relative to the timeline depends.
Events with the same types are placed on the same line.

Features:
- The date scale supports the gradations Hour, Day, Month.
- If events do not fit into an accessible area, it is able to scroll through it.
- Each event contains information about the type and time period.
- Each event contains a button that generates a signal to make a decision about deletion (for example, using a MessageBox).
- The event supports the ability to move the mouse on the scale, accordingly changing its time interval.

Classes are designed in accordance with the architecture of MVC.
