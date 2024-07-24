// Run And Gun Game. All Rights Received.


#include "RaGGameModeBase.h"
#include "Player/RaGBaseCharacter.h"
#include "Player/RaGPlayerController.h"

ARaGGameModeBase::ARaGGameModeBase() {

	DefaultPawnClass = ARaGBaseCharacter::StaticClass();
    PlayerControllerClass = ARaGPlayerController::StaticClass();

}