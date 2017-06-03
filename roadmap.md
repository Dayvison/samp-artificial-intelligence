- [ ] Algoritimos
    + [ ] Detecção de ruidos
        * [ ] Andar/Correr
        * [ ] Atirar
        * [ ] Falar
        * [ ] Motor de veiculos/Aceleração
        * [ ] Fogo/Explosões
        * [ ] Pular/Agaichar
        * [ ] Nadar, Entrar na Agua
        * [ ] Estar cansado
        * [ ] Levar dano
        * [ ] Queda

- [ ] Opções pré-compiler
    + [ ] habilitar/desabilitar mapAndreas
    + [ ] habilitar/desabilitar colAndreas
    + [ ] habilitar/desabilitar y_iterate
    + [ ] detectar yhooks, caso não esteja incluida fazer hooks manualmente
- [x] **Estrutura dos AI's**
- [ ] **Iteratores**
    + [x] AIs
    + [ ] PlayerAIs
    + [ ] AIsPlayers
- [x] **API FCNPC**
    + [x] FCNPC_IsAI
    + [x] FCNPC_GetAIID

# Funções
- [ ] **Setup de AI's**
    - [x] AI_Create
    - [x] AI_CreateEX
    - [x] AI_OnCreate
    - [x] AI_IsValid
    - [x] AI_Destroy
    - [x] AI_OnDestroy
    - [x] AI_Spawn
    - [x] AI_IsSpawned
    - [x] AI_OnSpawn
    - [x] AI_Respawn
    - [x] AI_OnRespawn
    - [x] AI_GetFCNPCID
    - [x] AI_OnDeath
    - [ ] AI_OnKill
- [x] **Postura**
    + [x] AI_SetPosture
    + [x] AI_GetPosture
- [x] **Movimento**
    - [x] AI_SetMoveInfo
    - [x] AI_GetMoveInfo
    - [x] **Tipo de movimento**
        + [x] AI_SetMoveType
        + [x] AI_GetMoveType
    - [x] **Velocidade**
        + [x] AI_SetMoveSpeed
        + [x] AI_GetMoveSpeed
    - [x] **MapAndreas**
        + [x] AI_ToogleUseMapAndreas
        + [x] AI_IsMapAndreasUsed
    - [x] **ColAndreas**
        + [x] AI_ToogleUseColAndreas
        + [x] AI_IsColAndreasUsed
    - [x] **Corrigir angulo**
        + [x] AI_ToogleSetAngle
        + [x] AI_IsSetAngle
    - [x] **Raio**
        + [x] AI_SetRadius
        + [x] AI_GetRadius

- [x] **Combate**
    - [x] Precisão
        + [x] AI_SetPrecision
        + [x] AI_GetPrecision
    - [x] Força
        + [x] AI_SetStrength
        + [x] AI_GetStrength

- [ ] **Alvos**
    - [ ] AI_SetTarget
    - [ ] AI_GetTarget

- [ ] **Perseguição**
    - [ ] AI_FollowPlayer
    - [ ] AI_IsFollowingPlayer
    - [ ] AI_IsFollowingAnyPlayer
    - [ ] AI_GetFollowInfo
    - [ ] AI_OnFailFollow
    - [ ] AI_OnFollowHasTrouble

- [ ] **Rotas**
    - [ ] FCNPC_LoadMovePath
    - [ ] FCNPC_SaveMovePath
    - [ ] AI_SetRoute
    - [ ] AI_GetRoute

- [ ] **Detecção**
    - [ ] AI_SetDetectionRange
    - [ ] AI_GetDetectionRange

- [ ] **Vida**
    - [ ] AI_SetHealth
    - [ ] AI_GetHealth

- [ ] **Colete**
    - [ ] AI_SetArmour
    - [ ] AI_GetArmour

- [ ] **Barulho**
    + [ ] AI_SendNoise
    + [ ] AI_OnListenNoise
    + [ ] AI_CompareNoises

> Passos para detectar sons: 
> * Método 1:
>     * Gerar som um por um(in game)
>     * Gravar de diferentes posições(1.0,10.0,20.0,30.0)
>     * Encontrar algum software que pega o nivel mais alto do som
>     * Comparar os niveis dos ruidos
>     * Então finalmente cataloga-los em um array no pawn
> * Método 2:
>     * Abrir arquivos do jogo, e pegar todos os ruidos
>     * Encontrar algum software que pega o nivel mais alto do som
>     * Comparar os niveis dos ruidos
>     * Descobrir como GTA sa calcula o som(distancia)
>     * Então finalmente cataloga-los em um array no pawn
>
