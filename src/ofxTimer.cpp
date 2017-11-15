//
//  ofxTimer.cpp
//
//  Created by enrico<nausea>viola on 11/14/16.
//
//

#include "ofxTimer.h"

ofxTimer::ofxTimer(){
    setAutoUpdate(true);
    totTime = 0.0;
    curPct=0.0;
    bRunning = false;
}

ofxTimer::~ofxTimer(){
    handleStop();
}

void ofxTimer::setup(float _totTime, bool _autoUpdate){
    if(bRunning)return;
    totTime = _totTime;
    bRunning = false;
    setAutoUpdate(_autoUpdate);
}

void ofxTimer::setAutoUpdate(bool b){
    if(bRunning)return;
    bAutoUpdate = b;
}

void ofxTimer::start(){
    if(bRunning)return;
    startTime = ofGetElapsedTimef();
    endTime = startTime+totTime;
    curPct=0.0;
    bRunning = true;
    if(bAutoUpdate)ofAddListener(ofEvents().update, this, &ofxTimer::update);
}

void ofxTimer::stop(){
    if(!bRunning)return;
    handleStop();
    hardStopCallback();
}

void ofxTimer::handleStop(){
    bRunning = false;
    if(bAutoUpdate)ofRemoveListener(ofEvents().update, this, &ofxTimer::update);
}

void ofxTimer::update(){
    if(bRunning){
        float now = ofGetElapsedTimef();
        curPct = ofMap(now, startTime, endTime, 0.0, 1.0);
        if(now>=endTime){
            handleStop();
            naturalStopCallback();
        }
    }
}