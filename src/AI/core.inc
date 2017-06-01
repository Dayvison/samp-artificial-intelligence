/*
 * Artificial intelligence
 * by Dayvison Balmant
 * 
 * Responsavel pela criação de AI's

## Changelog:
> - 

## API:
 * **Definitions:**
 	- 
 * **Callbacks:**
 	- 
 * **Enums:**
 	- 
 * **Tags:**
 	- 
 * **Functions:**
 	- 
 * **Commands:**
 	- 
 * **Macros:**
 	- 

## Internal:
 * **Callbacks:**
 	- 
 * **Enums:**
 	- 
 * **Tags:**
 	- 
 * **Functions:**
 	- 
 * **Variables:**
	- 
 * **Macros:**
 	- 

## Configuration:
 	- 
*/

#if defined _AI_core_inc
 	#endinput
#endif
#define _AI_core_inc

#define __linux
#include <samp/a_samp>
#include <plugins/streamer>
#include <plugins/FCNPC>
#include <plugins/colandreas>

#include <YSI/y_iterate>
#include <YSI/y_hooks>
#include <SAM/3DTryg>

/*================================================
=  ___  ____ ____ _ _  _ _ ___ _ ____ _  _ ____  =
=  |  \ |___ |___ | |\ | |  |  | |  | |\ | [__   =
=  |__/ |___ |    | | \| |  |  | |__| | \| ___]  =
=                                                =
*================================================*/

#if !defined MAX_AI_NAME
	#define MAX_AI_NAME MAX_PLAYER_NAME
#endif

#if !defined MAX_AIS
	#define MAX_AIS (32)
#endif

const AI:INVALID_AI_ID = AI:-1;

#if !defined AI_QUIET
	#define AI_Error(%0) printf("[AI error]: "%0)
	#define AI_Warning(%0) printf("[AI warning]: "%0)
#else
	#define AI_Error(%0)
	#define AI_Warning(%0)
#endif

#if !defined AI_DEFAULT_TYPE
	#define AI_DEFAULT_TYPE           (MOVE_TYPE_AUTO)
#endif

#if !defined AI_DEFAULT_SPEED
	#define AI_DEFAULT_SPEED          (MOVE_SPEED_AUTO)
#endif

#if !defined AI_DEFAULT_USEMAPANDREAS
	#define AI_DEFAULT_USEMAPANDREAS  (false)
#endif

#if !defined AI_DEFAULT_USECOLANDREAS
	#define AI_DEFAULT_USECOLANDREAS  (true)
#endif

#if !defined AI_DEFAULT_SETANGLE
	#define AI_DEFAULT_SETANGLE       (true)
#endif

#if !defined AI_DEFAULT_RADIUS
	#define AI_DEFAULT_RADIUS         (0.0)
#endif

#if !defined AI_DEFAULT_PRECISION
	#define AI_DEFAULT_PRECISION      (85.0)
#endif

#if !defined AI_DEFAULT_STRENGTH
	#define AI_DEFAULT_STRENGTH       (5.0)
#endif

#if !defined AI_DEFAULT_PATHID
	#define AI_DEFAULT_PATHID         (0)
#endif

#if !defined AI_DEFAULT_RANGE
	#define AI_DEFAULT_RANGE          (30.0)
#endif

#if !defined AI_DEFAULT_CHECKOBSTACLES
	#define AI_DEFAULT_CHECKOBSTACLES (true)
#endif

#if !defined AI_DEFAULT_CHECKVISION
	#define AI_DEFAULT_CHECKVISION    (true)
#endif

#if !defined AI_DEFAULT_POSTURE
	#define AI_DEFAULT_POSTURE        (PASSIVE)
#endif

#if !defined AI_DEFAULT_ANGLE
	#define AI_DEFAULT_ANGLE        (0.0)
#endif

#if !defined AI_DEFAULT_VIRTUAL_WORLD
	#define AI_DEFAULT_VIRTUAL_WORLD        (0)
#endif

#if !defined AI_DEFAULT_INTERIOR
	#define AI_DEFAULT_INTERIOR        (0)
#endif

#if !defined DEFAULT_AI_TICK_RATE
	#define DEFAULT_AI_TICK_RATE        (1000)
#endif


/*================================================
=             ____ ____ ___ _  _ ___             =
=             [__  |___  |  |  | |__]            =
=             ___] |___  |  |__| |               =
=                                                =
*================================================*/
/// Postura adotada pelo AI
enum AIPosture {
	NONE,       /// Nenhum, não faz nada, mesmo que receba dano
	AGGRESSIVE, /// Agressivo, ataca qualquer um próximo, continua perseguindo o objetivo a qualquer distância
	PASSIVE,    /// Passivo, apenas reaje caso sofra ameaça, pode perseguir objetivo por uma curta distância
	DEFENSIVE   /// Defensivo, ataca quem invade sua zona, porém guarda sua posição
};

/// Estrutura de dados dos AI's
static enum E_AI_DATA {
	AI_FCNPCID,                  /// ID recebido pelo FCNPC
	string:AI_Name[MAX_AI_NAME], /// Nome

	// Movimento
	AI_Type,                     /// Movimento executado pelo AI (MOVE_TYPE_AUTO, MOVE_TYPE_WALK, MOVE_TYPE_RUN, MOVE_TYPE_SPRINT, MOVE_TYPE_DRIVE)
	Float:AI_Speed,              /// Velocidade de movimento do AI (MOVE_SPEED_AUTO, MOVE_SPEED_WALK, MOVE_SPEED_RUN, MOVE_SPEED_SPRINT)
	bool:AI_UseMapAndreas,       /// Se irá usar a correção do eixo Z com MapAndreas oferecido pelo plugin FCNPC ao movimentar
	bool:AI_UseColAndreas,       /// Se irá usar a correção do eixo Z com ColAndreas feito em pawn
	bool:AI_SetAngle,            /// Se o FCNPC irá corrigir o angulo do AI, quando ele se movimentar
	Float:AI_Radius,             /// Quando for instruido o AI a se movimentar, caso a nova posição esteja neste raio a ação será ignorada

	// Combate
	Float:AI_Precision,          /// Taxa de acertos dos tiros(0, a 100%)
	Float:AI_Strength,           /// Força do NPC, ataques fisicos(Valor do dano)

	// Caminho/Detecção
	AI_Pathid,                   /// Caminho para o NPC percorrer criado com FCNPC_CreateMovePath
	Float:AI_Range,              /// Area de detecção de um objetivo pelo NPC(Streamer_Area)
	bool:AI_CheckObstacles,      /// Se para detecção de um objetivo, irá usar ColAndreas para checar se existe obstáculos no seu caminho, impossibilitando o AI de alcançar o objetivo
	bool:AI_CheckVision,         /// Se para detecção de um objetivo, irá checar se o objetivo é visto pelo AI (IsElementOnFakeScreen)
	//AI_Solutions[AISolution],    /// Soluções automáticas para problemas encontrados durante a perseguição de um objetivo
	
	AIPosture:AI_Posture,        /// Postura adotada pelo AI [AIPosture](#AIPosture)
	
	// Status
	Float:AI_Health,             /// Vida padrão do AI ao se spawnar
	Float:AI_Armour,             /// Colete padrão do AI ao se spawnar

	// Objetivos
};

/// Dados dos AI's
static AI_Data[AI:MAX_AIS][E_AI_DATA];

new
	Iterator:AIs<MAX_AIS>,                     /// AI's criados
	Iterator:PlayerAIs<MAX_PLAYERS, MAX_AIS>,  /// AI's seguindo o player
	Iterator:AIsPlayers<MAX_AIS, MAX_PLAYERS>  /// Players na área de detecção do AI
;

static AI_TickRate = DEFAULT_AI_TICK_RATE;

forward AI_OnCreate(AI:id);
forward AI_OnDestroy(AI:id);
forward AI_OnSpawn(AI:id);
forward AI_OnRespawn(AI:id);
forward AI_OnDeath(AI:id, killerid, weaponid);

forward AI:AI_Create(string:name[MAX_AI_NAME]);
forward AI:AI_CreateEX(
	string:name[MAX_AI_NAME],
	type                  = AI_DEFAULT_TYPE,
	Float:speed           = AI_DEFAULT_SPEED,
	bool:useMapAndreas    = AI_DEFAULT_USEMAPANDREAS,
	bool:useColAndreas    = AI_DEFAULT_USECOLANDREAS,
	bool:setAngle         = AI_DEFAULT_SETANGLE,
	Float:radius          = AI_DEFAULT_RADIUS,
	Float:precision       = AI_DEFAULT_PRECISION,
	Float:strength        = AI_DEFAULT_STRENGTH,
	pathid                = AI_DEFAULT_PATHID,
	Float:range           = AI_DEFAULT_RANGE,
	bool:checkObstacles   = AI_DEFAULT_CHECKOBSTACLES,
	bool:checkVision      = AI_DEFAULT_CHECKVISION,
	//solutions[AISolution] = AI_DEFAULT_SOLUTIONS,
	AIPosture:posture     = AI_DEFAULT_POSTURE
);
forward AI_IsValid(AI:id);
forward AI_Destroy(AI:id);
forward AI_Spawn(AI:id, skinid, Float:x, Float:y, Float:z, Float:angle = AI_DEFAULT_ANGLE, interior = AI_DEFAULT_VIRTUAL_WORLD, virtualworld = AI_DEFAULT_INTERIOR);
forward AI_IsSpawned(AI:id);

/*================================================
=    ____ _  _ _  _ ____ ___ _ ____ _  _ ____    =
=    |___ |  | |\ | |     |  | |  | |\ | [__     =
=    |    |__| | \| |___  |  | |__| | \| ___]    =
=                                                =
*================================================*/
/**
 * Cria um AI
 *
 * @param      name  Nome do AI
 *
 * @date       18:03 01/06/2017
 * @author     Dayvison
 *
 * @return     - `ID do AI criado` Sucesso
 *             - `INVALID_AI_ID` caso ocorra algum erro:
 *                 + Máximo de AI's alcançado
 *                 + FCNP_Create falhou
 */
stock AI:AI_Create(string:name[MAX_AI_NAME])
{
	return AI_CreateEX(name);
}

/**
 * Cria um AI com todas opções de personalização
 *
 * @param      name                 Nome
 * @param      type                 Movimento executado pelo AI (MOVE_TYPE_AUTO, MOVE_TYPE_WALK, MOVE_TYPE_RUN, MOVE_TYPE_SPRINT, MOVE_TYPE_DRIVE)
 * @param      speed                Velocidade de movimento do AI (MOVE_SPEED_AUTO, MOVE_SPEED_WALK, MOVE_SPEED_RUN, MOVE_SPEED_SPRINT)
 * @param      useMapAndreas        Se irá usar a correção do eixo Z com MapAndreas oferecido pelo plugin FCNPC ao movimentar
 * @param      useColAndreas        Se irá usar a correção do eixo Z com ColAndreas feito em pawn
 * @param      setAngle             Se o FCNPC irá corrigir o angulo do AI, quando ele se movimentar
 * @param      radius               Quando for instruido o AI a se movimentar, caso a nova posição esteja neste raio a ação será ignorada
 * @param      precision            Taxa de acertos dos tiros(0, a 100%)
 * @param      strength             Força do NPC, ataques fisicos(Valor do dano)
 * @param      pathid               Caminho para o NPC percorrer criado com FCNPC_CreateMovePath
 * @param      range                Area de detecção de um objetivo pelo NPC(Streamer_Area)
 * @param      checkObstacles       Se para detecção de um objetivo, irá usar ColAndreas para checar se existe obstáculos no seu caminho, impossibilitando o AI de alcançar o objetivo
 * @param      checkVision          Se para detecção de um objetivo, irá checar se o objetivo é visto pelo AI (IsElementOnFakeScreen)
 * @param      solutionsAISolution  Soluções automáticas para problemas encontrados durante a perseguição de um objetivo
 * @param      posture              Postura adotada pelo AI [AIPosture](#AIPosture)
 *
 * @date       18:08 01/06/2017
 * @author     Dayvison
 *
 * @return     - `ID do AI criado` Sucesso
 *             - `INVALID_AI_ID` caso ocorra algum erro:
 *                 + Máximo de AI's alcançado
 *                 + FCNP_Create falhou
 */
stock AI:AI_CreateEX(
	string:name[MAX_AI_NAME],
	type                  = AI_DEFAULT_TYPE,
	Float:speed           = AI_DEFAULT_SPEED,
	bool:useMapAndreas    = AI_DEFAULT_USEMAPANDREAS,
	bool:useColAndreas    = AI_DEFAULT_USECOLANDREAS,
	bool:setAngle         = AI_DEFAULT_SETANGLE,
	Float:radius          = AI_DEFAULT_RADIUS,
	Float:precision       = AI_DEFAULT_PRECISION,
	Float:strength        = AI_DEFAULT_STRENGTH,
	pathid                = AI_DEFAULT_PATHID,
	Float:range           = AI_DEFAULT_RANGE,
	bool:checkObstacles   = AI_DEFAULT_CHECKOBSTACLES,
	bool:checkVision      = AI_DEFAULT_CHECKVISION,
	//solutions[AISolution] = AI_DEFAULT_SOLUTIONS,
	AIPosture:posture     = AI_DEFAULT_POSTURE
)
{
	new AI:id = AI:Iter_Free(AIs);

	if(_:id == cellmin)
	{
		AI_Error("Increase MAX_AIS.");
		return INVALID_AI_ID;
	}

	new ID = FCNPC_Create(name);
	if(ID == INVALID_PLAYER_ID)
	{
		AI_Error("Failed to create NPC name %s.", name);
		return INVALID_AI_ID;
	}

	Iter_Add(AIs, _:id);
	AI_Data[id][AI_FCNPCID]        = ID;
	AI_Data[id][AI_Name]           = name;
	AI_Data[id][AI_Type]           = type;
	AI_Data[id][AI_Speed]          = speed;
	AI_Data[id][AI_UseMapAndreas]  = useMapAndreas;
	AI_Data[id][AI_UseColAndreas]  = useColAndreas;
	AI_Data[id][AI_SetAngle]       = setAngle;
	AI_Data[id][AI_Radius]         = radius;
	AI_Data[id][AI_Precision]      = precision;
	AI_Data[id][AI_Strength]       = strength;
	AI_Data[id][AI_Pathid]         = pathid;
	AI_Data[id][AI_Range]          = range;
	AI_Data[id][AI_CheckObstacles] = checkObstacles;
	AI_Data[id][AI_CheckVision]    = checkVision;
	//AI_Data[id][AI_Solutions]      = solutions;
	AI_Data[id][AI_Posture]        = posture;

	CallLocalFunction("AI_OnCreate", "d", _:id);

	return id;
}

/**
 * Determina se um AI é valido
 *
 * @param      AI    ID do AI
 *
 * @date       18:38 01/06/2017
 * @author     Dayvison
 *
 * @return     - `1` Válido
 *             - `0` Inválido:
 */
stock AI_IsValid(AI:id)
{
	// O id é inválido
	if(!(0 <= _:id < MAX_AIS))
		return 0;

	// O id não existe
	if(!Iter_Contains(AIs, _:id))
		return 0;

	return 1;
}

/**
 * Destrói um AI
 *
 * @param      id    ID do AI
 *
 * @date       18:12 01/06/2017
 * @author     Dayvison
 *
 * @return     - `1` Sucesso
 *             - `0` caso ocorra algum erro:
 *                 + O id é inválido
 *                 + O id não existe
 */
stock AI_Destroy(AI:id)
{
	// O id é inválido
	if(!(0 <= _:id < MAX_AIS))
		return 0;

	// O id não existe
	if(!Iter_Contains(AIs, _:id))
		return 0;

	static const AI_DATA_CLEAN[E_AI_DATA];

	AI_Data[id] = AI_DATA_CLEAN;

	CallLocalFunction("AI_OnDestroy", "d", _:id);

	SetTimerEx("@AI_IterClear", 1, false, "d", _:id);

	// TODO: Destruir areas

	return 1;
}

/**
 * Remove o AI de qualquer iterator em que ele esteja
 */
@AI_IterClear(id);
@AI_IterClear(id)
{
	Iter_Remove(AIs, id);
	Iter_Clear(AIsPlayers<id>);
	
	foreach(new playerid: Player)
	{
		if(Iter_Contains(PlayerAIs<playerid>, id))
			Iter_Remove(PlayerAIs<playerid>, id);
	}
}

/**
 * Spawna um AI
 *
 * @param      AI            ID do AI
 * @param      skinid        ID da skin para spawnar
 * @param      x             Posição X
 * @param      y             Posição Y
 * @param      z             Posição Z
 * @param      angle         Ângulo
 * @param      interior      ID do interior
 * @param      virtualworld  ID do virtual world
 *
 * @date       19:04 01/06/2017
 * @author     Dayvison
 *
 * @return     - `1` Sucesso
 *             - `0` caso ocorra algum erro:
 *                 + O id é inválido
 *                 + O id não existe
 *                 + Skin inválida
 *                 + FCNPC_Spawn erro(O player já está spawnado)
 */
stock AI_Spawn(AI:id, skinid, Float:x, Float:y, Float:z, Float:angle = AI_DEFAULT_ANGLE, interior = AI_DEFAULT_INTERIOR, virtualworld = AI_DEFAULT_VIRTUAL_WORLD)
{
	// O id é inválido
	if(!(0 <= _:id < MAX_AIS))
		return 0;

	// O id não existe
	if(!Iter_Contains(AIs, _:id))
		return 0;

	// Skin inválida
	if(NOT_IN_RANGE(skinid, 0, 311+1))
		return 0;

	new npcid = AI_Data[id][AI_FCNPCID];

	if(!FCNPC_Spawn(npcid, skinid, x, y, z))
		return 0;

	FCNPC_SetAngle(npcid, angle);
	FCNPC_SetVirtualWorld(npcid, virtualworld);
	FCNPC_SetInterior(npcid, interior);

	return 1;
}

/**
 * Determina se um AI está spawnado
 *
 * @param      id    ID do AI
 *
 * @date       19:40 01/06/2017
 * @author     Dayvison
 *
 * @return     - `1` Esta spawnado
 *             - `0` Não esta spawnado
 *             - `0` caso ocorra algum erro:
 *                 + O id é inválido
 *                 + O id não existe
 */
stock AI_IsSpawned(AI:id)
{
	// O id é inválido
	if(!(0 <= _:id < MAX_AIS))
		return 0;

	// O id não existe
	if(!Iter_Contains(AIs, _:id))
		return 0;

	return FCNPC_IsSpawned(AI_Data[id][AI_FCNPCID]);
}
/*================================================
=  ____ ____ _    _    ___  ____ ____ _  _ ____  =
=  |    |__| |    |    |__] |__| |    |_/  [__   =
=  |___ |  | |___ |___ |__] |  | |___ | \_ ___]  =
=                                                =
*================================================*/

hook OnScriptInit()
{
	SetTimer("AI@Internal_OnTick", AI_TickRate, true);
}

hook AI@Internal_OnTick()
{
	foreach(new ai: AIs)
	{
		foreach(new playerid: AIsPlayers<ai>)
		{
			
		}
	}
}

hook OnPlayerEnterDynArea(playerid, STREAMER_TAG_AREA areaid)
{

}
hook OnPlayerLeaveDynArea(playerid, STREAMER_TAG_AREA areaid)
{

}
/*================================================
=     ____ ____ _  _ _  _ ____ _  _ ___  ____    =
=     |    |  | |\/| |\/| |__| |\ | |  \ [__     =
=     |___ |__| |  | |  | |  | | \| |__/ ___]    =
=                                                =
*================================================*/



/*================================================
=                   ____ ___  _                  =
=                   |__| |__] |                  =
=                   |  | |    |                  =
=                                                =
*================================================*/

@ai_func_in();@ai_func_in()
{
	AI_Create("");
	AI_CreateEX("");
	AI_IsValid(INVALID_AI_ID);
	AI_Destroy(INVALID_AI_ID);
	AI_Spawn(INVALID_AI_ID, 0, 0.0, 0.0, 0.0);
	AI_IsSpawned(INVALID_AI_ID);
}
