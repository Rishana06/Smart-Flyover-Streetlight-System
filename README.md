# Smart Flyover Streetlight System

## Overview

The Smart Flyover Streetlight System is an intelligent lighting solution designed to optimize energy consumption on flyovers and streets. The system automatically adjusts street lighting based on ambient light conditions and vehicle presence, reducing unnecessary power usage while ensuring adequate illumination when needed.

![System Overview](image1.png)
*Figure 1: Real-world implementation showing vehicle detection and lighting control sequence*

## Features

- **Automatic Day/Night Detection**: Uses an LDR (Light Dependent Resistor) sensor to detect ambient light levels
- **Motion-Based Lighting**: Detects vehicle movement using IR sensors to trigger full brightness
- **Energy Efficient**: Maintains dim lighting during night hours and full brightness only when vehicles are present
- **Sequential Detection**: Uses two IR sensors to track vehicle direction and movement

## Hardware Requirements

### Components

- **Microcontroller**: ESP32 or Arduino-compatible board
- **IR Sensors (x2)**: For vehicle detection
  - IR1 connected to GPIO 18
  - IR2 connected to GPIO 19
- **LDR Sensor**: For ambient light detection
  - Connected to GPIO 25 (analog input)
- **LED/Street Light**: Controllable lighting element
  - Connected to GPIO 21 (PWM capable pin)
- **Resistors**: As required for LDR voltage divider circuit
- **Power Supply**: Appropriate voltage for your microcontroller and LED

### Pin Configuration

| Component | GPIO Pin | Pin Type |
|-----------|----------|----------|
| IR Sensor 1 | 18 | Digital Input |
| IR Sensor 2 | 19 | Digital Input |
| LED/Light | 21 | PWM Output |
| LDR Sensor | 25 | Analog Input |

## Circuit Diagram

```
            ESP32/Arduino
                 │
    ┌────────────┼────────────┐
    │            │            │
   IR1          IR2          LDR
  (GPIO18)    (GPIO19)    (GPIO25)
    │            │            │
    └────────────┴────────────┘
                 │
               LED1
            (GPIO21)
```

## How It Works

![System Logic Flowchart](image2.png)
*Figure 2: Circuit schematic and decision logic flowchart*

### System Logic

The system operates in three distinct modes:

#### 1. **Daytime Mode**
- **Condition**: LDR reading < 2000
- **Action**: LED is turned OFF completely
- **Reason**: Natural daylight provides sufficient illumination

#### 2. **Nighttime Standby Mode**
- **Condition**: LDR reading ≥ 2000 and no vehicle detected
- **Action**: LED operates at 2% brightness (PWM value: 5/255)
- **Reason**: Provides minimal visibility while conserving energy

#### 3. **Vehicle Detection Mode**
- **Trigger**: Sequential detection by IR sensors
- **Action**: LED brightness increases to 98% (PWM value: 250/255)
- **Duration**: Remains at full brightness until vehicle passes second sensor

### State Machine Flow

The system uses a state-based approach with three states:

```
sense = 0 (Initial State)
    ↓
    └→ Waiting for IR1 detection
       ↓
sense = 1 (IR1 Triggered)
    ↓
    └→ LED at low brightness (5)
       └→ When vehicle detected: LED increases to 250
          ↓
sense = 2 (Tracking Vehicle)
    ↓
    └→ Waiting for IR2 detection
       ↓
       └→ Vehicle passed: LED returns to 5
          ↓
sense = 0 (Reset)
```

### Sequential Detection Process

1. **Initial State (sense = 0)**: System waits in standby with dim lighting
2. **First Sensor Triggered (sense = 1)**: When IR1 detects a vehicle, LED brightness jumps to maximum
3. **Second Sensor Triggered (sense = 2)**: When IR2 detects the same vehicle, LED returns to dim mode
4. **Reset**: System returns to sense = 0, ready for next vehicle

## Installation

### Image References

Before starting installation, refer to:
- **Figure 1** (top of document): Shows the complete system working in a real flyover scenario with vehicle detection zones and lighting states
- **Figure 2** (How It Works section): Displays the circuit connections and programming logic flow

### Software Setup

1. **Install Arduino IDE** or PlatformIO
2. **Install Board Support**:
   - For ESP32: Install ESP32 board package via Board Manager
   - For Arduino: Ensure proper board is selected
3. **Upload the Code**:
   - Connect your microcontroller via USB
   - Select correct board and port
   - Upload the sketch

### Hardware Setup

1. **Connect IR Sensors**:
   - Mount IR1 and IR2 on consecutive light poles along the road
   - Position sensors to face oncoming traffic direction
   - Recommended spacing: 20-50 meters apart (one sensor per light pole)
   - Connect VCC to 5V, GND to Ground, OUT to respective GPIO pins (18 and 19)

2. **Connect LDR Sensor**:
   - Create voltage divider circuit with LDR and a 10kΩ resistor
   - Connect to analog input (GPIO 25)

3. **Connect LED/Street Light**:
   - Connect LED through appropriate current-limiting resistor or driver circuit
   - For high-power lights, use a MOSFET or relay module

4. **Power Supply**:
   - Ensure stable power supply for microcontroller and all peripherals
   - Consider surge protection for outdoor installation

## Configuration

### Adjustable Parameters

You can modify these values in the code to suit your requirements:

```cpp
// LDR threshold for day/night detection
if (ldr < 2000)  // Change 2000 to adjust sensitivity

// LED brightness levels
analogWrite(LED1, 250);  // Full brightness (0-255)
analogWrite(LED1, 5);    // Dim brightness (0-255)

// Detection delay
delay(300);  // 300ms delay between readings
```

### Calibration Tips

- **LDR Threshold**: Test your LDR readings at different times and adjust the threshold (2000) accordingly
- **IR Sensor Distance**: Position sensors based on average vehicle speed to ensure proper detection
- **LED Brightness**: Adjust PWM values based on your LED specifications and desired brightness levels

## Testing

### Serial Monitor Output

The system provides real-time status updates via Serial communication (9600 baud):

- `day` - Daytime mode active
- `night` - Nighttime standby mode
- `ir1` - First IR sensor triggered
- `ir2` - Second IR sensor triggered
- State value (0, 1, or 2)

### Test Procedure

1. Open Serial Monitor at 9600 baud
2. Cover LDR to simulate night conditions
3. Trigger IR1 by placing an object in front of it
4. Observe LED brightness increase
5. Trigger IR2 to complete the cycle
6. Verify LED returns to dim state

## Troubleshooting

| Issue | Possible Cause | Solution |
|-------|---------------|----------|
| LED always OFF | LDR threshold too high | Adjust threshold value or check LDR wiring |
| LED always ON | LDR not working | Check LDR circuit and connections |
| IR sensors not detecting | Wrong sensor type or wiring | Verify IR sensor output (active LOW) |
| LED not dimming | PWM pin issue | Ensure GPIO 21 supports PWM |
| Erratic behavior | Delay too short | Increase delay value |

## Future Enhancements

- Add wireless connectivity (WiFi/LoRa) for remote monitoring
- Implement data logging for traffic analysis
- Add multiple brightness levels based on vehicle density
- Integrate weather sensors for adaptive lighting
- Create mobile app for system configuration
- Add solar panel integration for off-grid operation

## Energy Savings

**Estimated Savings**:
- Traditional street lights: 100% power consumption throughout the night
- Smart system: ~2% standby + brief 98% bursts = approximately 70-85% energy savings

## Safety Considerations

- Ensure all electrical connections are properly insulated
- Use weatherproof enclosures for outdoor installation
- Install surge protection devices
- Follow local electrical codes and regulations
- Consider backup power systems for critical locations

## License

This project is open-source and available for educational and commercial use.

## Contributing

Contributions are welcome! Please feel free to submit pull requests or open issues for bugs and feature requests.

## Contact

For questions or support, please open an issue on the project repository.

---

**Version**: 1.0  
**Last Updated**: December 2025  
**Tested On**: ESP32 DevKit, Arduino Uno