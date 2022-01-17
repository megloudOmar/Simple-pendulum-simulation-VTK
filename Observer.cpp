#include <vtkRenderWindowInteractor.h>
#include "Observer.h"

void Observer::Execute(vtkObject* caller, unsigned long eventId, void* callData)
{
    vtkRenderWindowInteractor *interactor = vtkRenderWindowInteractor::SafeDownCast(caller); // transtyper
    if(interactor->GetKeyCode() == 's') // s pressed
    {
		// set the enable attribute to 1
        this->m_o->setEnable();
    }

	if (interactor->GetKeyCode() == 'n')
	{
		// set angle attribute to 1 
		this->m_o->setAngleWithoutDamping();
	}

	if (interactor->GetKeyCode() == 'd')
	{
		// set angle attribute to 2
		this->m_o->setAngleWithDamping();
	}

}