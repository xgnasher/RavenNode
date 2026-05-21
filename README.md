<P align="center">
  <h1>RavenNode</h1>
  <p>ESP32 Pentesting tool in progress</p>

open-source ESP32-based
multi-tool inspired by devices like the flipper Zero.
Designed for experimentation, learning, and 
lightweight hardware interaction.

# Features
Simple UI Menu
- navigation button
- execution button 
# Display Support
- Basic screen interface 
- Menu based navigation
# WiFi Connectivity
- connect to local network editing SSID and PASSWORD on main.cpp
# Basic Network Scanner
- Ultra-light Nmap-style scanning
- Early implementation (experimental)
# Experimental Modules
- NFC = still working
- RFID = still working

# Hardware
- 128x64 SSD1306 Oled screen
- ESP32 S2
- 2x basic push buttons

# Controls
- Btn1 navigation = GPIO17
- Btn2 execute = GPIO16

# Status
- This project is on early developement

# Setup
- Clone the repository
- Open with vscode or prefered IDE
- Upload to ESP32 using PlatformIO
- Some PCs could need cp210x driver by silicon labs

# Roadmap
- improve UI/UX
- Expand network scanning capabilities
- Implement NFC features
- Implement RFID support
- Add more hardware modules

# Disclaimer
- this project is intended for educational and ethical use only
- Do not use it on networks or systems without permission

# Author
Developed by a single engineer working across experimental and professional enviroments.
