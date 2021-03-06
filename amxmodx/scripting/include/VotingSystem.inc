#if defined _votingsystem_included
    #endinput
#endif
#define _votingsystem_included

enum VS_T_Voting { Invalid_Voting = -1 }

enum VS_E_VotingEvent {
    VS_VotingEvent_OnStart = 0,
    VS_VotingEvent_OnVote,
    VS_VotingEvent_OnFinish,
}

/**
 * Вызывается при инициализации системы голосований
 *
 * @noreturn
*/
forward VS_OnInit();

/**
 * Инициализация системы голосований
 *
 * @noreturn
*/
native VS_Init();

/**
 * Создание нового голосования
 *
 * @param sTitle    Заголовок меню голосоавния
 *
 * @return  Хендлер созданного голосования
*/
native VS_T_Voting:VS_Voting_Create(const sTitle[]);

/**
 * Удаление голосования и всех его пунктов
 *
 * @param iVoting   Хендлер голосования
 *
 * @return  Invalid_Voting
*/
native VS_T_Voting:VS_Voting_Remove(&VS_T_Voting:iVoting);

/**
 * Добавление слушалки события
 *
 * @param iVoting   Хендлер голосования
 * @param iEvent    Событие
 * @param sCallback Название функции
 *
 * @noreturn
*/
native VS_Voting_AddListener(const VS_T_Voting:iVoting, const VS_E_VotingEvent:iEvent, const sCallback[]);

/**
 * Запуск голосования
 *
 * @param iVoting   Хендлер голосования
 *
 * @return true, если голосование запущено успешно, иначе false
*/
native bool:VS_Voting_Start(const VS_T_Voting:iVoting);

/**
 * Запуск голосования
 *
 * @return  Хендлер текущего голосования. Invalid_Voting, если сейчас голосование на запущено.
*/
native VS_Voting_GetCurrent();
