#include <Arduino.h>
#include <stdint.h>
#include <esp_now.h>
#include <WiFi.h>

#define GPIO_SPEED GPIO_NUM_36
#define GPIO_DIR_X GPIO_NUM_39
#define GPIO_DIR_Y GPIO_NUM_35
#define GPIO_LED GPIO_NUM_2

#define ADC_RESOLUTION 4096

#define CALIBRATION_DELTA (45) // The lower the Vref, the bigger should be this number.
#define UPDATE_DELTA (5)

struct coor
{
  int8_t speed;
  int8_t y;
  int8_t x;
} __attribute__((packed));

// Note: Attention: the bit 0 of the first byte of MAC address can not be 1.
// For example, the MAC address can set to be “1a:XX:XX:XX:XX:XX”, but can not be “15:XX:XX:XX:XX:XX”.
esp_now_peer_info_t peer_info = {
    .peer_addr = {0x1A, 0xFF, 0x00, 0xFF, 0x00, 0xFF},
    .channel = 0,
    .encrypt = false};

static coor coord;

void setup()
{
  // Serial.begin(9600);
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK || esp_now_add_peer(&peer_info) != ESP_OK)
  {
    return;
  }

  pinMode(GPIO_SPEED, INPUT);
  pinMode(GPIO_DIR_Y, INPUT);
  pinMode(GPIO_DIR_X, INPUT);
  pinMode(GPIO_LED, OUTPUT);

  digitalWrite(GPIO_LED, 0);
}

void loop()
{
  int speed = analogRead(GPIO_SPEED);
  int y = analogRead(GPIO_DIR_Y);
  int x = analogRead(GPIO_DIR_X);

  speed = map(speed, 0, ADC_RESOLUTION, -100, 100);
  y = map(y, 0, ADC_RESOLUTION, -100, 100);
  x = map(x, 0, ADC_RESOLUTION, -100, 100);

  // To deal with calibration issues.
  if ((0 < speed && speed < CALIBRATION_DELTA) || (0 > speed && speed > -CALIBRATION_DELTA))
  {
    speed = 0;
  }
  if ((0 < y && y < CALIBRATION_DELTA) || (0 > y && y > -CALIBRATION_DELTA))
  {
    y = 0;
  }
  if ((0 < x && x < CALIBRATION_DELTA) || (0 > x && x > -CALIBRATION_DELTA))
  {
    x = 0;
  }

  if ((abs(coord.speed - speed) > UPDATE_DELTA) || (abs(coord.y - y) > UPDATE_DELTA) || (abs(coord.x - x) > UPDATE_DELTA))
  {
    coord.speed = speed;
    coord.y = y;
    coord.x = x;

    esp_err_t result = esp_now_send(peer_info.peer_addr, (uint8_t *)&coord, sizeof(struct coor));
    if (result != ERR_OK)
    {
      if (result == ESP_ERR_ESPNOW_NO_MEM)
      {
        delay(10);
      }
      digitalWrite(GPIO_LED, 1);
    }

    // Serial.printf("Speed: %d | Y: %d | X: %d | res: %d\n", speed, y, x, result);
  }
}
