# Smart Cement Mixer 🦷⚙️

An IoT-based smart dental cement mixing system designed to automate and simplify the preparation of Glass Ionomer Cement (GIC) for dental applications. The project focuses on reducing manual effort, improving consistency, and enabling wireless control through a smartphone.

# 📌 Overview

The GIC Smart Cement Mixer is a compact embedded system that uses an ESP32 microcontroller and a servo motor to automate the mixing process of dental cement. The device can be remotely controlled using a mobile application, allowing dentists to start, stop, and adjust mixing speed wirelessly.

The system currently supports 9 different speed modes for flexible mixing control. Future versions aim to include custom automated mixing ratios, preset profiles, and intelligent mixing algorithms for enhanced precision.

# ✨ Features
📱 Smartphone-controlled operation
⚡ Wireless communication using Wi-Fi/Bluetooth
🎚️ 9 adjustable mixing speed modes
▶️ Start/Stop control from mobile app
🔄 Servo motor-based mixing mechanism
🦷 Designed specifically for GIC dental cement
🔋 Compact and energy-efficient design
🧼 Improves hygiene by reducing manual interaction
🚀 Expandable for future smart automation features
🛠️ Hardware Components

# Component	Description
ESP32	Main microcontroller with Wi-Fi/Bluetooth
Servo Motor	Drives the mixing mechanism
Power Supply	Powers the system
Mixing Chamber	Holds and mixes the cement
Smartphone App	Controls the mixer remotely
Motor Driver (optional)	Additional motor control support

# 🧠 Working Principle
The user connects their smartphone to the mixer.
Commands are sent wirelessly to the ESP32.
The ESP32 processes the commands and controls the servo motor.
The servo rotates at the selected speed mode to mix the cement.
The dentist can start, stop, or change mixing speed in real time.

# 📲 Mobile App Features
Start mixing
Stop mixing
Select from 9 speed modes
Real-time control
Future support for:
Preset mixing profiles
Automated ratio selection
Timer-based mixing
Data logging
