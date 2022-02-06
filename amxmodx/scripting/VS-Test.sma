#include <amxmodx>
#include <VotingSystem>

#pragma compress 1
#pragma semicolon 1

public stock const PluginName[] = "[VS] Test";
public stock const PluginVersion[] = "1.0.0";
public stock const PluginAuthor[] = "ArKaNeMaN";
public stock const PluginURL[] = "t.me/arkaneman";

public VS_OnInit(){
    register_plugin(PluginName, PluginVersion, PluginAuthor);
    
    new VS_T_Voting:iVoting = VS_Voting_Create("Test");
    VS_Voting_AddListener(iVoting, VS_VotingEvent_OnStart, "@OnStart");
    set_task(2.0, "@Task", _:iVoting);
    log_amx("[TEST] Create voting #%d", iVoting);
}

@Task(const VS_T_Voting:iVoting) {
    VS_Voting_Start(iVoting);
}

@OnStart(const VS_T_Voting:iVoting) {
    log_amx("[TEST] @OnStart(%d)", iVoting);
}
