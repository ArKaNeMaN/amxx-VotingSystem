#include amxmodx
#include VotingSystem

#pragma compress 1
#pragma semicolon 1

public stock const PluginName[] = "Voting System";
public stock const PluginVersion[] = "1.0.0";
public stock const PluginAuthor[] = "ArKaNeMaN";
public stock const PluginURL[] = "t.me/arkaneman";
new const API_PREFIX[] = "VS";

#include "VotingSystem/Forwards"
#include "VotingSystem/Core/Votings"

public plugin_precache() {
    PluginInit();
}

PluginInit() {
    static bool:bIsInited;
    if (bIsInited) {
        return;
    }
    bIsInited = true;

    register_plugin(PluginName, PluginVersion, PluginAuthor);

    Votings_Init();
    Forwards_Init(API_PREFIX);
    Forwards_RegAndCall("Init", ET_IGNORE);

    // Наброски
    Forwards_Reg("StartVoting", ET_IGNORE, FP_CELL);
    Forwards_Reg("Voted", ET_IGNORE, FP_CELL, FP_CELL);
    Forwards_Reg("FinishVoting", ET_IGNORE, FP_CELL);
}

#include "VotingSystem/Core/Natives"
