#include <amxmodx>
#include "VotingSystem/Natives"

#define CALLBACK_MAX_LENGTH 128

public plugin_natives() {
    Natives_Init(API_PREFIX);
    Natives_Reg("Init");
    Natives_Reg("Voting_Create");
    Natives_Reg("Voting_Remove");
    Natives_Reg("Voting_AddListener");
    Natives_Reg("Voting_Start");
    Natives_Reg("Voting_GetCurrent");
}

@_Init() {
    PluginInit();
}

VS_T_Voting:@_Voting_Create() {
    enum {P_Title = 1}
    new sTitle[VOTIGS_TITLE_MAX_LENGTH];
    get_string(P_Title, sTitle, charsmax(sTitle));
    
    return Votings_Create(sTitle);
}

VS_T_Voting:@_Voting_Remove() {
    enum {P_Voting = 1}
    new VS_T_Voting:iVoting = VS_T_Voting:get_param_byref(P_Voting);
    
    Votings_Remove(iVoting);
    set_param_byref(P_Voting, _:iVoting);
    return iVoting;
}

@_Voting_AddListener(iPluginId) {
    enum {P_Voting = 1, P_Event, P_Callback}
    new VS_T_Voting:iVoting = VS_T_Voting:get_param(P_Voting);
    new VS_E_VotingEvent:iEvent = VS_E_VotingEvent:get_param(P_Event);
    new sCallback[CALLBACK_MAX_LENGTH];
    get_string(P_Callback, sCallback, charsmax(sCallback));

    switch (iEvent) {
        default: { // (const VS_T_Voting:iVoting)
            Votings_AddListener(iVoting, iEvent, iPluginId, sCallback, FP_CELL);
        }
    }
}

bool:@_Voting_Start() {
    enum {P_Voting = 1}
    new VS_T_Voting:iVoting = VS_T_Voting:get_param(P_Voting);
    
    return Votings_Start(iVoting);
}

VS_T_Voting:@_Voting_GetCurrent() {
    return Votings_gCurrentVoting;
}
