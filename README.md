The overall work of me is ,first write a UART program in which you are sending data (string) at the destination port. This UART is generally used in keyboard, mouse, etc. UART stands for universal asynchronous receiver / transmitter and is a simple, two-wire protocol for exchanging serial data.The more information is given by ""
Asynchronous means no shared clock, so for UART to work, the same bit or baud rate must be configured on both sides of the connection. For choosing buad rate ,you have to know the clock frequency of device ,it is 16 MHz.
the UART function is written in uart.c and uart.h, the function uses timer , I use TIMER2  in my function, so it is written in  timer.c with header file in timer.h. there are two function , Delay_ms() and Delay_us(),which are create delay in milisecond and microsecond respectively.

The doc : "https://docs.google.com/document/d/1l0l4cMFl-Auo7-HpqH78_K5mvYUA42Em3one0gEC7Lo/edit?tab=t.0" is having some details of programing of DTH11 working, their some diagram of data movement between sensor and the MCU. The circuit diagram is also included in the doc.
The all work is done in ukeil vision.

DTH11 is working correctly , it is giving output. it is using Single-bus data format for communication and synchronization between MCU and
DHT11 sensor. One communication process is about 4ms.
The program is written in dth11.c with header file in dth11.h, the error will seen in putty by giving it port no of communication , which you will get in Devices and Monitor and baud rate is 9600 bits /sec.
We try to set I2C mahine code to integrate the output to the screen by I2C protocol.
