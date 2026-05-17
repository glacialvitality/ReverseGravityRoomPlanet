#include "ReverseGravityRoomPlanet.h"

namespace NrvReverseGravityRoomPlanet {
    FULL_NERVE(ReverseGravityRoomPlanetNrvDownStart, ReverseGravityRoomPlanet, DownStart);
    FULL_NERVE(ReverseGravityRoomPlanetNrvDownWait, ReverseGravityRoomPlanet, DownWait);
    FULL_NERVE(ReverseGravityRoomPlanetNrvUpStart, ReverseGravityRoomPlanet, UpStart);
    FULL_NERVE(ReverseGravityRoomPlanetNrvUpWait, ReverseGravityRoomPlanet, UpWait);
};  // namespace NrvReverseGravityRoomPlanet

ReverseGravityRoomPlanet::ReverseGravityRoomPlanet(const char* pName) : MapObjActor(pName) {
    mInvert = -1;
}

void ReverseGravityRoomPlanet::init(const JMapInfoIter& rIter) {
    MapObjActor::init(rIter);
    MapObjActorInitInfo info;
    info.setupHioNode("惑星");
    info.setupDefaultPos();
    info.setupConnectToScene();
    info.setupEffect(0, false);
    info.setupFarClipping(-1.0f);
    info.setupNerve(&NrvReverseGravityRoomPlanet::ReverseGravityRoomPlanetNrvDownWait::sInstance);

    MR::getJMapInfoArg0NoInit(rIter, &mInvert); 

    initialize(rIter, info);
}

void ReverseGravityRoomPlanet::exeDownStart() {
    if (MR::isFirstStep(this)) {
        MR::startBck(this, "ChangeRed", 0);
    }

    if (MR::isBckStopped(this)) {
        setNerve(&NrvReverseGravityRoomPlanet::ReverseGravityRoomPlanetNrvDownWait::sInstance);
    }
}

void ReverseGravityRoomPlanet::exeDownWait() {}

void ReverseGravityRoomPlanet::exeUpStart() {
    if (MR::isFirstStep(this)) {
        MR::startBck(this, "ChangeBlue", 0);
    }

    if (MR::isBckStopped(this)) {
        setNerve(&NrvReverseGravityRoomPlanet::ReverseGravityRoomPlanetNrvUpWait::sInstance);
    }
}

void ReverseGravityRoomPlanet::exeUpWait() {}

void ReverseGravityRoomPlanet::initCaseUseSwitchA(const MapObjActorInitInfo& rIter) {
    if (mInvert == -1) {
        void (ReverseGravityRoomPlanet::*startOff)(void) = &ReverseGravityRoomPlanet::startSwitchOff;
        void (ReverseGravityRoomPlanet::*startOn)(void) = &ReverseGravityRoomPlanet::startSwitchOn;
        MR::listenStageSwitchOnOffA(this, MR::Functor(this, startOff), MR::Functor(this, startOn));
    } else {
        void (ReverseGravityRoomPlanet::*startOff)(void) = &ReverseGravityRoomPlanet::startSwitchOn;
        void (ReverseGravityRoomPlanet::*startOn)(void) = &ReverseGravityRoomPlanet::startSwitchOff;
        MR::listenStageSwitchOnOffA(this, MR::Functor(this, startOff), MR::Functor(this, startOn));
    }
}

void ReverseGravityRoomPlanet::startSwitchOn() {
    setNerve(&NrvReverseGravityRoomPlanet::ReverseGravityRoomPlanetNrvUpStart::sInstance);
}

void ReverseGravityRoomPlanet::startSwitchOff() {
    setNerve(&NrvReverseGravityRoomPlanet::ReverseGravityRoomPlanetNrvDownStart::sInstance);
}

ReverseGravityRoomPlanet::~ReverseGravityRoomPlanet() {}
