//
// Created by rcastill on 1/23/16.
//

#ifndef PROJECT_STRAT_BUTTONMASTER_H
#define PROJECT_STRAT_BUTTONMASTER_H

class SimpleButton;

class ButtonMaster
{
public:
    virtual void onPrimaryClick(SimpleButton *button) = 0;
};

#endif //PROJECT_STRAT_BUTTONMASTER_H
