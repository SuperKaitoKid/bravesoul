#ifndef STATE_H
#define STATE_H

#include <SFML/Graphics.hpp>
#include <stdio.h>

/**
 * States manage themselves. Are their own factory, creates other states, etc.
 * Abstract class.
 */

class State {
    public:
        State();
        State(sf::Event **event);
        virtual ~State();
        State* setEvent(sf::Event **event); /// should never be using this
        virtual void pause();
        virtual void resume();
        virtual State* run() = 0; /// represents the entire use time of the state
    protected:
        sf::Event **event;
        bool toArchive; /// archive if you want to deallocate its memory
};

#endif // STATE_H
