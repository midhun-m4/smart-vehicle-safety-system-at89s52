# smart-vehicle-safety-system-at89s52
Smart Vehicle Safety System using AT89S52 with automatic headlight dimming, obstacle detection, and automatic braking.
# Smart Vehicle Safety System using AT89S52

A Smart Vehicle Safety System developed using the **AT89S52 (8051) microcontroller**. The project combines automatic headlight dimming and obstacle detection to enhance driving safety. The system reduces glare from oncoming vehicles and automatically stops the vehicle when an obstacle is detected within a critical distance.

---

## Features

- Automatic headlight dimming using LDR sensor
- Obstacle detection using HC-SR04 ultrasonic sensor
- Automatic braking for collision prevention
- PWM-based headlight brightness control
- DC motor control

---

## Working

The system uses an **LDR sensor** to detect high-intensity light from oncoming vehicles. When the incoming light intensity exceeds a predefined level, the headlight brightness is automatically reduced using PWM control to minimize glare and improve driver visibility during night driving.

An **HC-SR04 ultrasonic sensor** continuously measures the distance to obstacles in front of the vehicle. If an obstacle is detected within **5 cm**, the vehicle automatically stops to help prevent collisions.

This combination of automatic headlight dimming and obstacle detection enhances overall vehicle safety.

---

## Technologies Used

- Embedded C
- AT89S52 Microcontroller
- Keil uVision
- HC-SR04 Ultrasonic Sensor
- LDR Sensor
- L298N Motor Driver
- PWM using Timer Interrupts

---

## Block Diagram

![Block Diagram](svs%20block%20diagram.png)

---

## Hardware Demonstration

![Hardware Demo](hardware_demo.jpeg)

---

## Repository Contents

| File | Description |
|--------|-------------|
| `smart_vehicle.c` | Source code |
| `svs block diagram.png` | System block diagram |
| `hardware_demo.jpeg` | Hardware demonstration image |

---

## Team Members

- MIDHUN M 
- ARCHANA NAIR
- VISHNUPRIYA R
- VARUNAPRIYA

---


## Academic Project

This project was developed as part of the Semester 4 Microcontroller Laboratory coursework using the AT89S52 microcontroller.
