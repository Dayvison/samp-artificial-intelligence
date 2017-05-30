/*
 * Tags:
 * AI:
 * AIPosture:
 * AISolution:
 * AITrouble:
 */
Iterator:AIs<MAX_AIS>                     /// AI's criados
Iterator:PlayerAIs<MAX_PLAYERS, MAX_AIS>  /// AI's seguindo o player
Iterator:AIsPlayers<MAX_AIS, MAX_PLAYERS> /// Players na área de detecção do AI

enum FollowInfo{
	player: follow_Player,
	Float:  follow_MaxDistance,
	Float:  follow_DistanceTraveled,
	Float:  follow_Distance,
	        follow_RoutesFixed,
	        follow_TimesLoose,
	Float:  follow_PlayerStartPosX,
	Float:  follow_PlayerStartPosY,
	Float:  follow_PlayerStartPosZ,
	Float:  follow_NPCStartPosX,
	Float:  follow_NPCStartPosY,
	Float:  follow_NPCStartPosZ
};
enum AIPosture{

};
enum AITrouble{

};
enum AISolution{

};
// Setup
	stock AI:AI_Create(string:name[MAX_AI_NAME]);

	stock AI:AI_CreateEx(string:name[MAX_AI_NAME],
		type,                // AI_SetMoveType
		speed,               // AI_SetMoveSpeed
		bool:useMapAndreas,  // AI_ToogleUseMapAndreas
		bool:useColAndreas,  // AI_ToogleUseColAndreas
		bool:setAngle,       // AI_ToogleSetAngle
		Float:radius,        // AI_SetRadius
		Float:precision,     // AI_SetPrecision
		Float:strength,      // AI_SetStrength
		pathid,              // AI_SetRoute
		Float:range,         // AI_SetDetectionRange
		bool:checkObstacles, // 
		bool:checkVision,    //
		Float:health,        // AI_SetHealth
		Float:armour,        // AI_SetArmour
		AIPosture:posture,   // AI_SetPosture
		solutions[AISolution]
	);

	stock AI_Destroy(AI:id);

	stock AI_Spawn(AI:id, skinid, Float:posX, Float:posY, Float:posZ, Float:posA, interior, virtualworld);
	stock AI_IsSpawned(AI:id);

	stock AI_GetFCNPCID(AI:id);

	// Postura
	stock AI_SetPosture(AI:id, AIPosture:posture);
	stock AIPosture:AI_GetPosture(AI:id);

// Movimento
	stock AI_SetMoveInfo(AI:id, type = MOVE_TYPE_AUTO, Float:speed = MOVE_SPEED_AUTO, bool:useMapAndreas = false, bool:useColAndreas = false, Float:radius = 0.0, bool:setAngle = true);
	stock AI_GetMoveInfo(AI:id, &type, &Float:speed, &bool:useMapAndreas, &bool:useColAndreas, &Float:radius, &bool:setAngle);

	// Tipo de movimento
	stock AI_SetMoveType(AI:id, type);
	stock AI_GetMoveType(AI:id);

	// Velocidade
	stock AI_SetMoveSpeed(AI:id, speed);
	stock AI_GetMoveSpeed(AI:id);

	// MapAndreas
	stock AI_ToogleUseMapAndreas(AI:id, bool:toogle);
	stock AI_IsMapAndreasUsed(AI:id);

	// ColAndreas
	stock AI_ToogleUseColAndreas(AI:id, bool:toogle);
	stock AI_IsColAndreasUsed(AI:id);

	// Corrigir angulo
	stock AI_ToogleSetAngle(AI:id, bool:toogle);
	stock AI_IsSetAngle(AI:id);

	// Raio
	stock AI_SetRadius(AI:id, Float:radius);
	stock Float:AI_GetRadius(AI:id);

// Combate
	// Precisão
	stock AI_SetPrecision(AI:id, Float:precision);
	stock Float:AI_GetPrecision(AI:id);

	// Força
	stock AI_SetStrength(AI:id, Float:strength);
	stock Float:AI_GetStrength(AI:id);

// Alvos
stock AI_SetTarget(AI:id, player:playerid, bool:checkRange, AIPosture:posture, bool:allowFollow = false, Float:followMaxDistance = 0.0, bool:checkObstacles = false, bool:checkVision = false);
stock AI_GetTarget(AI:id, &player:playerid, &bool:checkRange, &AIPosture:posture, &bool:allowFollow, &Float:followMaxDistance, &bool:checkObstacles, &bool:checkVision);

// Perseguição
stock AI_FollowPlayer(AI:id, player:playerid, Float:maxDistance = AI_MAX_DISTANCE_FOLLOW);
stock AI_IsFollowingPlayer(AI:id, player:playerid);
stock AI_IsFollowingAnyPlayer(AI:id);
stock AI_GetFollowInfo(AI:id, info[FollowInfo]);

forward AI_OnFailFollow(AI:id, player:playerid);
forward AISolution:AI_OnFollowHasTrouble(AI:id, player:playerid, AITrouble:trouble);

// Rotas
stock FCNPC_LoadMovePath(string:name[]);
stock FCNPC_SaveMovePath(pathid, string:name[]);

stock AI_SetRoute(AI:id, pathid);
stock AI_GetRoute(AI:id);

// Detecção
stock AI_SetDetectionRange(AI:id, Float:range);
stock Float:AI_GetDetectionRange(AI:id);

// Vida
stock AI_SetHealth(AI:id, Float:health);
stock Float:AI_GetHealth(AI:id);

// Colete
stock AI_SetArmour(AI:id, Float:armour);
stock Float:AI_GetArmour(AI:id);
