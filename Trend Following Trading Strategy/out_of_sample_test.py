"""trading_main.py: trading strategy implemented. Uses functions
and variables from trading_module.py"""

from trading_module import calculate_max_dd
from trading_module import get_price_data
import pandas



import numpy as np 
import matplotlib.pyplot as plt
import timeit



def main():
    W,L=[],[]
    which_data = "X" #initial invalid value for which data set to use
    channel_start = 0 #first index of channel # initalized to zero# last index of channel # initalized to zero
    
    which_data = input("Which data set? Enter '1' for US Dollar Index, '2' for Treasuries:\n")
    which_data = int(which_data)
    T=input("T")
    tau=input("tau")
    parameter=pandas.read_csv("GridSearchOutputT10t3.csv",header=None)
    parac=parameter[1]
    parat=parameter[0]
    Open_wdata,Close_wdata,High_wdata,Low_wdata = get_price_data(which_data)
    current_wlist=np.zeros(len(Close_wdata))
    max_wlist=np.zeros(len(Close_wdata))
    current=100000
    sell=0
    buy=0
    market_position=0
    gross_gain=0
    gross_loss=0
    Winner,win_period=0,0
    Loser,lose_period=0,0
    period=0
    for i in range (0 , len(parac)):
        High = 0 # initalized to zero
        Low = 0 # initalized to zero
        Open=0
        Close=0
        prev_peak = 0 # initalized to zero
        prev_trough = 0 # initalized to zero
        channel_high=[]# the set of prices for a particular channel
        hh=0
        ll=0
        channel_length=parac[i]
        stop_percentage=parat[i]
        Open_data=Open_wdata[T*252*80+80*21*tau*i-channel_length:T*252*80+80*21*tau*(i+1)]
        Close_data=Close_wdata[T*252*80+80*21*tau*i-channel_length:T*252*80+80*21*tau*(i+1)]
        High_data=High_wdata[T*252*80+80*21*tau*i-channel_length:T*252*80+80*21*tau*(i+1)]
        Low_data=Low_wdata[T*252*80+80*21*tau*i-channel_length:T*252*80+80*21*tau*(i+1)]
        
        data_length=len(Close_data)-channel_length#biede
        #market_position = 0 # begin at position 0
        #buy=0
        #sell=0
    
        current_list=np.zeros(len(Close_data))+current
        max_list=np.zeros(len(Close_data))#to make the equity curve
        Close = Close_data[0]
        Low=Low_data[0]
        High=High_data[0]
        Open=Open_data[0]
        start_time = timeit.default_timer()
        #count_period=0
        for channel_start in xrange(channel_length-channel_length,data_length):#we can judge if marketpostition=0 then search if!=0 then read length
    
            # Get only the channel needed
            channel_end=channel_start+channel_length-1
    
    
    
            Close=Close_data[channel_end]
            Open=Open_data[channel_end+1]
            High=High_data[channel_end+1]
            Low=Low_data[channel_end+1]
            if(market_position == 0):
                #channel_start=i
                channel_high = High_data[channel_start: channel_end+1]
                channel_low = Low_data[channel_start: channel_end+1]
            
    
                hh=np.max(channel_high)
                ll =np.min(channel_low)
                if(Open>=hh):
                    entry_price=Open
                    #print(Open,channel_end)
                    market_position=1
                    #current=current-Open
                    prev_peak=Open
                    buy=buy+1
                    current_list[channel_end+1]=current_list[channel_end]+1000*(Close_data[channel_end+1]-Open)-8.5
                    #print(current_list[channel_end+1],channel_end+1)
                    flg=0
                elif(High_data[channel_end+1]>=hh):
                    entry_price=hh
                    #print(hh,channel_end)
                    market_position=1
                    #current=current-hh
                    prev_peak=hh
                    buy=buy+1
                    current_list[channel_end+1]=current_list[channel_end]+1000*(Close_data[channel_end+1]-hh)-8.5
                    #print(current_list[channel_end+1],channel_end+1)
                    flg=0
                else:
                    flg=1
                if(Open<=ll):
                    entry_price=Open
                    #print(-Open,channel_end)
                    market_position=-1
                    #current=current+Open
                    prev_trough=Open
                    sell=sell+1
                    current_list[channel_end+1]=current_list[channel_end]-1000*(Close_data[channel_end+1]-Open)-8.5
                    flg=0
                elif(Low_data[channel_end+1]<=ll):
                    entry_price=ll
                    #print(-ll,channel_end)
                    market_position=-1
                    #current=current+ll
                    prev_trough=ll
                    sell=sell+1
                    current_list[channel_end+1]=current_list[channel_end]-1000*(Close_data[channel_end+1]-ll)-8.5
                    flg=0
                else:
                    if(flg==1):
                        flg=1
                if(flg==1):
                    current_list[channel_end+1]=current_list[channel_end]
                if(flg==0):
                    count_period=0
                    max_list[channel_end+1]=max(max_list[channel_end],current_list[channel_end+1])
                    record=current_list[channel_end]
                    continue
    
            if(market_position > 0):
                count_period=count_period+1
                period=period+1
                if(Close > prev_peak):
                    prev_peak = Close
                if(Open<=prev_peak*(1-stop_percentage)):#zheliyouwenti
                    deal_price=Open
                    market_position=0
                    #current=current+Open
                    if(deal_price>entry_price):
                        gross_gain=gross_gain+1000*(deal_price-entry_price)-17
                        Winner=Winner+1
                        win_period=win_period+count_period
                        W.append((1000*(deal_price-entry_price)-17)/record)
                    else:
                        gross_loss=gross_loss+1000*(deal_price-entry_price)-17
                        Loser=Loser+1
                        lose_period=lose_period+count_period
                        L.append((1000*(deal_price-entry_price)-17)/record)
                    current_list[channel_end+1]=current_list[channel_end]+1000*(deal_price-Close)-8.5
                    #print("**",deal_price,channel_end)
                elif(Low_data[channel_end+1]<=prev_peak*(1-stop_percentage)):
                    deal_price=prev_peak*(1-stop_percentage)
                    market_position=0
                    #current=current+deal_price
                    if(deal_price>entry_price):
                        gross_gain=gross_gain+1000*(deal_price-entry_price)-17
                        Winner=Winner+1
                        win_period=win_period+count_period
                        W.append((1000*(deal_price-entry_price)-17)/record)
                    else:
                        gross_loss=gross_loss+1000*(deal_price-entry_price)-17
                        Loser=Loser+1
                        lose_period=lose_period+count_period
                        L.append((1000*(deal_price-entry_price)-17)/record)
                    current_list[channel_end+1]=current_list[channel_end]+1000*(deal_price-Close)-8.5
                    #print("**",deal_price,channel_end)
                else:
                    current_list[channel_end+1]=current_list[channel_end]+1000*(Close_data[channel_end+1]-Close)
                    # next bar at Prev_Peak*(1-StpPct) Stop
    
            if(market_position < 0):
                count_period=count_period+1
                period=period+1
                if(Close < prev_trough):
                    prev_trough = Close
                if(Open>=prev_trough*(1+stop_percentage)):
                    deal_price=Open
                    market_position=0
                    #current=current-Open
                    if(deal_price<entry_price):
                        gross_gain=gross_gain-1000*(deal_price-entry_price)-17
                        Winner=Winner+1
                        win_period=win_period+count_period
                        W.append((-1000*(deal_price-entry_price)-17)/record)
                    else:
                        gross_loss=gross_loss-1000*(deal_price-entry_price)-17
                        Loser=Loser+1
                        lose_period=lose_period+count_period
                        L.append((-1000*(deal_price-entry_price)-17)/record)
                    current_list[channel_end+1]=current_list[channel_end]-1000*(deal_price-Close)-8.5
                    #print("**",deal_price,channel_end)
                elif(High_data[channel_end+1]>=prev_trough*(1+stop_percentage)):
                    deal_price=prev_trough*(1+stop_percentage)
                    market_position=0
                    #current=current-deal_price
                    if(deal_price<entry_price):
                        gross_gain=gross_gain-1000*(deal_price-entry_price)-17
                        Winner=Winner+1
                        win_period=win_period+count_period
                        W.append((-1000*(deal_price-entry_price)-17)/record)
                    else:
                        gross_loss=gross_loss-1000*(deal_price-entry_price)-17
                        Loser=Loser+1
                        lose_period=lose_period+count_period
                        L.append((-1000*(deal_price-entry_price)-17)/record)
                    current_list[channel_end+1]=current_list[channel_end]-1000*(deal_price-Close)-8.5
                    #print("**",deal_price,channel_end)
                else:
                    current_list[channel_end+1]=current_list[channel_end]-1000*(Close_data[channel_end+1]-Close)
            max_list[channel_end+1]=max(max_list[channel_end],current_list[channel_end+1])
    
        dd=np.max(max_list-current_list)
        elapsed = timeit.default_timer() - start_time
        ROA=(current_list[len(Close_data)-1]-current)/dd
        sig=np.std(current_list)
        ratio=(current_list[len(Close_data)-1]-current)/sig
        print(dd)
        print(current_list[len(Close_data)-1],buy,sell)
        current=current_list[len(Close_data)-1]
        current_wlist[T*252*80+80*21*tau*i:T*252*80+80*21*tau*(i+1)]=current_list[len(Close_data)-data_length : len(Close_data)]
    max_wlist[T*252*80]=100000
    
    
    for j in range(T*252*80,T*252*80+80*21*tau*(i+1)-1):
        max_wlist[j+1]=max(max_wlist[j],current_wlist[j+1])                  
    plt.plot(current_wlist[T*252*80:T*252*80+80*21*tau*(i+1)])
    dd=np.max(max_wlist-current_wlist)
    print("Net Equity",current_wlist[T*252*80+80*21*tau*(i+1)-1])
    print("Net Profit",current_wlist[T*252*80+80*21*tau*(i+1)-1]-100000)
    print("Net Profit To Worst Drawdown",(current_wlist[T*252*80+80*21*tau*(i+1)-1]-100000)/dd)
    print("Gorss Gain and Gross Loss",gross_gain,gross_loss)
    
    print("Win Bars, Lose Bars, Bars",win_period,lose_period,period)
    print("Avg Bars In Win, Avg Bars In Lose, Avg Bars In Trade",win_period/Winner,lose_period/Loser,period/(Winner+Loser))
    
    
    
    
    
    
    
    print("Best Winner, Worst Loser, Best Winner To Worst Loser",np.max(W),np.min(L),np.max(W)/np.min(L))
    
    
    print("Average Winner To Average Loser", np.mean(W)/np.mean(L))
    
    
    
    
    
    W=np.array(W)
    L=np.array(L)
    print("Average Winner, Average Loser", np.mean(W),np.mean(L))
    
    
    
    
    
    
    print("Profit Factor",gross_gain/gross_loss)
    print("Percent Winners, Percent Losers", Winner/(Winner+Loser*1.0),Loser/(Winner*1.0+Loser))
    print("Winners Losers Ratio",Winner/1.0/Loser)
    print("Average Drawdown",np.mean(max_wlist[T*252*80+80*21*tau*i:T*252*80+80*21*tau*(i+1)]-current_wlist[T*252*80+80*21*tau*i:T*252*80+80*21*tau*(i+1)]))
    print("ROA",(current_wlist[T*252*80+80*21*tau*(i+1)-1]-100000)/dd)
    return_list=np.diff(np.log(current_wlist[T*252*80:T*252*80+80*21*tau*(i+1)]))
    print("S Ratio",np.mean(return_list)*80*252/(np.std(return_list)*np.sqrt(80*252)))
    print("Worst Drawdown",dd)
    print("Long, Short",buy,sell)
    print("Standard Deviation Annualized",np.std(return_list)*np.sqrt(80*252))
    
    

main()