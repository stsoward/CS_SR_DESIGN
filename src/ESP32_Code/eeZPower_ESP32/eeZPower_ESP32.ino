#include "BluetoothSerial.h"
#include "VescUart.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

/*Define a vescUart object*/
VescUart VESCUART;
/*Define a serial bluetooth*/
BluetoothSerial SerialBT;


void setup() {
  /*Set Baude Rate to 115200, make sure VESC is set to the same on UART*/
  Serial.begin(115200);
  /*Set Bluetooth Name to eeZPower*/
  SerialBT.begin("eeZPower");
  /*Print bluetooth state*/
  Serial.println("Bluetooth Started! Ready to pair...");
  /*Set Serial port for vescUart object */
  VESCUART.setSerialPort(&Serial);
}

void loop() {
  /*check and run .getVescValues method to update assocaited values 
   * NOTE: for some reason this command outputs some char to Serial Monitor that is not readable, not sure why
   *       I am not 100% familiar with the VescUart library debugPort->print commands so I left it as is
   *       This is not added to the sendToApp string
   */
  if(VESCUART.getVescValues()){
    /*use SerialBT.println() to send data over Bluetooth
     * use Serial.println() to send data to Serial Monitor
     * 
     * Below are testing strings
     *     SerialBT.println(VESCUART.data.inputVoltage);
     *     Serial.println(VESCUART.data.inputVoltage);
     *     SerialBT.println(VESCUART.data.rpm);
     *     Serial.println(VESCUART.data.rpm);
    */
    /*create a string with all the needed values and send it to the App over bluetooth*/
    String sendToApp = "volt=" + String(VESCUART.data.inputVoltage) + "|" + "rpm=" + String(VESCUART.data.rpm) + "|" + "tach=" + String(VESCUART.data.tachometerValue;
    //Serial.println(sendToApp);
    SerialBT.println(sendToApp);
  }
  delay(20);
}
