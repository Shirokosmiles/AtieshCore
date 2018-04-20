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

#ifndef TRINITY_JUMPMOVEMENTGENERATOR_H
#define TRINITY_JUMPMOVEMENTGENERATOR_H

#include "MovementGenerator.h"

class Creature;

template<class T>
class JumpMovementGenerator : public MovementGeneratorMedium< T, JumpMovementGenerator<T> >
{
    public:
        explicit JumpMovementGenerator(uint32 id, float x, float y, float z, float o, float speedXY = 0.0f, float speedZ = 0.0f, bool hasOrientation = false, bool setorientationFixed = false) : _movementId(id), _x(x), _y(y), _z(z), _o(o), _speedXY(speedXY), _speedZ(speedZ), _hasOrientation(hasOrientation), _setorientationFixed(setorientationFixed) { }

        MovementGeneratorType GetMovementGeneratorType() const override;

        void DoInitialize(T*);
        void DoFinalize(T*);
        void DoReset(T*);
        bool DoUpdate(T*, uint32);

    private:
        void MovementInform(T*);

        uint32 _movementId;
        float _x, _y, _z, _o;
        float _speedXY;
        float _speedZ;
        bool _hasOrientation;
        bool _setorientationFixed;
};
#endif
