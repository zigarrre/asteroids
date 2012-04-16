/**
* Copyright (c) 2012, Jens Mölzer
* This file is part of the asteroids project and is realeased under the BSD 2-Clause License.
* For more Details on licensing, see 'LICENCE.txt'.
**/

#pragma once

#include "MessageReceiver.hpp"
#include <set>
#include <vector>
#include <boost/any.hpp>

/**
* Messagesystem, used for comunication between different parts of the engine/game
*
* This calss is a singleton (constructor private) and the handler can be obtained with getHandle()
* If a class should receive messages, it must inherit from MessageReceiver and register itself with registerReceiver
**/
class MessageSystem {

public:
	/**
	* Obtain a reference to the singleton
	**/
	static MessageSystem& getHandle();

	/**
	* Registers a handler.
	* All handlers will receive all messages.
	**/
	void registerReceiver(MessageReceiver* receiver);

	void unregisterReceiver(MessageReceiver* receiver);

	/**
	* Sends a message to all registered receivers
	*
	* msg: the type of the message (see Messages.hpp for definition of Message Types)
	* params: the parameters needed to process the message. For details about which messages have which parameters, see Messages.hpp.
	**/
	void sendMessage(unsigned int msg, const std::vector<boost::any>& params = std::vector<boost::any>());

private:
	MessageSystem() {} // constructor private because this is a singleton

	std::set<MessageReceiver*> receivers;

};