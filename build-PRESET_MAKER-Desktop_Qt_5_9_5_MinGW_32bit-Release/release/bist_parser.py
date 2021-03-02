import sys
import json
from collections import OrderedDict
from matplotlib import pyplot as plt
import seaborn as sns
import matplotlib.cm as cm
from matplotlib.colors import LinearSegmentedColormap
import numpy as np
from matplotlib.ticker import ScalarFormatter
import os
import datetime
import time
from matplotlib import gridspec

def createFolder(directory):
    try:
        if not os.path.exists(directory):
            os.makedirs(directory)
    except OSError:
        print ('Error: Creating directory. ' +  directory)
 

def file_open_fnc(strPath):
    f = open(strPath,'r')
    strRead = f.read()
    f.close()

    return strRead


def file_write_fnc(strPath, jsonStr):
    strPath = strPath.replace('.log','')
    with open(strPath +'.json','w',encoding="utf-8") as make_file:
        json.dump(jsonStr,make_file,ensure_ascii=False,indent="\t")


def file_read_func(strPath):
    strPath = strPath.replace('.log','.json')
    with open(strPath) as json_file:
        json_data = json.load(json_file)

    return json_data


def Search_Left_Right_Center(strVal):
    max_left_val = 0
    max_tap_val = 0

    left_val = 0
    tap_val = 0
    center_val = 0

    val_cnt = 0

    strVal = strVal.replace(' ','')
    for n in range(len(strVal)):
        if strVal[n] == ' ':
            continue
        
        if strVal[n] == '1':
            center_val = val_cnt
        elif strVal[n] == '3' and left_val == 0:
            left_val = val_cnt
        elif (strVal[n] == '5' or strVal[n] == '7') and left_val != 0:
            if max_tap_val < tap_val:
                max_tap_val = tap_val
                max_left_val = left_val

                left_val = 0
                tap_val = 0

        if left_val != 0:
            tap_val = tap_val + 1

        val_cnt = val_cnt + 1

    if max_tap_val < tap_val:
        max_tap_val = tap_val
        max_left_val = left_val

        left_val = 0
        tap_val = 0

    return max_left_val,(max_left_val+max_tap_val-1),center_val

############# Main Function



######################################## main argument

ch = int(sys.argv[1])
output_index = str(sys.argv[2])
filename = str(sys.argv[3])
lun = 8

if filename.find('.json') != -1:
    analysis = 0
else:
    analysis = 1

print(str(ch))
print(filename)
print(output_index)

######################################## Create array
strValueWrite = []
strValueRead = []
strValueLunWrite = []
strValueLunRead = []
strCount = []
strLunCount = []

write_left_right_center_val = []
read_left_right_center_val = []
for n in range(ch):
    strValueWrite.append([])
    strValueRead.append([])
    strCount.append(0)

    write_left_right_center_val.append([])
    read_left_right_center_val.append([])

    strValueLunWrite.append([])
    strValueLunRead.append([])
    strLunCount.append([])
    for li in range(lun):
        strValueLunWrite[n].append([])
        strValueLunRead[n].append([])
        

######################################## File read
strRead = file_open_fnc(filename)
strLines = strRead.splitlines()
######################################## File data parsing

analysis_test_count = 1
if analysis == 1:

    for strN in range(len(strLines)):
        
        if strLines[strN].find('ch write read') != -1:
            for n in range(ch):
                write_left_right_center_val[n].append([])
                write_left_right_center_val[n][strCount[n]-1] = []
                read_left_right_center_val[n].append([])
                read_left_right_center_val[n][strCount[n]-1] = []
                
                strValue = strLines[strN + 1 + n].split(' ')
                write_left_right_center_val[n][strCount[n]-1].append(strValue[1])
                read_left_right_center_val[n][strCount[n]-1].append(strValue[2])
        elif strLines[strN].find('ch write_left write_right read_left read_right') != -1:
            for n in range(ch):
                strValue = strLines[strN + 1 + n].split(' ')
                write_left_right_center_val[n][strCount[n]-1].append(strValue[1])
                write_left_right_center_val[n][strCount[n]-1].append(strValue[2])
                read_left_right_center_val[n][strCount[n]-1].append(strValue[3])
                read_left_right_center_val[n][strCount[n]-1].append(strValue[4])
        for n in range(ch):
           
            if n < 10:
                findStr = '============ test CH[0' + str(n)
            else:
                findStr = '============ test CH[' + str(n)
            
            startIndex = strLines[strN].find(findStr)
            if startIndex != -1:

                strValueWrite[n].append([])
                strValueRead[n].append([])

                for li in range(lun):
                    strValueLunWrite[n][li].append([])

                    for np in range(strN,len(strLines)):
                        strTemp = "LUN[%03d] PROG " % li
                        startIndex = strLines[np].find(strTemp)
                        if startIndex != -1:
                            strVal = strLines[np]
                            strValueLunWrite[n][li][strCount[n]] = (strVal[14:(len(strVal)+14)])
                            break
                        
                        if strLines[np].find("LUN[ALL] PROG ") != -1:
                            break;
                
                for li in range(lun):
                    strValueLunRead[n][li].append([])

                    for np in range(strN,len(strLines)):
                        strTemp = "LUN[%03d] READ " % li
                        startIndex = strLines[np].find(strTemp)
                        if startIndex != -1:
                            strVal = strLines[np]
                            strValueLunRead[n][li][strCount[n]] = (strVal[14:(len(strVal)+14)])
                            break
                        
                        if strLines[np].find("LUN[ALL] READ ") != -1:
                            break;

                for np in range(strN,len(strLines)):
                    startIndex = strLines[np].find("LUN[ALL] PROG ")
                    if startIndex != -1:
                        strVal = strLines[np]
                        strValueWrite[n][strCount[n]] = strVal[14:(len(strVal)+14)]
                        break

                for np in range(strN,len(strLines)):
                    startIndex = strLines[np].find("LUN[ALL] READ ")
                    if startIndex != -1:
                        strVal = strLines[np]
                        strValueRead[n][strCount[n]] = strVal[14:(len(strVal)+14)]
                        break

                for li in range(lun):
                    if not strValueLunWrite[n][li][strCount[n]]:
                        continue
                    else:
                        #if (strValueLunWrite[n][li][strCount[n]][2] >= '0') and (strValueLunWrite[n][li][strCount[n]][2] <= '9'):
                        #    continue;
                        checkCount = strValueLunWrite[n][li][strCount[n]].split(' ')
                        checkCount = ' '.join(checkCount).split()
                        if (checkCount[0][0] >= '0') and (checkCount[0][0] <= '9'):
                            continue;
                        
                        
                        if len(strValueLunWrite[n][li][strCount[n]]) > 128:
                            strValueLunWrite[n][li][strCount[n]] = strValueLunWrite[n][li][strCount[n]][0:128]
                            
                        strValueLunWrite[n][li][strCount[n]] = strValueLunWrite[n][li][strCount[n]].replace('u','7 ')
                        strValueLunWrite[n][li][strCount[n]] = strValueLunWrite[n][li][strCount[n]].replace('%','7 ')
                        strValueLunWrite[n][li][strCount[n]] = strValueLunWrite[n][li][strCount[n]].replace('x','7 ')
                        strValueLunWrite[n][li][strCount[n]] = strValueLunWrite[n][li][strCount[n]].replace('z','7 ')
                        strValueLunWrite[n][li][strCount[n]] = strValueLunWrite[n][li][strCount[n]].replace(',','5 ')
                        strValueLunWrite[n][li][strCount[n]] = strValueLunWrite[n][li][strCount[n]].replace('.','3 ')
                        strValueLunWrite[n][li][strCount[n]] = strValueLunWrite[n][li][strCount[n]].replace('@','3 ')
                        strValueLunWrite[n][li][strCount[n]] = strValueLunWrite[n][li][strCount[n]].replace('$','1 ')
                        strValueLunWrite[n][li][strCount[n]] = strValueLunWrite[n][li][strCount[n]].replace('!','1 ')
                    
                    if not strValueLunRead[n][li][strCount[n]]:
                        continue
                    else:
                        #if (strValueLunRead[n][li][strCount[n]][2] >= '0') and (strValueLunRead[n][li][strCount[n]][2] <= '9'):
                        #    continue;
                        checkCount = strValueLunRead[n][li][strCount[n]].split(' ')
                        checkCount = ' '.join(checkCount).split()
                        if (checkCount[0][0] >= '0') and (checkCount[0][0] <= '9'):
                            continue;
                        
                        if len(strValueLunRead[n][li][strCount[n]]) > 128:
                            strValueLunRead[n][li][strCount[n]] = strValueLunRead[n][li][strCount[n]][0:128]

                        strValueLunRead[n][li][strCount[n]] = strValueLunRead[n][li][strCount[n]].replace('u','7 ')
                        strValueLunRead[n][li][strCount[n]] = strValueLunRead[n][li][strCount[n]].replace('%','7 ')
                        strValueLunRead[n][li][strCount[n]] = strValueLunRead[n][li][strCount[n]].replace('x','7 ')
                        strValueLunRead[n][li][strCount[n]] = strValueLunRead[n][li][strCount[n]].replace('z','7 ')
                        strValueLunRead[n][li][strCount[n]] = strValueLunRead[n][li][strCount[n]].replace(',','5 ')
                        strValueLunRead[n][li][strCount[n]] = strValueLunRead[n][li][strCount[n]].replace('.','3 ')
                        strValueLunRead[n][li][strCount[n]] = strValueLunRead[n][li][strCount[n]].replace('@','3 ')
                        strValueLunRead[n][li][strCount[n]] = strValueLunRead[n][li][strCount[n]].replace('$','1 ')
                        strValueLunRead[n][li][strCount[n]] = strValueLunRead[n][li][strCount[n]].replace('!','1 ')
                
                    
                
                if not strValueWrite[n][strCount[n]]:
                    strCount[n] = strCount[n] + 1
                    continue
                else:
                    #if (strValueWrite[n][strCount[n]][2] >= '0') and (strValueWrite[n][strCount[n]][2] <= '9'):
                    #    strCount[n] = strCount[n] + 1
                    #    continue
                    checkCount = strValueWrite[n][strCount[n]].split(' ')
                    checkCount = ' '.join(checkCount).split()
                    if (checkCount[0][0] >= '0') and (checkCount[0][0] <= '9'):
                        strCount[n] = strCount[n] + 1
                        continue;
                    
                    analysis_test_count = 0
                    if len(strValueWrite[n][strCount[n]]) > 128:
                        strValueWrite[n][strCount[n]] = strValueWrite[n][strCount[n]][0:128]

                    strValueWrite[n][strCount[n]] = strValueWrite[n][strCount[n]].replace('u','7 ')
                    strValueWrite[n][strCount[n]] = strValueWrite[n][strCount[n]].replace('%','7 ')
                    strValueWrite[n][strCount[n]] = strValueWrite[n][strCount[n]].replace('x','7 ')
                    strValueWrite[n][strCount[n]] = strValueWrite[n][strCount[n]].replace('z','7 ')
                    strValueWrite[n][strCount[n]] = strValueWrite[n][strCount[n]].replace(',','5 ')
                    strValueWrite[n][strCount[n]] = strValueWrite[n][strCount[n]].replace('.','3 ')
                    strValueWrite[n][strCount[n]] = strValueWrite[n][strCount[n]].replace('@','3 ')
                    strValueWrite[n][strCount[n]] = strValueWrite[n][strCount[n]].replace('$','1 ')
                    strValueWrite[n][strCount[n]] = strValueWrite[n][strCount[n]].replace('!','1 ')
                
                
                if not strValueRead[n][strCount[n]]:
                    strCount[n] = strCount[n] + 1
                    continue
                else:
                    #if (strValueRead[n][strCount[n]][2] >= '0') and (strValueRead[n][strCount[n]][2] <= '9'):
                    #    strCount[n] = strCount[n] + 1
                    #    continue
                    checkCount = strValueRead[n][strCount[n]].split(' ')
                    checkCount = ' '.join(checkCount).split()
                    if (checkCount[0][0] >= '0') and (checkCount[0][0] <= '9'):
                        strCount[n] = strCount[n] + 1
                        continue;

                    analysis_test_count = 0
                    if len(strValueRead[n][strCount[n]]) > 128:
                        strValueRead[n][strCount[n]] = strValueRead[n][strCount[n]][0:128]

                    strValueRead[n][strCount[n]] = strValueRead[n][strCount[n]].replace('u','7 ')
                    strValueRead[n][strCount[n]] = strValueRead[n][strCount[n]].replace('%','7 ')
                    strValueRead[n][strCount[n]] = strValueRead[n][strCount[n]].replace('x','7 ')
                    strValueRead[n][strCount[n]] = strValueRead[n][strCount[n]].replace('z','7 ')
                    strValueRead[n][strCount[n]] = strValueRead[n][strCount[n]].replace(',','5 ')
                    strValueRead[n][strCount[n]] = strValueRead[n][strCount[n]].replace('.','3 ')
                    strValueRead[n][strCount[n]] = strValueRead[n][strCount[n]].replace('@','3 ')
                    strValueRead[n][strCount[n]] = strValueRead[n][strCount[n]].replace('$','1 ')
                    strValueRead[n][strCount[n]] = strValueRead[n][strCount[n]].replace('!','1 ')

                strCount[n] = strCount[n] + 1

    tc = 0
    for n in range(ch):
        if tc < strCount[n]:
            tc = strCount[n]
    print('tc = ' + str(tc))
    ######################################## Write Json format
    file_data = OrderedDict()
    file_data["file"] = filename
    file_data["testcnt"] = tc
    file_data["channelcnt"] = ch
    file_data["luncnt"] = lun


    for n in range(tc):
        na1 = 'test'+str(n)
        file_data[na1] = {'w0':[]}
        for np in range(ch):	
            na2 = 'w'+str(np)

            if len(strValueWrite[np]) <= n:
                file_data[na1][na2] = [];
            else:
                file_data[na1][na2] = strValueWrite[np][n]
            
        for np in range(ch):	
            na2 = 'r'+str(np)

            if len(strValueWrite[np]) <= n:
                file_data[na1][na2] = [];
            else:
                file_data[na1][na2] = strValueRead[np][n]
        

        for np in range(ch):
            for li in range(lun):
                na2 = 'w'+str(np)+'l'+str(li)

                if len(strValueWrite[np]) <= n:
                    file_data[na1][na2] = [];
                else:
                    file_data[na1][na2] = strValueLunWrite[np][li][n]
                
        
        for np in range(ch):
            for li in range(lun):
                na2 = 'r'+str(np)+'l'+str(li)

                if len(strValueWrite[np]) <= n:
                    file_data[na1][na2] = [];
                else:
                    file_data[na1][na2] = strValueLunRead[np][li][n]
        
        na1 = 'test_val'+str(n)
        file_data[na1] = {'left_right_center_w0':[write_left_right_center_val[0][n][1],write_left_right_center_val[0][n][2],write_left_right_center_val[0][n][0]]}
        for np in range(ch-1):
            na2 = 'left_right_center_w'+str(np+1)
            print(na2)
            file_data[na1][na2] = write_left_right_center_val[np+1][n][1],write_left_right_center_val[np+1][n][2],write_left_right_center_val[np+1][n][0]
        
        for np in range(ch):
            na2 = 'left_right_center_r'+str(np)
            file_data[na1][na2] = read_left_right_center_val[np][n][1],read_left_right_center_val[np][n][2],read_left_right_center_val[np][n][0]


    ######################################## Write Json file
    file_write_fnc(filename,file_data)




######################################## verification
json_data = file_read_func(filename)

t_n = json_data["file"]
print('test name = ' + str(t_n))
test_cnt = json_data["testcnt"]
print('test count = ' + str(test_cnt))
channel_cnt = json_data["channelcnt"]
print('channel count = ' + str(channel_cnt))
lun_cnt = json_data["luncnt"]
print('lun count = ' + str(lun_cnt))


if output_index == 'ui':
    for tc in range(test_cnt):
        str_ui = ''
        for n in range(channel_cnt):
            left = json_data['test_val'+str(tc)]['left_right_center_w'+str(n)][0]
            right = json_data['test_val'+str(tc)]['left_right_center_w'+str(n)][1]
            ui_val = (int(right) - int(left) + 1) / 128
            str_ui = str_ui + str(ui_val) + ' '
        for n in range(channel_cnt):
            left = json_data['test_val'+str(tc)]['left_right_center_r'+str(n)][0]
            right = json_data['test_val'+str(tc)]['left_right_center_r'+str(n)][1]
            ui_val = (int(right) - int(left) + 1) / 128
            str_ui = str_ui + str(ui_val) + ' '
        print(str_ui)
    sys.exit()


ch_data_test_w = []
ch_data_test_r = []
max_len = 0
for n in range(channel_cnt):
    ch_data_test_w.append([])
    ch_data_test_r.append([])
    for np in range(test_cnt):
        strVal = json_data["test"+str(np)]["w"+str(n)]

        if not strVal:
            ch_data_test_w[n].append([])
        else:
            ch_data_test_w[n].append(strVal.split(' '))
            ch_data_test_w[n][np] = ' '.join(ch_data_test_w[n][np]).split()
    

        strVal = json_data["test"+str(np)]["r"+str(n)]
        
        if not strVal:
            ch_data_test_r[n].append([])
        else:
            ch_data_test_r[n].append(strVal.split(' '))
            ch_data_test_r[n][np] = ' '.join(ch_data_test_r[n][np]).split()
            if max_len < len(ch_data_test_r[n][np]):
                    max_len = len(ch_data_test_r[n][np])

for n in range(channel_cnt):
    for np in range(test_cnt):
        if not ch_data_test_w[n][np]:
            ch_data_test_w[n][np] = [];
            for tap in range(max_len):
                ch_data_test_w[n][np].append('9999')
            
        if not ch_data_test_r[n][np]:
            for tap in range(max_len):
                ch_data_test_r[n][np].append('9999')

for np in range(ch):
    for n in range(test_cnt):
        ch_data_test_w[np][n] = [int (i) for i in ch_data_test_w[np][n]]
        ch_data_test_r[np][n] = [int (i) for i in ch_data_test_r[np][n]]


lun_data_test_w = []
lun_data_test_r = []
max_len = 0
for li in range(lun_cnt):
    lun_data_test_w.append([])
    lun_data_test_r.append([])
    for n in range(channel_cnt):
        lun_data_test_w[li].append([])
        lun_data_test_r[li].append([])
        for np in range(test_cnt):
            strVal = json_data["test"+str(np)]["w"+str(n)+"l"+str(li)]
            
            if not strVal:
                lun_data_test_w[li][n].append([])
            else:
                lun_data_test_w[li][n].append(strVal.split(' '))
                lun_data_test_w[li][n][np] = ' '.join(lun_data_test_w[li][n][np]).split()
            
            
            strVal = json_data["test"+str(np)]["r"+str(n)+"l"+str(li)]
            if not strVal:
                lun_data_test_r[li][n].append([])
            else:
                lun_data_test_r[li][n].append(strVal.split(' '))
                lun_data_test_r[li][n][np] = ' '.join(lun_data_test_r[li][n][np]).split()
                if max_len < len(lun_data_test_r[li][n][np]):
                    max_len = len(lun_data_test_r[li][n][np])

for li in range(lun_cnt):
    for n in range(channel_cnt):
        for np in range(test_cnt):
            if not lun_data_test_w[li][n][np]:
                lun_data_test_w[li][n][np] = [];
                for tap in range(max_len):
                    lun_data_test_w[li][n][np].append('9999')
                
            if not lun_data_test_r[li][n][np]:
                for tap in range(max_len):
                    lun_data_test_r[li][n][np].append('9999')

for li in range(lun_cnt):
    for np in range(ch):
        for n in range(test_cnt):
            lun_data_test_w[li][np][n] = [int (i) for i in lun_data_test_w[li][np][n]]
            lun_data_test_r[li][np][n] = [int (i) for i in lun_data_test_r[li][np][n]]


fig = []
fn = []

plt.figure(figsize=(20,10))
SMALL_SIZE = 8
MEDIUM_SIZE = 8
BIGGER_SIZE = 8

plt.rc('font', size=SMALL_SIZE) # controls default text sizes
plt.rc('axes', titlesize=SMALL_SIZE) # fontsize of the axes title
plt.rc('axes', labelsize=MEDIUM_SIZE) # fontsize of the x and y labels
plt.rc('xtick', labelsize=SMALL_SIZE) # fontsize of the tick labels
plt.rc('ytick', labelsize=SMALL_SIZE) # fontsize of the tick labels
plt.rc('legend', fontsize=SMALL_SIZE) # legend fontsize
plt.rc('figure', titlesize=BIGGER_SIZE) # fontsize of the figure title


range_yticks = []
range_ytexts = []
for np in range(test_cnt):
    range_yticks.append(np)
    range_ytexts.append(format((1000 - (np * 50))/1000,'.2f') + 'v')


if output_index == 'ch_all':

    fig.append(plt.figure(1,figsize=(20,10)))
    fn.append('write_channel_all.png')
    for n in range(ch):
        plt.subplot(ch,1,n+1)

        if (n%2) == 0: 
            cmap = LinearSegmentedColormap.from_list('custom blue',     ['#0099cc','#ffffff'], N=3)
        else:
            cmap = LinearSegmentedColormap.from_list('custom blue2',     ['#99ffcc','#ffffff'], N=3)
        sns.cubehelix_palette(as_cmap=True, reverse=True)
        if analysis_test_count == 0:
            sns.heatmap(data=ch_data_test_w[n],fmt='.1f',linewidths='.05',cmap=cmap, vmin=0, vmax=1)
        else:
            sns.heatmap(data=ch_data_test_w[n],fmt='.1f',linewidths='.05',cmap=cmap, vmin=0, vmax=1)
        
        plt.grid(True, axis='y',color='green', alpha=0.1, linestyle='--')
        plt.ylabel('CH ' + str(n))
        plt.yticks(range_yticks, range_ytexts, rotation=45)
        
        
        if n != ch-1 :
            ax = plt.gca()
            ax.axes.xaxis.set_visible(False)
        plt.plot()

    fig.append(plt.figure(2,figsize=(20,10)))
    fn.append('read_channel_all.png')
    for n in range(ch):
        plt.subplot(ch,1,n+1)
        
        if (n%2) == 0: 
            cmap = LinearSegmentedColormap.from_list('custom blue2',     ['#0099cc','#ffffff'], N=3)
        else:
            cmap = LinearSegmentedColormap.from_list('custom blue',     ['#0000ff','#ffffff'], N=3)
        sns.cubehelix_palette(as_cmap=True, reverse=True)
        if analysis_test_count == 0:
            sns.heatmap(data=ch_data_test_r[n],fmt='.1f',linewidths='.05',cmap=cmap, vmin=0, vmax=1)
        else:
            sns.heatmap(data=ch_data_test_r[n],fmt='.1f',linewidths='.05',cmap=cmap, vmin=0, vmax=1)
        
        plt.grid(True, axis='y',color='green', alpha=0.1, linestyle='--')
        plt.ylabel('CH ' + str(n))
        plt.yticks(range_yticks, range_ytexts, rotation=45)
        
        
        if n != ch-1 :
            ax = plt.gca()
            ax.axes.xaxis.set_visible(False)
        plt.plot()

elif output_index == 'lun_all':

    for li in range(lun_cnt):
        fig.append(plt.figure(li,figsize=(20,10)))
        fn.append('write_channel_lun%d.png' % li)
        for n in range(ch):
            plt.subplot(ch,1,n+1)
            
            if (n%2) == 0: 
                cmap = LinearSegmentedColormap.from_list('custom blue',     ['#0099cc','#ffffff'], N=3)
            else:
                cmap = LinearSegmentedColormap.from_list('custom blue2',     ['#99ffcc','#ffffff'], N=3)
            sns.cubehelix_palette(as_cmap=True, reverse=True)
            if analysis_test_count == 0:
            	sns.heatmap(data=lun_data_test_w[li][n],fmt='.1f',linewidths='.1',cmap=cmap, vmin=0, vmax=1) #2 or 100
            else:
                sns.heatmap(data=lun_data_test_w[li][n],fmt='.1f',linewidths='.1',cmap=cmap, vmin=0, vmax=1) #2 or 100

            plt.grid(True, axis='y',color='green', alpha=0.1, linestyle='--')
            plt.ylabel('CH ' + str(n))
            plt.yticks(range_yticks, range_ytexts, rotation=45)
            
            
            if n != (ch-1):
                ax = plt.gca()
                ax.axes.xaxis.set_visible(False)

            plt.plot()

        fig.append(plt.figure(li+lun_cnt,figsize=(20,10)))
        fn.append('read_channel_lun%d.png' % li)
        for n in range(ch):
            plt.subplot(ch,1,n+1)
            
            if (n%2) == 0: 
                cmap = LinearSegmentedColormap.from_list('custom blue2',     ['#0099cc','#ffffff'], N=3)
            else:
                cmap = LinearSegmentedColormap.from_list('custom blue',     ['#0000ff','#ffffff'], N=3)
            sns.cubehelix_palette(as_cmap=True, reverse=True)
            if analysis_test_count == 0:
                sns.heatmap(data=lun_data_test_r[li][n],fmt='.1f',linewidths='.1',cmap=cmap, vmin=0, vmax=1) #2 or 100
            else:
                sns.heatmap(data=lun_data_test_r[li][n],fmt='.1f',linewidths='.1',cmap=cmap, vmin=0, vmax=1) #2 or 100
            plt.grid(True, axis='y',color='green', alpha=0.1, linestyle='--')
            plt.ylabel('CH ' + str(n))
            plt.yticks(range_yticks, range_ytexts, rotation=45)
            

            if n != (ch-1):
                ax = plt.gca()
                ax.axes.xaxis.set_visible(False)

            plt.plot()

elif output_index == 'each_ch':
    
    spec = gridspec.GridSpec(ncols=1, nrows=2, height_ratios=[1, 1])
    for n in range(ch):
        fig.append(plt.figure(n,figsize=(20,10)))
        fn.append('each_ch%d.png' % n)

        plt.subplot(spec[0])

        
        cmap = LinearSegmentedColormap.from_list('custom blue',     ['#0099cc','#ffffff'], N=3)
        sns.cubehelix_palette(as_cmap=True, reverse=True)
        if analysis_test_count == 0:
            sns.heatmap(data=ch_data_test_w[n],fmt='.1f',linewidths='.05',cmap=cmap, vmin=0, vmax=1)
        else:
            sns.heatmap(data=ch_data_test_w[n],fmt='.1f',linewidths='.05',cmap=cmap, vmin=0, vmax=1)
        plt.grid(True, axis='y',color='green', alpha=0.1, linestyle='--')
        plt.ylabel('W_CH ' + str(n))
        
        #ax = plt.gca()
        #ax.axes.xaxis.set_visible(False)
        #plt.plot()

        #fig.append(plt.figure(n+ch,figsize=(20,10)))
        #fn.append('read_channel_%d.png' % n)
        plt.subplot(spec[1])

        cmap = LinearSegmentedColormap.from_list('custom blue',     ['#0000ff','#ffffff'], N=3)
        sns.cubehelix_palette(as_cmap=True, reverse=True)
        if analysis_test_count == 0:
            sns.heatmap(data=ch_data_test_r[n],fmt='.1f',linewidths='.05',cmap=cmap, vmin=0, vmax=1)
        else:
            sns.heatmap(data=ch_data_test_r[n],fmt='.1f',linewidths='.05',cmap=cmap, vmin=0, vmax=1)

        plt.grid(True, axis='y',color='green', alpha=0.1, linestyle='--')
        plt.ylabel('R_CH ' + str(n))
        #plt.yticks(range_yticks, range_ytexts, rotation=45)
        
        #ax = plt.gca()
        #ax.axes.xaxis.set_visible(False)
        plt.plot()
    

elif output_index == 'each_lun':

    spec = gridspec.GridSpec(ncols=1, nrows=2, height_ratios=[1, 1])
    for li in range(lun_cnt):
        for n in range(ch):
            fig.append(plt.figure(n+(li*ch),figsize=(20,10)))
            fn.append('each_ch%d_lun%d.png' % (n, li))

            #plt.subplot(ch,1,1)
            plt.subplot(spec[0])
            
            cmap = LinearSegmentedColormap.from_list('custom blue',     ['#0099cc','#ffffff'], N=3)
            sns.cubehelix_palette(as_cmap=True, reverse=True)
            if analysis_test_count == 0:
                sns.heatmap(data=lun_data_test_w[li][n],fmt='.1f',linewidths='.1',cmap=cmap, vmin=0, vmax=1) #2 or 100
            else:
                sns.heatmap(data=lun_data_test_w[li][n],fmt='.1f',linewidths='.1',cmap=cmap, vmin=0, vmax=1) #2 or 100
            plt.grid(True, axis='y',color='green', alpha=0.1, linestyle='--')
            plt.ylabel('W_CH[' + str(n) + ']LUN[' + str(li) + ']')
            plt.yticks(range_yticks, range_ytexts, rotation=45)
            
            
            #ax = plt.gca()
            #ax.axes.xaxis.set_visible(False)

            #plt.plot()

            #plt.subplot(ch,1,2)
            plt.subplot(spec[1])
            
            cmap = LinearSegmentedColormap.from_list('custom blue',     ['#0000ff','#ffffff'], N=3)
            sns.cubehelix_palette(as_cmap=True, reverse=True)
            if analysis_test_count == 0:
                sns.heatmap(data=lun_data_test_r[li][n],fmt='.1f',linewidths='.1',cmap=cmap, vmin=0, vmax=1) #2 or 100
            else:
                sns.heatmap(data=lun_data_test_r[li][n],fmt='.1f',linewidths='.1',cmap=cmap, vmin=0, vmax=1) #2 or 100
            plt.grid(True, axis='y',color='green', alpha=0.1, linestyle='--')
            plt.ylabel('R_CH[' + str(n) + ']LUN[' + str(li) + ']')
            plt.yticks(range_yticks, range_ytexts, rotation=45)
            

            #ax = plt.gca()
            #ax.axes.xaxis.set_visible(False)

            plt.plot()
#fig
now = time.localtime()
s = "%04d%02d%02d_%02d%02d%02d_%s" % (now.tm_year, now.tm_mon, now.tm_mday, now.tm_hour, now.tm_min, now.tm_sec, t_n)
createFolder(s)
for n in range(len(fig)):
    fig[n].savefig(s + '/' + fn[n])
#plt.show()
