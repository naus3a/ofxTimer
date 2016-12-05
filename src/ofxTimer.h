//
//  ofxTimer.h
//
//  Created by enrico<nausea>viola on 11/14/16.
//
//

#pragma once
#include "ofMain.h"

class ofxTimer{
public:
    ofxTimer();
    ~ofxTimer();
    void setup(float _totTime, bool _autoUpdate=true);
    void update();
    
    void setAutoUpdate(bool b);
    void start();
    void stop();
    
    inline bool isAutoUpdating(){return bAutoUpdate;}
    inline float getPeriod(){return totTime;}
    inline float getPct(){return bRunning?curPct:0.0;}
    
    template<typename T>
    inline void addCallback(void (T::*func)(), T* listener, std::function<void(void)> * fp){
        *fp = std::bind(func, listener);
    }
    
    template<typename T>
    inline void addNaturalStopCallback(void (T::*func)(), T* listener){
        addCallback(func, listener, &naturalStopCallback);
    }
    
    template<typename T>
    inline void addHardStopCallback(void (T::*func)(), T* listener){
        addCallback(func, listener, & hardStopCallback);
    }
    
protected:
    inline void update(ofEventArgs & e){update();}
    void handleStop();
    
    std::function<void(void)> hardStopCallback;
    std::function<void(void)> naturalStopCallback;
    
    float startTime;
    float endTime;
    float totTime;
    float curPct;
    bool bAutoUpdate;
    bool bRunning;
};