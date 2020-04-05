/*
 *  ------ P2P Code Example --------
 *
 *  Explanation: This example shows how to configure the module
 *  for P2P mode and the corresponding parameters. After this,
 *  the example shows how to send packets to other radio modules
 *  which must be set with the same radio settings
 *
 *  Copyright (C) 2015 Libelium Comunicaciones Distribuidas S.L.
 *  http://www.libelium.com
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Version:           1.3
 *  Design:            David Gascon
 *  Implementation:    Luismi Marti
 *  Ported to Arduino: Ruben Martin
 */

#include <Wire.h>

 // Cooking API libraries
#include <arduinoUART.h>
#include <arduinoUtils.h>

// LoRaWAN library
#include <arduinoLoRaWAN.h>

// Pin definition for LoRaWAN module error LED:
const int error_led = 13;

//////////////////////////////////////////////
uint8_t socket = SOCKET1;
//////////////////////////////////////////////

// define radio settings
//////////////////////////////////////////////
int8_t power = 15;
uint32_t frequency = 868100000;
char spreading_factor[] = "sf12";
char coding_rate[] = "4/5";
uint16_t bandwidth = 125;
char crc_mode[] = "on";
//////////////////////////////////////////////


// define data to send
char data[] = "0102030405060708090A0B0C0D0E0F";

// variable
uint8_t error;


void setup()
{
    //Radio P2P example - Sending packets
    pinMode(error_led, OUTPUT);
    digitalWrite(error_led, LOW);

    // module setup
    error = radioModuleSetup();

    // Check status
    if (error == 0)
    {
        //Module configured OK
        digitalWrite(error_led, LOW);
    }
    else
    {
        //Module configured ERROR"
        digitalWrite(error_led, HIGH);
    }
}


void loop()
{
    // Send packet
    error = LoRaWAN.sendRadio(data);

    // Check status
    if (error == 0)
    {
        //--> Packet sent OK
        digitalWrite(error_led, LOW);
    }
    else
    {
        //Error waiting for packets. error
        digitalWrite(error_led, LOW);
    }

    delay(5000);
}


/***********************************************************************************
*
* radioModuleSetup()
*
*   This function includes all functions related to the module setup and configuration
*   The user must keep in mind that each time the module powers on, all settings are set
*   to default values. So it is better to develop a specific function including all steps
*   for setup and call it everytime the module powers on.
*
*
***********************************************************************************/
uint8_t radioModuleSetup()
{

    uint8_t status = 0;
    uint8_t e = 0;

    //////////////////////////////////////////////
    // 1. switch on
    //////////////////////////////////////////////

    e = LoRaWAN.ON(socket);

    // Check status
    if (e == 0)
    {
        //1. Switch ON OK
        digitalWrite(error_led, LOW);
    }
    else
    {
        //1. Switch ON error 
        digitalWrite(error_led, HIGH);
        status = 1;
    }
    //-------------------------------------------------------

    //////////////////////////////////////////////
    // 2. Enable P2P mode
    //////////////////////////////////////////////

    e = LoRaWAN.macPause();

    // Check status
    if (e == 0)
    {
        //2. P2P mode enabled OK
        digitalWrite(error_led, LOW);
    }
    else
    {
        //2. Enable P2P mode error 
        digitalWrite(error_led, HIGH);
        status = 1;
    }
    //-------------------------------------------------------

    //////////////////////////////////////////////
    // 3. Set/Get Radio Power
    //////////////////////////////////////////////

    // Set power
    e = LoRaWAN.setRadioPower(power);

    // Check status
    if (e == 0)
    {
        //3.1. Set Radio Power OK
        digitalWrite(error_led, LOW);
    }
    else
    {
        //3.1. Set Radio Power error
        digitalWrite(error_led, HIGH);
        status = 1;
    }

    // Get power
    e = LoRaWAN.getRadioPower();

    // Check status
    if (e == 0)
    {
        //3.2. Get Radio Power OK.
        //"Power in LoRaWAN._radioPower
        digitalWrite(error_led, LOW);
    }
    else
    {
        //3.2. Get Radio Power error
        digitalWrite(error_led, HIGH);
        status = 1;
    }
    //-------------------------------------------------------

    //////////////////////////////////////////////
    // 4. Set/Get Radio Frequency
    //////////////////////////////////////////////

    // Set frequency
    e = LoRaWAN.setRadioFreq(frequency);

    // Check status
    if (e == 0)
    {
        //4.1. Set Radio Frequency OK
        digitalWrite(error_led, LOW);
    }
    else
    {
        //4.1. Set Radio Frequency error
        digitalWrite(error_led, LOW);
        status = 1;
    }

    // Get frequency
    e = LoRaWAN.getRadioFreq();

    // Check status
    if (e == 0)
    {
        //4.2. Get Radio Frequency OK
        //Frequency in LoRaWAN._radioFreq
        digitalWrite(error_led, LOW);
    }
    else
    {
        //4.2. Get Radio Frequency error
        digitalWrite(error_led, HIGH);
        status = 1;
    }
    //-------------------------------------------------------

    //////////////////////////////////////////////
    // 5. Set/Get Radio Spreading Factor (SF)
    //////////////////////////////////////////////

    // Set SF
    e = LoRaWAN.setRadioSF(spreading_factor);

    // Check status
    if (e == 0)
    {
        //5.1. Set Radio SF OK
        digitalWrite(error_led, LOW);
    }
    else
    {
        //5.1. Set Radio SF error 
        digitalWrite(error_led, HIGH);
        status = 1;
    }

    // Get SF
    e = LoRaWAN.getRadioSF();

    // Check status
    if (e == 0)
    {
        //5.2. Get Radio SF OK
        //Spreading Factor in LoRaWAN._radioSF
        digitalWrite(error_led, LOW);
    }
    else
    {
        //5.2. Get Radio SF error
        digitalWrite(error_led, HIGH);
        status = 1;
    }
    //-------------------------------------------------------

    //////////////////////////////////////////////
    // 6. Set/Get Radio Coding Rate (CR)
    //////////////////////////////////////////////

    // Set CR
    e = LoRaWAN.setRadioCR(coding_rate);

    // Check status
    if (e == 0)
    {
        //6.1. Set Radio CR OK
        digitalWrite(error_led, LOW);
    }
    else
    {
        //6.1. Set Radio CR error
        digitalWrite(error_led, HIGH);
        status = 1;
    }

    // Get CR
    e = LoRaWAN.getRadioCR();

    // Check status
    if (e == 0)
    {
        //6.2. Get Radio CR OK.
        //Coding Rate in LoRaWAN._radioCR
        digitalWrite(error_led, LOW);
    }
    else
    {
        //6.2. Get Radio CR error
        digitalWrite(error_led, HIGH);
        status = 1;
    }
    //-------------------------------------------------------

    //////////////////////////////////////////////
    // 7. Set/Get Radio Bandwidth (BW)
    //////////////////////////////////////////////

    // Set BW
    e = LoRaWAN.setRadioBW(bandwidth);

    // Check status
    if (e == 0)
    {
        //7.1. Set Radio BW OK
        digitalWrite(error_led, LOW);
    }
    else
    {
        //7.1. Set Radio BW error
        digitalWrite(error_led, HIGH);
    }

    // Get BW
    e = LoRaWAN.getRadioBW();

    // Check status
    if (e == 0)
    {
        //7.2. Get Radio BW OK.
        //Bandwidth in LoRaWAN._radioBW
        digitalWrite(error_led, LOW);
    }
    else
    {
        //7.2. Get Radio BW error 
        digitalWrite(error_led, HIGH);
        status = 1;
    }
    //-------------------------------------------------------

    //////////////////////////////////////////////
    // 8. Set/Get Radio CRC mode
    //////////////////////////////////////////////

    // Set CRC
    e = LoRaWAN.setRadioCRC(crc_mode);

    // Check status
    if (e == 0)
    {
        //8.1. Set Radio CRC mode OK
        digitalWrite(error_led, LOW);
    }
    else
    {
        //8.1. Set Radio CRC mode error 
        digitalWrite(error_led, HIGH);
        status = 1;
    }

    // Get CRC
    e = LoRaWAN.getRadioCRC();

    // Check status
    if (e == 0)
    {
        //8.2. Get Radio CRC mode OK.
        //CRC status in LoRaWAN._crcStatus
        digitalWrite(error_led, LOW);
    }
    else
    {
        //8.2. Get Radio CRC mode error
        digitalWrite(error_led, HIGH);
        status = 1;
    }
    //-------------------------------------------------------

    return status;
}
