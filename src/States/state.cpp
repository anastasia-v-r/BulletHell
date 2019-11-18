#include "state.hpp"

State::State(StateID id, std::queue<std::pair<StateChange, StateID>>& pendingChanges)
	: m_id{ id } 
	, pendingChanges{ pendingChanges } {

}