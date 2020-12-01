from enum import Enum
import time
import datetime
import sys
import os
import socket
import re


MIN = (60)
HOUR = (MIN*60)
LIMIT_TIMEOUT = (3*HOUR)

WAIT_TIME = 2
WAIT_TIME_1SEC = (1/WAIT_TIME)
WAIT_LOG_TIME = (10 * WAIT_TIME_1SEC)

host = '10.11.11.250'
port = 57732

class Chamber:

    def __init__(self, chamber_dev, mDevices, log_name):
        self.device = chamber_dev
        
        self.logs = []
        for n in range(len(mDevices)):
            self.logs.append(log_name + '_' + mDevices[n] + '.txt')
            self.logs[n] = self.logs[n].replace('/','_')
            
        self.current_temp = self._get_temp()
        self.target_temp = 0
        self.current_time = 0
        self.target_time = 0

        
	
        print('init func')

    def _writeMsg(self, strDes):
        for n in range(len(self.logs)):
            self.f = open(self.logs[n],'a')
            self.f.write(str(strDes))
            self.f.close()

    def _transceive(self, strCmd):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.connect((host, port))
        self.sock.sendall(str.encode(strCmd + '\r\n'))
        #self._writeMsg(strCmd + '\n')
        
        resp = self.sock.recv(1024)
        resp = resp.decode('utf-8')
        resp = resp.rstrip('\r\n')
        self.sock.close()

        #self._writeMsg(resp + '\n')
        return resp

    def start(self) :
        self._writeMsg('[' + str(datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')) + '] Chamber_Trans>> Start\n')
        
        retrycnt = 0
        while (retrycnt < 10) :

            resp = self._transceive('POWER,ON')
            divid_resp = resp.split(':')
            if divid_resp[0] != 'OK':
                retrycnt = retrycnt+1
                self._writeMsg('[' + str(datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')) + '] RESPONSE ERROR\n')
                continue
            else:
                break;
        
        if retrycnt >= 10:
            return -1

        return 0

    def stop(self) :
        self._writeMsg('[' + str(datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')) + '] Chamber_Trans>> Stop\n')
        
        retrycnt = 0
        while (retrycnt < 10) :
            resp = self._transceive('POWER,OFF')
            divid_resp = resp.split(':')
            if divid_resp[0] != 'OK':
                self._writeMsg('[' + str(datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')) + '] RESPONSE ERROR\n')
                continue
            else:
                break;
                
        if retrycnt >= 10:
            return -1

        return 0

    def get_temp(self) :
        self._writeMsg('[' + str(datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')) + '] Chamber_Trans>> get_temp\n')
        
        retrycnt = 0
        while (retrycnt < 10) :
            self.current_temp,humi = self._get_temp()

            if self.current_temp == 'error':
                retrycnt = retrycnt+1
                self._writeMsg('wait_temp error retry\n')
            else:
                break;

        if retrycnt >= 10:
            self._writeMsg('wait_temp tranceive error\n')
            return 'error', 'error'
        
        self._writeMsg('current temp : ' + str(self.current_temp) + '\'C, (' + str(humi) + '%)\n')
        return self.current_temp, humi

    def set_temp(self,Temp) :
        self._writeMsg('[' + str(datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')) + '] Chamber_Trans>> set_temp ' + str(Temp) + '\'C\n')

        retrycnt = 0
        while (retrycnt < 10) :
            temp_val = self._set_temp(Temp)

            if temp_val == 'error':
                continue
            else:
                break
        
        if retrycnt >= 10:
            return 'error'

        return temp_val

    def wait_temp(self, target_temp) :
        self._writeMsg('[' + str(datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')) + '] Chamber_Trans>> wait_temp ' + str(target_temp) + '\'C\n')

        self.target_temp = target_temp
        self.current_temp,humi = self._get_temp()

        self.current_time = time.time()
        self.target_time = time.time()+LIMIT_TIMEOUT

        timecnt = 0
        retrycnt = 0
        while (self.target_temp != self.current_temp) :
            self.current_temp,humi = self._get_temp()

            if self.current_temp == 'error':
                retrycnt = retrycnt+1
                if retrycnt > 10:
                    self._writeMsg('wait_temp tranceive error\n')
                    return -1
                else:
                    self._writeMsg('wait_temp error retry\n')
                    continue
            
            retrycnt = 0

            self.current_time = time.time()
            if self.current_time >= self.target_time :
                self._writeMsg('wait_temp func timeout error\n')
                return -1
            
            if (timecnt%WAIT_LOG_TIME) == 0:
                self._writeMsg('wait temp... [' + str(datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')) + '] : ' + str(self.current_temp) + '/' + str(self.target_temp) + ' (' + str(humi) + '%)\n')
            
            timecnt = timecnt+1
            time.sleep(WAIT_TIME)

        self._writeMsg('wait_temp func finish\n')
        return 0

    def wait_time(self, target_time) :
        self._writeMsg('[' + str(datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')) + '] Chamber_Trans>> wait_time ' + str(target_time) + 'sec\n')

        self.current_time = time.time()
        self.target_time = time.time()+target_time
        
        timecnt = 0
        while (self.current_time < self.target_time):
            if (timecnt%WAIT_LOG_TIME) == 0:
                self._writeMsg('wait time... [' + str(datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')) + ']\n')

            timecnt = timecnt+1
            time.sleep(WAIT_TIME)
            self.current_time = time.time()

        self._writeMsg('wait_time func finish\n')
        return 0

    def is_digit(self, str):
        try:
            tmp = float(str)
            return True
        except ValueError:
            return False

    def _get_temp(self) :
        print('_get_temp func')
        
        resp = self._transceive('TEMP?')
        divid_resp = resp.split(',')

        if self.is_digit(divid_resp[0]) == False:
            self._writeMsg('[' + str(datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')) + '] RESPONSE ERROR\n')
            return 'error'
        
        resp = self._transceive('HUMI?')
        divid_humi = resp.split(',')

        return float(divid_resp[0]), float(divid_humi[0])
        
    def _set_temp(self, Temp):
        print('_set_temp func temp = ' + str(Temp))
        resp = self._transceive('TEMP,S' + str(Temp))
        divid_resp = resp.split(':')
        if divid_resp[0] != 'OK':
            self._writeMsg('[' + str(datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')) + '] RESPONSE ERROR\n')
            return 'error'
        else:
            divid_resp2 = divid_resp[1].split(',')
            resp_val = divid_resp2[1].replace('S','')
            if int(resp_val) != int(Temp):
                self._writeMsg('[' + str(datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')) + '] SETTING ERROR\n')
                return 'error'
        
        resp = self._transceive('HUMI,SOFF')
        divid_resp = resp.split(':')
        if divid_resp[0] != 'OK':
            self._writeMsg('[' + str(datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')) + '] HUMI RESPONSE ERROR\n')
            return 'error'
        
        return float(resp_val)
