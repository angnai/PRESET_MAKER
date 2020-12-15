import serial
import time
import threading
import datetime
import json
import os.path

BAUDRATE = 115200
MIN = (60)
HOUR = (MIN*60)
LIMIT_TIMEOUT = (3*HOUR)



class BIST(threading.Thread) :
    def __init__(self, comport, CmdValue, LogName):
        threading.Thread.__init__(self)
        print(comport + ' init thread ' + CmdValue + '\n')

        self.Device = comport
        self.name = (LogName + '_' + self.Device.replace('/','_')  + '.log')
        self.send_cmd = str(CmdValue) + '\n'

        self.comport = comport
        self.com = serial.Serial(self.comport,BAUDRATE,timeout = 1)
        
        self.exit = 0

    def _json_init(self):
        for i in range(1, 5):
            self.para_json['soc_index'+str(i+1)] = {'dqs_ds':'1','dq_ds':'1','re_ds':'1','ctrl_ds':'1','dqs_odt':'1','dq_odt':'1'}
            self.para_json['nand_index'+str(i+1)] = {'nand_ds':'1','nand_podt':'1','nand_rodt':'1'}
        print('a')
        input()
        with open("para_info.json", "w") as json_file:
            json.dump(self.para_json, json_file)

    def _json_write(self):
        with open("para_info.json", "w") as json_file:
            json.dump(self.para_json, json_file)

    def _json_read(self):
        with open("para_info.json", "r") as json_file:
            self.para_json = json.load(json_file)

    def __del__(self):
        self.com.close()

    def ExitMsg(self):
        self.exit = 1

    def GetDeviceName(self):
        return self.Device

    def _writeMsg(self, strDes):
        self.f = open(self.name,'a')
        self.f.write(str(strDes))
        self.f.close()

    def run(self):
        print(self.Device + ' execute\n')
        self.current_time = time.time()
        self.start_time = time.time()
        
        line = ''
        timeout_val = 60
        self.ret_val = 0
        self.com.write(self.send_cmd.encode())
        self._writeMsg('[' + str(datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')) + '] Trans>>>' + self.send_cmd + '\n')
        

        while not self.exit:
            
            
            for c in self.com.read():
                if c == 0x0d:
                        continue
                
                line = line + chr(c)
                if c == 0x0a:
                    print(line)
                    self._writeMsg(line)
                    if str(line) == "start function\n":
                        print(self.name, 'input value start...')
                        timeout_val = LIMIT_TIMEOUT

                    elif str(line) == "end function\n": 
                        print('input value end...')
                        self.ret_val = 1
                        break

                    elif str(line) == "err function\n":
                        print('input value err...')
                        self.ret_val = -1
                        break;
                    
                    line = '';

            #time.sleep(0.01)
        
            if ((time.time() - self.start_time) >= timeout_val) :
                self.ret_val = -1
                break

            if self.ret_val != 0 :
                break

        self.com.close()

    def join(self):
        threading.Thread.join(self)
        self.com.close()
        return self.ret_val
