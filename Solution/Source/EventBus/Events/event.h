#pragma once

#include "object.h"

class Event : public Object
{
public:
    explicit Event(Object* sender);
    virtual ~Event();

	void    setCanceled(bool canceled);

    Object* getSender() const;
    bool    isCanceled() const;

protected:
	Object* m_sender;
	bool    m_canceled;
};