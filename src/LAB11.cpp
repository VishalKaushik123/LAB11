/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/Vishal/Documents/CTDProjects/LAB11/src/LAB11.ino"
#include "LIS3DH.h"

#include <blynk.h>

// Electron sample to print accelerometer samples to serial
// (also works on the Photon, P1, Core)

void setup();
void loop();
#line 8 "c:/Users/Vishal/Documents/CTDProjects/LAB11/src/LAB11.ino"
SYSTEM_THREAD(ENABLED);


// Print 10 samples per second to serial
const unsigned long PRINT_SAMPLE_PERIOD = 100;

// LIS3DH is connected as in the AssetTracker, to the primary SPI with A2 as the CS (SS) pin, and INT connected to WKP
LIS3DHSPI accel(SPI, D6, WKP);

unsigned long lastPrintSample = 0;

void setup() {
	Serial.begin(9600);

	Blynk.begin("lI9Uc55_IMOmfBI-SxA6sRakcOKzgO_h", IPAddress(167, 172, 234, 162), 9090);

	// Initialize sensors
	LIS3DHConfig config;
	config.setAccelMode(LIS3DH::RATE_100_HZ);

	bool setupSuccess = accel.setup(config);
	Serial.printlnf("setupSuccess=%d", setupSuccess);
}

void loop() {
	Blynk.run();
	if (millis() - lastPrintSample >= PRINT_SAMPLE_PERIOD) {
		lastPrintSample = millis();

		LIS3DHSample sample;
		
		if (accel.getSample(sample)) {
			Serial.printlnf("%d,%d,%d", sample.x, sample.y, sample.z);
			Blynk.virtualWrite(V0, sample.x);
  			Blynk.virtualWrite(V1, sample.y);
			Blynk.virtualWrite(V2, sample.z);

		}
		else {
			Serial.println("no sample");
		}
	}
}


