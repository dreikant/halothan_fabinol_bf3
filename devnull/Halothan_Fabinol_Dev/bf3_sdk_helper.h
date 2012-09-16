#include "BF3_SDK.h"

class BOSS
{
public:

fb::ClientPlayerManager* BOSS::getPlayerManager( )
{
    fb::ClientGameContext* clContext = fb::ClientGameContext::Singleton( );

    if ( VALID( clContext ) )
    {
        fb::ClientPlayerManager* playerManager = clContext->m_clientPlayerManager;

        if ( VALID( playerManager ) )
        {
            return playerManager;
        }
    }

    return NULL;
}


fb::ClientPlayer* BOSS::getPlayerById( int id )
{
    fb::ClientPlayerManager* playerManager = this->getPlayerManager( );
    if ( VALID( playerManager ) )
    {
        fb::ClientPlayer* targetPlayer = playerManager->getPlayerFromId( id );

        if ( VALID( targetPlayer ) )
            return targetPlayer;
    }        

    return NULL;
}


fb::ClientPlayer* BOSS::getLocalPlayer( )
{
    fb::ClientPlayerManager* playerManager = this->getPlayerManager( );
    if ( VALID( playerManager ) )
    {
        fb::ClientPlayer* localPlayer = playerManager->m_localPlayer;

        if ( VALID( localPlayer ) )
            return localPlayer;
    }        

    return NULL;
}


fb::ClientSoldierEntity* BOSS::getSoldier( fb::ClientPlayer* targetPlayer )
{
    if ( VALID( targetPlayer ) )
    {
        fb::ClientSoldierEntity* targetSoldier = targetPlayer->m_soldier.GetData( );

        if ( VALID( targetSoldier ) )
            return targetSoldier;
    }        

    return NULL;
}

fb::ClientSoldierEntity* BOSS::getLocalSoldier( )
{
    fb::ClientPlayer* localPlayer = getLocalPlayer( );
    if ( VALID( localPlayer ) )
    {
        fb::ClientSoldierEntity* localSoldier = getSoldier( localPlayer );
        if ( VALID( localSoldier ) )
        {
            return localSoldier;
        }
    }

    return NULL;
}
fb::BoneCollisionComponent* BOSS::getBones( fb::ClientSoldierEntity* targetSoldier )
{
    if ( VALID( targetSoldier ) )
    {
        fb::BoneCollisionComponent* bones = targetSoldier->m_boneCollisionComponent;
        if ( VALID( bones ) )
            return bones;
    }

    return NULL;
}


};