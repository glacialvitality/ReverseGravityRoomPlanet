#pragma once

#include "syati.h"


class ReverseGravityRoomPlanet : public MapObjActor {
public:
    ReverseGravityRoomPlanet(const char*);

    virtual ~ReverseGravityRoomPlanet();
    virtual void init(const JMapInfoIter&);
    virtual void initCaseUseSwitchA(const MapObjActorInitInfo&);

    void exeDownStart();
    void exeDownWait();
    void exeUpStart();
    void exeUpWait();
    void startSwitchOn();
    void startSwitchOff();
};