/**
* Copyright (c) 2012, Jens Mölzer
* This file is part of the asteroids project and is realeased under the BSD 2-Clause License.
* For more Details on licensing, see 'LICENCE.txt'.
**/

#pragma once

#include <boost/any.hpp>
#include <vector>

/**
* Abstract base class for receivers.
* See MessageSystem.hpp for details on the messagesystem.
**/
class MessageReceiver {

public:
	virtual void receiveMessage(unsigned int msg, const std::vector<boost::any>& params) = 0;

};