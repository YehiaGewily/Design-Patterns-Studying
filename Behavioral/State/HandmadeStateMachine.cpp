/*
 * Design Patterns - HandmadeStateMachine
 * Author: Yehya
 * Description: Implementation of the HandmadeStateMachine pattern in C++.
 */

#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <vector>

using namespace std;

enum class State
{
    off_hook,
    connecting,
    connected,
    on_hold,
    on_hook
};

inline ostream& operator<<(ostream& os, const State& s)
{
    switch (s)
    {
    case State::off_hook:
        os << "of the hook";
        break;

    case State::connecting:
        os << "connecting";
        break;

    case State::connected:
        os << "connected";
        break;

    case State::on_hold:
        os << "on_hold";
        break;

    case State::on_hook:
        os << "on_hook";
        break;
    }
    return os;
}

enum class Trigger
{
    CallDialed,
    HungUp,
    CallConnected,
    PlacedOnHold,
    TakenOffHold,
    LeftMessage,
    StopUsingPhone
};

inline ostream& operator<<(ostream& os, const Trigger& t)
{
    switch (t)
    {
    case Trigger::CallDialed:
        os << "call dialed";
        break;
    case Trigger::HungUp:
        os << "hung up";
        break;
    case Trigger::CallConnected:
        os << "call connected";
        break;
    case Trigger::PlacedOnHold:
        os << "placed on hold";
        break;
    case Trigger::TakenOffHold:
        os << "taken off hold";
        break;
    case Trigger::LeftMessage:
        os << "left message";
        break;
    case Trigger::StopUsingPhone:
        os << "putting phone on hook";
        break;
    default: break;
    }
    return os;
}


int main()
{
    map < State, vector<pair<Trigger, State>>> rules;
    
    rules[State::off_hook] = {
        {Trigger::CallDialed, State::connecting},
        {Trigger::StopUsingPhone, State::on_hook},

    };

    rules[State::connecting] = {
        {Trigger::HungUp, State::off_hook},
        {Trigger::CallConnected, State::connected}
    };

    rules[State::connected] = {
        {Trigger::LeftMessage, State::off_hook},
        {Trigger::HungUp, State::off_hook},
        {Trigger::PlacedOnHold, State::on_hold}
    };

    rules[State::on_hold] = {
        {Trigger::TakenOffHold, State::connected},
        {Trigger::HungUp, State::off_hook}
    };

    State currentState{ State::off_hook };
    State exitState{ State::on_hook };

    while (true)
    {
        cout<<"The phone is currently "<<currentState<<"\n";
        select_trigger:
        cout << "select a trigger:\n";

        int i = 0;
        for (auto item : rules[currentState])
        {
            cout << i++ << ". " << item.first << "\n";
        }
        int input;
        cin >> input;

        if (input < 0 || (input + 1) > rules[currentState].size())
        {
            cout << "Incorrect option" << endl;
            goto select_trigger;
        }

        currentState = rules[currentState][input].second;
        if (currentState == exitState) break;
    }

    cout << "we are done using the phone\n";

    return 0;
}
