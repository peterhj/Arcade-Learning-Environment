/* *****************************************************************************
 * The line 67 is based on Xitari's code, from Google Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 * *****************************************************************************
 * A.L.E (Arcade Learning Environment)
 * Copyright (c) 2009-2013 by Yavar Naddaf, Joel Veness, Marc G. Bellemare and 
 *   the Reinforcement Learning and Artificial Intelligence Laboratory
 * Released under the GNU General Public License; see License.txt for details. 
 *
 * Based on: Stella  --  "An Atari 2600 VCS Emulator"
 * Copyright (c) 1995-2007 by Bradford W. Mott and the Stella team
 *
 * *****************************************************************************
 */
#ifndef __PONG2_HPP__
#define __PONG2_HPP__

#include "../RomSettings.hpp"


/* RL wrapper for Pong2 */
class Pong2Settings : public RomSettings {

    public:

        Pong2Settings();

        // reset
        void reset();

        // is end of game
        bool isTerminal() const;

        // get the most recently observed reward
        reward_t getReward() const;
        reward_t getRewardB() const;

        // the rom-name
        const char* rom() const { return "pong2"; }

        // create a new instance of the rom
        RomSettings* clone() const;

        // is an action part of the minimal set?
        bool isMinimal(const Action& a) const;
        bool isMinimalB(const Action& a) const;

        // process the latest information from ALE
        void step(const System& system);

        // saves the state of the rom settings
        void saveState(Serializer & ser);
    
        // loads the state of the rom settings
        void loadState(Deserializer & ser);

        ActionVect getStartingActions();

        virtual bool isLegalB(const Action& a) const { return true; }

        virtual const int lives() { return 0; }
        virtual const int livesB() { return 0; }

    private:

        bool m_terminal;
        reward_t m_reward_l;
        reward_t m_reward_r;
        reward_t m_score_l;
        reward_t m_score_r;
};

#endif // __PONG2_HPP__

