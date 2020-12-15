import sys
import json
from collections import OrderedDict
import matplotlib.pyplot as plt
import seaborn as sns
import matplotlib.cm as cm
from matplotlib.colors import LinearSegmentedColormap

import numpy as np
from matplotlib.ticker import ScalarFormatter

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
tapcnt = int(sys.argv[2])
filename = str(sys.argv[3])
output_index = str(sys.argv[4])

print(str(ch))
print(str(tapcnt))
print(filename)
print(output_index)
#input()
######################################## Create array
strValueWrite = []
strValueRead = []
strValueLunWrite = []
strValueLunRead = []
strCount = []
strLunCount = []
for n in range(ch):
    strValueWrite.append([])
    strValueRead.append([])
    strValueLunWrite.append([])
    strValueLunRead.append([])
    strCount.append(0)
    strLunCount.append([])


######################################## File read
strRead = file_open_fnc(filename)
strLines = strRead.splitlines()


######################################## File data parsing
tc = 0
lun = 0
flag = 1
for strN in range(len(strLines)):
    for n in range(ch):
        if n < 10:
            findStr = '============ test CH[0' + str(n)
        else:
            findStr = '============ test CH[' + str(n)
        
        startIndex = strLines[strN].find(findStr)
        if startIndex != -1:
            if n == 0:
                tc = tc + 1

            if lun == 0:
                for np in range(strN,len(strLines)):
                    lun = lun + 1
                    startIndex = strLines[np].find("LUN[ALL] PROG ")
                    if startIndex != -1:
                        lun = lun-2 
                        break
            if flag == 1:
                print("lun = " + str(lun))
                for jk in range(ch):
                    for li in range(lun):
                        strValueLunWrite[jk].append([])
                        strValueLunRead[jk].append([])
                        strLunCount[jk].append(0)
                flag = 0


            for np in range(strN,len(strLines)):
                startIndex = strLines[np].find("LUN[ALL] PROG ")
                if startIndex != -1:
                    strVal = strLines[np]
                    #strValueWrite[n].append(strVal[14:(14+tapcnt)])
                    strValueWrite[n].append(strVal[14:(len(strVal)+14)])
                    break
		    
            for np in range(strN,len(strLines)):
                startIndex = strLines[np].find("LUN[ALL] READ ")
                if startIndex != -1:
                    strVal = strLines[np]
                    #strValueRead[n].append(strVal[14:(14+tapcnt)])
                    strValueRead[n].append(strVal[14:(len(strVal)+14)])
                    break

            strCount[n] = strCount[n] + 1
            
            strValueWrite[n][strCount[n]-1] = strValueWrite[n][strCount[n]-1].replace('u','7 ')
            strValueWrite[n][strCount[n]-1] = strValueWrite[n][strCount[n]-1].replace('%','7 ')
            strValueWrite[n][strCount[n]-1] = strValueWrite[n][strCount[n]-1].replace('x','7 ')
            strValueWrite[n][strCount[n]-1] = strValueWrite[n][strCount[n]-1].replace('z','7 ')
            strValueWrite[n][strCount[n]-1] = strValueWrite[n][strCount[n]-1].replace(',','5 ')
            strValueWrite[n][strCount[n]-1] = strValueWrite[n][strCount[n]-1].replace('.','3 ')
            strValueWrite[n][strCount[n]-1] = strValueWrite[n][strCount[n]-1].replace('@','3 ')
            strValueWrite[n][strCount[n]-1] = strValueWrite[n][strCount[n]-1].replace('$','1 ')
            strValueWrite[n][strCount[n]-1] = strValueWrite[n][strCount[n]-1].replace('!','1 ')
            
            strValueRead[n][strCount[n]-1] = strValueRead[n][strCount[n]-1].replace('u','7 ')
            strValueRead[n][strCount[n]-1] = strValueRead[n][strCount[n]-1].replace('%','7 ')
            strValueRead[n][strCount[n]-1] = strValueRead[n][strCount[n]-1].replace('x','7 ')
            strValueRead[n][strCount[n]-1] = strValueRead[n][strCount[n]-1].replace('z','7 ')
            strValueRead[n][strCount[n]-1] = strValueRead[n][strCount[n]-1].replace(',','5 ')
            strValueRead[n][strCount[n]-1] = strValueRead[n][strCount[n]-1].replace('.','3 ')
            strValueRead[n][strCount[n]-1] = strValueRead[n][strCount[n]-1].replace('@','3 ')
            strValueRead[n][strCount[n]-1] = strValueRead[n][strCount[n]-1].replace('$','1 ')
            strValueRead[n][strCount[n]-1] = strValueRead[n][strCount[n]-1].replace('!','1 ')
            
            
            for li in range(lun):
                for np in range(strN,len(strLines)):
                    strTemp = "LUN[%03d] PROG " % li
                    startIndex = strLines[np].find(strTemp)
                    if startIndex != -1:
                        #print(str(n) + " " + str(li) + " " + str(strLunCount[n][li]) + " " + strTemp )
                        strVal = strLines[np]
                        #strValueLunWrite[n][li].append(strVal[14:(14+tapcnt)])
                        strValueLunWrite[n][li].append(strVal[14:(len(strVal)+14)])
                        break
            
            for li in range(lun):
                for np in range(strN,len(strLines)):
                    strTemp = "LUN[%03d] READ " % li
                    startIndex = strLines[np].find(strTemp)
                    if startIndex != -1:
                        #print(str(n) + " " + str(li) + " " + str(strLunCount[n][li]) + " " + strTemp )
                        strVal = strLines[np]
                        #strValueLunRead[n][li].append(strVal[14:(14+tapcnt)])
                        strValueLunRead[n][li].append(strVal[14:(len(strVal)+14)])
                        break

            for li in range(lun):
                strLunCount[n][li] = strLunCount[n][li] + 1
                print(str(n) + " " + str(li) + " " + str(strLunCount[n][li]-1) + " " + strValueLunWrite[n][li][strLunCount[n][li]-1])

                strValueLunWrite[n][li][strLunCount[n][li]-1] = strValueLunWrite[n][li][strLunCount[n][li]-1].replace('u','7 ')
                strValueLunWrite[n][li][strLunCount[n][li]-1] = strValueLunWrite[n][li][strLunCount[n][li]-1].replace('%','7 ')
                strValueLunWrite[n][li][strLunCount[n][li]-1] = strValueLunWrite[n][li][strLunCount[n][li]-1].replace('x','7 ')
                strValueLunWrite[n][li][strLunCount[n][li]-1] = strValueLunWrite[n][li][strLunCount[n][li]-1].replace('z','7 ')
                strValueLunWrite[n][li][strLunCount[n][li]-1] = strValueLunWrite[n][li][strLunCount[n][li]-1].replace(',','5 ')
                strValueLunWrite[n][li][strLunCount[n][li]-1] = strValueLunWrite[n][li][strLunCount[n][li]-1].replace('.','3 ')
                strValueLunWrite[n][li][strLunCount[n][li]-1] = strValueLunWrite[n][li][strLunCount[n][li]-1].replace('@','3 ')
                strValueLunWrite[n][li][strLunCount[n][li]-1] = strValueLunWrite[n][li][strLunCount[n][li]-1].replace('$','1 ')
                strValueLunWrite[n][li][strLunCount[n][li]-1] = strValueLunWrite[n][li][strLunCount[n][li]-1].replace('!','1 ')
                
                            
                strValueLunRead[n][li][strLunCount[n][li]-1] = strValueLunRead[n][li][strLunCount[n][li]-1].replace('u','7 ')
                strValueLunRead[n][li][strLunCount[n][li]-1] = strValueLunRead[n][li][strLunCount[n][li]-1].replace('%','7 ')
                strValueLunRead[n][li][strLunCount[n][li]-1] = strValueLunRead[n][li][strLunCount[n][li]-1].replace('x','7 ')
                strValueLunRead[n][li][strLunCount[n][li]-1] = strValueLunRead[n][li][strLunCount[n][li]-1].replace('z','7 ')
                strValueLunRead[n][li][strLunCount[n][li]-1] = strValueLunRead[n][li][strLunCount[n][li]-1].replace(',','5 ')
                strValueLunRead[n][li][strLunCount[n][li]-1] = strValueLunRead[n][li][strLunCount[n][li]-1].replace('.','3 ')
                strValueLunRead[n][li][strLunCount[n][li]-1] = strValueLunRead[n][li][strLunCount[n][li]-1].replace('@','3 ')
                strValueLunRead[n][li][strLunCount[n][li]-1] = strValueLunRead[n][li][strLunCount[n][li]-1].replace('$','1 ')
                strValueLunRead[n][li][strLunCount[n][li]-1] = strValueLunRead[n][li][strLunCount[n][li]-1].replace('!','1 ')
            
######################################## Search valid left right center tap
write_left_right_center_val = []
read_left_right_center_val = []
for n in range(ch):
    write_left_right_center_val.append([])
    read_left_right_center_val.append([])

    for np in range(tc):
        write_left_right_center_val[n].append([])
        left_val,right_val,center_val = Search_Left_Right_Center(strValueWrite[n][np])
        write_left_right_center_val[n][np].append(left_val)
        write_left_right_center_val[n][np].append(right_val)
        write_left_right_center_val[n][np].append(center_val)

        read_left_right_center_val[n].append([])
        left_val,right_val,center_val = Search_Left_Right_Center(strValueRead[n][np])
        read_left_right_center_val[n][np].append(left_val)
        read_left_right_center_val[n][np].append(right_val)
        read_left_right_center_val[n][np].append(center_val)


######################################## Write Json format
file_data = OrderedDict()
file_data["file"] = filename
file_data["testcnt"] = tc
file_data["channelcnt"] = ch
file_data["luncnt"] = lun
file_data["tapcnt"] = tapcnt
for n in range(tc):
    na1 = 'test'+str(n)
    file_data[na1] = {'w0':strValueWrite[0][n]}
    for np in range(ch-1):	
        na2 = 'w'+str(np+1)
        file_data[na1][na2] = strValueWrite[np+1][n]
        
    for np in range(ch):	
        na2 = 'r'+str(np)
        file_data[na1][na2] = strValueRead[np][n]
    

    for np in range(ch):
        for li in range(lun):
            na2 = 'w'+str(np)+'l'+str(li)
            file_data[na1][na2] = strValueLunWrite[np][li][n]
            
    
    for np in range(ch):
        for li in range(lun):
            
            na2 = 'r'+str(np)+'l'+str(li)
            file_data[na1][na2] = strValueLunRead[np][li][n]
    

    na1 = 'test_val'+str(n)
    file_data[na1] = {'left_right_center_w0':[write_left_right_center_val[0][n][0],write_left_right_center_val[0][n][1],write_left_right_center_val[0][n][2]]}
    for np in range(ch-1):
        na2 = 'left_right_center_w'+str(np+1)
        file_data[na1][na2] = write_left_right_center_val[np+1][n][0],write_left_right_center_val[np+1][n][1],write_left_right_center_val[np+1][n][2]
    
    for np in range(ch):
        na2 = 'left_right_center_r'+str(np)
        file_data[na1][na2] = read_left_right_center_val[np][n][0],read_left_right_center_val[np][n][1],read_left_right_center_val[np][n][2]


######################################## Write Json file
file_write_fnc(filename,file_data)




######################################## verification
json_data = file_read_func(filename)

strVal = json_data["file"]
print('test name = ' + str(strVal))
test_cnt = json_data["testcnt"]
print('test count = ' + str(test_cnt))
channel_cnt = json_data["channelcnt"]
print('channel count = ' + str(channel_cnt))
tap_cnt = json_data["tapcnt"]
print('tap count = ' + str(tap_cnt))
lun_cnt = json_data["luncnt"]
print('lun count = ' + str(lun_cnt))


data_test_w = []
data_test_r = []

if output_index == "ch":
    for n in range(channel_cnt):
        data_test_w.append([])
        for np in range(test_cnt):
            strVal = json_data["test"+str(np)]["w"+str(n)]
            #print('ch [' + str(n) + '_w_' + str(np) + '] ' + strVal)
            data_test_w[n].append(strVal.split(' '))
            data_test_w[n][np] = ' '.join(data_test_w[n][np]).split()
            #data_test_w[n][np].remove('')
        
            
    for n in range(channel_cnt):
        data_test_r.append([])
        for np in range(test_cnt):
            strVal = json_data["test"+str(np)]["r"+str(n)]
            print('ch [' + str(n) + '_r_' + str(np) + '] ' + strVal)
            data_test_r[n].append(strVal.split(' '))
            data_test_r[n][np] = ' '.join(data_test_r[n][np]).split()
            #data_test_r[n][np].remove('')
            

        #print('\n\n')

    for np in range(ch):
        for n in range(test_cnt):
            print(str(data_test_w[np][n])+ '\n')
            data_test_w[np][n] = [int (i) for i in data_test_w[np][n]]
            data_test_r[np][n] = [int (i) for i in data_test_r[np][n]]

    #print(data_test_w[0])
    #print('\n\n')
    #print(data_test_r[0])
    #print('\n\n')

    lunelist = []
    for n in range(tap_cnt):
        lunelist.append('lun' + str(n))


    testlist = []
    for n in range(test_cnt):
        if n%3 == 0:
            testlist.append('test' + str(n))

    #print(testlist)
    #print('\n\n')
    

    plt.figure(1)
    for n in range(ch):
        plt.subplot(ch,1,n+1)
        sns.cubehelix_palette(as_cmap=True, reverse=True)
        
        if (n%2) == 0: 
            cmap = LinearSegmentedColormap.from_list('custom blue',     ['#0099cc','#ffffff'], N=3)
        else:
            cmap = LinearSegmentedColormap.from_list('custom blue2',     ['#99ffcc','#ffffff'], N=3)

        sns.heatmap(data=data_test_w[n],fmt='.1f',linewidths='.05',cmap=cmap)
        plt.ylabel('CH ' + str(n))
        
        ax = plt.gca()
        if n != ch-1 :
            ax.axes.xaxis.set_visible(False)
        #ax.axes.yaxis.set_visible(False)
        plt.plot()

    plt.figure(2)
    for n in range(ch):
        plt.subplot(ch,1,n+1)
        sns.cubehelix_palette(as_cmap=True, reverse=True)
        
        if (n%2) == 0: 
            cmap = LinearSegmentedColormap.from_list('custom blue2',     ['#0099cc','#ffffff'], N=3)
        else:
            cmap = LinearSegmentedColormap.from_list('custom blue',     ['#0000ff','#ffffff'], N=3)
        sns.heatmap(data=data_test_r[n],fmt='.1f',linewidths='.05',cmap=cmap)
        plt.ylabel('CH ' + str(n))
        
        ax = plt.gca()
        if n != ch-1 :
            ax.axes.xaxis.set_visible(False)
        #ax.axes.yaxis.set_visible(False)
        plt.plot()

else:
    for li in range(lun_cnt):
        data_test_w.append([])
        data_test_r.append([])
        for n in range(channel_cnt):
            data_test_w[li].append([])
            data_test_r[li].append([])
            for np in range(test_cnt):
                strVal = json_data["test"+str(np)]["w"+str(n)+"l"+str(li)]
                #print('ch [' + str(n) + '_w_' + str(np) + '] ' + strVal)
                data_test_w[li][n].append(strVal.split(' '))
                data_test_w[li][n][np] = ' '.join(data_test_w[li][n][np]).split()
                
                #data_test_w[li][n][np].remove('')
                
                strVal = json_data["test"+str(np)]["r"+str(n)+"l"+str(li)]
                #print('ch [' + str(n) + '_w_' + str(np) + '] ' + strVal)
                data_test_r[li][n].append(strVal.split(' '))
                data_test_r[li][n][np] = ' '.join(data_test_r[li][n][np]).split()
                #data_test_r[li][n][np].remove('')

    for li in range(lun_cnt):
        for np in range(ch):
            for n in range(test_cnt):
                data_test_w[li][np][n] = [int (i) for i in data_test_w[li][np][n]]
                data_test_r[li][np][n] = [int (i) for i in data_test_r[li][np][n]]

    lunelist = []
    for n in range(tap_cnt):
        lunelist.append('lun' + str(n))


    testlist = []
    for n in range(test_cnt):
        testlist.append('test' + str(n))

    #print(testlist)
    #print('\n\n')


    cmap = LinearSegmentedColormap.from_list('custom blue',      ['#0000ff','#ffffff'], N=3)#['#ffffff','#0000ff'], N=3)

    yticklist = []
    for ytickcnt in range(test_cnt+1):
        if (ytickcnt%3) == 0:
            yticklist.append(ytickcnt)
    print(yticklist)

    for li in range(lun_cnt):
        plt.figure(li)
        #plt.title("write LUN %d" % li)
        for n in range(ch):
            plt.subplot(ch,1,n+1)
            plt.xticks([])
            plt.yticks([])
            plt.rcParams["figure.figsize"] = [9, 4]
            plt.tight_layout(pad=0)

            sns.heatmap(data=data_test_w[li][n],fmt='.1f',linewidths='.1',cmap=cmap, vmin=0, vmax=2) #2 or 100
            plt.grid(True, axis='y',color='green', alpha=0.1, linestyle='--')
            plt.ylabel('CH ' + str(n))
            if n != (ch-1):
                ax = plt.gca()
                ax.axes.xaxis.set_visible(False)

            plt.plot()

        plt.figure(li+lun_cnt)
        # #plt.title("read LUN %d" % (li+lun_cnt))
        for n in range(ch):
            plt.subplot(ch,1,n+1)
            plt.xticks([])
            plt.yticks([])
            plt.rcParams["figure.figsize"] = [9, 4]
            plt.tight_layout(pad=0)

            sns.heatmap(data=data_test_r[li][n],fmt='.1f',linewidths='.1',cmap=cmap, vmin=0, vmax=2) #2 or 100
            plt.grid(True, axis='y',color='green', alpha=0.1, linestyle='--')
            plt.ylabel('CH ' + str(n))
            if n != (ch-1):
                ax = plt.gca()
                ax.axes.xaxis.set_visible(False)

            plt.plot()

plt.show()
    