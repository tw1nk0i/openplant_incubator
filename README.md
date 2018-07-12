# OpenPlant Incubator

This project is to support the creation of an inexpensive plant incubator for the growth of liveworts (_Marchantia polymorpha_) which is the model system used by the [OpenPlant][1] collaboration. Our hope is that this design will allow a diverse array of (citizen) scientists cultivate plants under controlled conditions and potentially contribute to basic research.

## Incubator design

This design attempts to replicate the ideal conditions identified by Vujičić ([et al. 2010][2]) and reported by Chiyoda ([et al. 2008][3]). These conditions can be summarized as:

* 22°C
* 50-60 μmol photons/m<sup>2</sup>s (which for cool white fluorescent light equals 3700-4440 lux \[[Thimijan and Heins 1983][4]\])
* 16 h light, 8 h dark cycle

Furthermore we would like this project to be a relatively simple build so in general we are using well documented components from [Adafruit][5]. However the use of a wide array of purchased or scavenged parts is encouraged. We will describe the parts and their interaction with code in the "Description of parts" section, so jump there if you're trying to make a substitution(s).

## Description of files

What follows is a description of the code used in this project. We recommend branches (and forks) to incorporate alternate hardware. The raspberry_pi branch is currently in development to incorporate remote monitoring by reading off the data the microcontroller sends out via USB serial connection.

### Test_data

## Description of parts

* *Micro-controller*, [Metro Mini][7]

	Uses an ATmega328 based microcontroller like the Arduino UNO. We chose this particular board because it has many GPIO pins and it fits nicely into a breadboard for when I was prototyping.The USB support allows is to easily program it over USB and send data out via this connection. It's also important that it has a 5V regulator to power the sensors. It can also deliver 3.3V regulated which allows for a more diverse array of breakout modules to be used. I'm also controlling the fans using the "blue" PWM wire which is specified at 24kHz which can be achieved by modifying the internal registers (see the code).

* *Real time clock*, [PCF8523][8]

	This was the cheapest I2C RTC breakout module on Adafruit. It is required to timestamp the data being written to the logs. We think logs are the best way to ensure experiments are conducted under controlled conditions as well as to ensure the incubator is properly working. One could also imagine that a small computer (like a pi) could also serve this function if always connected by serial. The I2C standard allows this to easily share a bus with other sensors as long as there are no address collisions.

* *SD card*, [MicroSD breakout board][9]

	With the RTC this forms the basis of the data logging functionality. SD cards use 3.3V logic so depending on the hardware that used you may have to add in a voltage regulator. This particular board from Adafruit can shift 5V to 3.3V so it can share a power bus with the rest of the breakout modules used in this project.

* *Temperature sensor*, [SHT31-D][10]

	This temperature sensor can also record humidity and operates over the I2C bus. It can be powered by 5V or 3.3V. The better the resolution of this device the better the output of the peltiers can be modified to maintain the setpoint temperature. However this is also limited by the sampling frequency.

* *Light sensor*, [TSL2561][11]

	This light sensor operates over the I2C bus as the other sensors in this project do and has an onboard voltage regulator allowing it to receive 5V (it operated on 3.3V).

* *N-channel MOSFET*, [IRLB8721][19]

	A transistor component was chosen to regulate the 12V power source to the LEDs and the peltier using the PWM control from the micro-controller. This could probably be substituted with a variety of components. We used an N-channel MOSFET here because it was what we were most comfortable with. It's important it can block 12V, responds to 5V (or low current) and about 6A per peltier used. Also make sure to stick a heat sink on it.

* *Peltier*, [TEC1-12706][12]

	Peltier elements use electrical energy to pump heat across their body. This results in one hot side and one cold side. This particular module uses 12V which works with the 12V fans off a common power bus. Together with the CPU fan/heatskinks, thermal paste, craft foam and screws they are assembled into units which much be installed into the walls of the incubator.

* *Fan and heatsink*, [CPU cooler][13]

	I didn't purchase this part from a store. Instead I was able to get many of these inexpensively off of Craigslist. I have also seen them on eBay for cheap. CPU fans have 4-pin connections which conform to standard [specifications][14]. Briefly, 12V and ground make up two pins. The third is for fan speed control and accepts a 24kHz PWM signal and the fourth is the output of Hall-effect sensors which measure RPM. 3-pin fans will have to be controlled by a transistor modulating the 12V via PWM from the micro-controller. If possible get fans which have mounting holes which do not align with the heatsink block. This is because these holes will be used to thread a screw to the mounting holes of another fan and heatsink sandwiching the peltier and craft foam in between. If holes align with the heatsink the screws will have to pass through the heatsink in order to reach the opposite mounting holes. Two (near) identical fans with heat sinks will be required per peltier. In the example of this Intel brand stock fan, I cut out the plastic mounting hardware leaving only the holes so that I could used screws for the assembly.

* *LED*, [7020 rigid strip][15]

	This product was chosen because it emits cool white light which is most similar to the cool white fluorescent light which is described in the literature on growth conditions. It uses a maximum of 12V which can be modulated lower to adjust the brightness. Furthermore, it was already mounted on an adhesive backed heatsink which would make installation easier in the incubator.

* *Diffuser*, [Diffuser film][16]

	This is another product which I did not purchase. Instead I was able to salvage the backlight diffuser from inside an LED television. It was gloss on one side and matte on the other. I liked this solution because it was stiff enough to remain an even layer which could be supported by push pins into short pieces of wood dowling which was glued to the lid of the incubator. A great alternative which I tested was inexpensive [white plastic table cloth][17]. In this case it is light enough to be supported by paper clips or similar flexible wire. It won't lie as an even layer, but this minimally affects the variance in light intensity.

* *Voltage shifter*, [MP1584EN][18]

	This breakout is a buck DC-DC voltage converter which works to step down voltage using high frequency switching. In this design it is useful because it has a potentiometer which controls the final output voltage allowing me to manually set the brightness of the LED light source in the hardware. It also shares some of the thermal load of voltage step down from the 12V source with the voltage regulator on the micro-controller board. A maximum of 3A can pass through this module. I'm not sure if this is really required in he final build as presumably the 12V can be directly regulated on the micro-controller board and the transistor which controls the LEDs can be fed a PWM signal which corresponds to the desired light level. Also please note how awkwardly spaced the pins are on this board so you have to solder headers on kinda crooked to fit into a breadboard/perfboard.

* *Power supply*, [12V 360W Switching][20]

	I did not purchase this on Amazon. I was able to find a deal for this device on Craigslist and this seems like the item that I purchased. Many options exist here as long as they have enough power to drive everything. According to some very rough calculations I think the incubator as I built version 1 uses about 108W (it might be less). An ATX (desktop computer) power supply could also be used as it provides both 12V and 5V. That would remove another reason to use a buck external voltage shifter. 

* *Insulated chamber*, [Styofoam box][21]

	Walk around the city and I'm sure you will find one of these kicking about. The thicker the walls the better the insulation but also the more difficult it will be to cut holes to mount your fan-heatsink-peltier-heatskink-fan constructions. I found mine outside of a grocery store and it was previously used to transport fish. I've also spotted them outside of clinics (for pharmaceutical transport). The flatter the better because this design wants to minimize the distance between the plants and the lights to decrease the amount of energy needed to achieve a particular luminous intensity. A layered design could be explored but keep in mind that the more LED strips are added (and the harder they work) the more cooling is required during the light cycle.

### Miscellaneous

The following items were sourced from various stores (except for the wire wrapping supplies and headers) and links are only provided as examples of these items.

* FOAM SHIM	https://www.michaels.com/12x18-foam-sheet-by-creatology/M10597609.html
THERMAL PASTE	https://www.newegg.com/Product/Product.aspx?Item=N82E16835103080
DOWLING		https://www.homedepot.com/p/Builder-s-Choice-1-4-in-x-36-in-Oak-Round-Dowel-HDDO1436/206184687
SCREWS		https://www.homedepot.com/p/Everbilt-Zinc-Plated-Machine-Screw-Kit-405-Piece-803264/205949025
* *Connectors*, Jumper wire crimp connectors: [male][https://tinkersphere.com/breadboard-perfboard-prototyping/2309-male-jumper-wire-crimp-connector-for-breadboards-10-pack.html]; [female][https://tinkersphere.com/breadboard-perfboard-prototyping/1562-female-jumper-wire-crimp-connector-for-breadboards-10-pack.html]; [Stacking headers][https://www.sparkfun.com/products/10007]

	
WIRE WRAP	https://www.jameco.com/z/901-0-Wire-Wrap-Kynar-Black-100-Feet-30AWG-100-Foot-Rolls-_22577.html
WRAP TOOL	https://www.jameco.com/z/HSM30-JDV-Products-Strip-Wrap-Unwrap-Tool_34585.html?CID=MERCH
PERF BOARD https://www.allelectronics.com/category/455/perf-boards/1.html

## Future development

Some ideas and priorities for future work on this project:

1. Protect the circuit from failure with some capacitors and diodes to prevent back voltages and spikes.
	* I notice that when the fans get touched (and the inductive load slowed) the clock time gets messed up.

2. Definitively decide if the PID parameters are properly tuned.

3. Develop remote monitoring and remote parameter adjustment.

4. Introduce heating control via an H-bridge to switch the voltage polarity on the peliters.
	* I was originally going to use cheap [motor drivers][6] from Amazon, but the peltiers use more current than they are rated for.

5. Complete an initialization script which incorporates unit tests.

6. Rewrite the code as a state based machine (using the millis() function) to allow for different sensor polling times and better interrupt handling.

[1]: https://www.openplant.org/ (openplant homepage)
[2]: http://www.pmf.kg.ac.rs/kjs/volumes/kjs32/kjs32vujiciccvetic73.pdf (vujicic paper)
[3]: https:/dx.doi.org/10.1007/s00299-008-0570-5 (chiyoda paper)
[4]: http://agris.fao.org/agris-search/search.do?recordID=US19850000983 (thimijan paper)
[5]: https://www.adafruit.com/ (adafruit homepage)
[6]: https://www.amazon.com/gp/product/B077P1D41F (motor drivers)
[7]: https://www.adafruit.com/product/2590 (metro mini)
[8]: https://www.adafruit.com/product/3295 (PCF8523)
[9]: https://www.adafruit.com/product/254 (SD breakout)
[10]: https://www.adafruit.com/product/2857 (SHT31-D)
[11]: https://www.adafruit.com/product/439 (TSL2561)
[12]: https://www.amazon.com/Glamorway-TEC1-12706-Thermoelectric-Cooling-Peltier/dp/B00IKDL22O/ (TEC1-12706)
[13]: https://www.amazon.com/Intel-LGA115x-CPU-Heatsink-E97379-003/dp/B01MSD39CN (Intel stock)
[14]: http://www.formfactors.org/developer%5Cspecs%5CREV1_2_Public.pdf (4-pin fan)
[15]: https://www.amazon.com/gp/product/B00NFBG1O0/ (7020 LED)
[16]: https://www.inventables.com/technologies/light-diffuser-film-rolls (diffuser film)
[17]: https://www.dollartree.com/White-Plastic-Tablecovers/p61986/index.pro (table cloth)
[18]: https://www.amazon.com/gp/product/B01MQGMOKI/ (MP1584EN)
[19]: https://www.adafruit.com/product/355 (IRLB8721)
[20]: https://www.amazon.com/dp/B06VWV5YCH/ref=psdc_1161760_t1_B01EWG6YT8 (power supply)
[21]: https://www.mrboxonline.com/16375x115x6-quart-styrofoam-cooler-p-47940.html (box)