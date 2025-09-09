    #include "DHT.h" // Include the Adafruit DHT library
    #include <SPI.h>
    #include <Wire.h>
    #include <Adafruit_GFX.h>
    #include <Adafruit_SSD1306.h>

    #define DHTPIN 8    // Define the digital pin the DHT11 data pin is connected to
    #define DHTTYPE DHT11 // Specify the type of DHT sensor being used (DHT11 in this case)
    #define SCREEN_WIDTH 128 // OLED display width, in pixels
    #define SCREEN_HEIGHT 64 // OLED display height, in pixels
    #define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
    #define SCREEN_ADDRESS 0x3C

    Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


    // Initialize DHT sensor.
    // Parameter 1: Pin number
    // Parameter 2: DHT type (DHT11, DHT22)
    DHT dht(DHTPIN, DHTTYPE);



    void setup() {




      Serial.begin(9600); // Initialize serial communication for output


      if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
      Serial.println(F("SSD1306 allocation failed"));
      for (;;); // Don't proceed, loop forever
      }


      dht.begin(); // Initialize the DHT sensor

   
    }

    void loop() {
      delay(2000); // Wait 2 seconds between measurements.

      // Read humidity (as a percentage)
      float h = dht.readHumidity();
      // Read temperature as Celsius (the default)
      float t = dht.readTemperature();
      // Read temperature as Fahrenheit (isFahrenheit = true)
      float f = dht.readTemperature(true);

      // Check if any reads failed and exit early (to try again).
      if (isnan(h) || isnan(t) || isnan(f)) {
        Serial.println(F("Failed to read from DHT sensor!"));
        return;
      }

      // Compute heat index in Fahrenheit (the default)
      float hif = dht.computeHeatIndex(f, h);
      // Compute heat index in Celsius
      float hic = dht.computeHeatIndex(t, h, false);

      display.clearDisplay();
      // Display Text
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(1, 5);
      display.println("Weather Station");
      display.println();
      display.print("Humidity: ");
    
      display.print(h);
      display.println("%");
      display.println();
      display.print("Temp: ");
      display.print(f);
      display.println(" F");
      display.println();

      display.print("Heat Index: ");
      display.print(hif);
      display.println(" F");
      


      
      display.display();
      display.clearDisplay();
      delay(2000);
    }