# Intelligent Car Control System - CS301 2024FALL

This project implements an intelligent car control system, designed and developed as part of the CS301 course for the Fall 2024 semester. The system integrates wireless communication, distance measurement, route planning, environmental exploration, and path following capabilities. It is built around an STM32 Mini development board and controlled via an LCD touch screen.

## Features

### 1. **Wireless Communication**
- **Bluetooth or 2.4GHz Communication**: The system supports wireless communication between the control board (STM32 Mini) and the car’s control board via Bluetooth or 2.4GHz wireless modules.
- **Connection Status**: Upon successful connection, the LCD displays a simple status message confirming the connection.

### 2. **Car Movement Control**
- **Manual Control**: The system allows the user to control the car’s movement using an LCD touch screen with the following actions:
  - Forward
  - Reverse
  - Left
  - Right
  - Left Rotation
  - Right Rotation
  - Stop
- **Movement Feedback**: The car's movement is visually reflected on the LCD in real-time as the user presses the corresponding buttons.

### 3. **Distance Measurement**
- **Ultrasonic Distance Module**: Utilizes an ultrasonic distance sensor to measure the distance to obstacles in front of the car.
- **Real-Time Display**: The measured distance is continuously displayed on the control board's LCD screen, ensuring the user is informed about the car's surroundings at all times.

### 4. **Route Planning & Navigation**
- **Field Setup**: The user can configure a 4x4 grid representing the navigation field and place obstacles randomly.
- **Route Planning**: Users can touch the LCD to set a start point, an endpoint, and obstacles. The system generates a path from start to end, avoiding obstacles.
- **Auto Navigation**: Once the path is planned, the car can autonomously navigate to the endpoint, avoiding obstacles along the way.

### 5. **Environmental Exploration**
- **Obstacle Detection**: The car automatically explores the environment and marks detected obstacles on the LCD.
- **Real-Time Mapping**: As obstacles are detected, the car returns their coordinates to the control board, and they are displayed in the 4x4 grid on the LCD.
- **Buzzer Alert**: Each time an obstacle is detected, a buzzer sound is emitted, alerting the user.

### 6. **Path Following (Auto & Manual Modes)**
- **Path Following**: The car can automatically follow a predefined path from start to end, navigating through curves and intersections.
- **Manual Override**: The user can switch between automatic path following and manual control mode using the LCD touch screen.
- **Track Navigation**: Supports both straight lines and curves, with features for overcoming sharp turns and intersections.

### 7. **Competition Mode (Optional)**
- **Timed Race**: The system includes a timed racing feature where the car follows a track, and the time taken is recorded. If the car exceeds the time limit, penalty points are applied.
- **Mode Switch**: Users can switch between path following and racing mode easily, ensuring smooth transitions during competitions.

## Setup

### Prerequisites
- **Hardware**:
  - STM32 Mini development board
  - Bluetooth or 2.4GHz wireless communication module
  - Ultrasonic distance measuring module
  - LCD touch screen
  - Motor control hardware for the car
    ### Installation

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/your-repo-link.git
   ```
2. Import into STM32CubeIDE:
- Open STM32CubeIDE.
- Import the project files into your workspace.
3. Build the Project:
- Compile the project in STM32CubeIDE to ensure there are no errors.
4. Upload to the STM32 Board:
- Connect the STM32 Mini development board to your computer.
- Use STM32CubeIDE to upload the code to the board.

### Folder Structure(to be edited)
```
/src
    /communication
        bluetooth.c            // Bluetooth communication functions
    /control
        motor.c                // Motor control functions
        navigation.c           // Path planning and navigation logic
    /environment
        ultrasonic.c           // Ultrasonic distance measuring functions
    /user_interface
        lcd.c                  // Functions for LCD touch screen interaction
        ui.c                   // User interface logic
/main.c                      // Main program entry point
```
### Development Tips:
- Use modular design for easy testing and debugging of individual components (communication, control, environment detection).
- Keep your functions and variables well-documented, especially in hardware control modules like motor.c and ultrasonic.c.
- For better maintainability, ensure that all magic numbers are defined as constants at the top of each file.


- **Including HJduino Library**:  
  To call motor control functions, include the `motor.h` header file in your source code. This header defines the necessary functions for controlling the motors and setting PWM speeds.

  ```c
  #include "motor.h"
  ```
  Motor Control: When working with motor functions, use the functions provided in the motor.c file. For example, to control the speed of a motor, you can call the SetMotorSpeed() or SetMotorSpeed2() function, depending on which motor you want to control. These functions set the speed of the left or right motors (for both motors in the front and back), and the direction can be controlled using positive or negative values for speed.
  Example usage:
  ```c
  // Set speed of motor 1 to 50
  SetMotorSpeed(1, 50);
  // Set speed of motor 2 to -50 (reverse direction)
  SetMotorSpeed2(1, -50);
  ```
  Initialization: For setting up PWM for the motors, you need to call the TIM4_PWM_Init() function with the appropriate parameters for arr (auto-reload value) and psc (prescaler). This function initializes the PWM configuration for motor control.
  Example usage:
  ```c
  // Initialize PWM for motor control with specific values
  TIM4_PWM_Init(1000, 72);  // arr = 1000, psc = 72
  ```
  Running Motors: To make the robot move forward, backward, turn left or right, or even brake, you can use the high-level functions like HJduino_run(), HJduino_back(), HJduino_left(), and others. These functions combine multiple motor speed adjustments and control functions to perform the desired movement.
  Example usage for forward movement:
  ```c
  // Move forward with speed 80 for 1000 ms
  HJduino_run(80, 1000);
  ```
  Braking and Stopping Motors: To stop or brake the motors, use the HJduino_brake() function, which will set all motor speeds to 0, effectively stopping the robot.
  Example usage:
  ```c
  // Stop all motors after 500 ms
  HJduino_brake(500);
  ```
- Module Integration: You can integrate other hardware modules like UltrasonicWave, remote, or IRSearch by including their respective header files and calling the appropriate functions defined within those modules. 
