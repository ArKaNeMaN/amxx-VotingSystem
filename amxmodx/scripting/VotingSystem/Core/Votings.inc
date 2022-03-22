#include <amxmodx>
#include "VotingSystem/Events"

#define VOTIGS_TITLE_MAX_LENGTH 128

enum _:S_Voting {
    VS_T_Voting:Voting_Id,
    Voting_Title[VOTIGS_TITLE_MAX_LENGTH],
    Array:Voting_Options,

    T_Events:Voting_Events,
}


new Trie:Votings_gList = Invalid_Trie;
new Votings_gLatestId = 0;
new VS_T_Voting:Votings_gCurrentVoting = Invalid_Voting;


stock __Votings_GetHandlerKey_str[16];
#define Votings_GetHandlerKey(%1) \
    (num_to_str(_:%1, __Votings_GetHandlerKey_str, charsmax(__Votings_GetHandlerKey_str)) ? __Votings_GetHandlerKey_str : NULL_STRING)

// Votings_Set(Voting[S_Voting]);
#define Votings_Set(%1) \
    TrieSetArray(Votings_gList, Votings_GetHandlerKey(Votings_GetId(%1)), %1, S_Voting)

// Votings_Unset(Voting[S_Voting]);
#define Votings_Unset(%1) \
    TrieDeleteKey(Votings_gList, Votings_GetHandlerKey(Votings_GetId(%1)))

// bool:Votings_IsValid(VS_T_Voting:iVoting);
#define Votings_IsValid(%1) \
    TrieKeyExists(Votings_gList, Votings_GetHandlerKey(%1))

// Votings_Get(VS_T_Voting:iVoting, Voting[S_Voting]);
#define Votings_Get(%1,%2) \
    TrieGetArray(Votings_gList, Votings_GetHandlerKey(%1), %2, S_Voting)

#define Votings_GetId(%1) \
    (VS_T_Voting:%1[Voting_Id])

#define Votings_AddListener(%1,%2,%3) \
    Votings_PushListener(%1, %2, CreateOneForward(%3))

#define Votings_CallEvent(%1,%2) \
    Events_CallP(%1[Voting_Events], %2, [Votings_GetId(%1)])

#define Votings_CallEventP(%1,%2,[%3]) \
    Events_CallP(%1[Voting_Events], %2, [Votings_GetId(%1), %3])


Votings_Init() {
    Votings_gList = TrieCreate();
}

VS_T_Voting:Votings_Create(const sTitle[]) {
    new Voting[S_Voting];
    Voting[Voting_Id] = VS_T_Voting:Votings_gLatestId;
    copy(Voting[Voting_Title], charsmax(Voting[Voting_Title]), sTitle);
    Voting[Voting_Options] = ArrayCreate(1, 4);
    Voting[Voting_Events] = Events_Init(_:VS_E_VotingEvent);

    Votings_Set(Voting);

    Votings_gLatestId++;
    return Votings_GetId(Voting);
}

VS_T_Voting:Votings_Remove(&VS_T_Voting:iVoting) {
    new Voting[S_Voting];
    Votings_Get(iVoting, Voting);

    Events_Destroy(Voting[Voting_Events]);

    // TODO: Удаление пунктов голосования
    ArrayDestroy(Voting[Voting_Options]);

    Votings_Unset(Voting);
    iVoting = Invalid_Voting;
    return Invalid_Voting;
}

Votings_PushListener(const VS_T_Voting:iVoting, const VS_E_VotingEvent:iEvent, const iForwardHandler) {
    new Voting[S_Voting];
    Votings_Get(iVoting, Voting);
    Events_PushListener(Voting[Voting_Events], iEvent, iForwardHandler);
}

bool:Votings_Start(const VS_T_Voting:iVoting) {
    if (Votings_gCurrentVoting != Invalid_Voting) {
        return false;
    }

    new Voting[S_Voting];
    Votings_Get(iVoting, Voting);

    // TODO: ...

    Votings_gCurrentVoting = iVoting;
    Forwards_CallP("StartVoting", iVoting);
    Votings_CallEvent(Voting, VS_VotingEvent_OnStart);
}
