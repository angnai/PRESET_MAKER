import argparse
import configparser
import Chamber_Control
import BIST_Control
#import Power_Control
import time
import datetime

global log_name

SLEEP_TIME = 0.1
SLEEP_TIME_1SEC = (1/SLEEP_TIME)
LOG_TIME = (3 * SLEEP_TIME_1SEC)

def Get_Argument():
    preset = get_preset()

    parser = argparse.ArgumentParser()
    parser.add_argument('-D', '--devices', type=str, nargs='+', help='Device name example) -D \"dev/ttyUSBx or COMx\"')
    parser.add_argument('-P', '--preset', type=str, nargs='?', help='Preset list) -P n1', choices=preset.sections())
    parser.add_argument('-T', '--test_name', type=str, nargs='?', help='Test name) -T test_name')
    parser.add_argument('-C', '--chamber', type=str, nargs='?', help='Chamber) -C chamber_port')
    args = parser.parse_args()

    preset_list = preset.get(args.preset, 'preset_list').split(',')

    return preset_list, args

def get_preset():
    config = configparser.ConfigParser()
    config.read('preset.ini')
    return config

def get_testcmd():
    config = configparser.ConfigParser()
    config.read('TestCmd.ini')
    return config

def get_bist_cmd(cmd_name):
    args = get_testcmd()
    cmd = args.get(cmd_name, 'Cmd')
    return cmd

def write_log(strDes):
    global log_name

    f = open(log_name + '.txt','a')
    f.write(str(strDes))
    f.close()


def get_cmd_list(preset_val):
    
    bist_cmd = "none"
    ch_cmd = "none"
    pwr_cmd = 'none'
    arg1 = 0
    
    split_var = preset_val.split('_')
    print(preset_val + " and " + split_var[0])
    if split_var[0] == 'ch' :
        if split_var[1] == 'set' or split_var[1] == 'wait':
            try:
                ch_cmd = split_var[1] + '_' + split_var[2]
                
                if split_var[2] == 'temp':
                    # ch_set_temp_n_10 => [ch_cmd = 'set_temp' , arg1[0] = temp_val]
                    # ch_wait_temp_n_10 => [ch_cmd = 'wait_temp' , arg1[0] = temp_val]
                    arg1 = int(split_var[4])
                    if split_var[3] == 'n' or split_var[3] == 'N':
                        arg1 = arg1*-1
                elif split_var[2] == 'time':
                    # ch_wait_time_10 => [ch_cmd = 'wait_time' , arg1 = 10]
                    arg1 = int(split_var[3])
                else:
                    # ch_cmd = 'error'
                    ch_cmd = 'error'
            except:
                # ch_cmd = 'error'
                ch_cmd = 'error'

        elif split_var[1] == 'get':
            if split_var[2] == 'temp':
                # ch_get_temp => [ch_cmd 'get_temp' , arg1 = empty]
                ch_cmd = split_var[1] + '_' + split_var[2]
            else:
                # ch_cmd = 'error'
                ch_cmd = 'error'

        elif split_var[1] == 'start' or split_var[1] == 'stop':
            # ch_start => [ch_cmd 'start' , arg1 = empty]
            # ch_start => [ch_cmd 'stop' , arg1 = empty]
            ch_cmd = split_var[1]
        else:
            # ch_cmd = 'error'
            ch_cmd = 'error'
    elif split_var[0] == 'power' :
        if split_var[1] == 'on':
            pwr_cmd = 'on'
        elif split_var[1] == 'off':
            pwr_cmd = 'off'
        else:
            # ch_cmd = 'error'
            pwr_cmd = 'error'
    else:
        bist_cmd = preset_val

    return bist_cmd, ch_cmd, pwr_cmd, arg1


def Create_BIST_Thread_And_Start(deviceName,TransCmd,LogName):
    dev = []
    for n in range(len(deviceName)):
        dev.append(BIST_Control.BIST(deviceName[n],TransCmd,LogName))
        dev[n].start()
        prt_log(deviceName[n] + 'thread start...\n')

    return dev

def Get_Thread_ReturnValue(n):
    return n.join()

def Remove_Device(devices,n):
    devices.remove(n)

def Get_TestLog_Name(name):
    return (str(datetime.datetime.now().strftime('%Y-%m-%d_%H%M%S')) + '_' + name)

def Threading_Log_Prt(n, timecnt):
    if (timecnt%LOG_TIME) == 0:
        prt_log('< ' + n.GetDeviceName() + ' > Threading... current CMD <' + bist_cmd +'>\n')

def prt_log(str_log):
    print('[' + str(datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')) + '] ' + str_log)
    write_log('[' + str(datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')) + '] ' + str_log)


def Execute_BIST_Cmd(bist_cmd, mDevices, log_name):
    TransCmd = get_bist_cmd(bist_cmd)
    if TransCmd == '':
        prt_log('error command .... stop!\n')
        return -1, mDevices
    
    devices = Create_BIST_Thread_And_Start(mDevices,TransCmd,log_name)

    timecnt = 0
    while True:
        for dev in devices:
            if dev.is_alive():
                Threading_Log_Prt(dev, timecnt)
            else:
                ret = Get_Thread_ReturnValue(dev)
                prt_log(dev.GetDeviceName() + 'ret value = ' + str(ret) + '\n')

                if ret == -1:
                    Remove_Device(mDevices,dev.GetDeviceName())
                    prt_log('!!!!test out device <' + dev.GetDeviceName() + '>\n')
                
                devices.remove(dev)
                break
                
            
        if len(devices) == 0 :
            break
        
        timecnt = timecnt+1
        time.sleep(SLEEP_TIME)

    return 0, mDevices


def Execute_Chamber_Cmd(chb_cmd,arg1,chb_dev,mDevice,log_name):
    ChmbCtrl = Chamber_Control.Chamber(chb_dev,mDevice,log_name)
    if chb_cmd == 'start':
        prt_log('< Chamber > Start CMD\n')
        if ChmbCtrl.start() == -1:
            prt_log('chamber start error!\n')
            return -1
    elif chb_cmd == 'stop':
        prt_log('< Chamber > Stop CMD\n')
        if ChmbCtrl.stop() == -1:
            prt_log('chamber stop error!\n')
            return -1
    elif chb_cmd == 'get_temp':
        prt_log('< Chamber > Get temp CMD\n')
        retVal,retVal2 = ChmbCtrl.get_temp()
        if retVal == 'error':
            prt_log('Get temperature error!\n')
            return -1
        prt_log('Current temperature is ' + str(retVal) + 'huminity is ' + str(retVal2) + '%\n')
    elif chb_cmd == 'set_temp':
        prt_log('< Chamber > Set temp CMD ' + str(arg1) + '\'C\n')
        if ChmbCtrl.set_temp(arg1) == 'error':
            prt_log('Set temperature error!\n')
            return -1
    elif chb_cmd == 'wait_temp':
        prt_log('< Chamber > Wait temperature CMD ' + str(arg1) + '\'C\n')
        if ChmbCtrl.wait_temp(arg1) == -1:
            prt_log('Wait for chamber temperature is timeout error!\n')
            return -1
        else:
            prt_log('Wait for chamber temperature complete!\n')
    elif chb_cmd == 'wait_time':
        prt_log('< Chamber > Wait time CMD ' + str(arg1) + 'sec\n')
        ChmbCtrl.wait_time(arg1)
        prt_log('Wait time complete\n')
    return 0

def Execute_Power_Cmd(pwr_cmd,mDevice,log_name):
    PwrCtrl = Power_control.PowerCtrl(mDevice,log_name)

    if pwr_cmd == 'on':
        PwrCtrl.PowerOn()
    elif pwr_cmd == 'off':
        PwrCtrl.PowerOff()


if __name__ == "__main__":
    global log_name

    
    preset_list, args = Get_Argument()
    log_name = Get_TestLog_Name(args.test_name)
    chb_dev = args.chamber
    retVal = 0

    prt_log('test preset is <' + args.preset + '>\n')

    for pl in preset_list :
        bist_cmd,chb_cmd,pwr_cmd,arg1 = get_cmd_list(pl)

        if bist_cmd != 'none': 
            if retVal == -1:
                if bist_cmd.find('si'):
                    retVal = 0
                    prt_log('<' + bist_cmd + '> SI Command Passed.... Reason is fail into setting value or init\n')
                    continue;
                else:
                    break;
            
            retVal, args.devices = Execute_BIST_Cmd(bist_cmd, args.devices, log_name)
            #if retVal == -1:
            #    break
            
        elif chb_cmd != 'none' :
            if chb_cmd == 'error':
                prt_log('error chamber command .... stop!\n')
                break
            
            if Execute_Chamber_Cmd(chb_cmd, arg1, chb_dev, args.devices, log_name) == -1:
                break
        elif pwr_cmd != 'none' :
            if pwr_cmd == 'error':
                prt_log('error power command ... stop!\n')
                break
            Execute_Power_Cmd(pwr_cmd,args.devices, log_name)

        else:
            prt_log(pl + ' error command .... stop!\n')
            break

    prt_log('Test End..\n')
    