from enum import Enum
import time
import datetime


MIN = (60)
HOUR = (MIN*60)
LIMIT_TIMEOUT = (1*HOUR)

WAIT_TIME = 0.1
WAIT_TIME_1SEC = (1/WAIT_TIME)
WAIT_LOG_TIME = (10 * WAIT_TIME_1SEC)


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

    def start(self) :
        self._writeMsg('[' + str(datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')) + '] Chamber_Trans>> Start\n')
        return 0

    def stop(self) :
        self._writeMsg('[' + str(datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')) + '] Chamber_Trans>> Stop\n')
        return 0

    def get_temp(self) :
        self._writeMsg('[' + str(datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')) + '] Chamber_Trans>> get_temp\n')
        val = self._get_temp()
        self._writeMsg('current temp : ' + str(val) + '\'C\n')
        return val

    def set_temp(self,Temp) :
        self._writeMsg('[' + str(datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')) + '] Chamber_Trans>> set_temp ' + str(Temp) + '\'C\n')
        return self._set_temp(Temp)

    def wait_temp(self, target_temp) :
        self._writeMsg('[' + str(datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')) + '] Chamber_Trans>> wait_temp ' + str(target_temp) + '\'C\n')

        self.target_temp = target_temp
        self.current_temp = self._get_temp()

        self.current_time = time.time()
        self.target_time = time.time()+LIMIT_TIMEOUT
        
        while (self.target_temp != self.current_temp) :
            self.current_temp = self._get_temp()

            timecnt = 0
            self.current_time = time.time()
            if self.current_time >= self.target_time :
                self._writeMsg('wait_temp func timeout error\n')
                return -1
            
            if (timecnt%WAIT_LOG_TIME) == 0:
                self._writeMsg('wait temp... [' + str(datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')) + '] : ' + str(self.current_temp) + '/' + str(self.target_temp) + '\n')
            
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
            self.current_time = time.time()

            if (timecnt%(WAIT_LOG_TIME*2)) == 0:
                self._writeMsg('wait time... [' + str(datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')) + ']\n')

            timecnt = timecnt+1
            time.sleep(WAIT_TIME)

        self._writeMsg('wait_time func finish\n')
        return 0

    def _get_temp(self) :
        print('_get_temp func')
        Temp = 1
        return Temp
        
    def _set_temp(self, Temp) :
        print('_set_temp func temp = ' + str(Temp))
        return Temp
        