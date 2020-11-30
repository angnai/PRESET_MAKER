import RPi.GPIO as GPIO
import datetime
import time


class PowerCtrl:
    def __init__(self, mDevices, log_name):

        self.logs = []
        for n in range(len(mDevices)):
            self.logs.append(log_name + '_' + mDevices[n] + '.txt')
            self.logs[n] = self.logs[n].replace('/','_')
        
        GPIO.setmode(GPIO.BCM)
        GPIO.setup(17, GPIO.OUT)    # PIN 11

    def _writeMsg(self, strDes):
        for n in range(len(self.logs)):
            self.f = open(self.logs[n],'a')
            self.f.write(str(strDes))
            self.f.close()

    def PowerOn(self):
        self._writeMsg('[' + str(datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')) + '] <<< Module Power on sequence >>>\n')
        GPIO.output(17, False)
        time.sleep(5)
        
    def PowerOff(self):
        self._writeMsg('[' + str(datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')) + '] <<< Module Power off sequence >>>\n')
        GPIO.output(17, True)
        time.sleep(5)


