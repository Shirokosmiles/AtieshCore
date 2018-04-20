/*
 * Copyright (C) 2008-2017 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "CreatureAI.h"
#include "Creature.h"
#include "Player.h"
#include "MotionMaster.h"
#include "MovementDefines.h"
#include "MoveSplineInit.h"
#include "MoveSpline.h"
#include "World.h"
#include "JumpMovementGenerator.h"

//---- JumpMovementGenerator
template<class T>
MovementGeneratorType JumpMovementGenerator<T>::GetMovementGeneratorType() const
{
    return JUMP_MOTION_TYPE;
}

template<class T>
void JumpMovementGenerator<T>::DoInitialize(T* owner)
{
    Movement::MoveSplineInit init(owner);
    init.MoveTo(_x, _y, _z, false);
    init.SetParabolic(_speedZ, 0);
    if (_setorientationFixed)
        init.SetOrientationFixed(_setorientationFixed);
    init.SetVelocity(_speedXY);
    if (_hasOrientation)
        init.SetFacing(_o);
    
    owner->SetIsJumping(true);
    init.Launch();
}

template<class T>
bool JumpMovementGenerator<T>::DoUpdate(T* owner, uint32 /*diff*/)
{
    if (!owner)
        return false;

    return !owner->movespline->Finalized();
}

template<class T>
void JumpMovementGenerator<T>::DoFinalize(T* owner)
{
    if (owner->movespline->Finalized())
        MovementInform(owner);

    owner->SetIsJumping(false);
}

template<class T>
void JumpMovementGenerator<T>::DoReset(T* owner)
{
    owner->StopMoving();
    DoInitialize(owner);
}

template<class T>
void JumpMovementGenerator<T>::MovementInform(T*) { }

template <>
void JumpMovementGenerator<Creature>::MovementInform(Creature* owner)
{
    if (owner->AI())
        owner->AI()->MovementInform(JUMP_MOTION_TYPE, _movementId);
}

template MovementGeneratorType JumpMovementGenerator<Player>::GetMovementGeneratorType() const;
template MovementGeneratorType JumpMovementGenerator<Creature>::GetMovementGeneratorType() const;
template void JumpMovementGenerator<Player>::DoInitialize(Player*);
template void JumpMovementGenerator<Creature>::DoInitialize(Creature*);
template void JumpMovementGenerator<Player>::DoFinalize(Player*);
template void JumpMovementGenerator<Creature>::DoFinalize(Creature*);
template void JumpMovementGenerator<Player>::DoReset(Player*);
template void JumpMovementGenerator<Creature>::DoReset(Creature*);
template bool JumpMovementGenerator<Player>::DoUpdate(Player*, uint32);
template bool JumpMovementGenerator<Creature>::DoUpdate(Creature*, uint32);
