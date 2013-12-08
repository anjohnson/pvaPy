#include <iostream>
#include "ChannelGetRequesterImpl.h"
#include "GetFieldRequesterImpl.h"
#include "ChannelRequesterImpl.h"
#include "RequesterImpl.h"
#include "pv/clientFactory.h"
#include "pv/logger.h"

PvaClient ChannelGetRequesterImpl::pvaClient;

ChannelGetRequesterImpl::ChannelGetRequesterImpl(const epics::pvData::String& channelName_) 
    :  epics::pvAccess::ChannelGetRequester(), 
    event(),
    channelName(channelName_), 
    done(false) 
{
}
    
ChannelGetRequesterImpl::ChannelGetRequesterImpl(const ChannelGetRequesterImpl& channelGetRequester) 
    :  epics::pvAccess::ChannelGetRequester(), 
    event(),
    channelName(channelGetRequester.channelName), 
    done(false) 
{
}
    
epics::pvData::String ChannelGetRequesterImpl::getRequesterName()
{
    return "ChannelGetRequesterImpl";
}

void ChannelGetRequesterImpl::message(const epics::pvData::String& message, epics::pvData::MessageType messageType)
{
    std::cerr << "[" << getRequesterName() << "] message(" << message << ", " << getMessageTypeName(messageType) << ")" << std::endl;
}

void ChannelGetRequesterImpl::channelGetConnect(const epics::pvData::Status& status,
    const epics::pvAccess::ChannelGet::shared_pointer& channelGet,
    const epics::pvData::PVStructure::shared_pointer& pvStructure, 
    const epics::pvData::BitSet::shared_pointer& bitSet)
{
    if (status.isSuccess()) {
        // show warning
        if (!status.isOK()) {
            std::cerr << "[" << channelName << "] channel get create: " << status.getMessage() << std::endl;
        }
    
        // assign smart pointers
        {
            epics::pvData::Lock lock(pointerMutex);
            this->channelGet = channelGet;
            this->pvStructure = pvStructure;
            this->bitSet = bitSet;
        }
            
        this->channelGet->get(true);
    }
    else {
        std::cerr << "[" << channelName << "] failed to create channel get: " << status.getMessage() << std::endl;
        event.signal();
    }
}

void ChannelGetRequesterImpl::getDone(const epics::pvData::Status& status)
{
    if (status.isSuccess()) {
        // show warning
        if (!status.isOK()) {
            std::cerr << "[" << channelName << "] channel get: " << status.getMessage() << std::endl;
        }

        // access smart pointers
        {
            epics::pvData::Lock lock(pointerMutex);
            done = true;

            // this is OK since callee holds also owns it
            channelGet.reset();
        }
    }
    else {
        std::cerr << "[" << channelName << "] failed to get: " << status.getMessage() << std::endl;
        {
            epics::pvData::Lock lock(pointerMutex);
            // this is OK since caller holds also owns it
            channelGet.reset();
        }
    }
        
    event.signal();
}

epics::pvData::PVStructure::shared_pointer ChannelGetRequesterImpl::getPVStructure()
{
    epics::pvData::Lock lock(pointerMutex);
    return pvStructure;
}

bool ChannelGetRequesterImpl::waitUntilGet(double timeOut)
{
    bool signaled = event.wait(timeOut);
    if (!signaled) {
        std::cerr << "[" << channelName << "] get timeout" << std::endl;
        return false;
    }

	epics::pvData::Lock lock(pointerMutex);
	return done;
}



