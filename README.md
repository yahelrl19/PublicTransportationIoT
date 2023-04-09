# Public Transportation System with IoT

This project aims to provide a public transportation system that utilizes Internet of Things (IoT) technologies. The system consists of two Arduino devices that communicate with each other using LoRa communication protocol. 

## Overview

The first Arduino device is responsible for collecting GPS data from the vehicle and transmitting it through LoRa to the second Arduino device. The second device receives the GPS data and converts it into estimated time of arrival (ETA) for the vehicle. Additionally, the second device uses a PIR sensor to detect the vehicle's capacity and display it as "Capacidad: baja", "Capacidad: media" or "Capacidad: alta", depending on the percentage of the vehicle's full capacity.

## Components

- Arduino Uno x2
- LoRa Module x2
- GPS Module
- PIR Sensor

## Setup

To set up the system, connect the GPS module and LoRa module to the first Arduino, and the LoRa module and PIR sensor to the second Arduino. The code for each Arduino can be found in the "src" folder of this repository.

## Usage

After setting up the system, turn on the first Arduino device and wait for it to transmit GPS data through LoRa to the second device. The second device will then display the estimated time of arrival and the vehicle's capacity on its screen.

## Contributing

Contributions to this project are welcome! If you would like to contribute, please follow the standard fork and pull request workflow on GitHub.

## License

This project is licensed under the MIT License. See the [LICENSE](./LICENSE) file for details.
