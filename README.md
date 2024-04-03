# Dual STM32F401C Interactive Timekeeping Demo

## Objective
Create a system where two STM32F401C microcontrollers, each equipped with an LCD and switches, communicate over UART to provide the following synchronized features:

### Core Features
- **Date and Time Display:** Each LCD prominently displays the current date and time (hours, minutes, seconds).
- **Editable Time and Date:** Users can enter an edit mode using switches to adjust the time and date settings.
- **Real-Time Clock (RTC):** The system maintains accurate timekeeping, potentially using the RTC peripheral for persistence during power cycles.
- **Background Clock:** The time updates continuously, even while in edit mode or stopwatch mode.

### Advanced Features
- **Stopwatch:** Tracks elapsed time with start, stop, and reset functionality. The stopwatch remains active when switching modes.
- **Millisecond Counter:** A separate counter provides millisecond-level time resolution.
- **Cross-Control:** Switches on one MCU can control the display mode and potentially other functions (edit time/date, stopwatch control) on the opposite MCU.

## Static Design
In the early stages of software development, it's crucial to establish the static design of the system. This involves:

- **Structural Design:** Decompose the system into modules and define relationships between them.
- **Class Design:** Design classes responsible for various functionalities.
- **Interface Design:** Define interfaces between components to specify methods and parameters.
- **Data Design:** Design data structures and databases for data storage and manipulation.

Static design serves as a blueprint for the system's structure and organization, guiding the development process to meet functional and non-functional requirements.

