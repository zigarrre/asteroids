/**
* Copyright (c) 2012, Jens Mölzer
* This file is part of the asteroids project and is realeased under the BSD 2-Clause License.
* For more Details on licensing, see 'LICENCE.txt'.
**/

#include "MessageSystem.hpp"

using namespace std;

MessageSystem& MessageSystem::getHandle() {
	static MessageSystem messageSystem;
	return messageSystem;
}

void MessageSystem::registerReceiver(MessageReceiver* receiver) {
	receivers.insert(receiver);
}

void MessageSystem::unregisterReceiver(MessageReceiver* receiver) {
	receivers.erase(receiver);
}

void MessageSystem::sendMessage(unsigned int msg, const std::vector<boost::any>& params) {
	set<MessageReceiver*>::iterator it = receivers.begin();
	for(;it != receivers.end(); ++it) {
		(*it)->receiveMessage(msg, params);
	}
}