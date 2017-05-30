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
 * **Variables:**
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


#include <streamer>
#include <FCNPC>
#include <ColAndreas>

#include <YSI\y_iterate>
#include <YSI\y_hooks>
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

/*================================================
=             ____ ____ ___ _  _ ___             =
=             [__  |___  |  |  | |__]            =
=             ___] |___  |  |__| |               =
=                                                =
*================================================*/
/// 
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
	AI_Type,                     /// Movimento executado pelo npc (MOVE_TYPE_AUTO, MOVE_TYPE_WALK, MOVE_TYPE_RUN, MOVE_TYPE_SPRINT, MOVE_TYPE_DRIVE)
	AI_Speed,                    /// Velocidade de movimento do npc (MOVE_SPEED_AUTO, MOVE_SPEED_WALK, MOVE_SPEED_RUN, MOVE_SPEED_SPRINT)
	bool:AI_UseMapAndreas,       /// Se irá usar a correção do eixo Z com MapAndreas oferecido pelo plugin FCNPC ao movimentar
	bool:AI_UseColAndreas,       /// Se irá usar a correção do eixo Z com ColAndreas feito em pawn
	bool:AI_SetAngle,            /// Se o FCNPC irá corrigir o angulo do npc, quando ele se movimentar
	Float:AI_Radius,             /// Quando for instruido o npc a se movimentar, caso a nova posição esteja neste raio a ação será ignorada

	// Combate
	Float:AI_Precision,          /// Taxa de acertos dos tiros(0, a 100%)
	Float:AI_Strength,           /// Força do NPC, ataques fisicos(Valor do dano)

	// Caminho/Detecção
	AI_Pathid,                   /// Caminho para o NPC percorrer criado com FCNPC_CreateMovePath
	Float:AI_Range,              /// Area de detecção de um objetivo pelo NPC(Streamer_Area)
	bool:AI_CheckObstacles,      /// Se para detecção de um objetivo, irá usar ColAndreas para checar se existe obstáculos no seu caminho, impossibilitando o npc de alcançar o objetivo
	bool:AI_CheckVision,         /// Se para detecção de um objetivo, irá checar se o objetivo é visto pelo npc (IsElementOnPlayerScreen)
	AI_Solutions[AISolution],    /// Soluções automáticas para problemas encontrados durante a perseguição de um objetivo
	
	AIPosture:AI_Posture,        /// Postura do AI see #AIPosture
	
	// Status
	Float:AI_Health,             /// Vida padrão do AI ao se spawnar
	Float:AI_Armour,             /// Colete padrão do AI ao se spawnar

	// Objetivos
};

/// Dados dos AI's
static AI_Data[MAX_AIS][E_AI_DATA];

new
	Iterator:AIs<MAX_AIS>,                     /// AI's criados
	Iterator:PlayerAIs<MAX_PLAYERS, MAX_AIS>,  /// AI's seguindo o player
	Iterator:AIsPlayers<MAX_AIS, MAX_PLAYERS>  /// Players na área de detecção do AI
;

/*================================================
=    ____ _  _ _  _ ____ ___ _ ____ _  _ ____    =
=    |___ |  | |\ | |     |  | |  | |\ | [__     =
=    |    |__| | \| |___  |  | |__| | \| ___]    =
=                                                =
*================================================*/

stock AI:AI_Create(string:name[MAX_AI_NAME])
{
	new AI:id = AI:Iter_Free(AIs);

	if(_:id == cellmin)
	{
		AI_Error("Increase MAX_AIS.");
		return INVALID_AI_ID;
	}
}


/*================================================
=  ____ ____ _    _    ___  ____ ____ _  _ ____  =
=  |    |__| |    |    |__] |__| |    |_/  [__   =
=  |___ |  | |___ |___ |__] |  | |___ | \_ ___]  =
=                                                =
*================================================*/

hook AI@Internal_OnTick()
{
	foreach(new ai: AIs)
	{
		foreach(new player: AIsPlayers<ai>)
		{
			
		}
	}
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

